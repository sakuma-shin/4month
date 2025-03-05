#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"

class door {
public:
	void Initialize();
	void Update();
	void Draw(KamataEngine::WorldTransform* worldtransform, KamataEngine::Camera* camera);

private:
	KamataEngine::Model* doormodel_;
	bool openflag = false;
};