#pragma once

#include "UnLitObject.h"
#include "OGLobjects.h"
#include "Square.h"
#include <Mesh.h>

class Mirror :
	public UnLitObject
{
public:
	Mirror(const Square &sq);
	~Mirror(void);

	virtual void initDrawing();
	virtual void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	Square sq;
	Mesh mesh;

	VertexArrayObject quadVAO;
	BufferObject quadData;
	VertexAttribArray quadAttribArray;

	FrameBufferObject fbo;
	RenderBufferObject rbo;
	Texture2D renderTarget;

	static bool enable;
};

