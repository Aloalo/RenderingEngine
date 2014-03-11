#include "InitialSettings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

using namespace std;

namespace reng
{
	InitialSettings *InitialSettings::instance = 0;

	InitialSettings& InitialSettings::get()
	{
		if(instance)
			return *instance;
		return *(instance = new InitialSettings("Settings.ini"));
	}

	InitialSettings::InitialSettings(const string &path)
	{	
		format["GL_NEAREST"] = GL_NEAREST;
		format["GL_LINEAR"] = GL_LINEAR;

		ifstream f(path);
		if(f.is_open())
		{
			try
			{
				while(!f.eof())
				{
					string name, value;
					f >> name;
					if(name.substr(0, 1) == "#")
					{
						f >> value;
						name = name.substr(1);
						try
						{
							values[name] = stoi(value);
						}
						catch(exception &ex)
						{
							values[name] = format[value];
						}
					}
				}
			}
			catch(std::exception *ex)
			{
				printf("%s\n", ex->what());
				exit(0);
			}
		}
		else
		{
			printf("Cannot open graphics settings");
			exit(0);
		}
		f.close();
	}


	unsigned int& InitialSettings::operator[](const string &variableName)
	{
		return values[variableName];
	}
}