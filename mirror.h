#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"
#include "Player.h"
#include <input/Input.h>
#include "Map.h"

class Map;

class mirror {
public:
	void Initialize(KamataEngine::WorldTransform* worldtransform,int x,int z,Map*map);
	void Update(Player* player);
	void Draw(int i,KamataEngine::Camera* camera);
	bool isInsideRhombus(KamataEngine::Vector3 mirror, KamataEngine::Vector3 player);
	KamataEngine::Vector3 Getpos() { 
		return worldtransform_->translation_;
	}
	int GetPos(int i) { 
		return Pos[i];
	}
	void PosChange(int i) { 
		if (i == 1) {
			Pos[0]++;//D
		}
		if (i == 2) {
			Pos[0]--;//A
		}
		if (i == 3) {
			Pos[1]++;//W
		}
		if (i == 4) {
			Pos[1]--;//S
		}
		
	}


	private:
	KamataEngine::WorldTransform* worldtransform_;

	KamataEngine::Model* mirrormodel_;

	KamataEngine::Model* mirrormodel2_;
	Player* player_;

	KamataEngine::Input* input_ = nullptr;

	uint32_t textureHandle_ = 0u;

	KamataEngine::WorldTransform* preworldtransform_;

	int Pos[2];

	int time = 0;

	Map* map_;

};
