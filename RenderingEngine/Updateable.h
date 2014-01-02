#pragma once

class Updateable
{
public:
	Updateable(void);
	virtual ~Updateable(void);

	virtual void initState();
	virtual void update(float deltaTime) = 0;
};

