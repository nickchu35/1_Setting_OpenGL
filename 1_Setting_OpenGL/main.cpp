#include <iostream>
#include <stdio.h>;
#include <stdlib.h>;
#include <fstream>;
#include <vector>;

#include "Core\Shader_Loader.h"
#include "Core\GameModels.h"

using namespace Core;

Models::GameModels* gameModels;
GLuint program;
GLuint vertex_shader, fragment_shader;
GLuint vertex_array_object;

void renderScene(void)
{
	// tells OpenGL to clear its buffers. In our case Depth and Color. To clear them simultaneously we OR them
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// specify clear values for color buffers. These values must be between 0.0 and 1.0. Arguments are : red, green, blue, alpha.
    glClearColor(0.0, 0.3, 0.3, 1.0);
	// swaps between back buffer and front buffer. Remember that we are using double buffering.

	glBindVertexArray(gameModels->GetModel("triangle1"));
	//use the created program
	glUseProgram(program);
	// The program in question is a container for the shaders we are going to use in drawing the scene. 
	// You can switch programs between objects drawn, if you want o use different shaders for different objects.

	// draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// the first argument is the drawing mode or the primitive(points, lines, triangles, triangle strip, etc.),
	// the third is the array of vertices in question and the second is the index from which the vertices will 
	// be drawn inside argument 3.

    glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
    glutLeaveMainLoop();
}

void Init(){
	glEnable(GL_DEPTH_TEST);
 
	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");

    //load and compile shaders
	Core::Shader_Loader shaderLoader;// = Core::Shader_Loader::Shader_Loader();
    program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
                                         "Shaders\\Fragment_Shader.glsl");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);										// initialize GLUT library
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  // determine the OpenGL display mode for the new window
	// GLUT_DEPTH tells OpenGL that we want a depth buffer (also called a Z buffer) 
	// GLUT_DOUBLE tells OpenGL that we want a double buffer (back buffer and front buffer) to have a smooth animation 
	// and to prevent flickering
	// GLUT_RGBA tells OpenGL how to allocate a 32-bit Framebuffer for the four 8-bit color channels: Red, Green, Blue, and Alpha.
	glutInitWindowPosition(300, 100);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("Drawing my first triangle!");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();
	if (glewIsSupported("GL_VERSION_3_1"))
	{
		std::cout << "GLEW Version is 3.1\n ";
	}
	else
	{
		std::cout << "GLEW 3.1 not supported\n ";
	}

	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);
	glutMainLoop();	// enters the GLUT processing loop, interupted only by callbacks.

	delete gameModels;
	glDeleteProgram(program);
	return 0;
}