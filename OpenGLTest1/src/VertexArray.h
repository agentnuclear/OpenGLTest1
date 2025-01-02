#pragma once

#include "VertexBuffer.h"


class VBLayout;

class VertexArray
{
private:

	unsigned int m_RendererID;

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VBLayout& layout);

	void Bind() const;
	void UnBind() const;
};