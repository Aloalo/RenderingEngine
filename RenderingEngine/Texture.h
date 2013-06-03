#pragma once

class Texture
{
public:
	Texture(unsigned int _target);
	~Texture(void);

	void bind();
	void load(const char *imagepath);
	void texParam(unsigned int paramName, unsigned int param);
	void texParam(unsigned int paramName, float param);

private:
	unsigned int ID;
	unsigned int target;
};

