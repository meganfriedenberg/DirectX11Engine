#include "stdafx.h"
#include "texture.h"
#include "Graphics.h"
#include "DirectXTK\Inc\DDSTextureLoader.h"
#include "DirectXTK\Inc\WICTextureLoader.h"
#include <string>

Texture::Texture()
    : mResource(nullptr)
    , mView(nullptr)
    , mWidth(0)
    , mHeight(0)
{
}

Texture::~Texture()
{
    Free();
}

void Texture::Free()
{
    if (nullptr != mView)
    {
        mView->Release();
        mView = nullptr;
    }
    if (nullptr != mResource)
    {
        mResource->Release();
        mResource = nullptr;
    }
    mWidth = 0;
    mHeight = 0;
}

bool Texture::Load(const WCHAR* fileName)
{
    Free();     // in case there was already a texture loaded here, release it

    ID3D11Device *pDev = Graphics::Get()->GetDevice();

    std::wstring fileStr(fileName);
    std::wstring extension = fileStr.substr(fileStr.find_last_of('.'));
    HRESULT hr = E_FAIL;
    if (extension == L".dds" || extension == L".DDS")
        hr = DirectX::CreateDDSTextureFromFile(pDev, fileName, &mResource, &mView);
    else
        hr = DirectX::CreateWICTextureFromFile(pDev, fileName, &mResource, &mView);
    DbgAssert(hr == S_OK, "Problem Creating Texture From File");
    if (S_OK != hr)
        return false;

    CD3D11_TEXTURE2D_DESC textureDesc;
    ((ID3D11Texture2D*)mResource)->GetDesc(&textureDesc);
    mWidth = textureDesc.Width;
    mHeight = textureDesc.Height;

    return true;
}

Texture* Texture::StaticLoad(const WCHAR* fileName, AssetManager* pManager)
{
    Texture* pTex = new Texture();
    if (false == pTex->Load(fileName))
    {
        delete pTex;
        return nullptr;
    }
    return pTex;
}

void Texture::SetActive(int slot) const
{
    Graphics::Get()->SetActiveTexture(slot, mView);
}

ID3D11RenderTargetView* Texture::CreateRenderTarget(int inWidth, int inHeight, DXGI_FORMAT format)
{
    Graphics* g = Graphics::Get();
    ID3D11Device* d = g->GetDevice();
    ID3D11Texture2D* textD;


    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = inWidth;
    descDepth.Height = inHeight;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = format;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // bind it as a render target and shader resource
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    HRESULT hr = d->CreateTexture2D(&descDepth, NULL, &textD);

    mResource = textD; // Use CreateTexture2D to initialize mResource

    if (hr == S_FALSE) { // if it didn't initialize
        return nullptr;
    }

    hr = d->CreateShaderResourceView(mResource, nullptr, &mView);

    if (hr == S_FALSE)
    {
        return nullptr;
    }

    ID3D11RenderTargetView* mRenderTargView;

    hr = d->CreateRenderTargetView(mResource,nullptr,&mRenderTargView);
    if (hr == S_FALSE)
    {
        return nullptr;
    }

    return mRenderTargView;
}