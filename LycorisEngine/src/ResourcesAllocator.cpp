#include <iostream>
#include <glm/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "ResourcesAllocator.h"
#include "Renderer.h"

ResourcesAllocator::ResourcesAllocator(Renderer* renderer) : _renderer(renderer)
{
}

ResourcesAllocator::~ResourcesAllocator()
{
}

MeshRef& ResourcesAllocator::LoadMesh(const std::string path, const std::string name, MeshType type, std::unordered_map<std::string, MeshRef>& dest)
{
    if (dest.contains(name))
        return dest.find(name)->second;

    auto [it, inserted] = dest.try_emplace(name);
    MeshRef& meshRef = it->second;

    if (false == inserted)
        throw std::runtime_error("failed to insert mesh");

    MeshData meshData;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        throw std::runtime_error(err);
    }

    std::unordered_map<Vertex, uint32_t> uniqueVertices{};

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};

            vertex.pos = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            vertex.texCoord = {
                attrib.texcoords[2 * index.texcoord_index + 0],
                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };

            vertex.color = { 1.0f, 1.0f, 1.0f };

            if (uniqueVertices.count(vertex) == 0) {
                uniqueVertices[vertex] = static_cast<uint32_t>(meshData.vertices.size());
                meshData.vertices.push_back(vertex);
            }

            meshData.indices.push_back(uniqueVertices[vertex]);
        }
    }


    meshRef.type = type;
    meshRef.id = _renderer->FillGeometryBuffer(type, meshData);

    return meshRef;
}
