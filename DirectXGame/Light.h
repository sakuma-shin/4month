#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene;
class Light {
public:
	/*enum GrowType { Up, Down, Right, Left,Reflection, NO };*/
	void Initialize(uint32_t textureHandle, Vector3 initialPos, Vector2 velocity);

	void Update();

	void Draw();

	/*void Grow();*/

	Vector2 GetSize() const { return {width_,height_}; }
	~Light();

	uint32_t IsReflection() const { return isReflection_; }

	Vector3 GetEndPosition() const { return {(initialPos_.x + width_)-velocity_.x, initialPos_.y + height_, initialPos_.z}; }

	/*GrowType GetGrowType() const { return growtype_; }
	GrowType GetNewType() const { return newType_; }

	void SetGrowType(GrowType type) { growtype_ = type; }*/

	/*bool SetIsrefrection(bool ref) { isReflection_ = ref; }*/


	Vector2 GetNewVelocity() const { return newVelocity_; }

	void SetRefrected() { isRefrected=true; }

	bool CanReflect() const { return isReflection_ && !isRefrected;}

private:

	float width_=0.0f;
	float height_=0.0f;

	Sprite* sprite_=nullptr;
	Vector3 initialPos_ = {};

	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_;

	/*GrowType growtype_ = NO;
	GrowType newType_ = NO;*/

	Vector2 velocity_ = {};

	GameScene* gameScene_ = nullptr;

	uint32_t isReflection_ = 0;

	Vector2 newVelocity_ = {};

	bool isRefrected = false;
};
