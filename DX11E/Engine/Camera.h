#pragma once
#include "VertexBuffer.h"
#include "engineMath.h"

class Camera
{
	struct PerCamConst
	{
		Matrix4 viewProjMatrix;
		Vector3 camPosition; // Need to align to 16 byte boundary. How do we do this?
		int padding; // 4 byte integer for padding
	};

public:
	Camera();
	virtual ~Camera();
	void SetActive();
	void SetWorldToCam(Matrix4 position, Matrix4 rotation);
	void SetWorldToCam(Matrix4 mat) { worldToCamera = mat; }
	Matrix4 GetWorldToCam() { return worldToCamera; }

	PerCamConst structPerCam;

protected:
	ID3D11Buffer* constBuff; // PDF says a "constant buffer" what does this mean?
	Matrix4 worldToCamera;
	Matrix4 projMatrix; // Projection matrix
};

