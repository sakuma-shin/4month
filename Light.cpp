#define _USE_MATH_DEFINES

#include "Light.h"
#include "GameScene.h"
#include "Map.h"
#include "MathUtility.h"
#include "math.h"
#include <algorithm>
#include <cassert>
#include <string>
using namespace KamataEngine;

void Light::Initialize(uint32_t textureHandle, Model* model, GrowType type, Vector3 initialPos, Vector3 scale_, std::vector<Target*> target, int color) {
	initialPos_ = initialPos;

	worldTransform_.Initialize();
	worldTransform_.scale_ = scale_;
	worldTransform_.translation_ = initialPos_;
	model_ = model;
	textureHandle_ = textureHandle;
	newtextureHandle_ = textureHandle;

	growtype_ = type;
	newType_ = NO;
	prevGrowType_ = growtype_;
	isMapHit = false;
	isRightUpHit = false;
	isRightDownHit = false;
	isVerticalHit = false;
	isHorizonalHit = false;
	isplysmHit = false;
	isWallHit = true;

	target_ = target;

	color_ = color;

	objectColor_.Initialize();
	objectColor_.SetColor({1, 1, 1, 0.5f});
}

void Light::Update() {
	Grow();

	if (growtype_ == NO) {
		Vector3 endPos = Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_);
		if (map_->CheckCollisionRay(initialPos_, endPos)) {
			worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
			worldTransform_.translation_ = initialPos_;
			growtype_ = prevGrowType_;
			isRefrected = false;
		}
	}

	if (!map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_))) {
		if (growtype_ == NO) {
			worldTransform_.scale_ = {0.5f, 0.5f, 0.5f};
			worldTransform_.translation_ = initialPos_;
		}

		growtype_ = prevGrowType_;
		isRefrected = false;
	}

	for (Target* target : target_) { //
		if (target->Getnumber() == map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_))) {

			if (target->Getcolor() == color_) {
				target->isHit();
			}
		} else {
			target->noHit();
		}
	}

	if (worldTransform_.scale_.x >= 1.0f && growtype_ == Down || worldTransform_.scale_.x <= -1.0f && growtype_ == Up) {
		if (map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_))) {
			OnCollisionMap(map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_)));
		}
	}

	if (worldTransform_.scale_.z >= 1.0f && growtype_ == Right || growtype_ == Left) {
		if (map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_))) {
			OnCollisionMap(map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_)));
		}
	}

	if (worldTransform_.scale_.x >= 1.0f && growtype_ == DownLeft || growtype_ == DownRight || growtype_ == UpLeft || growtype_ == UpRight) {
		if (map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_))) {
			OnCollisionMap(map_->CheckCollision(Add(Add(initialPos_, worldTransform_.scale_), worldTransform_.scale_)));
		}
	}

	worldTransform_.UpdateMatrix();
}

void Light::Draw(Camera* camera) { model_->Draw(worldTransform_, *camera, textureHandle_, &objectColor_); }

