#pragma once
#include "Graphics.h"
#include "Lights.h"
#include "Profiler.h"


class Shader;

class Game
{
public:
    Game();
    ~Game();

    void Init(HWND hWnd, float width, float height);
    void Shutdown();
	void Update(float deltaTime);
    void RenderFrame();

	void OnKeyDown(uint32_t key);
	void OnKeyUp(uint32_t key);
	bool IsKeyHeld(uint32_t key) const;

	Lights::PointLightData* AllocateLight();
	void FreeLight(Lights::PointLightData* pLight);
	void SetAmbientLight(const Vector3& color);
	const Vector3& GetAmbientLight() const;
	class Camera* GetCamera() { return mCam; }
	class Physics* GetPhy() { return phy; }
	class JobManager* GetJM() { return jm; }

	class VertexBuffer* screenQuad;

	class Texture* renderTargetTexture;
	class Texture* halfRenderTargText;
	class Texture* quarterOneRenderTargText;
	class Texture* quarterTwoRenderTargText;

private:
	std::unordered_map<uint32_t, bool> m_keyIsHeld;
	Graphics mGraphics;

	class Camera* mCam; 

	bool LoadLevel(const WCHAR* fileName);


	 std::vector<class RenderObj*> mObjects;

	struct Lights::LightingConstants* lights;
	ID3D11Buffer* lightingBuffer;

	class AssetManager* mAssetManager;

	class Physics* phy;

	class JobManager* jm;

	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11RenderTargetView* mHalfRenderTargetView;
	ID3D11RenderTargetView* mQuarterOneRenderTargetView;
	ID3D11RenderTargetView* mQuarterTwoRenderTargetView;

	float mWidth;
	float mHeight;

	ID3D11BlendState* mOpaque; // blend disabled
	ID3D11BlendState* mAdditive; // Final = Src + Dest


	// Directed Research

	class Texture* treeTexture;
	class VertexBuffer* treeBuffer;
	class Player* mPlayer;

	std::vector<class RenderForest*> geometryForest;

	// Deferred Rendering
	class Texture* colorText;
	class Texture* normalText;
	class Texture* worldPosText;

	ID3D11RenderTargetView* mRenderViews[3];


};