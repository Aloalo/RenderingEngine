#pragma once

#include "UnLitObject.h"
#include "OGLobjects.h"
#include "Updateable.h"
#include "MatrixStack.h"

class Triangle :
	public UnLitObject, public Updateable
{
public:
	Triangle(void);
	~Triangle(void);

	void initState();
	void update(float deltaTime);

	void initDrawing();
	void draw(const glm::mat4 &View, const glm::mat4 &Projection);

private:
	Program *p;
	VertexAttribArray attrib;
	VertexArrayObject triangleVAO;
	BufferObject vertices;

	float angle;
	float angularVel;
};

const GLfloat bufferData[] = { 
	-1.0f, -1.0f, 3.0f,
	1.0f, -1.0f, 3.0f,
	0.0f,  1.0f, 3.0f,
};