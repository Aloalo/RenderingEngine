#pragma once

class Updateable
{
public:
	Updateable(void);
	virtual ~Updateable(void);

	virtual void initState() = 0;
	virtual void update(float deltaTime) = 0;
};

