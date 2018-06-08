#pragma once

class VertexArrayObject {
private:
	unsigned int id;
public: 
	VertexArrayObject(){}
	~VertexArrayObject(){}

	void init();
	void bind();
	void unbind();
};