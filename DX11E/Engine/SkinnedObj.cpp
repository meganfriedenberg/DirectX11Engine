#include "stdafx.h"
#include "SkinnedObj.h"

SkinnedObj::~SkinnedObj()
{
	skinnedBuff->Release();
}
SkinnedObj::SkinnedObj(const Mesh* m) : RenderObj(m)
{
	for (int i = 0; i < TOTALMATRICES; i++) // fill in the skinning matrices with the identity matrix
	{
		skc.c_skinMatrix[i] = Matrix4::Identity;
	}

	//create the graphics buffer
	Graphics* pGraphics = Graphics::Get();
	skinnedBuff = pGraphics->CreateGraphicsBuffer(&skc, sizeof(skc), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}

void SkinnedObj::Draw()
{
	Graphics* mGraphics = Graphics::Get();
	mGraphics->UploadBuffer(skinnedBuff, &skc, sizeof(skc));
	mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_SKINNEDOBJ, 1, &skinnedBuff);
	RenderObj::Draw(); // call base
}

