#include "TutorialScene.h"

TutorialScene::~TutorialScene() {}

void TutorialScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/proto/protoTutorial.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);
}

void TutorialScene::Update() {
	if (input_->TriggerKey(DIK_SPACE) || input_->TriggerKey(DIK_I)) {

		isFinished_ = true;
	}
}

void TutorialScene::Draw() {
	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		sprite_->Draw();
		Sprite::PostDraw();
	}
}
