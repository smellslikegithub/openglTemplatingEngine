# 🌟 My Journey into Learning OpenGL 🚀

I'm embarking on an adventure to learn OpenGL using C++. This journal documents my progress, challenges, and resources I've found helpful along the way.

## 📚 Journal

### Day 1: Setting Up the Basics 🛠️
Today, I learned how to set up the necessary dependencies for OpenGL. Specifically, I focused on configuring **GLEW** and **GLFW**.

**References:**
- [OpenGL Documentation](https://docs.gl/)
- [LearnOpenGL - Getting Started](https://learnopengl.com/Getting-started/OpenGL)

---

### Day 2: Diving into the Learning 📖
🗓️ *Date: 2024-08-16*

Started reading the **LearnOpenGL.com** guide. I’m using the PDF version as my primary resource.

**Chapter:**
- Part 1: Getting Started
    - Introduction to OpenGL
        - Made a blank window that is re-sizeable
- Additional Implementations
    - Refactored some old implementations
 
### Day 3: Diving into the Learning 📖
🗓️ *Date: 2024-08-16*

Started reading the **LearnOpenGL.com** guide. I’m using the PDF version as my primary resource.

**Chapter:**
- Part 1: Getting Started
    - Introduction to OpenGL (Contd..)
        - Learning about the stages of the graphics pipeline. Each stage passes its output to the next stage.
            - Vertex Shader
                - Takes input a single vertex to tranform 3D coordinartes into different 3D coordinates. 
            - Shape Assembly
                - Assebles the vertex into shape given a primitive. Say for example GL_POINTS or GL_TRIANGLES     
            - Geometry shader
                - Takes as input a collection of vertices and grants the ability to generate other specified shape.     
            - Rasterization
                - This step maps the resulting primitive to the corresponding pixels resulting in fragments
                  for the fragment shader to use. Before the fragment shader is run, clipping is done to clip
                  out fragments not within the view.
            - Fragment Shader
                - All the advanced opengl stuff happens here. Here, the calculation of the final color of the 
                  pixel happens. Usually the fragment shader contains data about the 3D scene that it can use 
                  to calculate the final pixel color (like lights, shadows, color of the light and so on).
            - Tests an Blending
                - TBA    

        - In modern opengl we are required to define the **vertex** and **fragment shader** of our own.
- Additional Implementations
    - Added logging library statically
    - Fixed a bug where glew was not initialized

### Day 4: Diving into the Learning 📖
🗓️ *Date: 2024-8-18*

Started reading the **LearnOpenGL.com** guide. I’m using the PDF version as my primary resource.

**Chapter:**
- Part 1: Getting Started
    - Drawing Traingle best practices:
        - Use VAOs: Encapsulate vertex attribute configuration within VAOs to simplify the management of vertex data.
        - Bind VAOs Early: Bind VAOs before configuring VBOs and vertex attributes to ensure that all configurations are stored within the VAO.
        - Encapsulate Shaders: Compile and link shaders into a shader program, checking for errors at every step.
        - Efficient Drawing: Use glDrawArrays or glDrawElements depending on whether you're drawing with sequential or indexed vertices.
        - Clean Up: Unbind VAOs and VBOs after setup to avoid unintended modifications.

### Day 5: Diving into the Learning 📖
🗓️ *Date: 2024-8-21*

Started reading the **LearnOpenGL.com** guide. I’m using the PDF version as my primary resource.

**Chapter: 5.6**
- Part 1: Getting Started
    - Draw a rectangle using two triangles. Prooving that rects are created via traingles.
        - Element Buffer Objects    
    - Exercises
        - Started the drawing triangle again

- ### Day 6: Refactored some impl 📖
🗓️ *Date: 2024-8-24*

**Chapter: 5.6 - 5.8**
- Refactored code.
    - Seperated vertex shader and fragament shader code
    - created utilities to read shader from disk to ram
- Exercise:
    - Draw two triangles. Done 


---

Stay tuned as I continue to explore and learn more about OpenGL! 💻✨