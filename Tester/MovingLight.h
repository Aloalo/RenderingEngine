#pragma once

#include "Updateable.h"
#include "SpecularPointLight.h"
#include <memory>

class MovingLight :
	public Updateable
{
public:
	MovingLight(Light *light);
	~MovingLight(void);

	void initState();
	void update(float deltaTime);

private:
	float angle;
	float angularVel;
	SpecularPointLight *light;
};

