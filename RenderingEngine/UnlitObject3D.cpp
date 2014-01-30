#include "UnlitObject3D.h"

using namespace std;
using namespace glm;

UnlitObject3D::UnlitObject3D(Mesh *mesh, const Material &mat, Texture *tex, const mat4 &ModelMatrix)
	: mat(mat), mesh(mesh), tex(tex), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
	uv(GL_ARRAY_BUFFER, GL_STATIC_DRAW), vertAttrib(0, 3, GL_FLOAT, GL_FALSE),
	uvAttrib(2, 2, GL_FLOAT, GL_FLOAT), Model(ModelMatrix), p("../RenderingEngine/StockShaders/UnLitSimple")
{
	if(mesh->getIndexDataSize() > 0)
		indices = BufferObject(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}

UnlitObject3D::~UnlitObject3D(void)
{
	triangleVAO.destroy();
	vertices.destroy();
	indices.destroy();
	uv.destroy();
	delete mesh;
	delete tex;
}

void UnlitObject3D::initDrawing()
{
	triangleVAO.bind();
	vertices.setData(mesh->getVertexData(), mesh->getVertexDataSize());
	vertAttrib.attribPointer();
	uv.setData(mesh->getUVData(), mesh->getUVDataSize());
	uvAttrib.attribPointer();

	if(mesh->getIndexDataSize() > 0)
		indices.setData(mesh->getIndexData(), mesh->getIndexDataSize());

	p.use();
	p.setUniform("textureSampler", (int)tex->getID());
	p.setUniform("diffuseColor", mat.diffuseColor);
}

void UnlitObject3D::draw(const mat4 &View, const mat4 &Projection)
{
	triangleVAO.bind();
	p.use();
	p.setUniform("mvpMatrix", Projection * View * Model);

	if(mesh->getIndexDataSize() > 0)
		glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexDataSize());
}