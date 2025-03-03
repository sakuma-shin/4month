#include "Light.h"
#include "GameScene.h"
#include <cassert>
#include <string>

using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Vector3 initialPos, GrowType type) {
	/*sprite_ = sprite;*/
	worldTransform_.Initialize();
	sprite_ = Sprite::Create(textureHandle, {}); // 各LightごとにSpriteを作成

	initialPos_ = initialPos;
	sprite_->SetSize({width_, height_});

	width_ = 20.0f;
	height_ = 20.0f;
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
	isWallHit = false;
}

void Light::Update() {
	


	/*#ifdef DEBUG*/
	if (isRightUpHit) {
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
	}

	// #endif // DEBUG


	Grow();

	if (!isMapHit) {
		growtype_ = prevGrowType_;
	}

	if (isMapHit) {
		OnCollisionMap();
	} 

	/*ImGui::Begin("Light");
	ImGui::DragFloat3("Light.pos", &initialPos_.x, 0.01f);
	ImGui::DragFloat("Light.width", &width_, 0.01f);
	ImGui::DragFloat("Light.height", &height_, 0.01f);
	ImGui::Checkbox("Light.MapHit", &isMapHit);
	ImGui::Checkbox("Light.RightUpHit", &isRightUpHit);
	ImGui::Checkbox("Light.LeftUpHit", &isRightDownHit);
	ImGui::Checkbox("Light.VerticalHit", &isVerticalHit);
	ImGui::Checkbox("Light.HorizonalHit", &isHorizonalHit);
	ImGui::Checkbox("Light.PlysmHit", &isplysmHit);
	ImGui::Checkbox("Light.wallHit", &isWallHit);
	ImGui::End();*/

	// 各Lightごとにウィンドウを作成
	std::string windowName = "Light_" + std::to_string(reinterpret_cast<uintptr_t>(this));
	ImGui::Begin(windowName.c_str());

	ImGui::DragFloat3("Position", &initialPos_.x, 0.1f);
	ImGui::DragFloat("Width", &width_, 0.1f);
	ImGui::DragFloat("Height", &height_, 0.1f);

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



	sprite_->SetSize({width_, height_});
	sprite_->SetPosition({initialPos_.x, initialPos_.y});
}

void Light::Draw() { sprite_->Draw(); }

void Light::Grow() {
	float kSpeed = 1.0f;
	switch (growtype_) {
	case Up:

		velocity_ = {0.0f, -kSpeed};
		sprite_->SetRotation(0.0f);

		break;

	case Down:
		velocity_ = {0.0f, kSpeed};
		sprite_->SetRotation(0.0f);

		break;

	case Left:
		velocity_ = {-kSpeed, 0.0f};
		sprite_->SetRotation(0.0f);

		break;

	case Right:
		velocity_ = {kSpeed, 0.0f};
		sprite_->SetRotation(0.0f);

		break;

	case DownRight:
		sprite_->SetRotation(0.5f);
		velocity_ = {kSpeed, 0.0f};

		break;

	case UpRight:
		sprite_->SetRotation(-0.5f);
		velocity_ = {kSpeed, 0.0f};

		break;

	case UpLeft:
		sprite_->SetRotation(0.5f);
		velocity_ = {-kSpeed, 0.0f};

		break;

	case DownLeft:
		sprite_->SetRotation(-0.5f);
		velocity_ = {-kSpeed, 0.0f};

		break;
	case NO:
		velocity_ = {0.0f, 0.0f};

		break;
	}
	width_ += velocity_.x;
	height_ += velocity_.y;
}

Light::~Light() { delete sprite_; }

Vector3 Light::GetEndPosition() {
	float angle = sprite_->GetRotation(); // 回転角度 (ラジアン)

	// 終点の相対位置 (幅と高さを考慮)
	float localEndX = width_;
	float localEndY = height_;


	// 回転行列を適用
	float rotatedX = cos(angle) * localEndX - sin(angle) * localEndY;
	float rotatedY = sin(angle) * localEndX + cos(angle) * localEndY;

	// 初期位置にオフセットを加える
	return {initialPos_.x + rotatedX - velocity_.x, initialPos_.y + rotatedY - velocity_.y, initialPos_.z};

}

