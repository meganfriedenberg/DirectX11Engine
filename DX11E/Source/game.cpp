#include "stdafx.h"
#include "AssetManager.h"
#include "Camera.h"
#include "Character.h"
#include "CollisionBox.h"
#include "Game.h"
#include "engineMath.h"
#include "Graphics.h"
#include "JobManager.h"
#include "jsonUtil.h"
#include "Material.h"
#include "Mesh.h"
#include "Components\player.h"
#include "Components\followCam.h"
#include "RenderCube.h"
#include "RenderObj.h"
#include "Shader.h"
#include "SimpleRotate.h"
#include "SkinnedObj.h"
#include "stringUtil.h"
#include "texture.h"
#include "Components/PointLight.h"
#include "rapidjson\include\rapidjson\rapidjson.h"
#include "rapidjson\include\rapidjson\document.h"
#include "VertexBuffer.h"
#include <fstream>
#include <sstream>
#include <VertexFormat.h>
#include <iostream>
#include "MyClass.h"
#include "RenderForest.h"

float mRotation;

Game::Game()
{
	mAssetManager = new AssetManager();
	phy = new Physics();
	jm = new JobManager();
	jm->Begin();
}

Game::~Game()
{
	delete phy;
}

void Game::Init(HWND hWnd, float width, float height)
{
	MyClass c;
	int currSize = sizeof(c);
	currSize = sizeof(c.isAlive);
	mWidth = width;
	mHeight = height;

	mGraphics.InitD3D(hWnd, width, height);

	// vert is for drawing a triangle to test renderer
	VertexPosColor vert[] =
	{
	{ Vector3(0.0f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Graphics::Color4(1.0f, 0.0f, 0.0f, 1.0f) },
	{ Vector3(0.45f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Graphics::Color4(0.0f, 1.0f, 0.0f, 1.0f) },
	{ Vector3(-0.45f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 0.0f),Graphics::Color4(0.0f, 0.0f, 1.0f, 1.0f) }
	};
	
	uint16_t triangleIndices[] =
	{
		{0},
		{1},
		{2}
	};

	mCam = new Camera();

	D3D11_INPUT_ELEMENT_DESC inputElemUnlitMesh[] = // Since this is an array on the stack, does it have to be "popped"?
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPos, pos),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPos, normal),
	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPos, uv),
	D3D11_INPUT_PER_VERTEX_DATA, 0}

	};

	Shader* phongShader = new Shader();
	phongShader->Load(L"Shaders/Phong.hlsl", inputElemUnlitMesh, ARRAYSIZE(inputElemUnlitMesh));
	mAssetManager->SetShader(L"Phong", phongShader);

	Shader* unlitShader = new Shader();
	unlitShader->Load(L"Shaders/Unlit.hlsl", inputElemUnlitMesh, ARRAYSIZE(inputElemUnlitMesh));
	mAssetManager->SetShader(L"Unlit", unlitShader);

	// uncomment for triangle rendering
	// vertexBuffer = mGraphics.CreateGraphicsBuffer(vert, sizeof(vert), D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);


	D3D11_INPUT_ELEMENT_DESC inputElemBasicMesh[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosColor, pos),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosColor, normal),
	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexPosColor, color),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosColor, uv),
	D3D11_INPUT_PER_VERTEX_DATA, 0}

	};



	Vector3 verts2[] = {
	Vector3(1.0f, 2.0f, 3.0f),
	Vector3(0.0f, 0.0f, 0.0f),
	Vector3(-1.0f, -2.0f, -3.0f)
	};

	float size = sizeof(verts2);

	Mesh* m = mAssetManager->LoadMesh(L"Assets/Meshes/PlayerShip.itpmesh3");



	// Lighting buffer
	lights = new Lights::LightingConstants;
	lightingBuffer = mGraphics.CreateGraphicsBuffer(lights, sizeof(*lights), D3D11_BIND_CONSTANT_BUFFER, D3D11_CPU_ACCESS_WRITE, D3D11_USAGE_DYNAMIC);


	D3D11_INPUT_ELEMENT_DESC inputElemSkinnedMesh[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexSkinned, pos),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexSkinned, normal),
	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "BONES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, offsetof(VertexSkinned, bones),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHTS", 0,  DXGI_FORMAT_R8G8B8A8_UNORM, 0, offsetof(VertexSkinned, weights),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexSkinned, uv),
	D3D11_INPUT_PER_VERTEX_DATA, 0}

	};

	Animation* a = mAssetManager->LoadAnimation(L"Assets/Anims/ThirdPersonRun.itpanim2");
	Shader* skinnedShader = new Shader();
	skinnedShader->Load(L"Shaders/Skinned.hlsl", inputElemSkinnedMesh, ARRAYSIZE(inputElemSkinnedMesh));
	mAssetManager->SetShader(L"Skinned", skinnedShader);


	D3D11_INPUT_ELEMENT_DESC inputElemTangentMesh[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosTangent, pos),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosTangent, normal),
	D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPosTangent, tangent),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPosTangent, uv),
	D3D11_INPUT_PER_VERTEX_DATA, 0} 

	};

	Shader* tangentShader = new Shader(); 
	tangentShader->Load(L"Shaders/Normal.hlsl", inputElemTangentMesh, ARRAYSIZE(inputElemTangentMesh));
	mAssetManager->SetShader(L"Normal", tangentShader);

	D3D11_INPUT_ELEMENT_DESC inputElemCopyMesh[] = 
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexCopy, pos),
	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXTCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexCopy, uv),
	D3D11_INPUT_PER_VERTEX_DATA, 0} 
	};

	VertexCopy sourceVert[] =
	{
	{ Vector3(-1.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f) },
	{ Vector3(1.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f) },
	{ Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f) },
	{ Vector3(-1.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f) }

	};

	uint16_t copyIndices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	screenQuad = new VertexBuffer(sourceVert, sizeof(sourceVert), sizeof(VertexCopy),
		copyIndices, ARRAY_SIZE(copyIndices), sizeof(uint16_t));


	Shader* horizontalShader = new Shader();
	horizontalShader->Load(L"Shaders/Horizontal.hlsl", inputElemCopyMesh, ARRAYSIZE(inputElemCopyMesh));
	mAssetManager->SetShader(L"Horizontal", horizontalShader);

	Shader* verticalShader = new Shader();
	verticalShader->Load(L"Shaders/Vertical.hlsl", inputElemCopyMesh, ARRAYSIZE(inputElemCopyMesh));
	mAssetManager->SetShader(L"Vertical", verticalShader);

	Shader* copyShader = new Shader();
	copyShader->Load(L"Shaders/Copy.hlsl", inputElemCopyMesh, ARRAYSIZE(inputElemCopyMesh));
	mAssetManager->SetShader(L"Copy", copyShader);

	Shader* lightingShader = new Shader();
	lightingShader->Load(L"Shaders/Lighting.hlsl", inputElemCopyMesh, ARRAYSIZE(inputElemCopyMesh));
	mAssetManager->SetShader(L"Lighting", lightingShader);

	Shader* bloomMaskShader = new Shader();
	bloomMaskShader->Load(L"Shaders/BloomMask.hlsl", inputElemCopyMesh, ARRAYSIZE(inputElemCopyMesh));
	mAssetManager->SetShader(L"BloomMask", bloomMaskShader);

	// Bloom Mask render target declaration
	renderTargetTexture = new Texture();
	renderTargetTexture->SetHeight(height);
	renderTargetTexture->SetWidth(width);

	halfRenderTargText = new Texture();
	halfRenderTargText->SetHeight(height);
	halfRenderTargText->SetWidth(width);

	quarterOneRenderTargText = new Texture();
	quarterOneRenderTargText->SetHeight(height);
	quarterOneRenderTargText->SetWidth(width);

	quarterTwoRenderTargText = new Texture();
	quarterTwoRenderTargText->SetHeight(height);
	quarterTwoRenderTargText->SetWidth(width);


	// Deferred Rendering Textures

	colorText = new Texture();
	colorText->SetHeight(height);
	colorText->SetWidth(width);

	normalText = new Texture();
	normalText->SetHeight(height);
	normalText->SetWidth(width);

	worldPosText = new Texture();
	worldPosText->SetHeight(height);
	worldPosText->SetWidth(width);

	// End Deferred Rendering Textures


	// Deferred Rendering Render Targets

	mRenderViews[0] = colorText->CreateRenderTarget(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	mRenderViews[1] = normalText->CreateRenderTarget(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	mRenderViews[2] = worldPosText->CreateRenderTarget(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);

	// End Deferred Rendering Render Targets


	mRenderTargetView = renderTargetTexture->CreateRenderTarget(width, height, DXGI_FORMAT_R32G32B32A32_FLOAT);
	mHalfRenderTargetView = halfRenderTargText->CreateRenderTarget(width/2, height/2, DXGI_FORMAT_R32G32B32A32_FLOAT);
	mQuarterOneRenderTargetView = quarterOneRenderTargText->CreateRenderTarget(width/4, height/4, DXGI_FORMAT_R32G32B32A32_FLOAT);
	mQuarterTwoRenderTargetView = quarterTwoRenderTargText->CreateRenderTarget(width/4, height/4, DXGI_FORMAT_R32G32B32A32_FLOAT);

	mOpaque = mGraphics.CreateBlendState(false, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ZERO);
	mAdditive = mGraphics.CreateBlendState(true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_ZERO); // Changed from D3D11_BLEND_ONE


	{
		D3D11_INPUT_ELEMENT_DESC inputElem[] = 
		{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexTree, pos),
		D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		VertexTree vertTree[20];

		uint16_t treeIndices[20];
		uint16_t treeIndex[1];

		Shader* treeShader = new Shader();
		treeShader->Load(L"Shaders/GeometryQuad.hlsl", inputElem, ARRAYSIZE(inputElem));
		mAssetManager->SetShader(L"TreeQuad", treeShader);

		treeTexture = new Texture();
		treeTexture->Load((L"Assets/Textures/tree1.png"));


		// array of forests, want an instance of a forest
		for (int i = 0; i < 20; i++)
		{
			VertexTree t;
			if (i % 2)
			{
				t.pos = (Vector3(1200 + (i * 300), (i * 300), 200));
			}
			else if (i % 3)
			{
				t.pos = (Vector3(1200 + (i * 300), (i * 100), 200));
			}
			else
			{
				t.pos = (Vector3(1200 + (i * 300), (i * -300), 200));
			}

			vertTree[i] = t;
			treeIndices[i] = i;

		}

		treeBuffer = new VertexBuffer(vertTree, ARRAY_SIZE(vertTree), sizeof(vertTree[0]),
			treeIndices, ARRAY_SIZE(treeIndices), sizeof(treeIndices[0]));


		Material* treeMaterial = new Material();
		treeMaterial->SetShader(treeShader);
		treeMaterial->SetTexture(0, treeTexture);


		RenderForest* forest = new RenderForest(treeBuffer, treeMaterial);

		geometryForest.push_back(forest);

	}

	LoadLevel(L"Assets/Levels/Level10.itplevel");
}

void Game::Shutdown()
{
	lightingBuffer->Release();

	delete mCam;

	delete lights;

	for (auto r : mObjects)
	{
		delete r;
	}

	// Release the blend states
	mOpaque->Release();
	mAdditive->Release();

	delete renderTargetTexture;
	delete halfRenderTargText;
	delete quarterOneRenderTargText;
	delete quarterTwoRenderTargText;

	// delete the multi render target textures
	delete colorText;
	delete normalText;
	delete worldPosText;


	// delete the geometry forest
	for (auto r : geometryForest)
	{
		delete r;
	}

	delete treeTexture;


	delete screenQuad;

	mRenderTargetView->Release();
	mHalfRenderTargetView->Release();
	mQuarterOneRenderTargetView->Release();
	mQuarterTwoRenderTargetView->Release();

	// release the multi render targets
	for (auto t : mRenderViews)
	{
		t->Release();
	}

	mAssetManager->Clear();
	delete mAssetManager;

	jm->End();
	delete jm;

	mGraphics.CleanD3D(); // Graphics device is released

}

void Game::Update(float deltaTime)
{

	PROFILE_SCOPE(Update);

	for (auto r : mObjects)
	{
		r->Update(deltaTime);
	}

	
	jm->WaitForJobs();

}

void Game::RenderFrame()
{
	mGraphics.SetBlendState(mOpaque);
	PROFILE_SCOPE(RenderFrame);
	// Set the render target
	mGraphics.SetRenderTargets(3, mRenderViews, mGraphics.GetDepthStencilView());

	{	// Clear the screen to blue
		Graphics::Color4 clearColor(0.0f, 0.2f, 0.4f, 1.0f);
		mGraphics.ClearRenderTargets(3, mRenderViews, clearColor);
		mGraphics.ClearDepthBuffer(mGraphics.GetDepthStencilView(), 1.0f);
	}

	mCam->SetActive(); // Set the camera to be active BEFORE RenderObj is drawn


	for (auto r : mObjects)
	{
		r->Draw();
	}

	// TREE DRAWING
	mAssetManager->GetShader(L"TreeQuad")->SetActive();
	treeTexture->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	mGraphics.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);  
	
	for (RenderForest* forest : geometryForest)
	{
		forest->Draw();
	}

	mGraphics.GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


#if 0
	// Need to: 1) set the shader, 2) set the tree's matrix 3) set the tree's texture
	// 4) render the tree's vertex buffer, 5) scale and probably rotate the tree by tweaking matrix
	// 6) make sure tree is facing toward camera

	mGraphics.SetViewport(0.0, 0.0, mWidth / 2, mHeight / 2); // from full to half
	mGraphics.SetRenderTarget(mHalfRenderTargetView, nullptr);
	mAssetManager->GetShader(L"BloomMask")->SetActive(); // set the copy shader to be the active shader
	renderTargetTexture->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw(); // draw onto the half buffer

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL);

	mGraphics.SetViewport(0.0, 0.0, mWidth / 4, mHeight / 4); //from half to quarter
	mGraphics.SetRenderTarget(mQuarterOneRenderTargetView, nullptr);
	mAssetManager->GetShader(L"Copy")->SetActive(); // set the copy shader to be the active shader
	halfRenderTargText->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw(); // draw onto the quarter buffer

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL);

	// quarter 1 to quarter 2 horizontal pass
	mGraphics.SetViewport(0.0, 0.0, mWidth / 4, mHeight / 4); //set the viewport back to quarter
	mGraphics.SetRenderTarget(mQuarterTwoRenderTargetView, nullptr); // from quarter1 to quarter2
	mAssetManager->GetShader(L"Horizontal")->SetActive();
	quarterOneRenderTargText->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw();

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL); // unmap the texture so we can use it as a renderTarget again

	// quarter2 to quarter 1
	mGraphics.SetViewport(0.0, 0.0, mWidth / 4, mHeight / 4); //keep the viewport at a quarter
	mGraphics.SetRenderTarget(mQuarterOneRenderTargetView, nullptr); // from quarter2 onto quarter1
	mAssetManager->GetShader(L"Vertical")->SetActive(); // Vertical pass
	quarterTwoRenderTargText->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw();

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL);

	// then copy full to back buffer
	mGraphics.SetViewport(0.0, 0.0, mWidth, mHeight); //from quarter to full
	mGraphics.SetRenderTarget(mGraphics.GetBackBuffer(), nullptr); // set the render target back to the backbuffer
	mAssetManager->GetShader(L"Copy")->SetActive(); // set the copy shader to be the active shader
	renderTargetTexture->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw();

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL);

	// Copy back up to backbuffer
	mGraphics.SetBlendState(mAdditive);

	mGraphics.SetViewport(0.0, 0.0, mWidth, mHeight); //from quarter to full
	mGraphics.SetRenderTarget(mGraphics.GetBackBuffer(), nullptr);
	mAssetManager->GetShader(L"Copy")->SetActive(); // set the copy shader to be the active shader
	quarterOneRenderTargText->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	screenQuad->Draw(); // draw onto the quarter buffer
