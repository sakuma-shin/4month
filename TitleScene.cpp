#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete fade_;
	delete sprite_;
	delete mirrorModel_;
	delete skydome_;

	TextureManager::Unload(textureHandle_);
}

void TitleScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("./Resources/title.png");
	mirrorGH = TextureManager::Load("mirror2.png");
	sprite_ = Sprite::Create(textureHandle_, {0, 0}, {1, 1, 1, 1}, {0, 0}, 0, 0);

	mirrorModel_ = Model::CreateFromOBJ("mirorr", true);

	mirrorWorldTransform_.Initialize();

	mirrorWorldTransform_.translation_ = {17.0f, 0.0f, 0.0f};
	mirrorWorldTransform_.scale_ = {10.0f, 10.0f, 1.0f};
	mirrorWorldTransform_.rotation_ = {0.0f, 0.4f, 0.0f};

	mirrorWorldTransform_.UpdateMatrix();

	lightModel_ = Model::Create();

	lightWorldTransform_.Initialize();
	lightWorldTransform_.scale_.x = 33.0f;
	lightWorldTransform_.translation_.x = -15.0f;

	lightWorldTransform_.UpdateMatrix();

	lightWorldTransform2_.Initialize();
	lightWorldTransform2_.scale_.z = 33.0f;
	lightWorldTransform2_.translation_ = {18.0f, 0.0f, -22.5f};

	lightWorldTransform2_.UpdateMatrix();

	lightColor_.Initialize();

	lightColor_.SetColor({1.0f, 1.0f, 1.0f, 0.7f});

	camera_.Initialize();

	skydome_ = new skydome();
	skydome_->Initialize(&camera_);

	sceneChangeSoundHandle_ = audio_->LoadWave("sounds/firstMusic.mp3");

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void TitleScene::Update() {

	if (input_->TriggerKey(DIK_SPACE)) {

		/*	isFinished_ = true;*/
		if (audio_->IsPlaying(sceneChangeSoundHandle_)) {
			audio_->PlayWave(sceneChangeSoundHandle_, false, 0.5f);
		}
	}

	switch (phase_) {

	case FadePhase::kFadeIn:
		if (fade_->isFinished()) {
			phase_ = FadePhase::kMain;
		}
		break;

	case FadePhase::kMain:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = FadePhase::kfadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;

	case FadePhase::kfadeOut:
		if (fade_->isFinished()) {
			isFinished_ = true;
		}
		break;
	}

	skydome_->Update();

	fade_->Update();
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	if (this != nullptr) {
		Sprite::PreDraw(dxCommon_->GetCommandList());
		skydome_->Draw();
		Sprite::PostDraw();
	}

	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///
	lightModel_->Draw(lightWorldTransform2_, camera_, TextureManager::Load("white1x1.png"), &lightColor_);
	lightModel_->Draw(lightWorldTransform_, camera_, TextureManager::Load("white1x1.png"), &lightColor_);
	mirrorModel_->Draw(mirrorWorldTransform_, camera_, mirrorGH);
	///
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	Sprite::PreDraw(commandList);
	sprite_->Draw();
	fade_->Draw(dxCommon_->GetCommandList());
	Sprite::PostDraw();
}
