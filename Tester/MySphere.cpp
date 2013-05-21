#include "MySphere.h"
#include <Engine.h>
#include <NormalDrawer.h>

MySphere::MySphere(int slices, int stacks, float radius)
	:p(new Program("../RenderingEngine/StockShaders/Simple")),
	sphereVAO(), vertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	attrib(0, 3, GL_FLOAT, GL_FALSE), indexBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
{
	p = new Program("../RenderingEngine/StockShaders/Simple");

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
	vertexBuffer.destroy();
	indexBuffer.destroy();
	sphereVAO.destroy();
	delete sphereMesh;
}

void MySphere::initDrawing()
{
	sphereVAO.bind();
	vertexBuffer.bind();
	vertexBuffer.setData(sphereMesh->getVertexData(), sphereMesh->getVertexDataSize());
	attrib.enable();
	attrib.attribPointer();
	indexBuffer.bind();
	indexBuffer.setData(sphereMesh->getIndexData(), sphereMesh->getIndexDataSize());
}

void MySphere::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	p->use();
	p->setUniform("MVPmatrix", 1, &(Projection * View));
	sphereVAO.bind();
	glDrawElements(GL_TRIANGLES, sphereMesh->numOfIndices(), sphereMesh->getIndexDataType(), 0);
}
