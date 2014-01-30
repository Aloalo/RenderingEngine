#pragma once

#include "LitObject.h"
#include "Mesh.h"
#include "OGLobjects.h"


/**
Does memory handleing
*/
class Object3D :
	public LitObject
{
public:
	Object3D(Mesh *mesh, const Material &mat = Material::defaultWhite(), Texture *tex = Texture::defaultWhite(), const glm::mat4 &ModelMatrix = glm::mat4(1.0f));
	~Object3D(void);
	

	void setModelMatrix(const glm::mat4 &ModelMatrix);
	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);
	const Material& getMaterial() const;
	const glm::mat4& modelMatrix() const;
	const Texture* getTexture() const;
	
private:
	Material mat;
	Mesh *mesh;
	Texture *tex;
	glm::mat4 Model;
	
	VertexArrayObject triangleVAO;
	VertexAttribArray vertAttrib;
	VertexAttribArray normAttrib;
	VertexAttribArray uvAttrib;
	BufferObject vertices;
	BufferObject normals;
	BufferObject uv;
	BufferObject indices;
};

