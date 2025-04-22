#include "Color.h"

using namespace KamataEngine;

void Color::Initialize(KamataEngine::Model* model, uint32_t purpleTextureHandle, uint32_t redTextureHandle, uint32_t blueTextureHandle, uint32_t greenTextureHandle) {
	assert(model);

	model_ = model;
	purpleTextureHandle_ = purpleTextureHandle;
	redTextureHandle_ = redTextureHandle;
	blueTextureHandle_ = blueTextureHandle;
	greenTextureHandle_ = greenTextureHandle;

	// インスタンス
	input_ = Input::GetInstance();

	// ワールド変換を初期化
	purpleWorldTransform_.Initialize();
	redWorldTransform_.Initialize();
	blueWorldTransform_.Initialize();

	purpleWorldTransform_.translation_ = {-10.0f, 0.0f, 0.0f};
	purpleWorldTransform_.UpdateMatrix();

	redWorldTransform_.translation_.x = purpleWorldTransform_.translation_.x + 5.0f;
	redWorldTransform_.UpdateMatrix();

	blueWorldTransform_.translation_.x = purpleWorldTransform_.translation_.x - 5.0f;
	blueWorldTransform_.UpdateMatrix();
}

void Color::Update() {

	if (input_->TriggerKey(DIK_RETURN)) {
		isSplit = !isSplit;
	}

	/*ImGui::Begin("isSplit");
	ImGui::Checkbox("IsSplit", &isSplit);
	ImGui::End();*/
}

void Color::Draw(Camera* camera) {
	if (!isSplit) {

		model_->Draw(purpleWorldTransform_, *camera, purpleTextureHandle_);
	} else {

		model_->Draw(redWorldTransform_, *camera, redTextureHandle_);
		model_->Draw(blueWorldTransform_, *camera, blueTextureHandle_);
	}
}
