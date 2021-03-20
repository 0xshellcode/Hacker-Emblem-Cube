#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; // This is used in order to keep track of the object that we are using, internal RenderID
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count); // Constructor
	~IndexBuffer(); // Destructor

	void Bind() const;
	void Unbind() const;
	
	inline unsigned int GetCount() const { return m_Count; }
};