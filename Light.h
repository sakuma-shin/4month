#pragma once
#include "KamataEngine.h"
#include "Target.h"

using namespace KamataEngine;
class Map;
class GameScene;
class Light {
public:
	enum GrowType { Up, Down, Right, Left, UpRight, DownRight, UpLeft, DownLeft, NO };

	enum HitType { RightUp, RightDown, Horizonal, Vertical, Wall, plysm };
	void Initialize(uint32_t textureHandle, Model* model, GrowType type, Vector3 initialPos, Vector3 scale_, std::vector<Target*> target, int color);

	void Update();

	void Draw(Camera* camera);

	void Grow();

	// Vector2 GetSize() const { return {width_,height_}; }
	~Light();

	/*uint32_t IsReflection() const { return isReflection_; }*/

	Vector3 GetEndPosition();

	GrowType GetGrowType() const { return growtype_; }
	GrowType GetNewType() const { return newType_; }
	GrowType GetNewType2() const { return newType2_; }

	void SetGrowType(GrowType type) { growtype_ = type; }

	/*bool SetIsrefrection(bool ref) { isReflection_ = ref; }*/

	// Vector2 GetNewVelocity() const { return newVelocity_; }

	void SetRefrected() { isRefrected = true; }

	bool CanReflect() const { return growtype_ == NO && !isRefrected; }

	void OnCollisionMap(int mapNum);

	void SetMapData(Map* map) { map_ = map; }

	Vector3 GetinitialPos() { return initialPos_; }

	void Death() { live = false; }

	bool IsDeath() { return live; }
	uint32_t GetnewTextureHandle() { return newtextureHandle_; }

	int Digit(int number);

	int Getcolor() { return color_; }

private:
	// float width_=0.0f;
	// float height_=0.0f;

	// Sprite* sprite_=nullptr;

	Model* model_ = nullptr;

	Vector3 initialPos_ = {};

	uint32_t textureHandle_ = 0;
	WorldTransform worldTransform_;

	GrowType growtype_ = NO;
	GrowType newType_ = NO;
	GrowType newType2_ = NO;
	GrowType prevGrowType_ = NO;

	Vector3 velocity_ = {};

	GameScene* gameScene_ = nullptr;

	/*uint32_t isReflection_ = 0;*/

	Vector3 newVelocity_ = {};

	bool isRefrected = false;

	HitType hitType_;

	Map* map_;

	bool isMapHit = false;
	bool isRightUpHit = false;
	bool isRightDownHit = false;
	bool isVerticalHit = false;
	bool isHorizonalHit = false;
	bool isplysmHit = false;
	bool isWallHit = false;

	bool live = true;
	uint32_t newtextureHandle_ = 0;

	std::vector<Target*> target_;

	int color_;

	ObjectColor objectColor_;
};
