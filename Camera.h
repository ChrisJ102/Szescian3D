#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	//glowne wektory kamery
	//pozycja kamery
	glm::vec3 Position = glm::vec3(2.5f, 2.5f, 2.0f);

	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width;
	int height;
	//konstruktor kamery
	Camera(int witdth, int height, glm::vec3 position);

	//aktualizuje i eksportuje macierz kamery do Vertex Shadera
	void Matrix(float FOVdeg, float nearPlane, float farPlane, ShaderClass& shader, const char* uniform);
	//obsluga wejscia kamery


};