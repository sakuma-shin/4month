#pragma once
#include "KamataEngine.h"

#include "CameraAngle.h"
#include "Player.h"

#include "Light.h"
#include <list>

#include "Map.h"

#include "Color.h"
// #include "ColorGlass.h"

using namespace KamataEngine;

class GameScene {
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

	void LightCreate(Light::GrowType type, Vector3 pos, uint32_t lightTextureHandle, int color);

	bool IsFinished() { return isFinished_; }

	void SetFinished(bool finished) { isFinished_ = finished; }

	bool GetLightFlag() { return lightDethflag; }

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

	// 色ガラス
	// ColorGlass* colorGlass_;

	bool isFinished_ = false;

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

	int stagenumber = 1;

	// カラー類
	Model* colorModel_ = nullptr;
	uint32_t redTextureHandle_ = 0u;
	uint32_t blueTextureHandle_ = 0u;
	uint32_t greenTextureHandle_ = 0u;

	uint32_t explanationTextureHandle_ = 0u;
	uint32_t brokenPrysmTextureHandle_ = 0u;
	uint32_t choiceNextStageTextureHandle_ = 0u;
	uint32_t purpleTextureHandle_ = 0u;

	bool lightDethflag = false;
};
