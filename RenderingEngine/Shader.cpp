
#include "Shader.h"
#include <cstring>
#include <cstdio>
#include <cstdio>

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
		printf("no %s\n", sn);
		id = -1;
		return;
	}

	id = glCreateShader(getGlType());

	int cnt = fread(source, 1, 2000, f);
	if(cnt == 2000)
		puts("omgomg, nemam dosta mem");
	fclose(f);

	int status;
	const char *sp = source;
	glShaderSource(id, 1, &sp, 0);
	glCompileShader(id);

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
