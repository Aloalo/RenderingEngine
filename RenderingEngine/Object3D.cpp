#include "Object3D.h"

using namespace std;
using namespace glm;

Object3D::Object3D(Mesh *mesh, const Material &mat, const mat4 &ModelMatrix)
	: mat(mat), mesh(mesh), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	normals(GL_ARRAY_BUFFER, GL_STATIC_DRAW), uv(GL_ARRAY_BUFFER, GL_STATIC_DRAW), 
	vertAttrib(0, 3, GL_FLOAT, GL_FALSE), normAttrib(1, 3, GL_FLOAT, GL_FALSE), 
	uvAttrib(2, 2, GL_FLOAT, GL_FLOAT), Model(ModelMatrix)
{
	if(mesh->getIndexDataSize() > 0)
		indices = BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}


Object3D::~Object3D(void)
{
	triangleVAO.destroy();
	vertices.destroy();
	normals.destroy();
	indices.destroy();
	uv.destroy();
	delete mesh;
}

void Object3D::setModelMatrix(const glm::mat4 &ModelMatrix)
{
	Model = ModelMatrix;
}


void Object3D::initDrawing()
{
	triangleVAO.bind();
	vertices.setData(mesh->getVertexData(), mesh->getVertexDataSize());
	vertAttrib.attribPointer();
	normals.setData(mesh->getNormalData(), mesh->getNormalDataSize());
	normAttrib.attribPointer();
	uv.setData(mesh->getUVData(), mesh->getUVDataSize());
	uvAttrib.attribPointer();

	if(mesh->getIndexDataSize() > 0)
		indices.setData(mesh->getIndexData(), mesh->getIndexDataSize());
}

void Object3D::draw(const mat4 &View, const mat4 &Projection)
{
	triangleVAO.bind();
	if(mesh->getIndexDataSize() > 0)
		glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexDataSize());
}

const Material& Object3D::getMaterial() const
{
	return mat;
}

mat4& Object3D::modelMatrix()
{
	return Model;
}