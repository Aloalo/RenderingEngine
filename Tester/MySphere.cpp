#include "MySphere.h"
#include <Engine.h>
#include <NormalDrawer.h>

MySphere::MySphere(int slices, int stacks, float radius)
	: sphereVAO(), vertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	normalBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW), normAttrib(1, 3, GL_FLOAT, GL_FALSE),
	vertAttrib(0, 3, GL_FLOAT, GL_FALSE), indexBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
{
	Sphere *sphere = new Sphere(1.0f, glm::vec3(0.0f));
	sphereMesh = new Mesh(sphere->generate(4));
	delete sphere;


	sphereMesh->setOrientation(GL_CCW);
	sphereMesh->calculateNormals();
	sphereMesh->interpolateNormals();
	sphereMesh->applyIndexing();

	//Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(sphereMesh)));
}

MySphere::~MySphere(void)
{
	vertexBuffer.destroy();
	indexBuffer.destroy();
	sphereVAO.destroy();
	delete sphereMesh;
}

void MySphere::initDrawing()
{
	sphereVAO.bind();
	vertexBuffer.setData(sphereMesh->getVertexData(), sphereMesh->getVertexDataSize());
	vertAttrib.attribPointer();
	normalBuffer.setData(sphereMesh->getNormalData(), sphereMesh->getNormalDataSize());
	normAttrib.attribPointer();
	indexBuffer.setData(sphereMesh->getIndexData(), sphereMesh->getIndexDataSize());
}

void MySphere::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	sphereVAO.bind();
	glDrawElements(GL_TRIANGLES, sphereMesh->numOfIndices(), sphereMesh->getIndexDataType(), 0);
}

glm::vec4 MySphere::diffuseColor()
{
	return glm::vec4(0.2f, 0.1f, 1.0f, 1.0f);
}

glm::vec4 MySphere::specularColor()
{
	return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

glm::vec4 MySphere::ambientColor()
{
	return glm::vec4(0.2f, 0.1f, 1.0f, 1.0f);
}

float MySphere::shininessFactor()
{
	return 64.0f;
}

glm::mat4 MySphere::modelMatrix()
{
	return glm::mat4(1.0f);
}
