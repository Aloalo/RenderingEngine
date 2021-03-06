#pragma once

#include "InputObserver.h"
#include "Camera.h"
#include "Updateable.h"

namespace reng
{
	class CameraHandler :
		public InputObserver, public Updateable
	{
	public:
		CameraHandler(const Camera &cam);
		virtual ~CameraHandler(void);

		virtual glm::mat4 getProjectionMatrix() const = 0;
		virtual glm::mat4 getViewMatrix() const = 0;
		const glm::vec3& getPosition() const;

		Camera cam;
	};
}
