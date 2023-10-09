#include "stdafx.h"
#include "VertexBuffer.h"
#include "Graphics.h"


VertexBuffer::VertexBuffer(const void* vertexData, uint32_t vertexCount, uint32_t vertStride,
	const void* indexData, uint32_t indexCount, uint32_t indexStride)
{
	mStride = vertStride;
	mVertices = vertexCount;
	mIndexStride = indexStride;
	mIndexCount = indexCount;
	if (mIndexStride == 2)
	{
		mIndexFormat = DXGI_FORMAT_R16_UINT;
	}
	else
	{
		mIndexFormat = DXGI_FORMAT_R16_UINT;
	}

	Graphics* pGraphics = Graphics::Get();

	mBuffer = pGraphics->CreateGraphicsBuffer(vertexData, (int)vertexCount * vertStride, D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
	mIndexBuffer = pGraphics->CreateGraphicsBuffer(indexData, (int)indexCount * indexStride, D3D11_BIND_INDEX_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);
}
VertexBuffer::~VertexBuffer()
{
	mBuffer->Release();
	mIndexBuffer->Release();
}

void VertexBuffer::Draw() const
{
	Graphics* pGraphics = Graphics::Get();
	ID3D11DeviceContext* dContext = pGraphics->GetDeviceContext();
	UINT zero = 0; 
	dContext->IASetVertexBuffers(0, 1, &mBuffer, &mStride, &zero);
	dContext->IASetIndexBuffer(mIndexBuffer, mIndexFormat, zero);
	dContext->DrawIndexed(mIndexCount, 0,0);
}
