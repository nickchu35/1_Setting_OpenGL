#pragma once
 
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include <iostream>
 
namespace Core
{
	class Shader_Loader
	{
		private:
        std::string ReadShader(char *filename);
        GLuint CreateShader(GLenum shaderType, std::string source, char* shaderName);
		// GLuint variables will hold the shader and program handles (basically empty 
		// objects to hold these entities) which will be used for integration.
		// CreateShader creates and compiles a shader (vertex or fragment).
 
        public:
        Shader_Loader(void);
        ~Shader_Loader(void);
        GLuint CreateProgram(char* VertexShaderFilename, char* FragmentShaderFilename);
		// CreateProgram method uses ReadShader to extract the shader contents and 
		// to create both shaders and load them into the program which is returned to be used in rendering loop.

	};
}