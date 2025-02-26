#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene;

class Light {
public:
	void Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity);

	void Update();

	void Draw();

	Vector2 GetSize() const { return {width_, height_}; }

	~Light();

	uint32_t IsReflection() const { return isReflection_; }

	Vector3 GetEndPosition() const { return {(initialPos_.x + width_) - velocity_.x, initialPos_.y + height_, initialPos_.z}; }

	Vector2 GetNewVelocity() const { return newVelocity_; }

	void SetRefrected() { isRefrected = true; }

	bool CanReflect() const { return isReflection_ && !isRefrected; }

	// ワールド座標を取得する
	Vector3 GetWorldPosition() const {
		// ワールド行列から平行移動成分を取得
		return {
		    worldTransform_.matWorld_.m[3][0], // X 座標
		    worldTransform_.matWorld_.m[3][1], // Y 座標
		    worldTransform_.matWorld_.m[3][2]  // Z 座標
		};
	}

	Vector3 GetWorldPositionFromScreen(float screenPosX, float screenPosY);

private:
	float width_ = 0.0f;
	float height_ = 0.0f;

	Sprite* sprite_ = nullptr;
	Vector3 initialPos_ = {};

	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_;

	Vector2 velocity_ = {};

	GameScene* gameScene_ = nullptr;

	uint32_t isReflection_ = 0;

	Vector2 newVelocity_ = {};

	bool isRefrected = false;
};
