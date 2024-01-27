#pragma once
#include "Windows.h"
#include "glew.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Renderer
{
public:
	Renderer();
	~Renderer();

	static GLuint WindowShader;
	void Init();
	void Render();

private:
	GLuint VertexShader, FragmentShader;
	std::map<std::string, std::string> ShadersToLoad = 
	{
	{"VertexShader.hlsl", VertexShaderSource},
	{"FragmentShader.hlsl", FragmentShaderSource}
	};
	void InitVertexShader();
	void InitFragmentShader();
	void InitShader();
	void InitBuffers();
	void InitVAO();
	void InitVBO();
	void Cleanup();
	void TryLoadShaders();
	void LoadShader(const char* File, std::string &ReturnVal);

	#if _DEBUG
	void AttachDebugger(const GLuint *ShaderReference);
	#endif
	std::string VertexShaderSource = "", FragmentShaderSource = "";

	// Set up vertex data for a fullscreen quad
	GLfloat Vertices[8] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		-1.0f,  1.0f,
		 1.0f,  1.0f
	};

	//This window only
	GLuint VAO, VBO;
};
