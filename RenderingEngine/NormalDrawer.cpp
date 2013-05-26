#include "NormalDrawer.h"

NormalDrawer::NormalDrawer(const Mesh* mesh)
	: Model(1.0f)
{
	init(mesh);
}

NormalDrawer::NormalDrawer(const Mesh* mesh, glm::mat4 model)
	: Model(model)
{
	init(mesh);
}


NormalDrawer::~NormalDrawer(void)
{
	delete normalVAO;
	delete vertices;
	delete normals;
}

void NormalDrawer::init(const Mesh *mesh)
{
	vertexNum = mesh->numOfVertices();
	p = new Program("../RenderingEngine/StockShaders/NormalShader");
	normalVAO = new VertexArrayObject();
	vertices = new BufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh->getVertexData(), mesh->getVertexDataSize());
	vertAttrib = new VertexAttribArray(0, 3, GL_FLOAT, GL_FALSE);
	normals = new BufferObject(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh->getNormalData(), mesh->getNormalDataSize());
	norAttrib = new VertexAttribArray(1, 3, GL_FLOAT, GL_TRUE);
}

void NormalDrawer::initDrawing()
{
	normalVAO->bind();
	vertices->bind();
	vertAttrib->enable();
	vertAttrib->attribPointer();
	normals->bind();
	norAttrib->enable();
	norAttrib->attribPointer();
}

void NormalDrawer::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	glm::mat4 VP = Projection * View * Model;

	p->use();
	p->setUniform("MVP", VP);
	normalVAO->bind();
	glDrawArrays(GL_TRIANGLES, 0, vertexNum);
}
