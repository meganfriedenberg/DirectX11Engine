#pragma once
#include "assetCache.h"
#include "Animation.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skeleton.h"
#include "Texture.h"

class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void Clear();

    Shader* GetShader(const std::wstring& shaderName);
    void SetShader(const std::wstring& shaderName, Shader* pShader);

    Texture* LoadTexture(const std::wstring& fileName);

    Material* LoadMaterial(const std::wstring& fileName);

    Mesh* LoadMesh(const std::wstring& fileName);

    Skeleton* LoadSkeleton(const std::wstring& fileName);

    Animation* LoadAnimation(const std::wstring& fileName);



private:
    AssetCache<Shader> mAssetShader;
    AssetCache<Texture> mAssetTexturer;
    AssetCache<Material> mAssetMaterial;
    AssetCache<Mesh> mAssetMesh;
    AssetCache<Skeleton> mAssetSkeleton;
    AssetCache<Animation> mAssetAnimation;
 };
