#pragma once

#include "Drawable.h"
#include "Program.h"
#include "VertexArrayObject.h"
#include "BufferObject.h"
#include "VertexAttribArray.h"
#include "Updateable.h"
#include "MatrixStack.h"

class Triangle :
	public Drawable, public Updateable
{
public:
	Triangle(void);
	~Triangle(void);

	void initState();
	void update(float deltaTime);

	void initDrawing();
	void draw(const glm::mat4 &ViewProjection);

private:
	Program *p;
	VertexAttribArray *attrib;
	VertexArrayObject *triangleVAO;
	BufferObject *vertices;

	float angle;
	float angularVel;
};

const GLfloat bufferData[] = { 
	-1.0f, -1.0f, 3.0f,
	1.0f, -1.0f, 3.0f,
	0.0f,  1.0f, 3.0f,
};