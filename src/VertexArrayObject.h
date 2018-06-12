#pragma once

class VertexArrayObject {
private:
	unsigned int id;
public: 
	VertexArrayObject();
	~VertexArrayObject();

	void bind();
	void unbind();
};