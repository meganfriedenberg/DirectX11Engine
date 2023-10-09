#include "stdafx.h"
#include "Component.h"
#include "RenderObj.h"
#include "Graphics.h"

RenderObj::RenderObj()
{

}
RenderObj::RenderObj(const Mesh* mesh)
{
	mMesh = mesh;
	Graphics* mGraphics = Graphics::Get();
	structPerObj.floatMatrix = Matrix4::CreateRotationZ(Math::ToRadians(45.0f));
	objectBuffer = mGraphics->CreateGraphicsBuffer(&structPerObj, sizeof(structPerObj), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);

}
RenderObj::RenderObj(const VertexBuffer* vertexBuffer)
{
	mBuffer = vertexBuffer;
	Graphics* mGraphics = Graphics::Get();
	structPerObj.floatMatrix = Matrix4::CreateRotationZ(Math::ToRadians(45.0f));
	objectBuffer = mGraphics->CreateGraphicsBuffer(&structPerObj, sizeof(structPerObj), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);

}
RenderObj::~RenderObj()
{
	objectBuffer->Release();
	//delete mMaterial;
	//delete mBuffer;
}
void RenderObj::Draw()
{
	Graphics* mGraphics = Graphics::Get();
	// Copies our c_modeltoWorld matrix into constant buffer
	mGraphics->UploadBuffer(objectBuffer, &structPerObj, sizeof(structPerObj)); 
	mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_RENDEROBJ, 1, &objectBuffer);
	mMesh->Draw();
}

void RenderObj::Draw2()
{
	Graphics* mGraphics = Graphics::Get();
	// Copies our c_modeltoWorld matrix into constant buffer
	mGraphics->UploadBuffer(objectBuffer, &structPerObj, sizeof(structPerObj));
	mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_RENDEROBJ, 1, &objectBuffer);
	mGraphics->GetDeviceContext()->GSSetConstantBuffers(Graphics::CONSTANT_BUFFER_RENDEROBJ, 1, &objectBuffer);
	mBuffer->Draw();
}

void RenderObj::AddComponent(class Component* pComp)
{
	mComponents.push_back(pComp);
}
void RenderObj::Update(float deltaTime)
{
	for (auto c : mComponents)
	{
		c->Update(deltaTime);
	}
}