#else 
   // Bloom Mask uploading

	mGraphics.UploadBuffer(lightingBuffer, lights, sizeof(*lights));
	mGraphics.GetDeviceContext()->VSSetConstantBuffers(Graphics::CONSTANT_BUFFER_LIGHTS, 1, &lightingBuffer);
	mGraphics.GetDeviceContext()->PSSetConstantBuffers(Graphics::CONSTANT_BUFFER_LIGHTS, 1, &lightingBuffer);

	mGraphics.SetViewport(0.0, 0.0, mWidth, mHeight); //from quarter to full
	mGraphics.SetRenderTarget(mGraphics.GetBackBuffer(), nullptr);
	mAssetManager->GetShader(L"Lighting")->SetActive(); // set the lighting shader to be the active shader

	colorText->SetActive(Graphics::TEXTURE_SLOT_DIFFUSE);
	normalText->SetActive(Graphics::TEXTURE_SLOT_NORMAL);
	worldPosText->SetActive(Graphics::TEXTURE_SLOT_POSITION);


	screenQuad->Draw(); // draw onto the quarter buffer
#endif

	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_DIFFUSE, NULL);
	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_NORMAL, NULL);
	mGraphics.SetActiveTexture(Graphics::TEXTURE_SLOT_POSITION, NULL);


	mGraphics.EndFrame();
}

