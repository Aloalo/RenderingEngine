#include "IndexContainer.h"

IndexContainer::IndexContainer(const std::vector<unsigned int> &indexData)
{
	indexCount = indexData.size();
	if(indexCount <= UCHAR_MAX)
		cast(indexData, (unsigned char)0);
	else if(indexCount <= USHRT_MAX)
		cast(indexData, (unsigned short)0);
	else
		cast(indexData, (unsigned int)0);
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
void IndexContainer::cast(const std::vector<unsigned int> &indexData, T x)
{
	data = new T[indexCount];
	for(int i = 0; i < indexCount; i++)
		*((T*)data+i) = (T)indexData[i];

	sizeInBytes = indexCount * sizeof(T);
}

