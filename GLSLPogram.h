#pragma once

#include<string>
#include<glew.h>

class GLSLPogram
{
public:
	GLSLPogram();
	~GLSLPogram();
	void compileShaders(std::string vetexShaderFilePath, std::string fragmentShaderFilePath);
	void linkShaders();
	void addAttributes(std::string attributeName);
	GLint getUniformLocation(const std::string& uniformName);
	void use();
	void unuse();
private:
	void compileShader(std::string filePath,GLuint id);
	GLuint _ProgramID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	int _numAttributes;

};