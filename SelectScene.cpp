#include "SelectScene.h"

SelectScene::~SelectScene() {}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
}

void SelectScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;
	}

	if (input_->TriggerKey(DIK_RETURN)) {

		isExplanation_ = true;

	}

}

void SelectScene::Draw() {}
