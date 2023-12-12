#pragma once
#define NOMINMAX
#include <d3d12.h>
#include <DirectXMath.h>
#include <string>
#include <vector>

using namespace std;

struct Mesh;
struct Vertex;

struct aiMesh;
struct aiMaterial;

    struct Vertex
    {
        DirectX::XMFLOAT3 Position; // 位置座標
        DirectX::XMFLOAT3 Normal; // 法線
        DirectX::XMFLOAT2 UV; // uv座標
        DirectX::XMFLOAT3 Tangent; // 接空間
        DirectX::XMFLOAT4 Color; // 頂点色
    };

    struct Mesh
    {
        vector<Vertex> Vertices; // 頂点データの配列
        vector<uint32_t> Indices; // インデックスの配列
        wstring DiffuseMap; // テクスチャのファイルパス
    };

    struct ImportSettings // インポートするときのパラメータ
    {
        const string filename = nullptr; // ファイルパス
        vector<Mesh>& meshes; // 出力先のメッシュ配列
        bool inverseU = false; // U座標を反転させるか
        bool inverseV = false; // V座標を反転させるか
    };


class AssimpLoader
{
 public:
    bool Load(ImportSettings *setting); // モデルをロードする
 private:
    void LoadMesh(Mesh& dst, const aiMesh* src, bool inverseU, bool inverseV);
    void LoadTexture(const string filename, Mesh& dst, const aiMaterial* src);
};