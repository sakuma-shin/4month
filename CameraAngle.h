#pragma once
#include <KamataEngine.h>
#include <3d/WorldTransform.h>

class Player;

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

	KamataEngine::Vector3 translation_;      // 初期座標
	KamataEngine::Vector3 rotation_;         // 初期回転角度
	KamataEngine::Vector3 cameraPosition_;   // カメラ位置
	KamataEngine::Vector3 cameraTarget_;     // カメラターゲット
	KamataEngine::Vector3 cameraUp_;

	//入力
	KamataEngine::Input* input_ = nullptr;

	Player* player_;

};