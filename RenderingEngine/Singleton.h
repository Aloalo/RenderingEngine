#pragma once

template<class D>
struct Singleton
{
	static D& get()
	{
		if(!instance)
			instance = new D;
		return *instance;
	}

private:
	static D *instance;
};

template<class D>
D *Singleton<D>::instance = 0;