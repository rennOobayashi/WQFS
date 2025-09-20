#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>


class Shader
{
private:
	void CheckCompileErrors(unsigned int object, std::string type);
public:
	unsigned int ID;

	Shader() { }
	Shader& use();

	void Compile(const char *vertex_source, const char *fragment_source, const char *geometry_source = nullptr);

	void SetFloat(const char *name, float value, bool useShader = false);
	void SetInt(const char* name, int value, bool useShader = false);
	void SetVec2(const char* name, float x, float y, bool useShader = false);
	void SetVec2(const char* name, const glm::vec2 &value, bool useShader = false);
	void SetVec3(const char* name, float x, float y, float z, bool useShader = false);
	void SetVec3(const char* name, const glm::vec3& value, bool useShader = false);
	void SetVec4(const char* name, float x, float y, float z, float w, bool useShader = false);
	void SetVec4(const char* name, const glm::vec4& value, bool useShader = false);
	void SetMat4(const char* name, const glm::mat4 value, bool useShader = false);
};

#endif