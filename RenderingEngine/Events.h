#pragma once

#include <glm/glm.hpp>

namespace reng
{
	struct MouseClickEvent
	{
		MouseClickEvent(glm::vec2 pos, int button, int state, int mods) :
			pos(pos), button(button), state(state), mods(mods)
		{
		}

		glm::vec2 pos;
		int button;
		int state;
		int mods;
	};

	struct KeyPressEvent
	{
		KeyPressEvent(glm::vec2 pos, int key, int scancode, int action, int mods) :
			pos(pos), key(key), scancode(scancode), action(action), mods(mods)
		{
		}

		glm::vec2 pos;
		int key;
		int scancode;
		int action;
		int mods;
	};

	struct MouseMoveEvent
	{
		MouseMoveEvent(glm::vec2 pos) :
			pos(pos)
		{
		}

		glm::vec2 pos;
	};

	struct MouseWheelMoveEvent
	{
		MouseWheelMoveEvent(glm::vec2 pos) :
			pos(pos)
		{
		}

		glm::vec2 pos;
	};

	struct WindowResizeEvent
	{
		WindowResizeEvent(glm::ivec2 size) :
			size(size)
		{
		}

		glm::ivec2 size;
	};
}
