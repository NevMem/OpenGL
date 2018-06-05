#pragma once

class VertexBuffer {
private: 
	unsigned int id;

public:
	VertexBuffer(){}
	~VertexBuffer(){}

	void init();
	void bufferData(float *data, int length);
	void bind();
	void unbind();
};