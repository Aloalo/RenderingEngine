#pragma once

#include "InitialSettings.h"

#define SETTING(s) s(#s)

namespace reng
{
	template<class T>
	struct Setting
	{
		Setting(const std::string &name) :
			name(name)
		{
			x = InitialSettings::get()[name];
		}


		//void set(const map<std::string, T> &mp)
		//{
		//	x = mp[name];
		//}

		operator T&()
		{
			return x;
		}

		T& operator=(const T &v)
		{
			return x = v;
		}

		T x;
		std::string name;
	};
}