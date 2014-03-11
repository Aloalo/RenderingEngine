#pragma once

#include <vector>
#include <string>
#include <map>

namespace reng
{
	struct InitialSettings
	{
		unsigned int& operator[](const std::string &variableName);

		static InitialSettings& get();

	private:
		InitialSettings(const std::string &path);

		static InitialSettings *instance;

		std::map<std::string, unsigned int> values;
		std::map<std::string, unsigned int> format;
		//std::vector<Setting<unsigned int>> settings;
	};
}

