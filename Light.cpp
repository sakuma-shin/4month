#include "Light.h"
#include <cassert>
#include"GameScene.h"

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity) {
	/*sprite_ = sprite;*/
	worldTransform_.Initialize();
	sprite_ = Sprite::Create(textureHandle, {}); // 各LightごとにSpriteを作成

	initialPos_ = initialPos;
	sprite_->SetSize({width_,height_});
	velocity_ = velocity;

	width_ = 20.0f;
	height_ = 20.0f;
	/*growtype_ = type;
	newType_ = NO;*/
	isReflection_ = false;
}

void Light::Update() {
	/*Grow();*/
	
	//if (壁に当たったら速度0)
	if (height_ >= 400) {
		velocity_ = {};
	}

	float reflectionWidth = 800.0f; // 反射する境界
	if (width_ >= reflectionWidth) {
		// if(動きが斜めじゃないとき)
		isReflection_ = 1;
		//if(右下がりに当たって反射する場合)
		newVelocity_ = {velocity_.y,velocity_.x};

		//if (右上がりに当たる場合)
		/*newVelocity_ = {-velocity_.y, -velocity_.x};*/

	} else {
		width_ += velocity_.x;
		height_ += velocity_.y;
	}

	//switch (growtype_) {
	//case Right:

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

	//case Reflection:

	//	break;
	//};

	

	/*ImGui::Begin("Light");
	ImGui::DragFloat3("Light.pos", &initialPos_.x, 0.01f);;
	ImGui::DragFloat("Light.width", &width_, 0.01f);
	ImGui::DragFloat("Light.height", &height_, 0.01f);
	ImGui::End();*/

	sprite_->SetSize({width_, height_});
	sprite_->SetPosition({initialPos_.x, initialPos_.y});

}


void Light::Draw() {
	//sprite_->Draw(); 
}

//void Light::Grow() {
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
//}

Light::~Light() { 
delete sprite_; }


