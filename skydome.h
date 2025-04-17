#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class skydome {
public:
	void Initialize(Camera*camera);
	void Update();
	void Draw();

private:
	WorldTransform* worldtransform_ = new WorldTransform;
	Model* model_;
	Camera* camera_;

};
