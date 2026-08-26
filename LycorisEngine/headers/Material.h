#pragma once

struct Material {
	int _descriptorOffset; // Offset of the uniform in the descriptor // WIP
	VkPipeline* _pipeline; // hum.. gotta need a pch at some point ig? // WIP
};