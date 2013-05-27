#include "Shader.h"
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <Windows.h>

void Shader::init(const char *name)
{
	char sn[64];
	strcpy(sn, name);
	strcat(sn, getExtension());

	char source[2000];
	memset(source, 0, sizeof source);
	FILE *f = fopen(sn, "r");
	if(f == 0)
	{
		printf("Could not open %s\n%s\n", sn, strerror(errno));
		id = -1;
		return;
	}

	int cnt = fread(source, 1, 2000, f);
	if(cnt == 2000)
		puts("omgomg, nemam dosta mem");
	fclose(f);

	init2(source, name);
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
