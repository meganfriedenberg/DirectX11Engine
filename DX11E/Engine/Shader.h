#pragma once

class Shader
{
public:
    Shader();
    ~Shader();

    bool Load(const WCHAR* fileName, const D3D11_INPUT_ELEMENT_DESC* layoutArray, int numLayoutElements);
    void SetActive() const;

private:
    ID3D11VertexShader* mShaderVS;
    ID3D11PixelShader* mShaderPS;
    ID3D11GeometryShader* mShaderGS;
    ID3D11InputLayout* mInputLayout;
};