#pragma once
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include "KamataEngine.h"
#include "Map.h"
#include "Player.h"
#include "math/Vector2.h"
#include <input/Input.h>

class Map;

class ColorGlass {

public:
	~ColorGlass();

	void Initialize(KamataEngine::WorldTransform* worldtransform, Map* map, int x, int z, int number);

	void Update();

	void Draw(KamataEngine::Camera* camera);

	KamataEngine::Vector3 GetPosition() const;

	int Getpos(int i) { return pos[i]; }
	int Getnumber();

private:
	KamataEngine::WorldTransform* worldTransform_;

	KamataEngine::Model* colorGlassModel_;

	Player* player_;

	uint32_t textureHandle_ = 0u;

	Map* map_;
	int pos[2];

	int mapnumber_;
};