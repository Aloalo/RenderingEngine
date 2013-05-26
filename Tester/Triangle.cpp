#include "StdAfx.h"
#include "Triangle.h"

#include <glm/gtc/matrix_transform.hpp>


Triangle::Triangle(void)
	: p(new Program("../RenderingEngine/StockShaders/Simple")), triangleVAO(), vertices(GL_ARRAY_BUFFER, GL_STATIC_DRAW, bufferData, sizeof(bufferData)),
	attrib(0, 3, GL_FLOAT, GL_FALSE)
{
}


Triangle::~Triangle(void)
{
}

void Triangle::initDrawing()
{
	triangleVAO.bind();
	vertices.bind();
	attrib.enable();
	attrib.attribPointer();
}

void Triangle::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	MatrixStack model;
	model.pushMatrix();
		model.rotate(angle, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 MVP = Projection * View * model.top();

		p->use();
		p->setUniform("MVPmatrix", MVP);
		triangleVAO.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	model.popMatrix();
}

void Triangle::initState()
{
	angle = 0.0f;
	angularVel = 30.0;
}

void Triangle::update(float deltaTime)
{
	angle += angularVel * deltaTime;
	if(angle >= 360.0f)
		angle -= 360.0f;
}
