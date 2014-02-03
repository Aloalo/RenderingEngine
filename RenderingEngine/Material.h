#pragma once

#include <glm/glm.hpp>
#include <assimp/material.h>
#include "Texture.h"

namespace reng
{
	struct Material
	{
		Material(const glm::vec4 &ambientColor, const glm::vec4 &diffuseColor, const glm::vec4 &specularColor, float shininess);
		Material(const aiMaterial *mat, const std::string &path);
		~Material(void);

		static Material defaultWhite();
		void print();
		void printIfUnknown();

		std::string name;
		glm::vec4 diffuseColor;
		glm::vec4 specularColor;
		glm::vec4 ambientColor;
		glm::vec3 emission;
		float shininess;
		float ior;

		Texture ambient_tex;
		Texture diffuse_tex;
		Texture specular_tex;
		Texture normal_tex;
		std::map<std::string, std::string> unknown_parameter;
	};
}
