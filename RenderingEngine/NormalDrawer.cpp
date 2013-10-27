#include "NormalDrawer.h"

NormalDrawer::NormalDrawer(const Mesh &mesh)
	: Model(1.0f), p("../RenderingEngine/StockShaders/NormalShader"),
	vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh.getVertexData(), mesh.getVertexDataSize()),
	vertAttrib(0, 3, GL_FLOAT, GL_FALSE),
	normals(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh.getNormalData(), mesh.getNormalDataSize()),
	norAttrib(1, 3, GL_FLOAT, GL_TRUE)
{
	vertexNum = mesh.numOfVertices();
}

NormalDrawer::NormalDrawer(const Mesh &mesh, glm::mat4 model)
	: Model(model), p("../RenderingEngine/StockShaders/NormalShader"),
	vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh.getVertexData(), mesh.getVertexDataSize()),
	vertAttrib(0, 3, GL_FLOAT, GL_FALSE),
	normals(GL_ARRAY_BUFFER, GL_STATIC_DRAW, mesh.getNormalData(), mesh.getNormalDataSize()),
	norAttrib(1, 3, GL_FLOAT, GL_TRUE)
{
	vertexNum = mesh.numOfVertices();
}


NormalDrawer::~NormalDrawer(void)
{
}

void NormalDrawer::initDrawing()
{
	normalVAO.bind();
	vertices.bind();
	vertAttrib.attribPointer();
	normals.bind();
	norAttrib.attribPointer();
}

void NormalDrawer::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	glm::mat4 MVP = Projection * View * Model;

	p.use();
	p.setUniform("MVP", MVP);
	normalVAO.bind();
	glDrawArrays(GL_TRIANGLES, 0, vertexNum);
}
