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

	GLfloat vertices[] = {
		-0.5f, 1.0f,
		-1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		0.5f, -1.0f,
		1.0f, 0.0f
	};


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	const char* pathToVertextShader = "shaders\\vertexShader.vert";
	const char* pathToFragmentShader = "shaders\\fragmentShader.frag";
	
	
	const GLuint shaderProgramId = LoadShadersFromFile(pathToVertextShader, pathToFragmentShader);
	glUseProgram(shaderProgramId);


	//const char* pathToVertextShader = "C:\\Users\\Ashish Husain\\source\\repos\\openglLevel\\src\\vertexShader.vert";




	while (!glfwWindowShouldClose(window)) {

		// Prosses input 
		processKeyboardInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Note: glClearColor() is a state setting
		glClear(GL_COLOR_BUFFER_BIT); // Note: glClear() is a state using function. All of opengl is a state machine. glClear will use the settings stored in glClearColor when it is called

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
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
