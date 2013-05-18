#pragma once

#include <vector>
#include <climits>

class IndexContainer
{
public:
	IndexContainer(void);
	IndexContainer(const std::vector<unsigned int> &indexData);
	~IndexContainer(void);

	int size() const;
	int getSizeInBytes() const;
	const void* getData() const;

private:
	template <class T>
	void cast(const std::vector<unsigned int> &indexData);
	void *data;
	int indexCount;
	int sizeInBytes;
};