void Light::Grow() {
	float kSpeed = 1.0f;
	switch (growtype_) {
	case Up:

		velocity_ = {-kSpeed, 0.0f, 0.0f};

		break;

	case Down:
		velocity_ = {kSpeed, 0.0f, 0.0f};

		break;

	case Left:
		velocity_ = {
		    0.0f,
		    0.0f,
		    kSpeed,
		};

		break;

	case Right:
		velocity_ = {
		    0.0f,
		    0.0f,
		    kSpeed,
		};

		break;

	case DownRight:
		worldTransform_.rotation_ = {0.0f, -(1.0f / 4.0f) * float(M_PI), 0.0f};
		velocity_ = {kSpeed, 0.0f, kSpeed};

		break;

	case UpRight:
		worldTransform_.rotation_ = {0.0f, -(7.0f / 4.0f) * float(M_PI), 0.0f};
		velocity_ = {-kSpeed, 0.0f, kSpeed};

		break;

	case UpLeft:
		worldTransform_.rotation_ = {0.0f, -(5.0f / 4.0f) * float(M_PI), 0.0f};
		velocity_ = {-kSpeed, 0.0f, -kSpeed};

		break;

	case DownLeft:
		worldTransform_.rotation_ = {0.0f, -(3.0f / 4.0f) * float(M_PI), 0.0f};
		velocity_ = {kSpeed, 0.0f, -kSpeed};

		break;
	case NO:
		velocity_ = {0.0f, 0.0f, 0.0f};

		break;
	}

	if (growtype_ == DownRight) {
		worldTransform_.scale_.x += (velocity_.x * sqrtf(2)) / 2;
		worldTransform_.scale_.y = velocity_.y;
		worldTransform_.scale_.z = velocity_.z / sqrtf(2);
		worldTransform_.translation_.x += velocity_.x / 2;
		worldTransform_.translation_.y += velocity_.y / 2;
		worldTransform_.translation_.z += velocity_.z / 2;
	} else if (growtype_ == DownLeft) {
		worldTransform_.scale_.x += (velocity_.x * sqrtf(2)) / 2;
		worldTransform_.scale_.y = velocity_.y;
		worldTransform_.scale_.z = velocity_.z / sqrtf(2);
		worldTransform_.translation_.x += velocity_.x / 2;
		worldTransform_.translation_.y += velocity_.y / 2;
		worldTransform_.translation_.z += velocity_.z / 2;
	} else if (growtype_ == UpRight) {
		worldTransform_.scale_.x += (velocity_.x * sqrtf(2)) / 2;
		worldTransform_.scale_.y = velocity_.y;
		worldTransform_.scale_.z = velocity_.z / sqrtf(2);
		worldTransform_.translation_.x += velocity_.x / 2;
		worldTransform_.translation_.y += velocity_.y / 2;
		worldTransform_.translation_.z += velocity_.z / 2;
	} else if (growtype_ == UpLeft) {
		worldTransform_.scale_.x += (velocity_.x * sqrtf(2)) / 2;
		worldTransform_.scale_.y = velocity_.y;
		worldTransform_.scale_.z = velocity_.z / sqrtf(2);
		worldTransform_.translation_.x += velocity_.x / 2;
		worldTransform_.translation_.y += velocity_.y / 2;
		worldTransform_.translation_.z += velocity_.z / 2;
	} else {
		worldTransform_.scale_.x += velocity_.x / 2;
		worldTransform_.scale_.y += velocity_.y / 2;
		worldTransform_.scale_.z += velocity_.z / 2;
		worldTransform_.translation_.x += velocity_.x / 2;
		worldTransform_.translation_.y += velocity_.y / 2;
		worldTransform_.translation_.z += velocity_.z / 2;
	}
}

Light::~Light() {}

