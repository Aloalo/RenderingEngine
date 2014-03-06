#pragma once

#include "Component.h"
#include <GLFW/glfw3.h>

namespace reng
{
	using namespace glm;

	class Button : public Component
	{
	public:
		Button(void) :
			a(0)
		{
			d = vec2(100, 20);
		}

		virtual void onClick(const MouseClickEvent &e)
		{
			if(a && e.button == GLFW_MOUSE_BUTTON_LEFT && e.state == GLFW_PRESS)
				a->exec();
		}

		template<class F>
		void setAction(F *f)
		{
			if(a)
				delete a;
			a = new ActionT<F>(f);
		}

	private:
		struct Action
		{
			virtual ~Action() {};
			virtual void exec() = 0;
		};

		template<class F>
		struct ActionT : Action
		{
			ActionT(F *f) :
				f(f)
			{
			}

			void exec()
			{
				(*f)();
			}

			F *f;
		};

		Action *a;
	};

}
