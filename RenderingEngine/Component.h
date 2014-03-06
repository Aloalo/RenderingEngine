#pragma once

#include <glm/glm.hpp>
#include "InputObserver.h"
#include "Events.h"

namespace reng
{
	class Component 
	{
	public:
		Component(void);
		~Component(void);

		virtual void draw();

		virtual void onClick(const MouseClickEvent &e);

		bool shown;
		glm::vec2 p, d;
		glm::vec4 color;

		bool contains(glm::vec2 v) const;
	};
}
