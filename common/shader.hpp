#ifndef SHADER_HPP
#define SHADER_HPP
typedef unsigned int GLuint; // Just so that I don't see a red squiggly in the editor.

GLuint LoadShadersFromFile(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
GLuint LoadShaders(const char* vertexShaderCode, const char* fragmentShaderCode);

#endif // !SHADER_HPP
