#include<GL/glew.h> // make sure this is the first include
#include <GLFW/glfw3.h>
#include<stdio.h>


// prototypes
void checkOpenGlWorks();

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // This has to initiated after getting the opengl window context
    if (glewInit() != GLEW_OK)
        printf("%s", "Error initializing glew init");
    else
        printf("%s", "glew init success!");


    float positions[6] = {
       -0.5f, -0.5f,
       0.0f, 0.5f,
       0.5f, -0.5f
    };

    unsigned int bufferId;
    glGenBuffers(1, &bufferId);
    printf("The buffer Id: %i", bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, (6 * sizeof(float)), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void checkOpenGlWorks() {
    
    // Using legacy opengl way to draw a triangle. Warning, do not use this approach. I am using this to see if opengl works properly or not.
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}