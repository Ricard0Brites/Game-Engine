#pragma once
#include "Windows.h"
#include "glew.h"
#include <string>
#include <vector>
#include <map>


class Renderer
{
	Renderer();
	~Renderer();

	void Init();

public:
	 GLuint WindowShader = 0;

private:
	GLuint VertexShader, FragmentShader;
	std::map<std::string, const char*> ShadersToLoad = 
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
	void Render();
	void Cleanup();
	void TryLoadShaders();
	void LoadShader(const char* File, const char *ReturnVal);

	#if _DEBUG
	void AttachDebugger(const GLuint *ShaderReference);
	#endif
	const char *VertexShaderSource, *FragmentShaderSource;

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

