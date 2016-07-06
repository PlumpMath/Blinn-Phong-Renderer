#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


GLuint loadAndCompileShader(GLenum shaderType, const std::string& path)
{
	std::ifstream f;
	f.open(path.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		throw std::runtime_error(std::string("Can't open shader file ") + path);
	}
	std::stringstream buffer;
	buffer << f.rdbuf();

	GLuint shader = glCreateShader(shaderType);
	if (!shader)
	{
		throw std::runtime_error(std::string("Can't create shader for file ") + path);
	}

	const std::string& bufferAsString = buffer.str();
	const GLchar* shaderCode = bufferAsString.c_str();
	const GLchar* codeArray[] = { shaderCode };
	GLint size = strlen(shaderCode);
	glShaderSource(shader, 1, codeArray, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		std::cerr << "Compilation error in shader file " << path << std::endl;
		GLint logLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char *log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(shader, logLen, &written, log);
			std::cerr << "Shader log: " << std::endl;
			std::cerr << log << std::endl;
			delete[] log;
		}
		throw std::runtime_error(
			std::string("Can't compile the shader defined in file ") + path);
	}
	return shader;
}

GLuint createVertexFragmentProgram(const std::string& vertex_shader_path, const std::string& fragment_shader_path)
{

	GLuint vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertex_shader_path);
	GLuint fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragment_shader_path);

	GLuint program = glCreateProgram();
	if (!program) {
		throw std::runtime_error("Can't create GLSL program.");
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		std::cerr << "Linking error in shader program!" << std::endl;
		GLint logLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			char *log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(program, logLen, &written, log);
			std::cerr << "Shader log: " << std::endl;
			std::cerr << log << std::endl;
			delete[] log;
		}
		throw std::runtime_error("Can't link shader program.");
	}
	return program;
}

class Shader
{
public:
	Shader() {}
	Shader(const std::string &_p, const GLenum _t)
		: path(_p), type(_t)
	{ 
		id = loadAndCompileShader(type, path);
	}
	~Shader() 
	{ 
		if (id != 0)
		{
			glDeleteShader(id); 
			id = 0;
		}
	}
	bool reload()
	{
		glDeleteShader(id);
		id = loadAndCompileShader(type, path);
		if (id) return true;
		else return false;
	}
	GLenum getType() { return type; }
	GLuint getID() { return id; }
private:
	std::string path;
	GLenum type;
	GLuint id = 0;
};

class ShaderProgram
{
public:
	ShaderProgram() {}
	ShaderProgram(const Shader &_frag, const Shader &_vert)
		:frag(_frag), vert(_vert)
	{
		id = glCreateProgram();
		if (!id) {
			throw std::runtime_error("Can't create GLSL program.");
		}
		glAttachShader(id, vert.getID());
		glAttachShader(id, frag.getID());
		glLinkProgram(id);
		programStatus();
	}
	ShaderProgram(const std::string &_frag, const std::string &_vert)
	{
		frag = Shader(_frag, GL_FRAGMENT_SHADER);
		vert = Shader(_vert, GL_VERTEX_SHADER);
		id = glCreateProgram();
		if (!id) {
			throw std::runtime_error("Can't create GLSL program.");
		}
		glAttachShader(id, vert.getID());
		glAttachShader(id, frag.getID());
		glLinkProgram(id);
		programStatus();
	}
	~ShaderProgram()
	{ 
		glDeleteProgram(id); id = 0; 
	}

	void programStatus()
	{
		GLint status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (!status) {
			std::cerr << "Linking error in shader program!" << std::endl;
			GLint logLen;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0) {
				char *log = new char[logLen];
				GLsizei written;
				glGetProgramInfoLog(id, logLen, &written, log);
				std::cerr << "Shader log: " << std::endl;
				std::cerr << log << std::endl;
				delete[] log;
			}
			throw std::runtime_error("Can't link shader program.");
		}
	}
	GLuint getID() { return id; }
private:
	GLuint id = 0;
	Shader frag;
	Shader vert;
};