#pragma once

#include "UnLitObject.h"
#include "OGLobjects.h"
#include "Mesh.h"

class NormalDrawer :
	public UnLitObject
{
public:
	NormalDrawer(const Mesh &mesh);
	NormalDrawer(const Mesh &mesh, const glm::mat4 &model);
	~NormalDrawer(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	Program p;
	VertexArrayObject normalVAO;
	BufferObject vertices;
	VertexAttribArray vertAttrib;
	BufferObject normals;
	VertexAttribArray norAttrib;

	int vertexNum;
	glm::mat4 Model;
};

