#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>

#include "Scene.h"

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

public:
	int Init(GLFWwindow* window);
	int InitVulkan();

	int UnInit();

	void Tick();

private:
	int CreateVkInstance();
	void CreateSurface();
	bool CheckValidationLayerSupport();
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
	void CreateLogicalDevice();

	void CreateSwapChain();
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	void CreateImageViews();
	void CreateRenderPass();

	void CreateDescriptorSetLayout();

	void CreateGraphicsPipeline();
	VkShaderModule CreateShaderModule(const std::vector<char>& code);

	void CreateFrameBuffers();
	void CreateCommandPools();

	void CreateDepthResources();
	VkFormat FindDepthFormat();
	bool HasStencilComponent(VkFormat format);

	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();

	void CreateVertexBuffer();
	void CreateVertexIndexBuffer();
	void CreateUniformBuffers();

	void CreateDescriptorPool();
	void CreateDescriptorSets();

	void CreateCommandBuffers();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void CreateSyncObjects();

	void ClearSwapChain();
	void RecreateSwapChain();

public:
	void FillGeometryBuffers(Mesh& mesh);

private:
	void DrawFrame();

	void UpdateUniformBuffer(uint32_t currentImage);

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	VkCommandBuffer BeginSingleTimeCommands();
	void EndSingleTimeCommands(VkCommandBuffer commandBuffer);

	void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	void CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

	uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

	static std::vector<char> ReadFile(const std::string& filename);

private:
	GLFWwindow* _win;
	VkInstance _instance;

	VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
	VkDevice _device; // Logial device

	VkSurfaceKHR _surface;

	VkQueue _graphicsQueue;
	VkQueue _presentQueue;

	VkSwapchainKHR _swapChain;
	std::vector<VkImage> _swapChainImages;
	std::vector<VkImageView> _swapChainImageViews;
	std::vector<VkFramebuffer> _swapChainFramebuffers;
	VkFormat _swapChainImageFormat;
	VkExtent2D _swapChainExtent;

	VkRenderPass _renderPass;
	VkDescriptorSetLayout _descriptorSetLayout;;
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	VkCommandPool _mainCommandPool;
	VkCommandPool _transientCommandPool;
	std::vector<VkCommandBuffer> _commandBuffers;

	// Vertetx Buffers
	VkBuffer _vertexBuffer;
	VkDeviceMemory _vertexBufferMemory;
	VkBuffer _indexBuffer;
	VkDeviceMemory _indexBufferMemory;

	// Uniorm Buffers
	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;
	std::vector<void*> _uniformBuffersMapped;

	VkDescriptorPool _descriptorPool;
	std::vector<VkDescriptorSet> _descriptorSets;

	// Texture
	VkImage _textureImage;
	VkDeviceMemory _textureImageMemory;
	VkImageView _textureImageView;
	VkSampler _textureSampler;

	// Depth
	VkImage _depthImage;
	VkDeviceMemory _depthImageMemory;
	VkImageView _depthImageView;

private:
	std::vector<VkSemaphore> _imageAvailableSemaphores;
	std::vector<VkSemaphore> _renderFinishedSemaphores;
	std::vector<VkFence> _inFlightFences;

private:
#ifdef NDEBUG
	const bool _enableValidationLayers = false;
#else
	const bool _enableValidationLayers = true;
#endif
	const std::vector<const char*> _validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

private:
	const std::vector<const char*> _deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

private:
	const int _maxInFlightFrames = 2;

	uint32_t _currentFrame = 0;

	bool _framebufferResized = false;
};

