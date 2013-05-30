#pragma once

#include "LitObject.h"
#include "Program.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "VertexAttribArray.h"
#include <vector>
#include <Mesh.h>

class MeshTester :
	public LitObject
{
public:
	MeshTester(void);
	~MeshTester(void);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

	glm::vec4 diffuseColor();
	glm::vec4 specularColor();
	glm::vec4 ambientColor();
	float shininessFactor();
	glm::mat4 modelMatrix();

private:
	Mesh *mesh;
	VertexAttribArray vertAttrib;
	VertexAttribArray normAttrib;
	VertexArrayObject triangleVAO;
	BufferObject vertices;
	BufferObject normals;
	BufferObject indices;

	glm::mat4 Model;
};