#pragma once

#include "Drawable.h"
#include <BufferObject.h>
#include <VertexArrayObject.h>
#include <VertexAttribArray.h>
#include <Program.h>
#include <Mesh.h>
#include <Sphere.h>

class MySphere :
	public Drawable
{
public:
	MySphere(int slices, int stacks, float radius);
	~MySphere(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	VertexArrayObject sphereVAO;
	BufferObject vertexBuffer;
	BufferObject indexBuffer;
	VertexAttribArray attrib;
	Program *p;

	Mesh *sphereMesh;
};

