#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(const glm::vec3 _position, float _aspectRatio, float _FoV);
	~Camera(void);

	void update(float distance);
	void rotate(float pitch, float yaw);
	void translate(const glm::vec3 &dir);

	void setPitch(float pitch);
	void setYaw(float yaw);
	void setAspectRatio(float _aspectRatio);
	void setFieldOfView(float _FoV);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

	glm::vec3 getDirection() const;
	glm::vec3 getRight() const;
	glm::vec3 getUp() const;
	glm::vec3 getPosition() const;

private:
	glm::vec3 dir;
	glm::vec3 position;
	float phix, phiy;
	float FoV;
	float aspectRatio;
};

