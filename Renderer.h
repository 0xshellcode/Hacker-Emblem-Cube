#pragma once

#include <GL/glew.h> // Defines function pointers

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <windows.h>


#define ASSERT(x) if(!(x)) DebugBreak(); // Break if not true, it was __debugbreak(); I change it for __debugbreak();

// Tne back slash scapes the "\n"

#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public: 
    void Clear() const;
    void Draw(const VertexArray& va, const Shader& shader) const;

};

