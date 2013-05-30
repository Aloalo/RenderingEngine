#pragma once

#include "LitObject.h"
#include <BufferObject.h>
#include <VertexArrayObject.h>
#include <VertexAttribArray.h>
#include <Program.h>
#include <Mesh.h>
#include <Sphere.h>

class MySphere :
	public LitObject
{
public:
	MySphere(int slices, int stacks, float radius);
	~MySphere(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

	glm::vec4 diffuseColor();
	glm::vec4 specularColor();
	glm::vec4 ambientColor();
	float shininessFactor();
	glm::mat4 modelMatrix();

private:
	VertexArrayObject sphereVAO;
	BufferObject vertexBuffer;
	BufferObject normalBuffer;
	BufferObject indexBuffer;
	VertexAttribArray vertAttrib;
	VertexAttribArray normAttrib;

	Mesh *sphereMesh;
};

