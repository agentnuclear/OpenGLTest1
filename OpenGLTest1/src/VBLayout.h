#pragma once

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"


struct VertexBufferElement
{
	unsigned int count;
	unsigned int type;
	unsigned char normalise;

	VertexBufferElement(unsigned int t, unsigned int c, unsigned char n) :
		type(t), count(c), normalise(n)
	{

	}

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VBLayout
{
private:

	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VBLayout();
	~VBLayout();

	template<typename T>
	void Push(unsigned int cout)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement({ GL_FLOAT , count, GL_FALSE }));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement({ GL_UNSIGNED_INT , count, GL_FALSE }));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) ;

	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back(VertexBufferElement({ GL_UNSIGNED_BYTE , count, GL_TRUE }));
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);

	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};