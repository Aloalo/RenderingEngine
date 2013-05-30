#include "MeshTester.h"
#include <SineCosine.h>
#include <MathFunctions.h>
#include <NormalDrawer.h>
#include <Engine.h>
#include <FunctionGraph.h>


MeshTester::MeshTester(void)
	: triangleVAO(), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW), normals(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	vertAttrib(0, 3, GL_FLOAT, GL_FALSE), normAttrib(1, 3, GL_FLOAT, GL_FALSE),
	indices(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
{
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

	mesh->setOrientation(GL_CCW);
	mesh->applyIndexing();

	//Engine::addToDisplayList(std::shared_ptr<Drawable>(new NormalDrawer(mesh, Model)));
}


MeshTester::~MeshTester(void)
{
	triangleVAO.destroy();
	vertices.destroy();
	normals.destroy();
	indices.destroy();
	delete mesh;
}

void MeshTester::initDrawing()
{
	triangleVAO.bind();
	vertices.setData(mesh->getVertexData(), mesh->getVertexDataSize());
	vertAttrib.attribPointer();
	normals.setData(mesh->getNormalData(), mesh->getNormalDataSize());
	normAttrib.attribPointer();
	indices.setData(mesh->getIndexData(), mesh->getIndexDataSize());
}

void MeshTester::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	triangleVAO.bind();
	glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
}

glm::vec4 MeshTester::diffuseColor()
{
	return glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
}

glm::vec4 MeshTester::specularColor()
{
	return glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
}

glm::vec4 MeshTester::ambientColor()
{
	return glm::vec4(1.0f, 0.2f, 0.2f, 1.0f);
}

float MeshTester::shininessFactor()
{
	return 128.0f;
}

glm::mat4 MeshTester::modelMatrix()
{
	return Model;
}
