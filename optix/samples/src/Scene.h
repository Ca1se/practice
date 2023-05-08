#pragma once

#include <vector>
#include <memory>

#include "Aabb.h"
#include "Camera.h"
#include "CudaBufferView.h"
#include "CudaDeviceBuffer.h"
#include "cuda/PbrMaterial.h"
#include "Matrix.h"

struct Scene
{
    struct Instance
    {
        Matrix<4, 4> transform;
        Aabb         aabb;
        uint32_t     mesh_index;
    };

    struct Mesh
    {
        std::vector<CudaTriangleIndexBufferView> indices;
        std::vector<CudaBufferView<float3>>      positions;
        std::vector<CudaBufferView<float3>>      normals;
        std::vector<CudaBufferView<float2>>      texcoords;
        std::vector<CudaBufferView<float4>>      colors;
        std::vector<int32_t>                     material_indices;
        Aabb                                     aabb;
    };

    std::vector<Camera>                    cameras   = {};
    std::vector<std::shared_ptr<Mesh>>     meshes    = {};
    std::vector<std::shared_ptr<Instance>> instances = {};
    std::vector<PbrMaterial>               materials = {};
    std::vector<cudaArray_t>               images    = {};
    std::vector<cudaTextureObject_t>       textures  = {};
    Aabb                                   aabb      = {};

    std::vector<CudaDeviceBuffer> buffers = {};

    static void loadFromGltf(Scene& scene, const std::string& filename);
    static void cleanup(Scene& scene);
};