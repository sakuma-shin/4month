#pragma once
#include <KamataEngine.h>
#include <3d/WorldTransform.h>

class Player;

class CameraAngle {

public:

	void Initialize(const KamataEngine::WorldTransform& worldTransform, Player* player);

	void Update();

	KamataEngine::Camera& GetCamera() { return camera_; }

	const KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

	void SetEye(const KamataEngine::Vector3& eye);

	void SetTarget(const KamataEngine::Vector3& target);

	void SetUp(const KamataEngine::Vector3& up);

	void UpdateViewMatrix();

	const KamataEngine::Matrix4x4& GetViewMatrix() const { return matView; }

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

	KamataEngine::Matrix4x4 matView;

	Player* player_;

};