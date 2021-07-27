#pragma once

#include <vulkan/vulkan.h>

class GLFWwindow;

class VKApplication
{
public:
	VKApplication();
	~VKApplication();

	void Run();

private:
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

	void enumerateLayerProperty();
	void createInstance();

private:
	int m_windowWidth, m_windowHeight;
	GLFWwindow* m_window;
	VkInstance m_instance;
};