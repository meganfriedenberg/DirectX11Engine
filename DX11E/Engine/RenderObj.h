#pragma once
#include "VertexBuffer.h"
#include "engineMath.h"
#include "Material.h"
#include "Mesh.h"
class RenderObj
{
public:
	RenderObj(); // Default constructor needed so other classes can inherit from this class
	RenderObj(const Mesh* m);
	RenderObj(const VertexBuffer* vertexBuffer);
	virtual ~RenderObj();
	virtual void Draw();
	virtual void Draw2();
	void AddComponent(class Component* pComp);
	virtual void Update(float deltaTime);

	const VertexBuffer* mBuffer;

	struct PerObjConst
	{
		Matrix4 floatMatrix;
	};

	PerObjConst structPerObj;
	ID3D11Buffer* objectBuffer;

	//Material* mMaterial;

	const Mesh* mMesh;

	std::vector<class Component*> mComponents;


private:


};

