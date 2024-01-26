#include "Renderer.h"
#include <iostream>
#include <fstream>
#include "Logger\Logger.h"

using namespace std;

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Init()
{
	// Initialize GLEW
	glewInit();
	TryLoadShaders();
	InitVertexShader();
	InitFragmentShader();
	InitShader();
	InitBuffers();
}

void Renderer::InitVertexShader()
{
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSource, nullptr);
	glCompileShader(VertexShader);
	#pragma region Debug
#if _DEBUG
	AttachDebugger(&VertexShader);
#endif  
#pragma endregion
}

void Renderer::InitFragmentShader()
{
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, nullptr);
	glCompileShader(FragmentShader);
	#pragma region Debug
#if _DEBUG
	AttachDebugger(&FragmentShader);
#endif  
#pragma endregion

}

void Renderer::InitShader()
{
	WindowShader = glCreateProgram();
	glAttachShader(WindowShader, VertexShader);
	glAttachShader(WindowShader, FragmentShader);
	glLinkProgram(WindowShader);
	glUseProgram(WindowShader);
}

void Renderer::InitBuffers()
{
	//Do not change the order
	InitVBO();
	InitVAO();
}

void Renderer::InitVAO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::InitVBO()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	//Send Vertices to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Bind VAO and draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Renderer::Cleanup()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(WindowShader);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

void Renderer::TryLoadShaders()
{
	for (std::pair<std::string, const char*> ShaderPair : ShadersToLoad)
	{
		LoadShader(ShaderPair.first.c_str(), ShaderPair.second);
		if(!ShaderPair.second)
			LOG("Attempt to load Shader Failed" __FILE__,3);
	}
}

#if _DEBUG
void Renderer::AttachDebugger(const GLuint* ShaderReference)
{
	GLint isCompiled = 0;
	glGetShaderiv(*ShaderReference, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(*ShaderReference, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(*ShaderReference, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(*ShaderReference);

		string debugMsg = "Shader Log:\n";
		for (GLchar Character : infoLog)
		{
			debugMsg += Character;
		}
		cout << debugMsg << endl;
	}
}
#endif

void Renderer::LoadShader(const char* File, const char *ReturnVal)
{
	ifstream file(File);
	if (!file)
		return;

	string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	ReturnVal = shaderCode.c_str();
}