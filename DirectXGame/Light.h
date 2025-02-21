#pragma once
#include"KamataEngine.h"

using namespace KamataEngine;
class Light {
public:
	void Initialize(Sprite* sprite, uint32_t textureHandle);

	void Update();

	void Draw();

	void Grow();

private:

	Sprite* sprite_;
	Vector3 initialPos_ = {};
	float width_ =0.0f;
	float height_=0.0f;
	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_; 
	enum GrowType {
		Up,
		Down,
		Right,
		Left,
		NO
	};

	GrowType growtype=NO;

	Vector3 velocity_ = {};
};
