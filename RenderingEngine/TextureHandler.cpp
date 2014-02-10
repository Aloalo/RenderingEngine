#include "TextureHandler.h"
#include <IL/ilut.h>
#include <glm/glm.hpp>
#include <iostream>

using namespace std;
using namespace glm;

namespace reng
{
	map<string, Texture> TextureHandler::existingTextures;
	Texture TextureHandler::defaultTexture("DefaultTexture");

	TextureHandler::TextureHandler(void)
	{
	}


	TextureHandler::~TextureHandler(void)
	{
		for(auto it = existingTextures.begin(); it != existingTextures.end(); ++it)
			(*it).second.destroy();
	}


	Texture TextureHandler::getTexture(const std::string &path, const std::string &name, GLenum format)
	{
		if(existingTextures.find(name) != existingTextures.end())
			return existingTextures[name];


		Texture ret(name);
		ILuint imageID;
		ILboolean success;
		ILenum error;
		ilGenImages(1, &imageID);
		ilBindImage(imageID);
		success = ilLoadImage((const ILstring)(path + name).c_str());

		if (success)
		{
			ILinfo ImageInfo;
			iluGetImageInfo(&ImageInfo);
			if(ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
				iluFlipImage();

			success = ilConvertImage(IL_RGBA, IL_FLOAT);

			if (!success)
			{
				error = ilGetError();
				cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << endl;
				exit(-1);
			}
			ret.generate();
			ret.bind();
			ret.texImage(0, format, vec3(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0), ilGetInteger(IL_IMAGE_FORMAT), GL_FLOAT, ilGetData());
		}
		else
		{
			error = ilGetError();
			std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			exit(-1);
		}
		ilDeleteImages(1, &imageID);

		existingTextures[name] = ret;
		return ret;
	}

	Texture TextureHandler::getTexture(const std::string &name, GLenum target)
	{
		if(existingTextures.find(name) != existingTextures.end())
			return existingTextures[name];

		Texture ret(name, target);
		ret.generate();
		existingTextures[name] = ret;
		return ret;
	}

	Texture TextureHandler::getDefaultTexture()
	{
		return defaultTexture;
	}

	bool TextureHandler::hasTexture(const std::string &name)
	{
		if(existingTextures.find(name) != existingTextures.end())
			return true;
		return false;
	}

	void TextureHandler::generateDefaultTex()
	{
		defaultTexture.generate();
		float data[] = {1.0f, 1.0f, 1.0f, 1.0f};
		defaultTexture.bind();
		defaultTexture.texImage(0, GL_RGBA, vec3(1, 1, 0), GL_RGBA, GL_FLOAT, data);
	}
}
