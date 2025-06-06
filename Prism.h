#pragma once
#include "KamataEngine.h"
#include "Light.h"
#include "Map.h"
#include "Target.h"

using namespace KamataEngine;

class Prism {
public:
	~Prism();

	void Initialize(int key, WorldTransform* worldTransform, int x, int z, Map* map);

	void Update(Player* player);

	void Draw(Camera* camera);

	void Broken();

	void Set();

	Light::GrowType SetGrowType() { return prismDirection_; }

	bool IsSet() { return isSet_; }

	int GetPos(int num) { return pos_[num]; }

	int ReturnKey() { return key_; }

	WorldTransform* GetworldTransform() { return worldTransform_; }

	int PosAdjust(int i, int direct) {
		if (i % 2 != 0) {
			if (direct < 0) {
				return i - direct;
			} else if (direct > 0) {
				return i + direct;
			}
		}
		return i;
	}

private:
	Model* model_ = nullptr;

	bool isSet_ = true;

	int key_ = 0;

	int pos_[2] = {};

	int directX = 0;
	int directZ = 0;

	Map* map_ = nullptr;

	Player* player_ = nullptr;

	Input* input_ = nullptr;

	WorldTransform* worldTransform_ = nullptr;

	Light::GrowType prismDirection_ = Light::GrowType::NO;
};