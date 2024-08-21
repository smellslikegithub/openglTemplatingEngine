#include<GL/glew.h> // make sure this is the first include
#include <GLFW/glfw3.h>
#include<stdio.h>
#include "easylogging++.h"


// prototypes
void checkOpenGlWorks();
void openGlSetup();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processKeyboardInput(GLFWwindow* window);
bool initializeGlew();
bool initializeGlfw();

// Shaders
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragRedColor;\n"
"void main()\n"
"{\n"
"   //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"	FragRedColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);  // Red color\n"
"}\n\0";

INITIALIZE_EASYLOGGINGPP

struct WindowDimension {
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

	/* START: Prep a triangle */

	// Step 1: Create the vertex data


	float vertices[] = {
		0.5f, 0.5f, 0.0f, // top right
		0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f // top left
	};

	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// Step 3: Generate and bind VAO so that any subsequent calls to configure vertex attributes or bind buffers
	// are stored in this VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate the VBO and add the vertex data to the buffer
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Step 4: Define the Vertext Attribute Pointers; For simplicity, it describes how the VBO data is I.e., its size, stride etc 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Step 5: Create and Compile Shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check for compilation errors
	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Check for compilation errors
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	// Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// STEP 6 Attach previously compiled shaders to the Shader Program.
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}
	/*Every shader and rendering call after glUseProgram will now use this program object(and
	 thus the shaders).*/
	glUseProgram(shaderProgram);

	// We no longer need the shaders anymore since it is loaded into the program.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/* END: Prep a triangle */

	while (!glfwWindowShouldClose(window)) {

		// Prosses input 
		processKeyboardInput(window);

		// Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Note: glClearColor() is a state setting
		glClear(GL_COLOR_BUFFER_BIT); // Note: glClear() is a state using function. All of opengl is a state machine. glClear will use the settings stored in glClearColor when it is called


		// draw our first triangle
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glUseProgram(shaderProgram);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
