#pragma once
#include <KamataEngine.h>
#include <3d/WorldTransform.h>

class CameraAngle {

public:

	void Initialize(const KamataEngine::WorldTransform& worldTransform);

	void Update();

	KamataEngine::Camera& GetCamera() { return camera_; }

	const KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

private:

	//ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	//ビュープロジェクション
	KamataEngine::Camera camera_;

	KamataEngine::Vector3 translation_ = { 0.0f, 30.0f, -30.0f };
		
	KamataEngine::Vector3 rotation_ = { 0.5f, 0.0f, 0.0f };

};