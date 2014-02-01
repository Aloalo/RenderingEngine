#include "UnlitObject3D.h"

using namespace std;
using namespace glm;

UnlitObject3D::UnlitObject3D(Mesh *mesh, const Material &mat, const mat4 &ModelMatrix)
	: mat(mat), mesh(mesh), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
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
	sampler.destroy();
	delete mesh;
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

	sampler.generate();
	sampler.samplerParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	sampler.samplerParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	sampler.samplerParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	sampler.samplerParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);

	p.use();
	p.setUniform("textureSampler", 0);
	p.setUniform("diffuseColor", mat.diffuseColor);
	p.bindSamplerObjectToSampler("textureSampler", sampler);
}

void UnlitObject3D::draw(const mat4 &View, const mat4 &Projection)
{
	p.use();
	p.setUniform("mvpMatrix", Projection * View * Model);
	
	glActiveTexture(GL_TEXTURE0 + p.getUniformi("textureSampler"));
	mat.diffuse_tex.bind();

	triangleVAO.bind();
	if(mesh->getIndexDataSize() > 0)
		glDrawElements(GL_TRIANGLES, mesh->numOfIndices(), mesh->getIndexDataType(), 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexDataSize());
}