#include "Player.h"
#include "Map.h"

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

	// プレイヤーの初期位置を設定
	//worldTransform_.translation_ = { -5.0f, 2.5f, 0.0f };

	//Vector3 playerPosition=map_->

}

void Player::Update()
{

	////キャラクターの移動ベクトル
	//Vector3 move = { 0,0,0 };

	////キャラクターの移動速度
	//const float kCharacterSpeed = 0.2f;

	////押した方向で移動ベクトルを変更(左右)
	//if (input_->PushKey(DIK_A)) {

	//	move.x -= kCharacterSpeed;

	//}

	//if (input_->PushKey(DIK_D)) {

	//	move.x += kCharacterSpeed;

	//}

	////押した方向で移動ベクトルを変更(上下)
	//if (input_->PushKey(DIK_W)) {

	//	move.z += kCharacterSpeed;

	//}

	//if (input_->PushKey(DIK_S)) {

	//	move.z -= kCharacterSpeed;

	//}

	////座標移動
	//worldTransform_.translation_.x += move.x;
	//worldTransform_.translation_.z += move.z;

	//移動入力
	if (Input::GetInstance()->PushKey(DIK_D)||Input::GetInstance()->PushKey(DIK_A)) {

		//加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_D)) {

			acceleration.x += kAcceleration;

		} else if (Input::GetInstance()->PushKey(DIK_A)) {

			acceleration.x -= kAcceleration;

		}

		velocity_.x += acceleration.x;

	} else {

		velocity_.x *= (1.0f - kAttenuation);

	}

	if (Input::GetInstance()->PushKey(DIK_W) || Input::GetInstance()->PushKey(DIK_S)) {

		//加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_W)) {

			acceleration.z += kAcceleration;

		} else if (Input::GetInstance()->PushKey(DIK_S)) {

			acceleration.z -= kAcceleration;

		}

		velocity_.z += acceleration.z;

	} else {

		velocity_.z *= (1.0f - kAttenuation);

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
