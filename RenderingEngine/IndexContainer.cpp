#include "IndexContainer.h"

namespace reng
{
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
		if(data != NULL)
			delete [] data;
	}

	unsigned int IndexContainer::get(int idx)
	{
		if(indexCount <= UCHAR_MAX)
			return get<unsigned char>(idx);
		else if(indexCount <= USHRT_MAX)
			return get<unsigned short>(idx);
		else
			return get<unsigned int>(idx);
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


	template <class T>
	T& IndexContainer::get(int idx)
	{
		return *((T*)data+idx);
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
}
