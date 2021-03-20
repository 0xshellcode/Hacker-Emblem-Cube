#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID)); // Defines how many buffers do we want (arg 1), and indicates the address of the buffer ID
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Union between the buffer and the ID
	
    /* Set size of the data, copy data of position varible to 
    the vertex buffer, and draw it staticaly (data store contents
    will be modified once and used many times) */
	
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); 
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}