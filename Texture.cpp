#include "Texture.h"


Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	type = texType;

	int widthImg, heightImg, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);

	glActiveTexture(slot);

	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLint mipMapLev = 0;
	GLint border = 0;

	glTexImage2D(texType, mipMapLev, GL_RGBA, widthImg, heightImg, border, format, pixelType, bytes);

	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(texType, 0);
}

void Texture::texUnit(ShaderClass& shaderProgram, const char* uniform, GLuint unit) {

	GLuint texUni = glGetUniformLocation(shaderProgram.ID, uniform);

	shaderProgram.Activate();

	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}
void Texture::Unbind() {
	glBindTexture(type, 0);
}
void Texture::Delete() {
	glDeleteTextures(1, &ID);
}