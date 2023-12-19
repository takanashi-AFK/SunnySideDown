#include "AssimpLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <d3d11.h>
#include <filesystem>

bool AssimpLoader::Load(ImportSettings *setting)
{
	Assimp::Importer importer;

	auto& meshes = setting->meshes;
	auto inverseU = setting->inverseU;
	auto inverseV = setting->inverseV;
    
	string path = (setting->filename);

    int flag = 0;

    flag |= aiProcess_Triangulate;
    flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;

    const aiScene* scene = importer.ReadFile(path, flag);
    if (scene == nullptr)
    {
        MessageBox(nullptr, importer.GetErrorString(), "Error!!", 0);
	    return false;
    }

    meshes.clear();
    meshes.resize(scene->mNumMeshes);
    for (size_t i = 0; i < meshes.size(); ++i)
    {
        const auto pMesh = scene->mMeshes[i];
        LoadMesh(meshes[i], pMesh, inverseU, inverseV);
        const auto pMaterial = scene->mMaterials[i];
        LoadTexture(setting->filename, meshes[i], pMaterial);
    }

    scene = nullptr;

    return true;
}

void AssimpLoader::LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV)
{
    aiVector3D zero3D(0.0f, 0.0f, 0.0f);
    aiColor4D zeroColor(0.0f, 0.0f, 0.0f, 0.0f);

    dst.Vertices.resize(src->mNumVertices);
    dst.Indices.resize(src->mNumFaces * 3);

    for (unsigned int i = 0; i < src->mNumVertices; ++i)
    {
        auto position = &(src->mVertices[i]);
        auto normal = &(src->mNormals[i]);
        auto uv = (src->HasTextureCoords(0)) ? &(src->mTextureCoords[0][i]) : &zero3D;
        auto tangent = (src->HasTangentsAndBitangents()) ? &(src->mTangents[i]) : &zero3D;
        auto color = (src->HasVertexColors(0)) ? &(src->mColors[0][i]) : &zeroColor;

        // ���]�I�v�V��������������UV�𔽓]������
        if (inverseU)
        {
            uv->x = 1 - uv->x;
        }
        if (inverseV)
        {
            uv->y = 1 - uv->y;
        }

        Vertex vertex = {};
        vertex.Position = DirectX::XMFLOAT3(position->x, position->y, position->z);
        vertex.Normal = DirectX::XMFLOAT3(normal->x, normal->y, normal->z);
        vertex.UV = DirectX::XMFLOAT2(uv->x, uv->y);
        vertex.Tangent = DirectX::XMFLOAT3(tangent->x, tangent->y, tangent->z);
        vertex.Color = DirectX::XMFLOAT4(color->r, color->g, color->b, color->a);

        dst.Vertices[i] = vertex;
        for (unsigned int j = 0u; j < src->mNumFaces; ++j)
        {
            const auto& face = src->mFaces[j];

            dst.Indices[j * 3 + 0] = face.mIndices[0];
            dst.Indices[j * 3 + 1] = face.mIndices[1];
            dst.Indices[j * 3 + 2] = face.mIndices[2];
        }
    }

}

void AssimpLoader::LoadTexture(const string filename, Mesh& dst, const aiMaterial* src)
{
    aiString path;
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    if (src->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
    {
        char dir[MAX_PATH];
        _splitpath_s(filename.c_str(), nullptr, 0, dir, MAX_PATH, nullptr, 0, nullptr, 0);
    }
    else dst.DiffuseMap.clear();
}
