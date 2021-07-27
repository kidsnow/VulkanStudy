#include "VKApplication.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>

VKApplication::VKApplication() :
	m_windowWidth(800),
	m_windowHeight(600)
{
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

VKApplication::~VKApplication()
{
}

void VKApplication::initWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "Vulkan", nullptr, nullptr);
}

void VKApplication::initVulkan()
{
	enumerateLayerProperty();
	createInstance();
}

void VKApplication::mainLoop()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
	}
}

void VKApplication::cleanup() {
	vkDestroyInstance(m_instance, nullptr);
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void VKApplication::enumerateLayerProperty()
{
	uint32_t instanceLayerCount;
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);

	VkLayerProperties* layerProperties = new VkLayerProperties[instanceLayerCount];
	vkEnumerateInstanceLayerProperties(&instanceLayerCount, layerProperties);

	for (int i = 0; i < instanceLayerCount; i++)
	{
		std::cout << "----------" << layerProperties[i].layerName << "----------" << std::endl;

		uint32_t instanceExtensionCount;
		vkEnumerateInstanceExtensionProperties(layerProperties[i].layerName, &instanceExtensionCount, nullptr);

		VkExtensionProperties* instanceExtensions = new VkExtensionProperties[instanceExtensionCount];
		vkEnumerateInstanceExtensionProperties(layerProperties[i].layerName, &instanceExtensionCount, instanceExtensions);
		for (int i = 0; i < instanceExtensionCount; i++)
		{
			std::cout << instanceExtensions[i].extensionName << std::endl;
		}
	}
}

void VKApplication::createInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}