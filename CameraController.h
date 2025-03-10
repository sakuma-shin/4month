#pragma once
#include <KamataEngine.h>
#include <3d/Camera.h>
#include <3d/WorldTransform.h>

class Player;

class CameraController {

	//矩形
	struct Rect {

		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;

	};


public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	const KamataEngine::Camera& GetCamera() const { return camera_; }

	void SetMovableArea(Rect area) { movableArea_ = area; }

private:

	KamataEngine::Camera camera_;

	Player* target_ = nullptr;

	//追従対象とカメラ座標の差
	KamataEngine::Vector3 targetOffset_ = { 0,0,-15.0f };

	Rect movableArea_ = { 0,100,0,100 };

};