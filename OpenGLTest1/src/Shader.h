#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>



//Structure for fetching shaders from a single shader file
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;

};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RenderedID;
	std::unordered_map<std::string, int> m_UnifromLocationCache;
	//chaching for uniforms

public:

	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	//Set Unifroms , as needed we add more here 
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);

private: 
	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);
};