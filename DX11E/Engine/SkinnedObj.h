#pragma once
#include "RenderObj.h"
#include "engineMath.h"
#include "Graphics.h"
class SkinnedObj : public RenderObj
{
public:
	SkinnedObj(const Mesh* m);
	~SkinnedObj();
	void Draw() override;

	const int TOTALMATRICES = 80;

	struct SkinnedConst // Lab05b
	{
		Matrix4 c_skinMatrix[80];
	};

	SkinnedConst skc; // writeup said it is ok to be public

	ID3D11Buffer* skinnedBuff;

private:

};

