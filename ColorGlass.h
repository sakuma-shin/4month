#pragma once
#include "KamataEngine.h"
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Player.h"
#include <input/Input.h>
#include "Map.h"

class Map;

class ColorGlass {

public:

	void Initialize();

	void Update();

	void Draw();

private:

	KamataEngine::WorldTransform* worldTransform_;

	KamataEngine::Model* colorGlassModel_;

	Player* player_;

	uint32_t textureHandle_ = 0u;

	Map* map_;

};