Vector3 Light::GetEndPosition() {
	if (prevGrowType_ == Down) {
		if (newType_ == Left) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Right) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z - worldTransform_.scale_.z + 1.0f};
		}
		if (newType_ == Down) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 1.0f, 0.0f, worldTransform_.translation_.z};
		}
		if (newType_ == DownRight) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z - worldTransform_.scale_.z - 0.5f};
		}
		if (newType_ == DownLeft) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z - worldTransform_.scale_.z - 0.5f};
		}
		if (newType_ == UpRight) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z - worldTransform_.scale_.z - 0.5f};
		}
		if (newType_ == UpLeft) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z - worldTransform_.scale_.z - 0.5f};
		}
	} else if (prevGrowType_ == Left) {
		if (newType_ == Left) {
			return {worldTransform_.translation_.x, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 1.0f};
		}
		if (newType_ == Up) {
			return {worldTransform_.translation_.x, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Down) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}

	} else if (prevGrowType_ == Up) {
		if (newType_ == Left) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z};
		}
		if (newType_ == Right) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x - 1.0f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Down) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Up) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x, 0.0f, worldTransform_.translation_.z};
		}
	} else if (prevGrowType_ == Right) {
		if (newType_ == Left) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x - 1.0f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z};
		}
		if (newType_ == Right) {
			return {worldTransform_.translation_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Down) {
			return {worldTransform_.translation_.x + worldTransform_.scale_.x + 0.5f, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
		if (newType_ == Up) {
			return {worldTransform_.translation_.x, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 0.5f};
		}
	}
	return {worldTransform_.translation_.x, 0.0f, worldTransform_.translation_.z + worldTransform_.scale_.z + 1.0f};
}

void Light::OnCollisionMap(int mapNum) {
	switch (growtype_) {
	case Up:
		switch (mapNum) {
		case 11:
			growtype_ = NO;

			break;

		case 31:
			growtype_ = NO;
			newType_ = Left;
			break;

		case 32:
			growtype_ = NO;
			newType_ = Right;
			break;

		case 51:
			newType_ = Up;
			growtype_ = NO;
			color_ = 1;
			break;

		case 93:
			growtype_ = NO;
			newType_ = Left;
			break;

		case 94:
			growtype_ = NO;
			newType_ = Right;
			break;
		}
		break;

	case Down:
		switch (mapNum) {
		case 31:
			growtype_ = NO;
			newType_ = Right;
			break;

		case 32:
			growtype_ = NO;
			newType_ = Left;
			break;

		case 51:
			newType_ = Down;
			growtype_ = NO;
			break;

		case 93:
			growtype_ = NO;
			newType_ = Right;
			break;

		case 94:
			growtype_ = NO;
			newType_ = Left;
			break;
		}
		break;

	case Left:
		switch (mapNum) {
		case 31:
			growtype_ = NO;
			newType_ = Down;
			break;

		case 32:
			growtype_ = NO;
			newType_ = Up;
			break;

		case 51:
			newType_ = Left;
			growtype_ = NO;
			break;

		case 52:
			newType_ = Left;
			growtype_ = NO;
			color_ = 2;
			newtextureHandle_ = TextureManager::Load("color/purple.png");
			break;

		case 91:
			growtype_ = NO;
			newType_ = Up;
			break;

		case 92:
			growtype_ = NO;
			newType_ = Down;
			break;
		}
		break;

	case Right:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;

		case 31:
			growtype_ = NO;
			newType_ = Down;
			break;

		case 32:
			growtype_ = NO;
			newType_ = Up;
			break;

		case 91:
			growtype_ = NO;
			newType_ = Up;
			break;

		case 92:
			growtype_ = NO;
			newType_ = Down;
			break;

		case 51:
			newType_ = Right;
			growtype_ = NO;
			break;

		case 52:
			newType_ = Right;
			growtype_ = NO;
			color_ = 2;
			newtextureHandle_ = TextureManager::Load("color/purple.png");
			break;
		}
		break;

	case DownRight:

		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;

		case 33:
			growtype_ = NO;
			newType_ = UpRight;
			break;

		case 34:
			growtype_ = NO;
			newType_ = DownLeft;
			break;
		}
		break;

	case UpRight:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;

		case 33:
			growtype_ = NO;
			newType_ = DownRight;
			break;

		case 34:
			growtype_ = NO;
			newType_ = UpLeft;
			break;
		}
		break;

	case UpLeft:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;

		case 33:
			growtype_ = NO;
			newType_ = DownRight;
			break;

		case 34:
			growtype_ = NO;
			newType_ = UpRight;
			break;
		}
		break;

	case DownLeft:
		switch (mapNum) {
		case 1:
			growtype_ = NO;

			break;

		case 33:
			growtype_ = NO;
			newType_ = UpLeft;
			break;

		case 34:
			growtype_ = NO;
			newType_ = DownRight;
			break;
		}
		break;
	}
	growtype_ = NO;
	velocity_ = {};
	isMapHit = true;

	Vector3 tip = initialPos_;
	Vector3 initial2MapCenter;
	initial2MapCenter.x = tip.x;
	initial2MapCenter.y = tip.y;
	initial2MapCenter.z = tip.z;
}

int Light::Digit(int number) {
	if (number / 10 < 1) {
		return number;
	}
	int k = 0;
	for (; number / 10 >= 1; k++) {
		number = number / 10;
	}
	return number;
}
