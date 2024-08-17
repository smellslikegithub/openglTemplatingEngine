#include<GL/glew.h> // make sure this is the first include
#include <GLFW/glfw3.h>
#include<stdio.h>
#include "easylogging++.h"


// prototypes
void checkOpenGlWorks();
void openGlSetup();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processKeyboardInput(GLFWwindow* window);

INITIALIZE_EASYLOGGINGPP

struct WindowDimension {
    int width;
    int height;
    char* windowTitle;
} mainWindow;

int main(void)
{   
    int glfwInitStatus = glfwInit();
    if (glfwInitStatus != GLFW_TRUE) {
        
        LOG(ERROR) << "Initialization of the glfwinit failed";
        return -1;
    }

    openGlSetup(); // Preliminary setup

    mainWindow.width = 800;
    mainWindow.height = 600;
    mainWindow.windowTitle = (char *)"My First Window";

    
    GLFWwindow *window = glfwCreateWindow(mainWindow.width, mainWindow.height, mainWindow.windowTitle, NULL, NULL); // Create a simple window
    if (window == NULL) {
        printf("%s", "Failed to create the window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, mainWindow.width, mainWindow.height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window)) {
        
        processKeyboardInput(window);
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
void checkOpenGlWorks() {
    
    // Using legacy opengl way to draw a triangle. Warning, do not use this approach. I am using this to see if opengl works properly or not.
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glColor3f(2.0f, 3.3f, 77.2f);
    glEnd();
}