#include "stdafx.h"
#include "Shader.h"
#include "Graphics.h"
#include <d3dcompiler.h>

#pragma comment (lib, "d3dcompiler.lib") 

Shader::Shader()
    : mShaderVS(nullptr)
    , mShaderPS(nullptr)
    , mShaderGS(nullptr)
    , mInputLayout(nullptr)
{
}

Shader::~Shader()
{
    mShaderVS->Release();
    mShaderPS->Release();
    if (mShaderGS != nullptr)
    {
        mShaderGS->Release();
    }
    mInputLayout->Release();
}

static bool LoadShader(const WCHAR* filename, const char* entryPoint, const char* model, ID3DBlob*& pBlobOut)
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;

    // Disable optimizations to further improve shader debugging
    dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3DBlob* pErrorBlob = nullptr;
    hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, model,
        dwShaderFlags, 0, &pBlobOut, &pErrorBlob);
    if (FAILED(hr))
    {
        if (pErrorBlob)
        {
            static wchar_t szBuffer[4096];
            _snwprintf_s(szBuffer, 4096, _TRUNCATE,
                L"%hs",
                (char*)pErrorBlob->GetBufferPointer());
            OutputDebugString(szBuffer);
#ifdef _WINDOWS
            //MessageBox(nullptr, szBuffer, L"Error", MB_OK);
#endif
            pErrorBlob->Release();
        }
        return false;
    }
    if (pErrorBlob)
    {
        pErrorBlob->Release();
    }

    return true;
}

bool Shader::Load(const WCHAR* fileName, const D3D11_INPUT_ELEMENT_DESC* layoutArray, int numLayoutElements)
{
    ID3DBlob* pBlobVS = nullptr;
    if (LoadShader(fileName, "VS", "vs_4_0", pBlobVS))
    {
        ID3DBlob* pBlobPS = nullptr;
        if (LoadShader(fileName, "PS", "ps_4_0", pBlobPS))
        {
            Graphics* pGraphics = Graphics::Get();
            HRESULT hr = pGraphics->GetDevice()->CreateVertexShader(pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), nullptr, &mShaderVS);
            DbgAssert(hr == S_OK, "Failed to create vertex shader");
            hr = pGraphics->GetDevice()->CreatePixelShader(pBlobPS->GetBufferPointer(), pBlobPS->GetBufferSize(), nullptr, &mShaderPS);
            DbgAssert(hr == S_OK, "Failed to create pixel shader");
            ID3DBlob* pBlobGS = nullptr;
            if (LoadShader(fileName, "GS", "gs_4_0", pBlobGS))
            {
                pGraphics->GetDevice()->CreateGeometryShader(pBlobGS->GetBufferPointer(), pBlobGS->GetBufferSize(), nullptr, &mShaderGS);
            }
            if (nullptr != mShaderVS && nullptr != mShaderPS)
            {
                hr = pGraphics->GetDevice()->CreateInputLayout(layoutArray, numLayoutElements, pBlobVS->GetBufferPointer(), pBlobVS->GetBufferSize(), &mInputLayout);
                DbgAssert(hr == S_OK, "Failed to create input layout");
                if (S_OK == hr)
                    return true;
            }
            return false;
        }
    }
    DbgAssert(false, "Failed to load shader");
    return false;
}

void Shader::SetActive() const
{
    Graphics* pGraphics = Graphics::Get();
    pGraphics->GetDeviceContext()->VSSetShader(mShaderVS, nullptr, 0);
    pGraphics->GetDeviceContext()->PSSetShader(mShaderPS, nullptr, 0);
    pGraphics->GetDeviceContext()->GSSetShader(mShaderGS, nullptr, 0);
    pGraphics->GetDeviceContext()->IASetInputLayout(mInputLayout);
}