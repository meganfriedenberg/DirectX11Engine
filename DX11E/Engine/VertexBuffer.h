#pragma once
class VertexBuffer
{
public:
    VertexBuffer(const void* vertexData, uint32_t vertexCount, uint32_t vertStride,
        const void* indexData, uint32_t indexCount, uint32_t indexStride
    );
    ~VertexBuffer();

    void Draw() const;

    ID3D11Buffer* mBuffer;
    ID3D11Buffer* mIndexBuffer;
    DXGI_FORMAT mIndexFormat;
    UINT mStride; // The stride of the vertex buffer - bytes per vertex (not total bytes)
    UINT mVertices; // The number of vertices. Total bytes = mStride*mVertices
    UINT mIndexCount; // Replace vertex count with an index count ?
    UINT mIndexStride;


};

