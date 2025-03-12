#include "Color.h"

using namespace KamataEngine;

void Color::Initialize(KamataEngine::Model* model, uint32_t purpleTextureHandle, uint32_t redTextureHandle, uint32_t blueTextureHandle)
{

	assert(model);

	model_ = model;
	purpleTextureHandle_ = purpleTextureHandle;
	redTextureHandle_ = redTextureHandle;
	blueTextureHandle_ = blueTextureHandle;



	//インスタンス
	input_ = Input::GetInstance();

	worldTransform_.Initialize();

}

void Color::Update()
{

	if (input_->TriggerKey(DIK_RETURN)) {

		isSplit = true;

	}

}

void Color::Draw(Camera* camera)
{
	if (!isSplit) {

		model_->Draw(worldTransform_, *camera, purpleTextureHandle_);

	}
	

}
