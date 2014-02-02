#include "Material.h"
#include "TextureHandler.h"
#include "MathFunctions.h"
#include <iostream>

using namespace glm;
using namespace mfl;
using namespace std;
using namespace tinyobj;

namespace reng
{
	Material::Material(const vec4 &ambientColor, const vec4 &diffuseColor, const vec4 &specularColor, float shininess)
		: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shininess(shininess),
		ambient_tex(TextureHandler::getDefaultTexture()), diffuse_tex(TextureHandler::getDefaultTexture()), 
		specular_tex(TextureHandler::getDefaultTexture()), normal_tex(TextureHandler::getDefaultTexture())
	{
	}

	Material::Material(const material_t &mat, const std::string &path)
		: ambientColor(mat.ambient[0], mat.ambient[1], mat.ambient[2], 1.0f), diffuseColor(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2], 1.0f), 
		specularColor(mat.specular[0], mat.specular[1], mat.specular[2], 1.0f), shininess(mat.shininess), name(mat.name), ior(ior),
		transmittance(mat.transmittance[0], mat.transmittance[1], mat.transmittance[2]), emission(mat.emission[0], mat.emission[1], mat.emission[2])
	{
		if(!mat.ambient_texname.empty())
			ambient_tex = TextureHandler::getTexture(path, mat.ambient_texname);
		else
			ambient_tex = TextureHandler::getDefaultTexture();

		if(!mat.diffuse_texname.empty())
			diffuse_tex = TextureHandler::getTexture(path, mat.diffuse_texname);
		else
			diffuse_tex = TextureHandler::getDefaultTexture();

		if(!mat.specular_texname.empty())
			specular_tex = TextureHandler::getTexture(path, mat.specular_texname);
		else
			specular_tex = TextureHandler::getDefaultTexture();

		if(!mat.normal_texname.empty())
			normal_tex = TextureHandler::getTexture(path, mat.normal_texname);
		else
			normal_tex = TextureHandler::getDefaultTexture();
	}

	Material::~Material(void)
	{
	}

	Material Material::defaultWhite()
	{
		return Material(vec4(0.8f), vec4(0.8f), vec4(0.7f), 1.0f);
	}


	void Material::print()
	{
		printf("Ka: [%.2f, %.2f, %.2f]\n", ambientColor.x, ambientColor.y, ambientColor.z);
		printf("Kd: [%.2f, %.2f, %.2f]\n", diffuseColor.x, diffuseColor.y, diffuseColor.z);
		printf("Ks: [%.2f, %.2f, %.2f]\n", specularColor.x, specularColor.y, specularColor.z);
		printf("Tr: [%.2f, %.2f, %.2f]\n", transmittance.x, transmittance.y, transmittance.z);
		printf("Em: [%.2f, %.2f, %.2f]\n", emission.x, emission.y, emission.z);
		printf("Sh: %.2f\n", shininess);
		printf("Ior: %.2f\n\n", ior);

		cout << "AmbientTex: " + ambient_tex.getName() << endl;
		cout << "DiffuseTex: " + diffuse_tex.getName() << endl;
		cout << "SpecularTex: " + specular_tex.getName() << endl;
		cout << "NormalTex: " + normal_tex.getName() << endl;
		cout << endl;

		cout << "Unknown params:" << endl;

		if(unknown_parameter.size() == 0)
			cout << "NONE" << endl;

		for(auto i = unknown_parameter.begin(); i != unknown_parameter.end(); ++i)
			cout << "unp[ " << i->first << " ] = " << i->second;

		cout << endl << endl << endl;
	}

	void Material::printIfUnknown()
	{
		for(auto i = unknown_parameter.begin(); i != unknown_parameter.end(); ++i)
			cout << "unp[ " << i->first << " ] = " << i->second;
	}
}