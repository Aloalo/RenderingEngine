#pragma once

#include <string>
#include "Component.h"
#include "Font.h"

namespace reng
{
	class Label : public Component
	{
	public:
		Label(void);
		~Label(void);

		virtual void draw();

		std::string text;
		Font *font;
	};
}
