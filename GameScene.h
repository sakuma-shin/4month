#pragma once
#include "KamataEngine.h"

#include "CameraAngle.h"
#include "Player.h"

#include "Light.h"
#include <list>

#include "Map.h"

#include "Color.h"
// #include "ColorGlass.h"

#include "skydome.h"

#include "Fade.h"

using namespace KamataEngine;

class GameScene {
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	void Initialize(int stageNum);

	void Update();

	void Draw();

	void LightCreate(Light::GrowType type, Vector3 pos, uint32_t lightTextureHandle, int color);

	bool IsFinished() { return isFinished_; }
	bool IsFinished2() { return isFinished2_; }

	void SetFinished(bool finished) { isFinished_ = finished; }

	bool GetLightFlag() { return lightDethflag; }

	void SetStageNum(int num) { stageNum_ = num; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// モデル
	Model* playerModel_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// プレイヤー
	Player* player_ = nullptr;

	// カメラ
	Camera camera_;

	// カメラアングル
	CameraAngle* cameraAngle_ = nullptr;

	// カラー
	Color* color_ = nullptr;

	bool isFinished_ = false;

	bool isFinished2_ = false;

	// ライト
	std::list<Light*> lights_;
	/*Sprite* lightSprite_ = nullptr;*/
	uint32_t lightTextureHandle_ = 0u;
	Model* lightModel_ = nullptr;

	Map* map_ = nullptr;

	Model* mapModel_ = nullptr;
	Sprite* explanationSprite_ = nullptr;
	Sprite* brokenPrysmSprite_ = nullptr;
	Sprite* choiceNextStageSprite_ = nullptr;
	Sprite* resetSprite_ = nullptr;

	// カラー類
	Model* colorModel_ = nullptr;
	uint32_t redTextureHandle_ = 0u;
	uint32_t blueTextureHandle_ = 0u;
	uint32_t greenTextureHandle_ = 0u;

	uint32_t explanationTextureHandle_ = 0u;
	uint32_t brokenPrysmTextureHandle_ = 0u;
	uint32_t choiceNextStageTextureHandle_ = 0u;
	uint32_t purpleTextureHandle_ = 0u;
	uint32_t resetTextureHandle_ = 0u;

	bool lightDethflag = false;

	skydome* skydome_ = new skydome;

	Fade* fade_ = nullptr;

	FadePhase phase_ = FadePhase::kFadeIn;

	int stageNum_ = 0;


};
