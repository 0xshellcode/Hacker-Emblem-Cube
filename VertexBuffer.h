#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID; // This is used in order to keep track of the object that we are using, internal RenderID
public:
	VertexBuffer(const void* data, unsigned int size); // Contructor
	~VertexBuffer(); // Destructor

	void Bind() const;
	void Unbind() const;
};