#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	Camera(const glm::vec3 _position, float _aspectRatio, float _FoV);
	~Camera(void);

	void update(float distance);
	void rotate(float yaw, float pitch);
	void translate(const glm::vec3 &dir);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

	void setDirection(const glm::vec3 &direction);

	glm::vec3 getDirection() const;
	glm::vec3 getRight() const;
	glm::vec3 getUp() const;

	glm::vec3 position;
	float phix, phiy;
	float FoV;
	float aspectRatio;
	glm::vec3 dir;
};

