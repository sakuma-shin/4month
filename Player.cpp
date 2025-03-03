#include "Player.h"
#include "Map.h"
#include <algorithm>

using namespace KamataEngine;

Player::~Player()
{



}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle,KamataEngine::Camera* camera, const KamataEngine::Vector3& position)
{

	//NULLチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;
	worldTransform_.translation_ = position;

	//インスタンス
	input_ = Input::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();

}

void Player::Update()
{

// 移動入力
bool isMovingX = Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A);
bool isMovingZ = Input::GetInstance()->PushKey(DIK_W) || Input::GetInstance()->PushKey(DIK_S);

//X軸移動
if (isMovingX) {
	//加速
	Vector3 acceleration = {};
	if (Input::GetInstance()->PushKey(DIK_D)) {
		if (velocity_.x < 0.0f) {
			velocity_.x *= (1.0f - kAttenuation);
		}
		acceleration.x += kAcceleration;
	} else if (Input::GetInstance()->PushKey(DIK_A)) {
		if (velocity_.x > 0.0f) {
			velocity_.x *= (1.0f - kAttenuation);
		}
		acceleration.x -= kAcceleration;
	}

	velocity_.x += acceleration.x;
	velocity_.x = std::clamp(velocity_.x, -kLimitSpeed, kLimitSpeed);

	//斜め移動を防止
	velocity_.z = 0.0f;

} else {
	velocity_.x *= (1.0f - kAttenuation);
	if (std::abs(velocity_.x) < 0.01f) {
		velocity_.x = 0.0f;
	}
}

//Z軸移動
if (!isMovingX && isMovingZ) { //X軸が動いていない場合のみ許可
	//加速
	Vector3 acceleration = {};
	if (Input::GetInstance()->PushKey(DIK_W)) {
		if (velocity_.z < 0.0f) {
			velocity_.z *= (1.0f - kAttenuation);
		}
		acceleration.z += kAcceleration;
	} else if (Input::GetInstance()->PushKey(DIK_S)) {
		if (velocity_.z > 0.0f) {
			velocity_.z *= (1.0f - kAttenuation);
		}
		acceleration.z -= kAcceleration;
	}

	velocity_.z += acceleration.z;
	velocity_.z = std::clamp(velocity_.z, -kLimitSpeed, kLimitSpeed);

} else {
	velocity_.z *= (1.0f - kAttenuation);
	if (std::abs(velocity_.z) < 0.01f) {
		velocity_.z = 0.0f;
	}
}


	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.z += velocity_.z;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera* camera)
{

	model_->Draw(worldTransform_,*camera,textureHandle_);

}
