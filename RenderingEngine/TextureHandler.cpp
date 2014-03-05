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

	ILboolean convertAndGetType(GLenum format, GLenum &type)
	{
		switch(format)
		{
		case GL_RGBA32F_ARB:
			type = GL_FLOAT;
			return ilConvertImage(IL_RGBA, IL_FLOAT);
			break;
		case GL_RGBA8:
			type = GL_UNSIGNED_BYTE;
			return ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
			break;
		case GL_RGBA8UI:
			type = GL_UNSIGNED_BYTE;
			return ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
			break;
		case GL_RGBA16:
			type = GL_UNSIGNED_SHORT;
			return ilConvertImage(IL_RGBA, IL_UNSIGNED_SHORT);
			break;
		default:
			throw new exception("Unsupported texture format");
		}
	}

	Texture TextureHandler::getTexture(const string &path, const string &def, GLenum format)
	{
		if(existingTextures.find(path) != existingTextures.end())
			return existingTextures[path];


		Texture ret(path);
		ILuint imageID;
		ILboolean success;
		ILenum error;
		ilGenImages(1, &imageID);
		ilBindImage(imageID);
		success = ilLoadImage((const ILstring)path.c_str());

		if(!success)
		{
			error = ilGetError();
			std::cout << "Image load failed " + path + "- IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			success = ilLoadImage((const ILstring)def.c_str());
			if(!success)
			{
				error = ilGetError();
				std::cout << "Image load failed " + def + "- IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
				exit(-1);
			}
		}

		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if(ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
			iluFlipImage();

		GLenum type;
		success = convertAndGetType(format, type);

		if(!success)
		{
			error = ilGetError();
			cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << endl;
			exit(-1);
		}
		ret.generate();
		ret.bind();
		ret.texImage(0, format, vec3(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0), ilGetInteger(IL_IMAGE_FORMAT), type, ilGetData());

		ilDeleteImages(1, &imageID);

		existingTextures[path] = ret;
		return ret;
	}

	Texture TextureHandler::genTexture(const std::string &path, GLenum target)
	{
		if(existingTextures.find(path) != existingTextures.end())
			return existingTextures[path];

		Texture ret(path, target);
		ret.generate();
		existingTextures[path] = ret;
		return ret;
	}

	Texture TextureHandler::getDefaultTexture()
	{
		return defaultTexture;
	}

	bool TextureHandler::hasTexture(const std::string &path)
	{
		if(existingTextures.find(path) != existingTextures.end())
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