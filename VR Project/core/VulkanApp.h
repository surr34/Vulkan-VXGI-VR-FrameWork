#pragma once

#include "VulkanDebug.h"
#include "VulkanQueue.h"
#include "VulkanSwapChain.h"

#include "Vertex.h"
#include "PostProcess.h"
#include "../assets/Material.h"
#include "../assets/Geometry.h"

#include "../actors/Camera.h"
#include "../actors/Light.h"


#include <sstream>



static bool leftMouseDown = false;
static bool rightMouseDown = false;
static bool middleMouseDown = false;

static double previousX = 0.0;
static double previousY = 0.0;

static double oldTime = 0.0;
static double currentTime = 0.0;
static int fps = 0;
static int fpstracker = 0;



static std::string convertToString(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

static std::string convertToString(double number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

static Camera camera;

class VulkanApp
{
public:
	VulkanApp();
	~VulkanApp();

	void initVulkan();
	void initWindow();

	void createInstance();

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void setupDebugCallback();


	void createSurface();

	void pickPhysicalDevice();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void createLogicalDevice();
	
	//QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	
	void createSwapChain();
	void reCreateSwapChain();
	void cleanUpSwapChain();

	void createImageViews();	

	void createFramebuffers();
	void createFrameBufferRenderPass();
	void createFrameBufferCommandPool();
	void createFrameBufferCommandBuffers();

	void createFramebufferDescriptorSetLayout();
	void createFramebufferDescriptorPool();
	void createFramebufferDescriptorSet();


	void createGbuffers();
	void createSceneBuffer();

	void createDeferredFramebuffer();

	void createDeferredRenderPass();
	void createDeferredCommandPool();
	void createDeferredCommandBuffers();

	void drawFrame();

	void createSemaphores();

	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

	VkCommandBuffer beginSingleTimeCommands(VkCommandPool commandPool);
	void endSingleTimeCommands(VkCommandPool commandPool, VkCommandBuffer commandBuffer, VkQueue queue);

	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, VkCommandPool commandPool);
	void createDepthResources();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VkFormat findDepthFormat();

	bool hasStencilComponent(VkFormat format);

	void run();
	
	void updateUniformBuffers();

	void mainLoop();

	void cleanUp();

	VkDevice getDevice()
	{
		return device;
	}
	

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location,	int32_t code, const char* layerPrefix, const char* msg,	void* userData);
	
	

private:	
	GLFWwindow* window;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;

	//This object will be implicitly destroyed
	VkPhysicalDevice physicalDevice;
	VkDevice device;

	VkQueue objectDrawQueue;

	VkQueue lightingQueue;

	VkQueue postProcessQueue;

	VkQueue presentQueue;

	VkSurfaceKHR surface;

	VkSwapchainKHR swapChain;

	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;


	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	
	VkRenderPass frameBufferRenderPass;
	VkCommandPool frameBufferCommandPool;
	std::vector<VkCommandBuffer> frameBufferCommandBuffers;

	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;


	LightingMaterial* lightingMaterial;

	HDRHighlightMaterial* hdrHighlightMaterial;

	BlurMaterial *horizontalMaterial;
	BlurMaterial *verticalMaterial;

	singleTriangular* offScreenPlane;

	singleTriangular* offScreenPlaneforPostProcess;

	singleQuadral* debugDisplayPlane;

	std::vector<DebugDisplayMaterial*> debugDisplayMaterials;

	LastPostProcessgMaterial* lastPostProcessMaterial;
	FinalRenderingMaterial* frameBufferMaterial;

	VkRenderPass deferredRenderPass;
	VkCommandPool deferredCommandPool;
	VkCommandBuffer deferredCommandBuffer;
	VkFramebuffer deferredFrameBuffer;

	std::vector<VkImage> gBufferImages;
	std::vector<VkDeviceMemory> gBufferImageMemories;
	std::vector<VkImageView>  gBufferImageViews;


	VkImage sceneImage;
	VkDeviceMemory sceneImageMemories;
	VkImageView sceneImageView;

	VkSemaphore objectDrawSemaphore;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore postProcessSemaphore;
	VkSemaphore renderFinishedSemaphore;
	

	uint32_t WIDTH;
	uint32_t HEIGHT;

	uint32_t LayerCount;

	std::vector<DirectionalLight> directionLights;

	std::vector<PostProcess*> postProcessStages;

	//for FrameRender
	PostProcess* sceneStage;
	PostProcess* theLastPostProcess;
	
};

