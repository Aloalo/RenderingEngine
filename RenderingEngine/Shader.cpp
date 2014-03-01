#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

namespace reng
{
	void Shader::init(const char *name)
	{
		string sn(name);
	    sn += getExtension();

		ifstream in(sn, ifstream::in);
		if(in)
		{
			unsigned long long int size = 0ull;
			in.seekg(0, ios::end);
			ifstream::pos_type szp = in.tellg();
			in.seekg(0, ios::beg);
			size = static_cast<unsigned long long int>(szp);

			char *source = new char[static_cast<size_t>(size)];
			memset(source, 0, static_cast<size_t>(size));
			in.read(source, static_cast<streamsize>(size));

			init2(source, name);
			delete[] source;
		}
		else
		{
			cerr << "no shader file found\n";
		}
		in.close();
	}

	void Shader::init(int idr, const char *name)
	{
		HRSRC hRes = FindResource(0, MAKEINTRESOURCE(idr), L"SHADER");
		HGLOBAL hData = LoadResource(0, hRes);
		int size = SizeofResource(0, hRes);
		const char *sd = (char*)LockResource(hData);

		init2(sd, name, size);
	}

	void Shader::init2(const char *src, const char *name, int len)
	{
		id = glCreateShader(getGlType());
		if(len == 0)
			glShaderSource(id, 1, &src, 0);
		else
			glShaderSource(id, 1, &src, &len);
		glCompileShader(id);

		int status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if(status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength+1];
			glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);

			fprintf(stderr, "Compile failure in %s shader %s:\n%s\n", getTypeString(), name, strInfoLog);
			delete[] strInfoLog;
		}
	}
}