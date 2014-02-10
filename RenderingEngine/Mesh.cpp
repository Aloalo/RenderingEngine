#include <GL/glew.h>
#include <map>
#include <algorithm>
#include <exception>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "MathFunctions.h"
#include "Vertex.h"

using namespace std;
using namespace glm;
using namespace mfl;

namespace reng
{
	Mesh::Mesh(void)
		: orientation(GL_CCW)
	{
	}

	Mesh::Mesh(const aiMesh *mesh)
		: orientation(GL_CCW)
	{
		constructFromaiMesh(mesh);
	}

	Mesh::Mesh(const vector<vec3> &_vertexData, const vector<vec3> &_normalData, const vector<vec2> &_uvData)
		: vertexData(_vertexData), normalData(_normalData), uvData(_uvData), orientation(GL_CCW)
	{
	}


	Mesh::~Mesh(void)
	{
	}


	void Mesh::constructFromaiMesh(const aiMesh *mesh)
	{
		vector<unsigned int> indices;
		for(int i = 0; i < mesh->mNumFaces; ++i)
			for(int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
				indices.push_back(mesh->mFaces[i].mIndices[j]);
		indexData.setData(indices);

		for(int i = 0; i < mesh->mNumVertices; ++i)
		{
			vertexData.push_back(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			normalData.push_back(vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			if(mesh->HasTextureCoords(0))
				uvData.push_back(vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		}
		if(uvData.empty())
			makeUpUVData();
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
		int n = vertexData.size();
		int k = indexData.size();
		float flip = orientation == GL_CCW ? 1.0f : -1.0f;

		if(k == 0)
		{
			normalData.clear();
			for(int i = 0; i < n; i += 3)
			{
				vec3 normal = cross(vertexData[i + 1] - vertexData[i], vertexData[i + 2] - vertexData[i]);
				normal = normalize(normal);

				normalData.push_back(flip * normal);
				normalData.push_back(flip * normal);
				normalData.push_back(flip * normal);
			}
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
			interpNor = normalize(interpNor);

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
}