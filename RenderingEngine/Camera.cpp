#include "Camera.h"
#include "MathFunctions.h"

using namespace glm;
using namespace mfl;

namespace reng
{
	Camera::Camera(const vec3 position, float aspectRatio, float FoV)
		: position(position), aspectRatio(aspectRatio), FoV(FoV), phix(0), phiy(0)
	{
	}

	Camera::Camera()
	{
	}

	Camera::~Camera(void)
	{
	}

	void Camera::rotate(float yaw, float pitch)
	{
		phix += yaw;
		phiy += pitch;
		if(phiy > pi / 2.f)
			phiy = pi / 2.f;
		if(phiy < -pi / 2.f)
			phiy = -pi / 2.f;
	}

	mat4 Camera::getProjectionMatrix() const
	{
		return perspective(FoV, aspectRatio, 0.1f, 100.0f);
	}

	mat4 Camera::getViewMatrix() const
	{
		vec3 direction = getDirection();
		vec3 right = getRight();
		vec3 up = cross(right, direction);
		return lookAt(position, position + direction, up);
	}

	vec3 Camera::getDirection() const
	{
		return vec3(
			cos(phiy) * sin(phix), 
			sin(phiy),
			cos(phiy) * cos(phix)
			);
	}

	vec3 Camera::getRight() const
	{
		return vec3(
			-cos(phix), 
			0,
			sin(phix)
			);
	}

	vec3 Camera::getUp() const
	{
		return cross(getRight(), getDirection());
	}
}