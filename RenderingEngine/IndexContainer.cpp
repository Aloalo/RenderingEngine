#include "IndexContainer.h"

IndexContainer::IndexContainer(const std::vector<unsigned int> &indexData)
	: data(NULL)
{
	setData(indexData);
}

IndexContainer::IndexContainer(void)
	: indexCount(0), sizeInBytes(0), data(NULL)
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

void IndexContainer::setData(const std::vector<unsigned int> &indexData)
{
	if(data != NULL)
		delete data;
	indexCount = indexData.size();
	if(indexCount <= UCHAR_MAX)
		cast<unsigned char>(indexData);
	else if(indexCount <= USHRT_MAX)
		cast<unsigned short>(indexData);
	else
		cast<unsigned int>(indexData);

}

