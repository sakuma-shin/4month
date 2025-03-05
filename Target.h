#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"

class Target {

	public:
		void Initialize(int number, KamataEngine::WorldTransform* worldTransform);
		void Update();
		void Draw(KamataEngine::Camera* camera);
	
	private:
		int coad;
	    int color;
		bool Hit;
	    KamataEngine::WorldTransform* worldTransform_;
};
