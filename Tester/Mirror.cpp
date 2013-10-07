#include "Mirror.h"
#include <Engine.h>

bool Mirror::enable = 1;

Mirror::Mirror(const Square &sq)
	: sq(sq), quadData(GL_VERTEX_ARRAY, GL_DRAW_BUFFER),
	quadAttribArray(0, 3, GL_FLOAT), fbo(GL_FRAMEBUFFER), renderTarget(GL_TEXTURE_2D)
{
}


Mirror::~Mirror(void)
{
}

void Mirror::initDrawing()
{
	renderTarget.texImage(0, GL_RGB, glm::vec3(1024, 768, 0), GL_RGB, GL_UNSIGNED_BYTE, 0);
	renderTarget.texParam(GL_TEXTURE_MAG_FILTER, (GLuint)GL_NEAREST);
	renderTarget.texParam(GL_TEXTURE_MIN_FILTER, (GLuint)GL_NEAREST);

	rbo.allocateStorage(GL_DEPTH_COMPONENT, 1024, 768);
	fbo.attachRenderBuffer(GL_DEPTH_ATTACHMENT, rbo);
	fbo.attachTexture(GL_COLOR_ATTACHMENT0, renderTarget, 0);

	fbo.setDrawBuffers();
}

void Mirror::draw(const glm::mat4 &View, const glm::mat4 &Projection)
{
	if(!enable)
		return;
	enable = 0;

	fbo.bind();
	glm::vec3 pos = Engine::getCamera()->getPosition();

	pos -= 2.f * glm::dot(pos - sq.c, sq.n) / glm::dot(sq.n, sq.n) * sq.n;
	glm::vec3 dir = glm::reflect(Engine::getCamera()->cam->getDirection(), sq.n);
	glm::vec3 up = glm::reflect(Engine::getCamera()->cam->getUp(), sq.n);
	
//	TODO::ZAVRSI;
	
	fbo.unBind();
}
