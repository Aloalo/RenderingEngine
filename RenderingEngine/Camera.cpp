#include "Camera.h"

#include "MathFunctions.h"

Camera::Camera(const glm::vec3 _position, float _aspectRatio, float _FoV)
	: position(_position), aspectRatio(_aspectRatio), FoV(_FoV)
{
	phix = phiy = 0.0;
	dir = glm::vec3(0., 0., 0.);
}


Camera::~Camera(void)
{
}

void Camera::update(float distance)
{
	glm::vec3 direction = getDirection();
	glm::vec3 right = getRight();
	glm::vec3 up = glm::cross(right, direction);
	position += (direction * dir.z + up * dir.y + right * dir.x) * distance;
}

void Camera::rotate(float pitch, float yaw)
{
	phix += pitch;
	phiy += yaw;
	if(phiy > MathFunctions::pi / 2.)
		phiy = MathFunctions::pi / 2.;
	if(phiy < -MathFunctions::pi / 2.)
		phiy = -MathFunctions::pi / 2.;
}

void Camera::translate(const glm::vec3 &_dir)
{
	dir += _dir;
}

void Camera::setAspectRatio(float _aspectRatio)
{
	aspectRatio = _aspectRatio;
}

void Camera::setFieldOfView(float _FoV)
{
	FoV = _FoV;
}

void Camera::setPitch(float pitch)
{
	phix = pitch;
}

void Camera::setYaw(float yaw)
{
	phiy = yaw;
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(FoV, aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() const
{
	glm::vec3 direction = getDirection();
	glm::vec3 right = getRight();
	glm::vec3 up = glm::cross(right, direction);
	return glm::lookAt(position, position + direction, up);
}

glm::vec3 Camera::getDirection() const
{
	return glm::vec3(
		cos(phiy) * sin(phix), 
		sin(phiy),
		cos(phiy) * cos(phix)
		);
}

glm::vec3 Camera::getRight() const
{
	return glm::vec3(
		sin(phix - MathFunctions::pi/2.0f), 
		0,
		cos(phix - MathFunctions::pi/2.0f)
		);
}

glm::vec3 Camera::getUp() const
{
	return glm::cross(getRight(), getDirection());
}

glm::vec3 Camera::getPosition() const
{
	return position;
}
