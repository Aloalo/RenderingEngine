#pragma once

#include "Drawable.h"
#include "Updateable.h"
#include "StockCameraHandler.h"

#include <list>
#include <cmath>
#include <memory>
#include "Renderer.h"

class Engine
{
public:
	Engine(float _updateInterval, int _windowWidth, int _windowHeight);
	~Engine();

	static void useStockCamera(const glm::vec3 &position, const glm::vec3 &direction, float FoV);
	static void setCamera(std::shared_ptr<CameraHandler> _cam);
	static std::shared_ptr<CameraHandler> getCamera();
	static Renderer& getRenderer();

	static void addToDisplayList(std::shared_ptr<Drawable> &d);
	static void addToUpdateList(std::shared_ptr<Updateable> &u);
	static void addLight(std::shared_ptr<Light> &light);

	static void start();
	static void stop();

	static void enableMode(GLenum mode);
	static void disableMode(GLenum mode);
	static void setBufferClearMask(GLbitfield _mask);
	static void setBackgroundColor(glm::vec4 color);

	static glm::mat4 getProjectionMatrix();
	static glm::mat4 getViewMatrix();

private:
	static void initialize();

	static void renderingLoop();
	static inline void nextFrame();

	static Renderer renderer;
	static std::list<std::shared_ptr<Updateable> > updateList;
	static std::shared_ptr<CameraHandler> cam;

	static int windowWidth, windowHeight;
	static float updateInterval;
	static GLbitfield mask;
	static glm::vec4 backgroundColor;
};