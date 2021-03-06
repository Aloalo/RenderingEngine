#include "Sphere.h"

using namespace glm;
using namespace std;

namespace reng
{
	float Sphere::radius = 0.0f;

	vector<vec3>* Sphere::generate(int depth, float r, const vec3 &center)
	{
		radius = r;
		const float X(0.525731112119133606f * radius);
		const float Z(0.850650808352039932f * radius);

		vec3 vdata[12] =
		{    
			glm::vec3(-X, 0.0, Z), glm::vec3(X, 0.0, Z), glm::vec3(-X, 0.0, -Z), glm::vec3(X, 0.0, -Z),    
			glm::vec3(0.0, Z, X), glm::vec3(0.0, Z, -X), glm::vec3(0.0, -Z, X), glm::vec3(0.0, -Z, -X),    
			glm::vec3(Z, X, 0.0), glm::vec3(-Z, X, 0.0), glm::vec3(Z, -X, 0.0), glm::vec3(-Z, -X, 0.0) 
		};
		unsigned int tindices[20][3] =
		{ 
			{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
			{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
			{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
			{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
		};

		vector<vec3> *out = new vector<vec3>();
		for(int i = 0; i < 20; i++)
			subdivide(vdata[tindices[i][0]], vdata[tindices[i][1]], vdata[tindices[i][2]], depth, *out);

		return out;
	}

	void Sphere::subdivide(const vec3 &a, const vec3 &b, const vec3 &c, 
		int depth, vector<vec3> &out)
	{
		if (depth == 0) 
		{
			out.push_back(a);
			out.push_back(b);
			out.push_back(c);
			return;
		}

		vec3 ab = normalize(a + b) * radius;
		vec3 bc = normalize(b + c) * radius;
		vec3 ca = normalize(c + a) * radius;

		subdivide(a, ab, ca, depth-1, out);
		subdivide(b, bc, ab, depth-1, out);
		subdivide(c, ca, bc, depth-1, out);
		subdivide(ab, bc, ca, depth-1, out);
	}
}