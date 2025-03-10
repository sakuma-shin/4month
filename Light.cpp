#include "Light.h"
#include "GameScene.h"
#include "Map.h"
#include "MathUtility.h"
#include <algorithm>
#include <cassert>
#include <string>

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Model* model, GrowType type, Vector3 initialPos) {
	/*sprite_ = sprite;*/
	initialPos_ = initialPos;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
	worldTransform_.translation_ = initialPos_;
	// sprite_ = Sprite::Create(textureHandle, {}); // 各LightごとにSpriteを作成
	model_ = model;
	textureHandle_ = textureHandle;
	// sprite_->SetSize({width_, height_});

	// width_ = 20.0f;
	// height_ = 20.0f;
	growtype_ = type;
	newType_ = NO;
	prevGrowType_ = growtype_;
	/*isReflection_ = false;*/
	isMapHit = false;
	isRightUpHit = false;
	isRightDownHit = false;
	isVerticalHit = false;
	isHorizonalHit = false;
	isplysmHit = false;
	isWallHit = true;
}

void Light::Update() {

	/*#ifdef DEBUG*/
	/*if (isRightUpHit) {
	    hitType_ = RightUp;
	}


	if (isRightDownHit) {
	    hitType_ = RightDown;
	}
	if (isVerticalHit) {
	    hitType_ = Vertical;
	}
	if (isHorizonalHit) {
	    hitType_ = Horizonal;
	}
	if (isplysmHit) {
	    hitType_ = plysm;
	}
	if (isWallHit) {
	    hitType_ = Wall;
	}*/

	// #endif // DEBUG

	//// 移動前の座標を保存
	//Vector3 prevPos = worldTransform_.translation_;
	//Vector3 prevScale = worldTransform_.scale_;

	Grow();

	if (!map_->CheckCollision(Add(initialPos_, worldTransform_.scale_))) {
		growtype_ = prevGrowType_;
	}

	if (map_->CheckCollision(Add(initialPos_, worldTransform_.scale_))) {
		OnCollisionMap(map_->CheckCollision(Add(initialPos_, worldTransform_.scale_)));
	}

	// 各Lightごとにウィンドウを作成
	std::string windowName = "Light_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());

	// ImGui::DragFloat3("Position", &initialPos_.x, 0.1f);
	// ImGui::DragFloat("Width", &width_, 0.1f);
	// ImGui::DragFloat("Height", &height_, 0.1f);

	ImGui::DragFloat3("light.translation", &worldTransform_.translation_.x, 0.01f);
	ImGui::DragFloat3("light.rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::DragFloat3("light.scale", &worldTransform_.scale_.x, 0.01f);
	ImGui::Checkbox("MapHit", &isMapHit);
	ImGui::Checkbox("RightUpHit", &isRightUpHit);
	ImGui::Checkbox("RightDownHit", &isRightDownHit);
	ImGui::Checkbox("VerticalHit", &isVerticalHit);
	ImGui::Checkbox("HorizonalHit", &isHorizonalHit);
	ImGui::Checkbox("PlysmHit", &isplysmHit);
	ImGui::Checkbox("WallHit", &isWallHit);

	// GrowType の選択 UI
	/*const char* growTypeNames[] = {"NO", "Up", "Down", "Left", "Right", "DownRight", "UpRight", "UpLeft", "DownLeft"};
	int currentType = static_cast<int>(growtype_);
	if (ImGui::Combo("GrowType", &currentType, growTypeNames, IM_ARRAYSIZE(growTypeNames))) {
	    growtype_ = static_cast<GrowType>(currentType);
	}*/

	// sprite_->SetSize({width_, height_});
	// sprite_->SetPosition({initialPos_.x, initialPos_.y});

	worldTransform_.UpdateMatrix();
}

void Light::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera, textureHandle_); }

