#include <glm/glm.hpp>

#include "Material.h"
#include "Renderer.h"

Material::Material(MaterialDesc& desc)
{
	renderer = desc.renderer;
	int maxInFlightFrames = renderer->_maxInFlightFrames;

	// Pool
	std::array<VkDescriptorPoolSize, 2> poolSizes{};
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[0].descriptorCount = static_cast<uint32_t>(maxInFlightFrames);
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = static_cast<uint32_t>(maxInFlightFrames);

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(maxInFlightFrames);
	poolInfo.flags = 0; // Optional

	renderer->CreateDescriptorPool(&poolInfo, &descriptorPool);

	// Texture
	textureId = renderer->CreateTextureImage(desc.texturePath);

	// Sets
	renderer->CreateDescriptorSets(descriptorPool, textureId, &descriptorSets);
}

Material::Material(Material& other)
{
	descriptorPool = other.descriptorPool;
	descriptorSets = other.descriptorSets;
	textureId = other.textureId;
	renderer = other.renderer;
}

Material::Material(Material&& other)
{
	descriptorPool = std::move(other.descriptorPool);
	descriptorSets = std::move(other.descriptorSets);
	textureId = other.textureId;
	renderer = other.renderer;
}

Material::~Material()
{
	
}

void Material::Free()
{
	renderer->DestroyDescriptorSets(descriptorPool);
}
