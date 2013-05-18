#include "IndexContainer.h"

IndexContainer::IndexContainer(const std::vector<unsigned int> &indexData)
{
	indexCount = indexData.size();
	if(indexCount <= UCHAR_MAX)
		cast<unsigned char>(indexData);
	else if(indexCount <= USHRT_MAX)
		cast<unsigned short>(indexData);
	else
		cast<unsigned int>(indexData);
}

IndexContainer::IndexContainer(void)
{
}


IndexContainer::~IndexContainer(void)
{
	delete [] data;
}

int IndexContainer::size() const
{
	return indexCount;
}

int IndexContainer::getSizeInBytes() const
{
	return sizeInBytes;
}

const void* IndexContainer::getData() const
{
	return data;
}


template <class T>
void IndexContainer::cast(const std::vector<unsigned int> &indexData)
{
	data = new T[indexCount];
	for(int i = 0; i < indexCount; i++)
		*((T*)data+i) = (T)indexData[i];

	sizeInBytes = indexCount * sizeof(T);
}

