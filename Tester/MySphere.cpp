#include "MySphere.h"
#include <Engine.h>
#include <NormalDrawer.h>

MySphere::MySphere(int slices, int stacks, float radius)
{
	p = new Program("../RenderingEngine/StockShaders/Simple");

	sphereVAO = new VertexArrayObject();
	vertexBuffer = new BufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	indexBuffer = new BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
	attrib = new VertexAttribArray(0, 3, GL_FLOAT, GL_FALSE);

	Sphere *sphere = new Sphere(1.0f, glm::vec3(0.0f));
	sphereMesh = new Mesh(sphere->generate(4));
	delete sphere;

	sphereMesh->calculateNormals();
	sphereMesh->interpolateNormals();
	sphereMesh->applyIndexing();

	Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(sphereMesh)));
}

MySphere::~MySphere(void)
{
	delete vertexBuffer;
	delete indexBuffer;
	delete sphereVAO;
	delete sphereMesh;
}

void MySphere::initDrawing()
{
	sphereVAO->bind();
	vertexBuffer->bind();
	vertexBuffer->setData(sphereMesh->getVertexData(), sphereMesh->getVertexDataSize());
	attrib->enable();
	attrib->attribPointer();
	indexBuffer->bind();
	indexBuffer->setData(sphereMesh->getIndexData(), sphereMesh->getIndexDataSize());
}

void MySphere::draw(const glm::mat4 &ViewProjection)
{
	p->use();
	p->setUniform("MVPmatrix", 1, &ViewProjection);
	sphereVAO->bind();
	glDrawElements(GL_TRIANGLES, sphereMesh->numOfIndices(), sphereMesh->getIndexDataType(), 0);
}
