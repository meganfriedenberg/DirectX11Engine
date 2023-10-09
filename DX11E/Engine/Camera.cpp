#include "stdafx.h"
#include "Camera.h"
#include "Graphics.h"

Camera::Camera()
{
	Graphics* pGraphics = Graphics::Get();
	worldToCamera = Matrix4::CreateTranslation(Vector3(500.0f, 0.0f, 0.f));
	projMatrix = Matrix4::CreateRotationY(-Math::PiOver2)
		* Matrix4::CreateRotationZ(-Math::PiOver2)
		* Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
	pGraphics->GetScreenWidth(), pGraphics->GetScreenHeight(), 25.0f, 10000.0f);

	constBuff = pGraphics->CreateGraphicsBuffer(&structPerCam, sizeof(structPerCam), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);

}
Camera::~Camera()
{
	constBuff->Release(); // Release the constant buffer
}
void Camera::SetActive()
{
	structPerCam.viewProjMatrix = worldToCamera * projMatrix; // Fill in c_viewProj
	Matrix4 worldToCamTemp = worldToCamera;
	worldToCamTemp.Invert();
	structPerCam.camPosition = worldToCamTemp.GetTranslation();
	Graphics* mGraphics = Graphics::Get();
	mGraphics->UploadBuffer(constBuff, &structPerCam, sizeof(structPerCam));
	mGraphics->GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_CAMERA, 1, &constBuff);
	mGraphics->GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_CAMERA, 1, &constBuff);
	mGraphics->GetDeviceContext()->GSSetConstantBuffers(Graphics::CONSTANT_BUFFER_CAMERA, 1, &constBuff);
}
void Camera::SetWorldToCam(Matrix4 position, Matrix4 rotation)
{
	worldToCamera = (rotation * position);
	worldToCamera.Invert();
}