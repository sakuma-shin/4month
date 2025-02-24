#include "Player.h"

using namespace KamataEngine;

Player::~Player()
{



}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle,KamataEngine::Camera* camera)
{

	//NULLチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	//インスタンス
	input_ = Input::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();


}

void Player::Update()
{

	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };

	//キャラクターの移動速度
	const float kCharacterSpeed = 0.2f;

	//押した方向で移動ベクトルを変更(左右)
	if (input_->PushKey(DIK_A)) {

		move.x -= kCharacterSpeed;

	}

	if (input_->PushKey(DIK_D)) {

		move.x += kCharacterSpeed;

	}

	//押した方向で移動ベクトルを変更(上下)
	if (input_->PushKey(DIK_W)) {

		move.z += kCharacterSpeed;

	}

	if (input_->PushKey(DIK_S)) {

		move.z -= kCharacterSpeed;

	}

	//座標移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.z += move.z;

	worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

}

void Player::Draw(Camera* camera)
{

	model_->Draw(worldTransform_,*camera,textureHandle_);

}

KamataEngine::Vector3 Player::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得
	// ワールド行列のTx
	worldPos.x = worldTransform_.matWorld_.m[3][0];

	// ワールド行列のTy
	worldPos.y = worldTransform_.matWorld_.m[3][1];

	// ワールド行列のTz
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::setParent(const KamataEngine::WorldTransform* parent)
{

	worldTransform_.parent_ = parent;

}
