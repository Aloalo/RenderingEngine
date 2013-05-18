#pragma once

#include "MathFunctions.h"
#include <vector>

class IndexedSphere
{
public:
	IndexedSphere(int _slices, int _stacks, float _radius);
	~IndexedSphere(void);

	const glm::vec3* getVertexArray() const;
	std::vector<glm::vec3>& getVertexVector();
	const unsigned short* getIndexArray() const;

	int getVertexArraySize() const;
	int getIndexArraySize() const;
	int getNumberOfVertices() const;
	int getNumberOfIndices() const;
	int numberOfTriangles() const;
	float getRadius() const;

private:
	void generate();

	int slices;
	int stacks;
	float radius;

	std::vector<glm::vec3> sphere;
	unsigned short *sphereid;
	int numberOfVertices;
	int numberOfIndices;
};