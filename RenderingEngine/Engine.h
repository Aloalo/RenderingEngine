#pragma once

#include <GL/glew.h>
#include <list>
#include <cmath>
#include "Drawable.h"
#include "Updateable.h"
#include "StockCameraHandler.h"

#include "Renderer.h"
#include "Mesh.h"
#include "TextureHandler.h"
#include <GLFW/glfw3.h>

namespace reng
{
	class Engine
	{
	public:
		Engine(float _updateInterval, int _windowWidth, int _windowHeight);
		~Engine();

		static void useStockCamera(const glm::vec3 &position, const glm::vec3 &direction, float FoV, float cameraSpeed);
		static void setCamera(CameraHandler *_cam);
		static CameraHandler* getCamera();
		static Renderer& getRenderer();
		static void setWindowTitle(const char *name);

		static void addToDisplayList(Drawable *d);

		static void addToUpdateList(Updateable *u);
		static void addLight(Light *light);

		static void start();
		static void stop();

		static void enableVsync(bool on);
		static void enableMode(GLenum mode);
		static void disableMode(GLenum mode);
		static void setBufferClearMask(GLbitfield _mask);
		static void setBackgroundColor(glm::vec4 color);

		static glm::mat4 getProjectionMatrix();
		static glm::mat4 getViewMatrix();
		static void getWindowSize(int &width, int &height);
		static void setWindowSize(int width, int height);
		static GLFWwindow* getWindow();

		static void hideMouse(bool hide);

	private:
		static void initialize();
		static void renderingLoop();
		static inline void nextFrame();
		static void displayFPS();

		static Renderer renderer;
		static std::list<Updateable*> updateList;
		static CameraHandler *cam;
		static GLFWwindow *window;

		static int windowWidth, windowHeight;
		static float updateInterval;
		static GLbitfield mask;
		static glm::vec4 backgroundColor;
		static char winTitle[150];

		TextureHandler texHandler;
	};
}