#pragma once

#include "UnLitObject.h"
#include "Mesh.h"
#include "Material.h"
#include "OGLobjects.h"

class UnlitObject3D :
	public UnLitObject
{
public:
	UnlitObject3D(Mesh *mesh, const Material &mat = Material::defaultWhite(), Texture *tex = Texture::defaultWhite(), const glm::mat4 &ModelMatrix = glm::mat4(1.0f));
	~UnlitObject3D(void);
	
	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	Material mat;
	Mesh *mesh;
	Texture *tex;
	glm::mat4 Model;
	
	VertexArrayObject triangleVAO;
	VertexAttribArray vertAttrib;
	VertexAttribArray uvAttrib;
	BufferObject vertices;
	BufferObject uv;
	BufferObject indices;
	Program p;
};

