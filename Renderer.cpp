#include "Renderer.h"

#include <iostream>

void GLClearError(){
    while (glGetError() != GL_NO_ERROR); // Clear all the errors until there are 0
}

bool GLLogCall(const char* function, const char* file, int line){
    while (GLenum error = glGetError()){ // Printing all the errors
    
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader) const {
    shader.Bind();   
    va.Bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 36)); // Draw call for our cube
}

