#include "UIManager.h"

#include <GL/glew.h>
#include "Engine.h"
#include "Input.h"

namespace reng
{
	UIManager *UIManager::uim = 0;

	UIManager::UIManager(void)
	{
		Input::addInputObserver(this);
	}

	UIManager::~UIManager(void)
	{
	}

	UIManager& UIManager::get()
	{
		if(!uim)
			uim = new UIManager();
		return *uim;
	}

	void UIManager::draw()
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		glUseProgram(0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_ALWAYS);
		glDisable(GL_CULL_FACE);
		glLoadIdentity();
		glPushMatrix();
		glOrtho(0, d.x, d.y, 0, -1, 1);
		Container::draw();
		glPopMatrix();
	}
	
	void UIManager::mouseClick(const MouseClickEvent &e)
	{
		onClick(e);
	}
}
