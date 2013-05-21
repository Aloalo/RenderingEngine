#pragma once

#include "Drawable.h"
#include "Program.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "VertexAttribArray.h"
#include <vector>
#include <Mesh.h>

class MeshTester :
	public Drawable
{
public:
	MeshTester(void);
	~MeshTester(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	Mesh *mesh;
	Program *p;
	VertexAttribArray attrib;
	VertexArrayObject triangleVAO;
	BufferObject vertices;
	BufferObject indices;

	glm::mat4 Model;
};