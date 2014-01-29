#include <GL/glew.h>
#include <map>
#include <algorithm>
#include <glm/gtc/swizzle.hpp>
#include "Mesh.h"
#include "MathFunctions.h"
#include "Vertex.h"

using namespace std;
using namespace glm;
using namespace mfl;
using namespace tinyobj;


Mesh::Mesh(void)
{
}

Mesh::Mesh(const shape_t &shape)
{
	constructFromShape(shape);
}

Mesh::Mesh(const vector<vec3> &_vertexData, const vector<vec3> &_normalData, const vector<vec2> &_uvData)
	: vertexData(_vertexData), normalData(_normalData), uvData(_uvData)
{
}


Mesh::~Mesh(void)
{
}


void Mesh::constructFromShape(const shape_t &shape)
{
	if(shape.mesh.normals.size() == 0 && shape.mesh.indices.size() > 0)
	{
		printf("Not a LitObject!\n");
		return;
	}
	int n = shape.mesh.positions.size() / 3;
	for(int i = 0; i < n; ++i)
	{
		vertexData.push_back(vec3(shape.mesh.positions[3*i+0], shape.mesh.positions[3*i+1], shape.mesh.positions[3*i+2]));
		if(shape.mesh.normals.size() > 0)
			normalData.push_back(vec3(shape.mesh.normals[3*i+0], shape.mesh.normals[3*i+1], shape.mesh.normals[3*i+2]));
		if(shape.mesh.texcoords.size() > 0)
			uvData.push_back(vec2(shape.mesh.texcoords[3*i+0], shape.mesh.texcoords[3*i+1]));
	}
	
	if(shape.mesh.texcoords.size() == 0)
		makeUpUVData();
	if(shape.mesh.normals.size() == 0)
		calculateNormals();
	if(shape.mesh.indices.size() != 0)
		indexData.setData(shape.mesh.indices);
}

void Mesh::makeUpUVData()
{
	uvData = vector<vec2>(vertexData.size(), vec2(0.0f, 0.0f));
}

void Mesh::clear()
{
	vertexData.clear();
	normalData.clear();
	uvData.clear();
}

void Mesh::addTriangle(const vec3 vert[3])
{
	vertexData.push_back(vert[0]);
	vertexData.push_back(vert[1]);
	vertexData.push_back(vert[2]);
}

void Mesh::addTriangle(const vec3 vert[3], const vec3 nor[3])
{
	vertexData.push_back(vert[0]);
	vertexData.push_back(vert[1]);
	vertexData.push_back(vert[2]);
	normalData.push_back(nor[0]);
	normalData.push_back(nor[1]);
	normalData.push_back(nor[2]);
}

void Mesh::addTriangle(const vec3 vert[3], const vec2 uv[3])
{
	vertexData.push_back(vert[0]);
	vertexData.push_back(vert[1]);
	vertexData.push_back(vert[2]);
	uvData.push_back(uv[0]);
	uvData.push_back(uv[1]);
	uvData.push_back(uv[2]);
}

void Mesh::calculateNormals()
{
	normalData.clear();
	int n = vertexData.size();
	float flip = orientation == GL_CCW ? -1.0f : 1.0f;
	for(int i = 0; i < n; i += 3)
	{
		vec3 normal = -cross(vertexData[i + 1] - vertexData[i], vertexData[i + 2] - vertexData[i]);
		normal = normalize(normal);

		normalData.push_back(flip * normal);
		normalData.push_back(flip * normal);
		normalData.push_back(flip * normal);
	}
}

void Mesh::interpolateNormals()
{
	int n = vertexData.size();
	vector<pair<Vertex, int> > out(n);
	for(int i = 0; i < n; i++)
		out[i] = pair<Vertex, int>(Vertex(vertexData[i]), i);
	sort(out.begin(), out.end());

	int index = 0;
	vec3 interpNor = normalData[out[0].second];
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

		interpNor = vec3(0.0f);
		index = i;
	}
}

bool getSimilarVertexIndex(const Vertex &packed, map<Vertex, unsigned int> &VertexToOutIndex, unsigned int &result)
{
	map<Vertex, unsigned int>::iterator it = VertexToOutIndex.find(packed);
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
	vector<vec3> outVertexData;
	vector<vec3> outNormalData;
	vector<vec2> outUvData;
	vector<unsigned int> outIndexData;

	map<Vertex, unsigned int> VertexToOutIndex;
	bool hasUV = uvData.size() > 0;
	bool hasNormal = normalData.size() > 0;
	const vec3 zero(0.0f);

	unsigned int n = vertexData.size();
	for (unsigned int i = 0; i < n; i++)
	{
		Vertex packed(vertexData[i], hasNormal ? normalData[i] : zero, hasUV ? uvData[i] : vec2(0.0f));

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

	indexData.setData(outIndexData);
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
	if(!((orientation == GL_CCW && ccw(vertexData[0], vertexData[1], vertexData[2]) > 0)
		|| (orientation == GL_CW && ccw(vertexData[0], vertexData[1], vertexData[2]) < 0)))
		flip();
}

const vec3* Mesh::getVertexData() const
{
	return vertexData.data();
}

const vec3* Mesh::getNormalData() const
{
	return normalData.data();
}

const vec2* Mesh::getUVData() const
{
	return uvData.data();
}

const void* Mesh::getIndexData() const
{
	return indexData.getData();
}

unsigned int Mesh::getIndexDataType() const
{
	int n = indexData.size();
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
	return indexData.size();
}

int Mesh::getVertexDataSize() const
{
	return vertexData.size() * sizeof(vertexData[0]);
}

int Mesh::getIndexDataSize() const
{
	return indexData.getSizeInBytes();
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
		swap(vertexData[i], vertexData[i + 1]);
		if(normalData.size())
			swap(normalData[i], normalData[i + 1]);
		if(uvData.size())
			swap(uvData[i], uvData[i + 1]);
	}
}
