#pragma once

#include "Drawable.h"
#include "Program.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "VertexAttribArray.h"
#include "Mesh.h"

class NormalDrawer :
	public Drawable
{
public:
	NormalDrawer(const Mesh* mesh);
	NormalDrawer(const Mesh* mesh, glm::mat4 model);
	~NormalDrawer(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	void init(const Mesh *mesh);


	Program *p;
	VertexArrayObject *normalVAO;
	BufferObject *vertices;
	VertexAttribArray *vertAttrib;
	BufferObject *normals;
	VertexAttribArray *norAttrib;

	int vertexNum;
	glm::mat4 Model;
};