//void Light::OnCollisionMap() {
//
//	  // 以前の growtype_ を保存
//	prevGrowType_ = growtype_;
//
//
//	switch (growtype_) {
//	case Up:
//		switch (hitType_) {
//		case RightUp:
//
//			newType_ = Right;
//			newType2_ = NO;
//
//			break;
//
//		case RightDown:
//
//			newType_ = Left;
//			newType2_ = NO;
//
//			break;
//
//		case plysm:
//			newType_ = UpRight;
//			newType2_ = UpLeft;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case Down:
//		switch (hitType_) {
//		case RightUp:
//
//			newType_ = Left;
//			newType2_ = NO;
//
//			break;
//
//		case RightDown:
//
//			newType_ = Right;
//			newType2_ = NO;
//
//			break;
//
//		case plysm:
//			newType_ = DownRight;
//			newType2_ = DownLeft;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case Left:
//		switch (hitType_) {
//		case RightUp:
//
//			newType_ = Down;
//			newType2_ = NO;
//
//			break;
//
//		case RightDown:
//
//			newType_ = Up;
//			newType2_ = NO;
//
//			break;
//
//		case plysm:
//			newType_ = DownLeft;
//			newType2_ = UpLeft;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case Right:
//		switch (hitType_) {
//		case RightUp:
//
//			newType_ = Up;
//			newType2_ = NO;
//
//			break;
//
//		case RightDown:
//
//			newType_ = Down;
//			newType2_ = NO;
//
//			break;
//
//		case plysm:
//			newType_ = DownRight;
//			newType2_ = UpRight;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case DownRight:
//		switch (hitType_) {
//		case Horizonal:
//
//			newType_ = UpRight;
//			newType2_ = NO;
//
//			break;
//
//		case Vertical:
//
//			newType_ = DownLeft;
//			newType2_ = NO;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case UpRight:
//		switch (hitType_) {
//		case Horizonal:
//
//			newType_ = DownRight;
//			newType2_ = NO;
//
//			break;
//
//		case Vertical:
//
//			newType_ = UpLeft;
//			newType2_ = NO;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case UpLeft:
//		switch (hitType_) {
//		case Horizonal:
//
//			newType_ = DownLeft;
//			newType2_ = NO;
//
//			break;
//
//		case Vertical:
//
//			newType_ = UpRight;
//			newType2_ = NO;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//
//	case DownLeft:
//		switch (hitType_) {
//		case Horizonal:
//
//			newType_ = UpLeft;
//			newType2_ = NO;
//
//			break;
//
//		case Vertical:
//
//			newType_ = DownRight;
//			newType2_ = NO;
//
//			break;
//
//		default:
//			newType_ = NO;
//			newType2_ = NO;
//
//			break;
//		}
//
//		break;
//	case NO:
//		velocity_ = {0.0f, 0.0f};
//
//		break;
//	}
//	growtype_ = NO;
//}

void Light::OnCollisionMap() {
	// 以前の growtype_ を保存
	prevGrowType_ = growtype_;

	switch (growtype_) {
	case Up:
		switch (hitType_) {
		case RightUp:
			newType_ = Right;
			break;
		case RightDown:
			newType_ = Left;
			break;
		case plysm:
			newType_ = UpRight;
			newType2_ = UpLeft;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case Down:
		switch (hitType_) {
		case RightUp:
			newType_ = Left;
			break;
		case RightDown:
			newType_ = Right;
			break;
		case plysm:
			newType_ = DownRight;
			newType2_ = DownLeft;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case Left:
		switch (hitType_) {
		case RightUp:
			newType_ = Down;
			break;
		case RightDown:
			newType_ = Up;
			break;
		case plysm:
			newType_ = DownLeft;
			newType2_ = UpLeft;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case Right:
		switch (hitType_) {
		case RightUp:
			newType_ = Up;
			break;
		case RightDown:
			newType_ = Down;
			break;
		case plysm:
			newType_ = DownRight;
			newType2_ = UpRight;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case DownRight:
		switch (hitType_) {
		case Horizonal:
			newType_ = UpRight;
			break;
		case Vertical:
			newType_ = DownLeft;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case UpRight:
		switch (hitType_) {
		case Horizonal:
			newType_ = DownRight;
			break;
		case Vertical:
			newType_ = UpLeft;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case UpLeft:
		switch (hitType_) {
		case Horizonal:
			newType_ = DownLeft;
			break;
		case Vertical:
			newType_ = UpRight;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case DownLeft:
		switch (hitType_) {
		case Horizonal:
			newType_ = UpLeft;
			break;
		case Vertical:
			newType_ = DownRight;
			break;
		default:
			newType_ = NO;
			newType2_ = NO;
			break;
		}
		break;

	case NO:
		velocity_ = {0.0f, 0.0f};
		break;
	}

	// マップに当たったら動きを止める
	growtype_ = NO;
}
