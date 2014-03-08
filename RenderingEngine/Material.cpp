#include "Material.h"
#include "TextureHandler.h"
#include "MathFunctions.h"
#include <iostream>

using namespace glm;
using namespace mfl;
using namespace std;

namespace reng
{
	Material::Material(const vec4 &ambientColor, const vec4 &diffuseColor, const vec4 &specularColor, float shininess)
		: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shininess(shininess),
		ambient_tex(TextureHandler::getDefaultTexture()), diffuse_tex(TextureHandler::getDefaultTexture()), 
		specular_tex(TextureHandler::getDefaultTexture()), normal_tex(TextureHandler::getDefaultTexture())
	{
	}

	Material::Material(const aiMaterial *mat, const std::string &path)
	{
		aiColor4D color;

		mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
		ambientColor = vec4(color.r, color.g, color.b, color.a);

		mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		diffuseColor = vec4(color.r, color.g, color.b, color.a);

		mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
		specularColor = vec4(color.r, color.g, color.b, color.a);

		mat->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		emission = vec3(color.r, color.g, color.b);

		mat->Get<float>(AI_MATKEY_SHININESS, shininess);

		if(mat->GetTextureCount(aiTextureType_AMBIENT) > 0)
		{
			aiString name;
			if(mat->GetTexture(aiTextureType_AMBIENT, 0, &name, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				ambient_tex = TextureHandler::getTexture(path + name.C_Str());
		}
		else
			ambient_tex = TextureHandler::getDefaultTexture();

		if(mat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString name;
			if(mat->GetTexture(aiTextureType_DIFFUSE, 0, &name, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
				diffuse_tex = TextureHandler::getTexture(path + name.C_Str());
		}
		else
			diffuse_tex = TextureHandler::getDefaultTexture();

		if(mat->GetTextureCount(aiTextureType_SPECULAR) > 0)
		{
			aiString name;
			if(mat->GetTexture(aiTextureType_SPECULAR, 0, &name, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
				specular_tex = TextureHandler::getTexture(path + name.C_Str());
		}
		else
			specular_tex = TextureHandler::getDefaultTexture();

		if(mat->GetTextureCount(aiTextureType_NORMALS) > 0)
		{
			aiString name;
			if(mat->GetTexture(aiTextureType_NORMALS, 0, &name, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
				normal_tex = TextureHandler::getTexture(path + name.C_Str());
		}
		else
			normal_tex = TextureHandler::getDefaultTexture();

		ambient_tex.generateMipmaps();
		diffuse_tex.generateMipmaps();
		specular_tex.generateMipmaps();
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