void Game::OnKeyDown(uint32_t key)
{
	m_keyIsHeld[key] = true;
}

void Game::OnKeyUp(uint32_t key)
{
	m_keyIsHeld[key] = false;
}

bool Game::IsKeyHeld(uint32_t key) const
{
	const auto find = m_keyIsHeld.find(key);
	if (find != m_keyIsHeld.end())
		return find->second;
	return false;
}



bool Game::LoadLevel(const WCHAR* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		return false;
	}

	std::string str = doc["metadata"]["type"].GetString();
	int ver = doc["metadata"]["version"].GetInt();

	// Check the metadata
	if (!doc["metadata"].IsObject() ||
		str != "itplevel" ||
		ver != 2)
	{
		return false;
	}

	const rapidjson::Value& camPosition = doc["camera"]["position"];
	if (!camPosition.IsArray() || camPosition.Size() != 3)
	{
		DbgAssert(false, "Level File Invalid Camera Position Format");
		return false;
	}
	std::vector<float> camPos;
	camPos.reserve(3);
	camPos.emplace_back(camPosition[0].GetDouble());
	camPos.emplace_back(camPosition[1].GetDouble());
	camPos.emplace_back(camPosition[2].GetDouble());

	const rapidjson::Value& camRotation = doc["camera"]["rotation"];
	if (!camRotation.IsArray() || camRotation.Size() != 4)
	{
		DbgAssert(false, "Level File Invalid Camera Rotation Format");
		return false;
	}
	std::vector<float> camRotat;
	camRotat.reserve(4);
	camRotat.emplace_back(camRotation[0].GetDouble());
	camRotat.emplace_back(camRotation[1].GetDouble());
	camRotat.emplace_back(camRotation[2].GetDouble());
	camRotat.emplace_back(camRotation[3].GetDouble());

	Quaternion q = Quaternion(camRotat[0], camRotat[1], camRotat[2], camRotat[3]);
	Vector3 camP = Vector3(camPos[0], camPos[1], camPos[2]);
	mCam->SetWorldToCam(Matrix4::CreateTranslation(camP), Matrix4::CreateFromQuaternion(q));

	const rapidjson::Value& lightingFormat = doc["lightingData"]["ambient"];
	if (!lightingFormat.IsArray() || lightingFormat.Size() != 3)
	{
		DbgAssert(false, "Level File Invalid Camera Rotation Format");
		return false;
	}
	std::vector<float> ambient;
	ambient.reserve(3);
	ambient.emplace_back(lightingFormat[0].GetDouble());
	ambient.emplace_back(lightingFormat[1].GetDouble());
	ambient.emplace_back(lightingFormat[2].GetDouble());

	lights->c_ambient = Vector3(ambient[0], ambient[1], ambient[2]);

	const rapidjson::Value& renderFormat = doc["renderObjects"];
	if (!renderFormat.IsArray() || renderFormat.Size() < 1)
	{
		DbgAssert(false, "Level File Invalid Render Objs Format");
		return false;
	}
	for (rapidjson::SizeType i = 0; i < renderFormat.Size(); i++)
	{
		if (!renderFormat[i].IsObject())
		{
			DbgAssert(false, "Level File Invalid Render Obj Sub Array Format");
			return false;
		}
		const rapidjson::Value& posMatrix = renderFormat[i]["position"];
		if (!posMatrix.IsArray() || posMatrix.Size() != 3)
		{
			DbgAssert(false, "Level File Invalid Render Obj Position Format");
			return false;
		}
		std::vector<float> pMat;
		pMat.reserve(3);
		pMat.emplace_back(posMatrix[0].GetDouble());
		pMat.emplace_back(posMatrix[1].GetDouble());
		pMat.emplace_back(posMatrix[2].GetDouble());
		Vector3 positionMatrix = Vector3(pMat[0], pMat[1], pMat[2]);

		const rapidjson::Value& roMatrix = renderFormat[i]["rotation"];
		if (!roMatrix.IsArray() || roMatrix.Size() != 4)
		{
			DbgAssert(false, "Level File Invalid Render Obj Rotation Format");
			return false;
		}
		std::vector<float> rMat;
		rMat.reserve(3);
		rMat.emplace_back(roMatrix[0].GetDouble());
		rMat.emplace_back(roMatrix[1].GetDouble());
		rMat.emplace_back(roMatrix[2].GetDouble());
		rMat.emplace_back(roMatrix[3].GetDouble());
		Matrix4 rotationMatrix = Matrix4::CreateFromQuaternion(Quaternion(rMat[0], rMat[1], rMat[2], rMat[3]));

		float sScale = 0;
		sScale = renderFormat[i]["scale"].GetDouble();
		
		std::wstring meshName;
		GetWStringFromJSON(renderFormat[i], "mesh", meshName);

		Matrix4 flMatrix = Matrix4::CreateScale(sScale) * rotationMatrix * Matrix4::CreateTranslation(positionMatrix);
		Mesh* m = mAssetManager->LoadMesh(meshName);

		RenderObj* r;
		if (m->isSkinned())
		{ //if it is skinned, load it as skinned
			r = new SkinnedObj(m);
			r->structPerObj.floatMatrix = flMatrix;
			mObjects.push_back(r);
		}
		else 
		{
			r = new RenderObj(m);
			r->structPerObj.floatMatrix = flMatrix;
			mObjects.push_back(r);
		}



		const rapidjson::Value& compArray = renderFormat[i]["components"];
		for (rapidjson::SizeType j = 0; j < compArray.Size(); j++) // Loop thru components array
		{
			std::string str;
			GetStringFromJSON(compArray[j], "type", str);
			if (str == "PointLight")
			{
				PointLight* p = new PointLight(r,this);
				p->LoadProperties(compArray[j]);
				r->AddComponent(p);
			}
			if (str == "Character")
			{
				Character* c = new Character((SkinnedObj*)r, this);
				c->LoadProperties(compArray[j]);
				r->AddComponent(c);

			}
			if (str == "Player")
			{
				Player* p = new Player((SkinnedObj*)r, this);
				p->LoadProperties(compArray[j]);
				r->AddComponent(p);
				mPlayer = p;

			}
			if (str == "FollowCam")
			{
				FollowCam* c = new FollowCam((SkinnedObj*)r, this);
				c->LoadProperties(compArray[j], mAssetManager);
				r->AddComponent(c);

			}
			if (str == "CollisionBox")
			{
				CollisionBox* c = new CollisionBox(r, phy);
				c->LoadProperties(compArray[j]);
				r->AddComponent(c);

			}
			if (str == "SimpleRotate")
			{
				SimpleRotate* sr = new SimpleRotate(r,this);
				sr->LoadProperties(compArray[j]);
				r->AddComponent(sr);

			}
		}

	}
	return true;
}
Lights::PointLightData* Game::AllocateLight()
{
	for (int i = 0; i < Lights::MAX_POINT_LIGHTS; i++)
	{
		if (!lights->c_pointLight[i].isEnabled) // Return a pointer to a light with isEnabled as false
		{
			lights->c_pointLight[i].isEnabled = true;
			return &(lights->c_pointLight[i]);
		}
	}

	return nullptr;
}
void Game::FreeLight(Lights::PointLightData* pLight)
{
	pLight->isEnabled = false;
}
void Game::SetAmbientLight(const Vector3& color)
{
	lights->c_ambient = color;
}
const Vector3& Game::GetAmbientLight() const
{
	return lights->c_ambient;
}