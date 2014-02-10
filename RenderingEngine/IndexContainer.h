#pragma once

#include <vector>
#include <climits>

namespace reng
{
	class IndexContainer
	{
	public:
		IndexContainer(void);
		IndexContainer(const std::vector<unsigned int> &indexData);
		~IndexContainer(void);

		unsigned int get(int idx);

		void setData(const std::vector<unsigned int> &indexData);
		int size() const;
		int getSizeInBytes() const;
		const void* getData() const;

	private:
		template <class T>
		void cast(const std::vector<unsigned int> &indexData);
		template <class T>
		T& get(int idx);

		void *data;
		int indexCount;
		int sizeInBytes;
	};
}
