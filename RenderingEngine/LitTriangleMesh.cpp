#include "LitTriangleMesh.h"


LitTriangleMesh::LitTriangleMesh(Mesh *mesh, const Material &mat, const glm::mat4 &modelMatrix)
	: mesh(mesh), mat(mat), Model(modelMatrix), triangleVAO(), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	normals(GL_ARRAY_BUFFER, GL_STATIC_DRAW), vertAttrib(0, 3, GL_FLOAT, GL_FALSE),
	normAttrib(1, 3, GL_FLOAT, GL_FALSE)
{
	if(mesh->getIndexDataSize() > 0)
		indices = BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}


LitTriangleMesh::~LitTriangleMesh(void)
{
	triangleVAO.destroy();
	vertices.destroy();
	normals.destroy();
	indices.destroy();
}

void LitTriangleMesh::initDrawing()
{
	triangleVAO.bind();
	vertices.setData(mesh->getVertexData(), mesh->getVertexDataSize());
	vertAttrib.attribPointer();
	normals.setData(mesh->getNormalData(), mesh->getNormalDataSize());
	normAttrib.attribPointer();

	if(mesh->getIndexDataSize() > 0)
		indices.setData(mesh->getIndexData(), mesh->getIndexDataSize());
}

void LitTriangleMesh::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	triangleVAO.bind();
	if(mesh->getIndexDataSize() > 0)
		glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexDataSize());
}

const Material& LitTriangleMesh::getMaterial() const
{
	return mat;
}

const glm::mat4& LitTriangleMesh::modelMatrix() const
{
	return Model;
}
