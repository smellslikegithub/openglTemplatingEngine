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

// Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

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
    mainWindow.windowTitle = (char *)"OpenGl Templating Engine";

    
    GLFWwindow *window = glfwCreateWindow(mainWindow.width, mainWindow.height, mainWindow.windowTitle, NULL, NULL); // Create a simple window
    if (window == NULL) {
        printf("%s", "Failed to create the window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    initializeGlew(); 

    glViewport(0, 0, mainWindow.width, mainWindow.height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

 


    /* START: Render a triangle */
    
    // STEP 0: Set the vertices of the triangle
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
    };

    // STEP 1: Send the vertices to the VERTEX SHADER by creating memory to hold the data in GPU
    
    // Step 1.1 Create a VBO (VERTEX BUFFER OBJECT)
    unsigned int VBO;
    glGenBuffers(1, &VBO); // Generate 1 buffer and store the unique id in VBO
    
    // Step 1.2 Bind the newly created buffer to type GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Step 1.3 From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be
    // used to configure the currently bound buffer, which is VBO.Then we can make a call to the
    // glBufferData function that copies the previously defined vertex data into the buffer’s memory :

    // glBufferData is a function specifically targeted to copy user-defined data into the currently bound buffer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Modern OpenGL requires that we at least set up a vertex and fragment shader if we want to do some rendering

    // STEP 2 Setup Vertext Shader.
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);



    // STEP 3 Setup Fragment Shader.


    /* END: Render a triangle */


    while (!glfwWindowShouldClose(window)) {
        
        // Prosses input 
        processKeyboardInput(window);
        
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Note: glClearColor() is a state setting
        glClear(GL_COLOR_BUFFER_BIT); // Note: glClear() is a state using function. All of opengl is a state machine. glClear will use the settings stored in glClearColor when it is called


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
        LOG(INFO) << "Key Pressed: "<< GLFW_KEY_ESCAPE<<"\n";
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
