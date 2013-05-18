#pragma once

#include "Drawable.h"
#include "Updateable.h"
#include "StockCameraHandler.h"

#include <list>
#include <cmath>
#include <memory>

class Engine
{
public:
	Engine(float _updateInterval, int _windowWidth, int _windowHeight);
	~Engine();

	static void useStockCamera(const glm::vec3 &position, const glm::vec3 &direction, float FoV);
	static void setCamera(std::shared_ptr<CameraHandler> _cam);

	static void addToDisplayList(std::shared_ptr<Drawable> d);
	static void addToUpdateList(std::shared_ptr<Updateable> u);

	static void initialize();
	static void start();
	static void stop();

	static void enableMode(GLenum mode);
	static void disableMode(GLenum mode);
	static void setBufferClearMask(GLbitfield _mask);
	static void setBackgroundColor(glm::vec4 color);

	static glm::mat4 getViewProjectionMatrix();

private:
	static void initalizeLists();

	static void renderingLoop();
	static inline void nextFrame();

	static std::list<std::shared_ptr<Drawable> > displayList;
	static std::list<std::shared_ptr<Updateable> > updateList;
	static std::shared_ptr<CameraHandler> cam;

	static int windowWidth, windowHeight;
	static float updateInterval;
	static GLbitfield mask;
	static glm::vec4 backgroundColor;
};