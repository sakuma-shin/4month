#include "Light.h"
#include <cassert>

using namespace KamataEngine;

void Light::Initialize(Sprite* sprite, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(sprite);
	sprite_ = sprite;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
}

void Light::Update() {
	Grow();

	worldTransform_.UpdateMatrix();
}

void Light::Draw() {}

void Light::Grow() {
	float kSpeed = 0.1f;
	switch (growtype) {
	case Up:
		
		velocity_ = {0.0f, -kSpeed, 0.0f};

		break;

	case Down:
		velocity_ = {0.0f, kSpeed, 0.0f};

		break;

	case Left:
		velocity_ = {-kSpeed, 0.0f, 0.0f};

		break;

	case Right:
		velocity_ = {kSpeed, 0.0f, 0.0f};

		break;

	case NO:
		velocity_ = {0.0f, 0.0f, 0.0f};

		break;
	}

	width_ += velocity_.x;
	height_ += velocity_.y;
}
