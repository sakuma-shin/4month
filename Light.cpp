#include "Light.h"
#include "GameScene.h"
#include <cassert>
#include "MathUtility.h"
#include<cmath>

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity) {
	/*sprite_ = sprite;*/
	model_ = Model::CreateFromOBJ("cube");
	textureHandle_ = textureHandle;

	initialPos_ = initialPos;
	velocity_ = velocity;

	/*growtype_ = type;
	newType_ = NO;*/
	isReflection_ = false;

	worldTransform_.Initialize();
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
		isReflection_ = false;
		isRefrected = false;
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
	ImGui::DragFloat3("Light.scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::DragFloat3("Light.rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("Light.translate", &worldTransform_.translation_.x, 0.01f);
	ImGui::Checkbox("rightDownHit", &rightDownHit);
	ImGui::Checkbox("rightUpHit", &rightUpHit);
	ImGui::Checkbox("wallHit", &wallHit);
	
	ImGui::End();

	 // **スケール調整に伴う位置補正**
	AdjustScaleOffset();

	worldTransform_.UpdateMatrix();
	PosCorrect();
}

void Light::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera, textureHandle_); }

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

Light::~Light() { delete model_; }

 void Light::PosCorrect() {
 }