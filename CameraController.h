#pragma once
#include <KamataEngine.h>
#include <3d/Camera.h>
#include <3d/WorldTransform.h>

class Player;

class CameraController {

public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	const KamataEngine::Camera& GetCamera() const { return camera_; }

private:

	KamataEngine::Camera camera_;

	Player* target_ = nullptr;

	//追従対象とカメラ座標の差
	KamataEngine::Vector3 targetOffset_ = { 0,0,-15.0f };

};