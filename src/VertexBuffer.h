#pragma once

class VertexBuffer {
private: 
	unsigned int id;

public:
	VertexBuffer();
	~VertexBuffer();

	void bufferData(float *data, int length);
	void bind();
	void unbind();
};