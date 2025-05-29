#include "ClearScene.h"

ClearScene::~ClearScene() {
	delete sprite_;
	TextureManager::Unload(textureHandle_);
}

void ClearScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("clear.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);
	camera_.Initialize();

	skydome_ = new skydome();

	skydome_->Initialize(&camera_);
}

void ClearScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;
	}
	skydome_->Update();
}

void ClearScene::Draw() {
	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		skydome_->Draw();
		sprite_->Draw();
		Sprite::PostDraw();
	}
}
