#include "SelectScene.h"

SelectScene::~SelectScene() {}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/proto/protoSelect.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);
}

void SelectScene::Update() {
	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;
	}
	if (input_->TriggerKey(DIK_I)) {

		isTutorial_ = true;
	}
}

void SelectScene::Draw() {
	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		sprite_->Draw();
		Sprite::PostDraw();
	}
}
