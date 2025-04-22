#include "TitleScene.h"

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/proto/protoTitle.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);

	sceneChangeSoundHandle_ = audio_->LoadWave("sounds/firstMusic.mp3");

}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;
		if (audio_->IsPlaying(sceneChangeSoundHandle_)) {
			audio_->PlayWave(sceneChangeSoundHandle_,false,0.5f);
		}
	}
}

void TitleScene::Draw() { 
	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		sprite_->Draw();
		Sprite::PostDraw();
	}
}
