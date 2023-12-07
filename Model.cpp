#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <d3d11.h>
#include <filesystem>
bool Model::Load(ImportSettings setting)
{
	Assimp::Importer importer;

	auto& meshes = setting.meshes;
	auto inverseU = setting.inverseU;
	auto inverseV = setting.inverseV;

	string path = ("PathIsHere");
    int flag = 0;

    flag |= aiProcess_Triangulate;
    flag |= aiProcess_PreTransformVertices;
    flag |= aiProcess_CalcTangentSpace;
    flag |= aiProcess_GenSmoothNormals;
    flag |= aiProcess_GenUVCoords;
    flag |= aiProcess_RemoveRedundantMaterials;
    flag |= aiProcess_OptimizeMeshes;

    auto scene = importer.ReadFile(path, flag);
    if (scene == nullptr)
    {
        MessageBox(nullptr, importer.GetErrorString(), "Error!!", 0);
    }

	return false;
}

void Model::LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV)
{
}

void Model::LoadTexture(const wchar_t* filename, Mesh& dst, const aiMaterial* src)
{
}
