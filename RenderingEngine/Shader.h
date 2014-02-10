#pragma once

#include <GL/glew.h>

namespace reng
{
	class Shader
	{
	public:
		int id;

		virtual const char* getExtension() = 0;
		virtual const char* getTypeString() = 0;
		virtual int getGlType() = 0;

	protected:
		void init(const char *name);
		void init(int idr, const char *name);

	private:
		void init2(const char *src, const char *name, int len = 0);
	};
}
