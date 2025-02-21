#include "Player.h"

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle,KamataEngine::Camera* camera)
{

	//NULLチェック
	assert(model);

	//引数の内容をメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	//ワールド変換の初期化
	worldTransform_.Initialize();


}

void Player::Update()
{

	worldTransform_.TransferMatrix();

}

void Player::Draw()
{

	model_->Draw(worldTransform_,*camera_,textureHandle_);

}
