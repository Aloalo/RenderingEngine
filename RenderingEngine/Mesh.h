#pragma once

#include "PackedVertex.h"
#include "IndexContainer.h"

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<glm::vec3> &_vertexData);
	Mesh(const std::vector<glm::vec3> &_vertexData,
		const std::vector<glm::vec3> &_normalData);
	Mesh(const std::vector<glm::vec3> &_vertexData,
		const std::vector<glm::vec3> &_normalData,
		const std::vector<glm::vec2> &_uvData);
	~Mesh(void);

	void clear();
	void addTriangle(const glm::vec3 vert[3]);
	void addTriangle(const glm::vec3 vert[3], const glm::vec3 nor[3]);

	void calculateNormals();
	void interpolateNormals();
	void applyIndexing();
	void flipOrientation();

	void setOrientation(unsigned int _orientation);

	const glm::vec3* getVertexData() const;
	const glm::vec3* getNormalData() const;
	const glm::vec2* getUVData() const;
	const void* getIndexData() const;

	int numOfVertices() const;
	int numOfNormals() const;
	int numOfUVs() const;
	int numOfIndices() const;
	unsigned int getIndexDataType() const;

	int getVertexDataSize() const;
	int getIndexDataSize() const;
	int getUVDataSize() const;
	int getNormalDataSize() const;

private:
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec3> normalData;
	std::vector<glm::vec2> uvData;

	IndexContainer *indexData;

	unsigned int orientation;
};

