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

 void Light::AdjustScaleOffset() {
	 // X方向の補正
	 if (worldTransform_.scale_.x > 1.0f) {
		 worldTransform_.translation_.x = initialPos_.x + (worldTransform_.scale_.x - 1.0f) ;
	 } else {
		 worldTransform_.translation_.x = initialPos_.x;
	 }

	 // Y方向の補正
	 if (worldTransform_.scale_.y > 1.0f) {
		 worldTransform_.translation_.y = initialPos_.y + (worldTransform_.scale_.y - 1.0f);
	 } else {
		 worldTransform_.translation_.y = initialPos_.y;
	 }

	 // Z方向の補正（必要なら追加）
 }

 Matrix4x4 Light::CalculateWorldMatrix() {
	 Matrix4x4 scaleMatrix = MakeScaleMatrix(worldTransform_.scale_);
	 Matrix4x4 rotationMatrix = RotateXYZMatrix(worldTransform_.rotation_);
	 Matrix4x4 translationMatrix = MakeTraslateMatrix(worldTransform_.translation_);

	  // **スケールに応じたオフセット補正**
	 Vector3 offset = CalculateScaleOffset();
	 Matrix4x4 offsetMatrix = MakeTraslateMatrix(offset);

	 // **スケール補正を加えた行列計算**
	 return translationMatrix * offsetMatrix * rotationMatrix * scaleMatrix;

 }

Vector3 Light::CalculateScaleOffset() {
	 Vector3 offset = {0.0f, 0.0f, 0.0f};

	 // X軸方向のスケール補正 (負のスケール対応)
	 if (fabs(worldTransform_.scale_.x) > 1.0f) {
		 float sign = (worldTransform_.scale_.x > 0) ? 1.0f : -1.0f;
		 offset.x = (fabs(worldTransform_.scale_.x) - 1.0f) * 0.5f * sign;
	 }

	 // Y軸方向のスケール補正 (負のスケール対応)
	 if (fabs(worldTransform_.scale_.y) > 1.0f) {
		 float sign = (worldTransform_.scale_.y > 0) ? 1.0f : -1.0f;
		 offset.y = (fabs(worldTransform_.scale_.y) - 1.0f) * 0.5f * sign;
	 }

	 return offset;
 }
