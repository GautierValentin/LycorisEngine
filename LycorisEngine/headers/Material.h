#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

class Renderer;

struct MaterialDesc {
	Renderer* renderer;
	const char* texturePath;
};

struct Material {
public:
	Material() {}; // Need a default constructor for some reason (needed in MeshRenderer)
	Material(MaterialDesc& desc);
	Material(Material& other);
	Material(Material&& other);
	~Material();

public:
	Material& operator=(Material& other) = default;
	Material& operator=(Material&& other) = default;

public:
	void Free();

public:
	int textureId;
	
public:
	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	Renderer* renderer;
};