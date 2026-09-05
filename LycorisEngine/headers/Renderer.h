#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <optional>
#include <iostream>

#include "pch.h"
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

struct ObjectPushConstants
{
	glm::mat4 model;
};

struct MeshBuffer {
	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkDeviceSize vertexBufferSize;
	std::vector<uint32_t> vertexBufferOffsets;
	std::vector<VkDeviceSize> vertexRegionsSize;

	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;
	VkDeviceSize indexBufferSize;
	std::vector<uint32_t> indexBufferOffsets;
	std::vector<VkDeviceSize> indexRegionsSize;

	MeshBuffer() {
		vertexBufferOffsets.push_back(0);
		indexBufferOffsets.push_back(0);
	}
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

	void CreateTextureSampler();

	void CreateMeshBuffers();
	void CreateUniformBuffers();


	void CreateCommandBuffers();
	void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::vector<RenderData>& data);
	void CreateSyncObjects();

	void ClearSwapChain();
	void RecreateSwapChain();

public:
	void DrawFrame(std::vector<RenderData>& data, glm::mat4 viewMatrix, glm::vec3 lightDirection, glm::vec3 lightColor);

private:

	void UpdateUniformBuffer(uint32_t currentImage, glm::mat4 viewMatrix, glm::vec3 lightDirection, glm::vec3 lightColor);

	void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size, VkDeviceSize srcOffset = 0, VkDeviceSize dstOffset = 0);

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

public:
	// Return the ID of the MeshRef
	uint8_t FillGeometryBuffer(MeshType bufferId, MeshData& mesh);

	void CreateDescriptorPool(VkDescriptorPoolCreateInfo* poolInfo, VkDescriptorPool* pool);
	void CreateDescriptorSets(VkDescriptorPool& pool, int imgId, std::vector<VkDescriptorSet>* sets);

	void DestroyDescriptorSets(VkDescriptorPool& pool);

	int CreateTextureImage(const char* path);

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
	VkPipelineLayout _pipelineLayout;
	VkPipeline _graphicsPipeline;

	VkCommandPool _mainCommandPool;
	VkCommandPool _transientCommandPool;
	std::vector<VkCommandBuffer> _commandBuffers;

	VkDescriptorSetLayout _descriptorsLayout;

	// Vertex Buffers
	std::vector<MeshBuffer> _meshBuffers;

	// Uniorm Buffers
	std::vector<VkBuffer> _uniformBuffers;
	std::vector<VkDeviceMemory> _uniformBuffersMemory;
	std::vector<void*> _uniformBuffersMapped;

	//VkDescriptorPool _descriptorPool;
	//std::vector<VkDescriptorSet> _descriptorSets;

	// Texture
	std::vector<VkImage> _textureImages;
	std::vector<VkDeviceMemory> _textureImagesMemory;
	std::vector<VkImageView> _textureImagesViews;
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

public:
	const int _maxInFlightFrames = 2;

private:
	uint32_t _currentFrame = 0;

	bool _framebufferResized = false;
};

