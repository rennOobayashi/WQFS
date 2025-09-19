#include "Shader.h"

Shader &Shader::use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
	unsigned int sVertex, sFragment, gShader;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	CheckCompileErrors(sVertex, "VERTEX");

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	CheckCompileErrors(sFragment, "FRAGMENT");

	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		CheckCompileErrors(gShader, "GEOMETRY");
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);

	if (geometrySource != nullptr) {
		glAttachShader(this->ID, gShader);
	}

	glLinkProgram(this->ID);
	CheckCompileErrors(this->ID, "PROGRAM");

	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr) {
		glDeleteShader(gShader);
	}
}

void Shader::SetFloat(const char* name, float value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInt(const char* name, int value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVec2(const char* name, float x, float y, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVec2(const char* name, const glm::vec2 &value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVec3(const char* name, float x, float y, float z, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVec3(const char* name, const glm::vec3& value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVec4(const char* name, float x, float y, float z, float w, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVec4(const char* name, const glm::vec4& value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const char* name, const glm::mat4 value, bool useShader) {
	if (useShader) {
		this->use();
	}
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(value));
}

void Shader::CheckCompileErrors(unsigned int object, std::string type) {
	int success;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n ------------------------------------------------------- " << std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n ------------------------------------------------------- " << std::endl;
		}
	}
}