#pragma once
#include "KamataEngine.h"
#include "Light.h"
#include "Map.h"
#include "Target.h"

using namespace KamataEngine;

class Prism {
public:
	void Initialize(int key, WorldTransform* worldTransform, int x, int z, Map* map);

	void Update(Player* player);

	void Draw(Camera* camera);

	/// <summary>
	/// 光の分解の際の処理
	/// </summary>
	void DecompositionLight();

	void Broken();

	void Set();

	Light::GrowType SetGrowType() { return prismDirection_; }

	bool IsSet() { return isSet_; }

	int GetPos(int num) { return pos_[num]; }

	int ReturnKey() { return key_; }

private:
	Model* model_ = nullptr;

	bool isSet_ = true;

	int key_ = 0;

	int pos_[2] = {};

	Map* map_ = nullptr;

	Player* player_ = nullptr;

	Input* input_ = nullptr;

	WorldTransform* worldTransform_ = nullptr;

	Light::GrowType prismDirection_ = Light::GrowType::NO;
};