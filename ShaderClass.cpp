#include "ShaderClass.h"


std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());

		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());

		in.close();
		return(contents);
	}
	throw(errno);
}

ShaderClass::ShaderClass(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Utwórz obiekt Vertex Shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Po³¹cz istniej¹cy obiekt z napisan¹ wczeœniej implementacj¹ shadera
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Skompiluj gotowy kod
	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX", vertexCode);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, "FRAGMENT", fragmentCode);

	// Utwórz program
	ID = glCreateProgram();
	// Pod³¹cz shadery pod program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	compileErrors(ID, "PROGRAM", vertexCode + "\n" + fragmentCode);
	// Usuñ niepotrzebne shadery
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void ShaderClass::Activate() {
	glUseProgram(ID);
}
void ShaderClass::Delete() {
	glDeleteProgram(ID);
}
void ShaderClass::compileErrors(unsigned int shader, const char* type, std::string shaderCode) {
	GLint hasCompiled;

	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE)glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		std::cout << type << "SHADER -----> STATUS KOMPILACJI: ";
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		std::cout << type << "SHADER -----> STATUS LINKOWANIA: ";
	}

	if (hasCompiled == GL_TRUE) {
		std::cout << "OK" << std::endl;
	}
	else {
		std::cout << "BAD" << std::endl;
		std::cout << shaderCode << std::endl;
		std::cout << infoLog << std::endl;
	}
}