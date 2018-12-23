#include "GLSLPogram.h"
#include "Error.h"
#include <fstream>
#include <vector>



GLSLPogram::GLSLPogram():_ProgramID(0),_vertexShaderID(0),_fragmentShaderID(0),_numAttributes(0)
{
}


GLSLPogram::~GLSLPogram()
{

}

void GLSLPogram::compileShaders(std::string vetexShaderFilePath, std::string fragmentShaderFilePath)
{
	_ProgramID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("\nVertex Shader not created !!!\n");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		perror(vetexShaderFilePath.c_str());
		fatalError("\nFragment Shader not created !!!\n");
	}
	
	compileShader(vetexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);


}

void GLSLPogram::linkShaders()
{
	

	// Attach our shaders to our program
	glAttachShader(_ProgramID, _vertexShaderID);
	glAttachShader(_ProgramID, _fragmentShaderID);

	// Link our program
	glLinkProgram(_ProgramID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_ProgramID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_ProgramID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_ProgramID);
		// Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		// Use the infoLog as you see fit.
		std::printf("%s\n", &(errorLog[0]));
		fatalError("\nShaders failed to link !!!");
	}

	// Always detach shaders after a successful link.
	glDetachShader(_ProgramID, _vertexShaderID);
	glDetachShader(_ProgramID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLPogram::addAttributes(std::string attributeName)
{
	glBindAttribLocation(_ProgramID, _numAttributes++, attributeName.c_str());
}

GLint GLSLPogram::getUniformLocation(const std::string & uniformName)
{
	GLint Location = glGetUniformLocation(_ProgramID, uniformName.c_str());
	if (Location == GL_INVALID_INDEX) {
		fatalError("\nUniform Location "+ uniformName +" can not be extracted!!!");
	}
	return Location;
}

void GLSLPogram::use()
{
	glUseProgram(_ProgramID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLPogram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}

void GLSLPogram::compileShader(std::string filePath, GLuint id)
{

	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		fatalError("\nCould not load !!!" + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		fileContents += line + "\n";
	}

	vertexFile.close();

	const char* Contentsptr = fileContents.c_str();
	glShaderSource(id, 1, &Contentsptr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &(errorLog[0]));
		fatalError("\nShader"+filePath+ " failed to compile !!!");
	}

}