void Light::Grow() {
	float kSpeed = 1.0f;
	switch (growtype_) {
	case Up:

		velocity_ = {-kSpeed, 0.0f, 0.0f};
		// sprite_->SetRotation(0.0f);

		break;

	case Down:
		velocity_ = {kSpeed, 0.0f, 0.0f};
		// sprite_->SetRotation(0.0f);

		break;

	case Left:
		velocity_ = {
		    0.0f,
		    0.0f,
		    kSpeed,
		};
		// sprite_->SetRotation(0.0f);

		break;

	case Right:
		velocity_ = {
		    0.0f,
		    0.0f,
		    -kSpeed,
		};
		// sprite_->SetRotation(0.0f);

		break;

	case DownRight:
		// sprite_->SetRotation(0.5f);
		velocity_ = {kSpeed, 0.0f, 0.0f};

		break;

	case UpRight:
		// sprite_->SetRotation(-0.5f);
		velocity_ = {kSpeed, 0.0f};

		break;

	case UpLeft:
		// sprite_->SetRotation(0.5f);
		velocity_ = {-kSpeed, 0.0f};

		break;

	case DownLeft:
		// sprite_->SetRotation(-0.5f);
		velocity_ = {-kSpeed, 0.0f};

		break;
	case NO:
		velocity_ = {0.0f, 0.0f};

		break;
	}
	worldTransform_.scale_.x += velocity_.x / 2;
	worldTransform_.scale_.y += velocity_.y / 2;
	worldTransform_.scale_.z += velocity_.z / 2;
	worldTransform_.translation_.x += velocity_.x / 2;
	worldTransform_.translation_.y += velocity_.y / 2;
	worldTransform_.translation_.z += velocity_.z / 2;
}

Light::~Light() {}

Vector3 Light::GetEndPosition() {
	// float angle = sprite_->GetRotation(); // 回転角度 (ラジアン)

	//// 終点の相対位置 (幅と高さを考慮)
	// float localEndX = width_;
	// float localEndY = height_;

	//// 回転行列を適用
	// float rotatedX = cos(angle) * localEndX - sin(angle) * localEndY;
	// float rotatedY = sin(angle) * localEndX + cos(angle) * localEndY;

	//// 初期位置にオフセットを加える
	// return {initialPos_.x + rotatedX - velocity_.x, initialPos_.y + rotatedY - velocity_.y, initialPos_.z};
	return {worldTransform_.translation_.x + worldTransform_.scale_.x, worldTransform_.translation_.y + worldTransform_.scale_.y, worldTransform_.translation_.z + worldTransform_.scale_.z};
}

void Light::OnCollisionMap(int mapNum) {

	growtype_ = NO;
	// 以前の growtype_ を保存
	prevGrowType_ = growtype_;

	switch (growtype_) {
	case Up:
		switch (mapNum) {
		case 11:
			growtype_ = NO;

			break;
		}
		break;

	case Down:
		switch (mapNum) {
		case 31:
			growtype_ = NO;

			break;
		}
		break;

	case Left:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;

	case Right:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;

	case DownRight:

		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;

	case UpRight:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;

	case UpLeft:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;

	case DownLeft:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;
		}
		break;
	}
	velocity_ = {};

	Vector3 tip = initialPos_ + worldTransform_.scale_;
	Vector3 initial2MapCenter;
	initial2MapCenter.x = tip.x / 2.0f;
	initial2MapCenter.y = tip.y / 2.0f;
	initial2MapCenter.z = tip.z / 2.0f;

	/*worldTransform_.translation_ = initial2MapCenter;
	worldTransform_.scale_.x= abs(tip.x);
	worldTransform_.scale_.y = abs(tip.y);
	worldTransform_.scale_.z = abs(tip.z);*/

	worldTransform_.scale_.x = std::clamp(worldTransform_.scale_.x, -initial2MapCenter.x, initial2MapCenter.x);
	/*worldTransform_.scale_.y = std::clamp(worldTransform_.scale_.y, -initial2MapCenter.y, initial2MapCenter.y);*/
	worldTransform_.scale_.z = std::clamp(worldTransform_.scale_.z, -initial2MapCenter.z, initial2MapCenter.z);

	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, initial2MapCenter.x, initial2MapCenter.x);
	/*worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, initial2MapCenter.y, initial2MapCenter.y);*/
	worldTransform_.translation_.z = std::clamp(worldTransform_.translation_.z, initial2MapCenter.z, initial2MapCenter.z);
}