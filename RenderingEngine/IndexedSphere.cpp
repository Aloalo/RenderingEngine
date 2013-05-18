#include "IndexedSphere.h"

IndexedSphere::IndexedSphere(int _slices, int _stacks, float _radius)
	: slices(_slices), stacks(_stacks), radius(_radius)
{
	sphere = std::vector<glm::vec3>(stacks * slices + 2);
	sphereid = new unsigned short[2 * (stacks - 1) * slices * 3];
	generate();
}

IndexedSphere::~IndexedSphere(void)
{
	sphere.clear();
	delete [] sphereid;
}

const glm::vec3* IndexedSphere::getVertexArray() const
{
	return sphere.data();
}

const unsigned short* IndexedSphere::getIndexArray() const
{
	return sphereid;
}

int IndexedSphere::getNumberOfVertices() const
{
	return numberOfVertices;
}

int IndexedSphere::getNumberOfIndices() const
{
	return numberOfIndices;
}

int IndexedSphere::getVertexArraySize() const
{
	return numberOfVertices * sizeof(glm::vec3);
}

int IndexedSphere::getIndexArraySize() const
{
	return numberOfIndices * sizeof(unsigned short);
}

int IndexedSphere::numberOfTriangles() const
{
	return numberOfIndices;
}

float IndexedSphere::getRadius() const
{
	return radius;
}

void IndexedSphere::generate()
{
	numberOfIndices = numberOfVertices = 0;

	{
		sphere[numberOfVertices] = glm::vec3(0, 1, 0);
		++numberOfVertices;
		float y = cos(MathFunctions::pi / stacks);
		float xzs = sin(MathFunctions::pi / stacks);
		for(int i = 0; i < slices; ++i)
		{
			sphere[numberOfVertices] = glm::vec3(sin(2 * MathFunctions::pi * i / slices) * xzs, y, cos(2 * MathFunctions::pi * i / slices) * xzs);
			sphereid[numberOfIndices * 3 + 0] = 0;
			sphereid[numberOfIndices * 3 + 1] = numberOfVertices;
			sphereid[numberOfIndices * 3 + 2] = numberOfVertices + 1;
			++numberOfVertices;
			++numberOfIndices;
		}
		sphereid[(numberOfIndices-1)*3+2] = numberOfVertices - slices;
	}

	for(int j = 2; j < stacks; ++j)
	{
		float y = cos(MathFunctions::pi * j / stacks);
		float xzs = sin(MathFunctions::pi * j / stacks);
		for(int i = 0; i < slices; ++i)
		{
			sphere[numberOfVertices] = glm::vec3(sin(2 * MathFunctions::pi * i / slices) * xzs, y, cos(2 * MathFunctions::pi * i / slices) * xzs);
			sphereid[numberOfIndices * 3 + 0] = numberOfVertices - slices;
			sphereid[numberOfIndices * 3 + 1] = numberOfVertices;
			sphereid[numberOfIndices * 3 + 2] = numberOfVertices + 1;
			++numberOfIndices;
			sphereid[numberOfIndices * 3 + 0] = numberOfVertices - slices + 1;
			sphereid[numberOfIndices * 3 + 1] = numberOfVertices - slices;
			sphereid[numberOfIndices * 3 + 2] = numberOfVertices + 1;
			++numberOfIndices;
			++numberOfVertices;
		}
		sphereid[(numberOfIndices-2)*3+2] = numberOfVertices - slices;
		sphereid[(numberOfIndices-1)*3+2] = numberOfVertices - slices;
		sphereid[(numberOfIndices-1)*3+0] = numberOfVertices - slices * 2;
	}

	{
		sphere[numberOfVertices] = glm::vec3(0, -1, 0);
		int tspi = numberOfVertices++;
		float y = cos(MathFunctions::pi * (stacks - 1) / stacks);
		float xzs = sin(MathFunctions::pi / stacks);
		for(int i = 0; i < slices; ++i)
		{
			sphere[numberOfVertices] = glm::vec3(sin(2 * MathFunctions::pi * i / slices) * xzs, y, cos(2 * MathFunctions::pi * i / slices) * xzs);
			sphereid[numberOfIndices * 3 + 0] = tspi;
			sphereid[numberOfIndices * 3 + 1] = numberOfVertices + 1;
			sphereid[numberOfIndices * 3 + 2] = numberOfVertices;
			++numberOfVertices;
			++numberOfIndices;
		}
		sphereid[(numberOfIndices-1)*3+1] = numberOfVertices - slices;
	}

	for(int i = 0; i < numberOfVertices; ++i)
		sphere[i] = radius * sphere[i];

	numberOfIndices *= 3;
}

std::vector<glm::vec3>& IndexedSphere::getVertexVector()
{
	return sphere;
}
