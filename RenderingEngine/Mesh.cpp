#include "Mesh.h"

#include <map>
#include <algorithm>
#include <GL/glew.h>
#include "glm/gtc/swizzle.hpp"
#include "MathFunctions.h"

Mesh::Mesh(const std::vector<glm::vec3> &_vertexData)
	: vertexData(_vertexData)
{
}

Mesh::Mesh(const std::vector<glm::vec3> &_vertexData, const std::vector<glm::vec3> &_normalData)
	: vertexData(_vertexData), normalData(_normalData)
{
}

Mesh::Mesh(const std::vector<glm::vec3> &_vertexData, const std::vector<glm::vec3> &_normalData, const std::vector<glm::vec2> &_uvData)
	: vertexData(_vertexData), normalData(_normalData), uvData(_uvData)
{
}

Mesh::Mesh()
{
}

Mesh::~Mesh(void)
{
	clear();
}


void Mesh::clear()
{
	vertexData.clear();
	normalData.clear();
	uvData.clear();
	delete indexData;
	indexData = NULL;
}

void Mesh::addTriangle(const glm::vec3 vert[3])
{
	vertexData.push_back(vert[0]);
	vertexData.push_back(vert[1]);
	vertexData.push_back(vert[2]);
}

void Mesh::addTriangle(const glm::vec3 vert[3], const glm::vec3 nor[3])
{
	vertexData.push_back(vert[0]);
	vertexData.push_back(vert[1]);
	vertexData.push_back(vert[2]);
	normalData.push_back(nor[0]);
	normalData.push_back(nor[1]);
	normalData.push_back(nor[2]);
}

void Mesh::calculateNormals()
{
	normalData.clear();
	int n = vertexData.size();
	float flip = orientation == GL_CCW ? -1.0f : 1.0f;
	for(int i = 0; i < n; i += 3)
	{
		glm::vec3 normal = -glm::cross(vertexData[i + 1] - vertexData[i], vertexData[i + 2] - vertexData[i]);
		normal = glm::normalize(normal);

		normalData.push_back(flip * normal);
		normalData.push_back(flip * normal);
		normalData.push_back(flip * normal);
	}
}

void Mesh::interpolateNormals()
{
	int n = vertexData.size();
	std::vector<std::pair<Vertex, int> > out(n);
	for(int i = 0; i < n; i++)
		out.push_back(std::pair<Vertex, int>(vertexData[i], i));
	std::sort(out.begin(), out.end());

	int index = 0;
	glm::vec3 interpNor = normalData[out[0].second];
	for(int i = 1; i < n; i++)
	{
		while(i < n && out[index].first == out[i].first)
		{
			interpNor += normalData[out[i].second];
			i++;
		}
		interpNor /= float(i - index);

		for(int j = index; j < i; j++)
			normalData[out[j].second] = interpNor;

		interpNor = glm::vec3(0.0f);
		index = i;
	}
}

bool getSimilarVertexIndex(PackedVertex &packed, std::map<PackedVertex, unsigned int> &VertexToOutIndex, unsigned int &result)
{
	std::map<PackedVertex, unsigned int>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end())
		return false;
	else
	{
		result = it->second;
		return true;
	}
}

void Mesh::applyIndexing()
{
	std::vector<glm::vec3> outVertexData;
	std::vector<glm::vec3> outNormalData;
	std::vector<glm::vec2> outUvData;
	std::vector<unsigned int> outIndexData;

	std::map<PackedVertex, unsigned int> VertexToOutIndex;
	bool hasUV = uvData.size() > 0;
	bool hasNormal = normalData.size() > 0;
	const glm::vec3 zero(0.0f);

	int n = vertexData.size();
	for (unsigned int i = 0; i < n; i++)
	{
		PackedVertex packed(vertexData[i], hasNormal ? normalData[i] : zero, hasUV ? uvData[i] : glm::vec2(0.0f));

		unsigned int index;
		bool found = getSimilarVertexIndex(packed, VertexToOutIndex, index);

		if (found)
			outIndexData.push_back(index);
		else
		{
			outVertexData.push_back(vertexData[i]);
			if(hasUV)
				outUvData.push_back(uvData[i]);
			if(hasNormal)
				outNormalData.push_back(normalData[i]);
			outIndexData.push_back(outVertexData.size() - 1);
			VertexToOutIndex[packed] = outVertexData.size() - 1;
		}
	}

	indexData = new IndexContainer(outIndexData);
	vertexData = outVertexData;
	uvData = outUvData;
	normalData = outNormalData;
}

void Mesh::flipOrientation()
{
	orientation == GL_CCW ? orientation = GL_CW : orientation = GL_CCW;
	flip();
}

void Mesh::setOrientation(unsigned int _orientation)
{
	orientation = _orientation;
	if(!((orientation == GL_CCW && MathFunctions::ccw(vertexData[0], vertexData[1], vertexData[2]) > 0)
		|| (orientation == GL_CW && MathFunctions::ccw(vertexData[0], vertexData[1], vertexData[2]) < 0)))
		flip();
}

const glm::vec3* Mesh::getVertexData() const
{
	return vertexData.data();
}

const glm::vec3* Mesh::getNormalData() const
{
	return normalData.data();
}

const glm::vec2* Mesh::getUVData() const
{
	return uvData.data();
}

const void* Mesh::getIndexData() const
{
	return indexData->getData();
}

unsigned int Mesh::getIndexDataType() const
{
	int n = indexData->size();
	return n <= UCHAR_MAX ? GL_UNSIGNED_BYTE : (n <= USHRT_MAX ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT);
}

int Mesh::numOfVertices() const
{
	return vertexData.size();
}

int Mesh::numOfNormals() const
{
	return normalData.size();
}

int Mesh::numOfUVs() const
{
	return uvData.size();
}

int Mesh::numOfIndices() const
{
	return indexData->size();
}

int Mesh::getVertexDataSize() const
{
	return vertexData.size() * sizeof(vertexData[0]);
}

int Mesh::getIndexDataSize() const
{
	return indexData->getSizeInBytes();
}

int Mesh::getUVDataSize() const
{
	return uvData.size() * sizeof(uvData[0]);
}

int Mesh::getNormalDataSize() const
{
	return normalData.size() * sizeof(normalData[0]);
}

void Mesh::flip()
{
	int n = vertexData.size();
	for(int i = 0; i < n; i += 3)
	{
		std::swap(vertexData[i], vertexData[i + 1]);
		if(normalData.size())
			std::swap(normalData[i], normalData[i + 1]);
		if(uvData.size())
			std::swap(uvData[i], uvData[i + 1]);
	}
}
