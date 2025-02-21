#include "Light.h"
#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity) {
	/*sprite_ = sprite;*/
	worldTransform_.Initialize();
	sprite_ = Sprite::Create(textureHandle, {}); // 各LightごとにSpriteを作成

	initialPos_ = initialPos;
	sprite_->SetSize({width_, height_});
	velocity_ = velocity;

	width_ = 20.0f;
	height_ = 20.0f;
	/*growtype_ = type;
	newType_ = NO;*/
	isReflection_ = false;
}

void Light::Update() {
	if (rightDownHit) {
		// if(動きが斜めじゃないとき)
		isReflection_ = 1;
		newVelocity_ = {velocity_.y, velocity_.x};
	}

	if (rightUpHit) {
		// if(動きが斜めじゃないとき)
		isReflection_ = 1;
		newVelocity_ = {-velocity_.y, -velocity_.x};
	}

	if (!wallHit && !rightDownHit && !rightUpHit) {
		width_ += velocity_.x;
		height_ += velocity_.y;
	} else {
		// if (壁に当たった時)
		velocity_ = {};
	}

	// switch (growtype_) {
	// case Right:

	//	if (width_ >= reflectionWidth &&!isReflection_) {
	//		growtype_ = Reflection; // 下に反射
	//		isReflection_ = true;   // 1回だけ反射
	//		newType_ = Down;
	//	}

	//	if (width_ >= reflectionWidth && !isReflection_) {
	//		growtype_ = Reflection; // 上に反射
	//		isReflection_ = true;   // 1回だけ反射
	//		newType_ = Up;
	//	}

	//	//if (!isReflection_) {
	//	//	growtype_ = Reflection;
	//	//	isReflection_ = true;   // 1回だけ反射
	//	//}
	//	break;

	// case Reflection:

	//	break;
	//};

	ImGui::Begin("Light");
	ImGui::DragFloat3("Light.pos", &initialPos_.x, 0.01f);
	;
	ImGui::DragFloat("Light.width", &width_, 0.01f);
	ImGui::DragFloat("Light.height", &height_, 0.01f);
	ImGui::Checkbox("rightDownHit", &rightDownHit);
	ImGui::Checkbox("rightUpHit", &rightUpHit);
	ImGui::Checkbox("wallHit", &wallHit);
	ImGui::End();

	sprite_->SetSize({width_, height_});
	sprite_->SetPosition({initialPos_.x, initialPos_.y});
}

void Light::Draw() { sprite_->Draw(); }

// void Light::Grow() {
//	float kSpeed = 10.0f;
//	switch (growtype_) {
//	case Up:
//
//		velocity_ = {0.0f, -kSpeed, 0.0f};
//
//		break;
//
//	case Down:
//		velocity_ = {0.0f, kSpeed, 0.0f};
//
//		break;
//
//	case Left:
//		velocity_ = {-kSpeed, 0.0f, 0.0f};
//
//		break;
//
//	case Right:
//		velocity_ = {kSpeed, 0.0f, 0.0f};
//
//		break;
//
//	case NO:
//		velocity_ = {0.0f, 0.0f, 0.0f};
//
//		break;
//	}
//	width_ += velocity_.x;
//	height_ += velocity_.y;
// }

Light::~Light() { delete sprite_; }
