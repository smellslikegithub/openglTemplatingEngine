#include<GL/glew.h> // make sure this is the first include
#include <GLFW/glfw3.h>
#include<stdio.h>
#include "easylogging++.h" // Not using this for now. Relying on std::cout
#include"../common/shader.hpp"

INITIALIZE_EASYLOGGINGPP

// prototypes
void checkOpenGlWorks();
void openGlSetup();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processKeyboardInput(GLFWwindow* window);
bool initializeGlew();
bool initializeGlfw();
void wireframeModeOn(); // For debugging/inspecting triangle wireframe
void wireframeModeOff();// For turning off debugging/inspecting triangle wireframe. Explicitly OFF.




struct WindowAttrib {
	int width;
	int height;
	char* windowTitle;
} mainWindow;

int main(void)
{


	initializeGlfw();
	openGlSetup(); // Preliminary setup

	mainWindow.width = 800;
	mainWindow.height = 600;
	mainWindow.windowTitle = (char*)"OpenGl Templating Engine";
	


	GLFWwindow* window = glfwCreateWindow(mainWindow.width, mainWindow.height, mainWindow.windowTitle, NULL, NULL); // Create a simple window
	if (window == NULL) {
		printf("%s", "Failed to create the window");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	initializeGlew();

	glViewport(0, 0, mainWindow.width, mainWindow.height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	


	// Exercise 1: Draw Two Triangles

	wireframeModeOff();

	GLfloat vertices[] = {
		-0.5f, -1.0f, //0
		-1.0f, 0.0f, //	1
		0.0f, 0.0f, //	2

		0.5f, -1.0f,//	3
		1.0f, 0.0f //	4
	};



	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int vertexBufferObject; // VBO
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	glEnableVertexAttribArray(0);
	// The first param that is zero in this code kind of tells opengl that the vertex shader data for the vertex data we provide can be found in the 0th index. 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	GLushort indices[] = {1,2,0,  2,3,4}; //W


	GLuint indexBufferId;
	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	
	// typedef void (GLAPIENTRY * PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	const char* pathToVertextShader = "shaders\\vertexShader.vert";
	const char* pathToFragmentShader = "shaders\\fragmentShader.frag";
	
	
	const GLuint shaderProgramId = LoadShadersFromFile(pathToVertextShader, pathToFragmentShader);
	glUseProgram(shaderProgramId);


	


	while (!glfwWindowShouldClose(window)) {

		// Prosses input 
		processKeyboardInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Note: glClearColor() is a state setting
		glClear(GL_COLOR_BUFFER_BIT); // Note: glClear() is a state using function. All of opengl is a state machine. glClear will use the settings stored in glClearColor when it is called

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	printf("Worked till here\n");

	glfwTerminate();

	return 0;

}

void processKeyboardInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		LOG(INFO) << "Key Pressed: " << GLFW_KEY_ESCAPE << "\n";
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	printf("Called the framebuffer_size_callback() function with WIDTH:%i and HEIGH: %i\n", width, height);
	glViewport(0, 0, width, height);
}

void openGlSetup() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

bool initializeGlew() {
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		LOG(ERROR) << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return false;
	}
	LOG(INFO) << "Successfully Initialized Glew" << std::endl;
	return true;
}

bool initializeGlfw() {

	const char* description;
	int glfwInitStatus = glfwInit();
	int errorCode = glfwGetError(&description);
	if (glfwInitStatus != GLFW_TRUE) {

		LOG(ERROR) << "GLFW Error (" << errorCode << "): " << description << std::endl;
		return false;
	}

	LOG(INFO) << "Successfully Initialized Glfw" << std::endl;
	return true;
}
void checkOpenGlWorks() {

	// Using legacy opengl way to draw a triangle. Warning, do not use this approach. I am using this to see if opengl works properly or not.
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glColor3f(2.0f, 3.3f, 77.2f);
	glEnd();
}

void wireframeModeOn() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void wireframeModeOff() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}