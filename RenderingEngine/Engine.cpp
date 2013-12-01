#include "Engine.h"
#include "Input.h"
#include "LitTriangleMesh.h"

int Engine::windowWidth = 1024;
int Engine::windowHeight = 768;
float Engine::updateInterval = 1. / 60.;
std::shared_ptr<CameraHandler> Engine::cam;
Renderer Engine::renderer;
std::list<std::shared_ptr<Updateable> > Engine::updateList;
GLbitfield Engine::mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
glm::vec4 Engine::backgroundColor = glm::vec4(0.4);
char Engine::winTitle[150];
GLFWwindow *Engine::window = NULL;


Engine::Engine(float _updateInterval, int _windowWidth, int _windowHeight)
{
	cam = NULL;
	updateInterval = _updateInterval;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
	initialize();
}

Engine::~Engine()
{
	stop();
}


void Engine::stop()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Engine::useStockCamera(const glm::vec3 &position, const glm::vec3 &direction, float FoV, float cameraSpeed)
{
	Camera c(position, (float) windowWidth / (float) windowHeight, FoV);
	glm::vec3 d = glm::normalize(direction);

	float phiy = asin(d.y);
	float phix = atan2(d.x, d.z);
	c.rotate(phix, phiy);

	cam = std::shared_ptr<CameraHandler>(new StockCameraHandler(c, cameraSpeed, 0.0025f));
	Input::addInputObserver(std::shared_ptr<InputObserver>(cam));
	addToUpdateList(std::shared_ptr<Updateable>(cam));
}

void Engine::setCamera(std::shared_ptr<CameraHandler> _cam)
{
	cam = _cam;
}

void Engine::addToDisplayList(std::shared_ptr<Drawable> &d)
{
	renderer.addObject(d);
}

void Engine::addToDisplayList(Mesh *mesh, const Material &mat, const glm::mat4 &modelMatrix)
{
	addToDisplayList(std::shared_ptr<Drawable>(new LitTriangleMesh(mesh, mat, modelMatrix)));
}

void Engine::addToUpdateList(std::shared_ptr<Updateable> &u)
{
	u->initState();
	updateList.push_back(u);
}

void Engine::start()
{
	renderingLoop();
}

void Engine::initialize()
{
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(windowWidth, windowHeight, "", NULL, NULL);
	glfwMakeContextCurrent(window);

	if(!window)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		glfwTerminate();
		exit(-1);
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		exit(-1);
	}

	memset(winTitle, 0, sizeof(winTitle));
}

void Engine::enableMode(GLenum mode)
{
	glEnable(mode);
}

void Engine::disableMode(GLenum mode)
{
	glDisable(mode);
}

void Engine::setBufferClearMask(GLbitfield _mask)
{
	mask = _mask;
}

void Engine::renderingLoop()
{
	while(!glfwWindowShouldClose(window))
		nextFrame();
}

inline void Engine::displayFPS()
{
	static double lastTime = glfwGetTime();
	static int frameCount = 0;

	frameCount++;
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	if(deltaTime > 1.0f)
	{
		char title[100];
		sprintf(title, "%s, FPS: %f", Engine::winTitle, (float)frameCount / deltaTime);
		glfwSetWindowTitle(window, title);
		lastTime = currentTime;
		frameCount = 0;
	}
}

inline void Engine::nextFrame()
{
	displayFPS();
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;

	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
	glClear(mask);
	
	for(std::list<std::shared_ptr<Updateable> >::iterator i = updateList.begin(); i != updateList.end(); i++)
	{
		if(*i == NULL)
			updateList.erase(i);
		(*i)->update(deltaTime);
	}

	glm::mat4 ViewMatrix = cam ? cam->getViewMatrix() : glm::mat4(1.0f);
	glm::mat4 ProjectionMatrix = cam ? cam->getProjectionMatrix() : glm::mat4(1.0f);

	renderer.draw(ViewMatrix, ProjectionMatrix);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Engine::setBackgroundColor(glm::vec4 color)
{
	backgroundColor = color;
}

glm::mat4 Engine::getProjectionMatrix()
{
	return cam->getProjectionMatrix();
}

glm::mat4 Engine::getViewMatrix()
{
	return cam->getViewMatrix();
}

void Engine::addLight(std::shared_ptr<Light> &light)
{
	renderer.addLight(light);
}

std::shared_ptr<CameraHandler>& Engine::getCamera()
{
	return cam;
}

Renderer& Engine::getRenderer()
{
	return renderer;
}

void Engine::setWindowTitle(const char *name)
{
	strcpy(winTitle, name);
}

void Engine::getWindowSize(int &width, int &height)
{
	width = windowWidth;
	height = windowHeight;
}

GLFWwindow* Engine::getWindow()
{
	return window;
}

void Engine::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}
