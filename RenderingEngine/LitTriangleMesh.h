#pragma once

#include "LitObject.h"
#include "OGLobjects.h"
#include "Mesh.h"

class LitTriangleMesh
	: public LitObject
{
public:
	LitTriangleMesh(Mesh *mesh, const Material *mat, const glm::mat4 &modelMatrix);
	~LitTriangleMesh(void);


	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

	const Material* getMaterial() const;
	const glm::mat4& modelMatrix() const;

private:
	Mesh *mesh;
	VertexAttribArray vertAttrib;
	VertexAttribArray normAttrib;
	VertexArrayObject triangleVAO;
	BufferObject vertices;
	BufferObject normals;
	BufferObject indices;

	const Material *mat;
	glm::mat4 Model;
};

