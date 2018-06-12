#pragma once

class IndexBuffer {
private: 
	unsigned int id;

public:
	IndexBuffer();
	~IndexBuffer();

	void bufferData(unsigned int *data, int length);
	void bind();
	void unbind();
};