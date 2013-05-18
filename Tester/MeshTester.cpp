#include "MeshTester.h"
#include <SineCosine.h>
#include <MathFunctions.h>
#include <NormalDrawer.h>
#include <Engine.h>
#include <FunctionGraph.h>


MeshTester::MeshTester(void)
{
	p = new Program("../RenderingEngine/StockShaders/Simple");
	triangleVAO = new VertexArrayObject();
	vertices = new BufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	attrib = new VertexAttribArray(0, 3, GL_FLOAT, GL_FALSE);
	indices = new BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

	Model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -10.0f, 0.0f));

	glm::vec2 x[] = 
	{
		glm::vec2(-20.0f, -20.0f), glm::vec2(-20.0f, 20.0f), glm::vec2(20.0f, 20.0f),
		glm::vec2(-20.0f, -20.0f), glm::vec2(20.0f, 20.0f), glm::vec2(20.0f, -20.0f)
	};
	mesh = new Mesh();
	FunctionGraph graph(new SineCosine());
	graph.generateGraph(x, 7, -1000.0f, mesh);
	graph.generateGraph(x+3, 7, -1000.0f, mesh);
	mesh->applyIndexing();

	Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(mesh, Model)));
}


MeshTester::~MeshTester(void)
{
	delete triangleVAO;
	delete vertices;
	delete indices;
	delete mesh;
}

void MeshTester::initDrawing()
{
	triangleVAO->bind();
	vertices->bind();
	vertices->setData(mesh->getVertexData(), mesh->getVertexDataSize());
	attrib->enable();
	attrib->attribPointer();

	indices->bind();
	indices->setData(mesh->getIndexData(), mesh->getIndexDataSize());
}

void MeshTester::draw(const glm::mat4 &ViewProjection)
{
	glm::mat4 MVP = ViewProjection * Model;

	p->use();
	p->setUniform("MVPmatrix", 1, &MVP);
	triangleVAO->bind();
	glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
}
