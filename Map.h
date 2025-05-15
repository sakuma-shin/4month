#pragma once
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include "ColorGlass.h"
#include "GameScene.h"
#include "Light.h"
#include "MathUtility.h"
#include "Player.h"
#include "Prism.h"
#include "Target.h"
#include "door.h"
#include "math/Vector2.h"
#include "mirror.h"
#include <KamataEngine.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

class mirror;
class ColorGlass;

class Prism;

class GameScene;

class Map {
public:
	~Map();

	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, int stagenumber, GameScene* game);
	void Update(Player* player);
	void Draw();
	void readCSV();

	int CheckCollision(KamataEngine::Vector3 pos);
	void Reorldtransform();

	bool CheckCollisionRay(Vector3 initialPos, Vector3 endPos);

	void CheckGoalCollision(KamataEngine::Vector3 pos);

	std::vector<KamataEngine::Vector3> GetTilePositionsInRange(int min, int max);
	std::vector<Light::GrowType> GetMirrorTypesInRange();

	std::vector<Target*> Gettarget() { return target_; }

	KamataEngine::Vector3 GetPlayerInitialPos();

private:
	int Digit(int number);

	int Digitnamber(int number);

	int UnFirstnumber(int number);

	std::vector<Target*> GetTargetList() { return target_; }

private:
	std::string filename;
	static const int MaxX = 10;
	static const int MaxY = 15;
	int map[MaxX][MaxY];
	// ブロックの大きさ
	KamataEngine::Vector3 Size = {2, 2, 2};
	// ワールド変換データ
	std::vector<KamataEngine::WorldTransform*> worldTransform_;
	// モデル
	KamataEngine::Model* model_;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	uint32_t walltextureHandle_ = 0u;

	KamataEngine::Camera* camera_;

	KamataEngine::Model* goalmodel_;

	KamataEngine::Model* prismmodel_;

	KamataEngine::Model* doormodel_;

	KamataEngine::Model* colorGlassModel_;

	std::vector<door*> door_;

	std::vector<Target*> target_;

	std::vector<mirror*> mirror_;

	std::vector<Prism*> prism_;

	std::vector<ColorGlass*> colorGlass_;

	int doorcount = 0;
	int targetcount = 0;

	int mirrorcount = 0;

	int prismcount = 0;

	int colorGlassCount = 0;

	GameScene* gameScene_;

	int rayCount = 0;
};
