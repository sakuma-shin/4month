#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}

GameScene::~GameScene() {

	delete playerModel_;
	delete player_;
	delete cameraAngle_;
	delete color_;
	for (Light* light : lights_) {
		delete light;
	}
	lights_.clear();
	delete lightModel_;
	delete map_;
	delete mapModel_;
	delete explanationSprite_;
	delete brokenPrysmSprite_;
	delete choiceNextStageSprite_;
	delete colorModel_;
	delete skydome_;
	delete fade_;

	TextureManager::Unload(textureHandle_);
	TextureManager::Unload(lightTextureHandle_);
	TextureManager::Unload(redTextureHandle_);
	TextureManager::Unload(blueTextureHandle_);
	TextureManager::Unload(greenTextureHandle_);
	TextureManager::Unload(explanationTextureHandle_);
	TextureManager::Unload(brokenPrysmTextureHandle_);
	TextureManager::Unload(choiceNextStageTextureHandle_);
	TextureManager::Unload(purpleTextureHandle_);
}

void GameScene::Initialize(int stageNum) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	mapModel_ = Model::Create();

	map_ = new Map;

	map_->Initialize(mapModel_, textureHandle_, &camera_, stageNum, this);

	// 3Dモデルの生成
	//playerModel_ = Model::Create();
	playerModel_ = Model::CreateFromOBJ("player", true);

	// プレイヤー関連
	player_ = new Player();
	player_->SetMap(map_);
	player_->Initialize(playerModel_, &camera_);

	camera_.Initialize();

	KamataEngine::WorldTransform initialTransform;
	initialTransform.translation_ = {0.0f, 0.0f, 0.0f};
	initialTransform.rotation_ = {0.0f, 0.0f, 0.0f};
	initialTransform.scale_ = {1.0f, 1.0f, 1.0f};

	cameraAngle_ = new CameraAngle();
	cameraAngle_->Initialize(initialTransform, player_);

	colorModel_ = Model::CreateFromOBJ("sensor", true);

	redTextureHandle_ = TextureManager::Load("color/red.png");
	blueTextureHandle_ = TextureManager::Load("color/blue.png");
	purpleTextureHandle_ = TextureManager::Load("color/purple.png");
	greenTextureHandle_ = TextureManager::Load("color/green.png");
	explanationTextureHandle_ = TextureManager::Load("UI/UI_explanation.png");
	brokenPrysmTextureHandle_ = TextureManager::Load("UI/brokenPrysm.png");
	choiceNextStageTextureHandle_ = TextureManager::Load("UI/choiceNextStage.png");
	resetTextureHandle_ = TextureManager::Load("UI/reset.png");

	explanationSprite_ = Sprite::Create(explanationTextureHandle_, {15.0f, 15.0f});
	explanationSprite_->SetSize({400.0f, 64.0f});

	brokenPrysmSprite_ = Sprite::Create(brokenPrysmTextureHandle_, {15.0f, 100.0f});

	choiceNextStageSprite_ = Sprite::Create(choiceNextStageTextureHandle_, {640.0f, 360.0f});

	resetSprite_ = Sprite::Create(resetTextureHandle_, {15.0f, 100.0f});
	resetSprite_->SetSize({128.0f, 32.0f});

	color_ = new Color();
	color_->Initialize(colorModel_, purpleTextureHandle_, redTextureHandle_, blueTextureHandle_, greenTextureHandle_);

	// colorGlass_ = new ColorGlass();
	// colorGlass_->Initialize(worldTra)

	lightTextureHandle_ = TextureManager::Load("white1x1.png");

	// ライトの初期化
	/*lightSprite_ = Sprite::Create(lightTextureHandle_, {});*/

	lightModel_ = Model::CreateFromOBJ("cube", true);

	Vector2 lightVelocity = {20.0f, 0.0f};

	std::vector<Vector3> initialPositions = map_->GetTilePositionsInRange(41, 44);

	std::vector<Light::GrowType> initialTypes = map_->GetMirrorTypesInRange();

	for (int i = 0; i < initialPositions.size(); i++) {
		Light* newLight = new Light();
		newLight->Initialize(lightTextureHandle_, lightModel_, initialTypes[i], initialPositions[i], {0.5f, 0.5f, 0.5f}, map_->Gettarget(), 1);
		newLight->SetMapData(map_);
		/*lightSprite_->SetSize(newLight->GetSize());*/
		lights_.push_back(newLight);
	}

	skydome_->Initialize(&camera_);

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	isFinished2_ = false;
}

void GameScene::Update() {
	lightDethflag = false;
	for (Light* light : lights_) {
		light->SetMapData(map_);
		light->Update();

		//// 反射した場合、新しいLightを作成
		if (light->CanReflect()) {
			light->SetRefrected();
			Vector3 newInitialPos = light->GetEndPosition(); // 反射したライトの現在位置を取得
			if (light->GetNewType() != Light::NO) {
				LightCreate(light->GetNewType(), newInitialPos, light->GetnewTextureHandle(), light->Getcolor());
			}

			if (light->GetNewType2() != Light::NO) {
				LightCreate(light->GetNewType2(), newInitialPos, light->GetnewTextureHandle(), light->Getcolor());
			}
		}
		if (map_->CheckCollision(light->GetinitialPos()) == 0 || map_->CheckCollision(light->GetinitialPos()) == 8) {
			light->Death();
			lightDethflag = true;
		}
	}

	lights_.remove_if([](Light* light) {
		if (!light->IsDeath()) {
			delete light;
			return true;
		}
		return false;
	});

	map_->Update(player_);
	player_->Update(map_);
	cameraAngle_->Update();
	color_->Update();

	camera_.matView = cameraAngle_->GetCamera().matView;
	camera_.matProjection = cameraAngle_->GetCamera().matProjection;
	camera_.TransferMatrix();
	skydome_->Update();
	KamataEngine::Vector3 playerPos = player_->GetPosition();

	// マップのゴール判定を行う
	map_->CheckGoalCollision(playerPos);

	/*if (input_->TriggerKey(DIK_SPACE)) {

	    isFinished_ = true;
	}*/

	// if (input_->TriggerKey(DIK_P) && stagenumber <= 5) {
	// stagenumber++;
	// Initialize();
	//}
	//	if (input_->TriggerKey(DIK_O) && stagenumber > 0) {
	// stagenumber--;
	// Initialize();
	//	}

	switch (phase_) {

	case FadePhase::kFadeIn:
		if (fade_->isFinished()) {
			phase_ = FadePhase::kMain;
		}
		break;

	case FadePhase::kMain:
		/*if (input_->TriggerKey(DIK_SPACE)) {
		    phase_ = FadePhase::kfadeOut;
		    fade_->Start(Fade::Status::FadeOut, 1.0f);
		}*/
		break;

	case FadePhase::kfadeOut:
		if (fade_->isFinished()) {
			isFinished_ = true;
		}
		break;
	}

	fade_->Update();

	if (input_->TriggerKey(DIK_R)) {
		for (Light* light : lights_) {
			delete light;
		}
		lights_.clear();
		Initialize(stageNum_);
	}

	if (input_->TriggerKey(DIK_T)) {
		isFinished2_ = true;
	}

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	skydome_->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///

	map_->Draw();

	for (Light* light : lights_) {
		light->Draw(&camera_);
	}
	player_->Draw(&camera_);
	/*color_->Draw(&camera_);*/

	// colorGlass_->Draw(&camera_);
	///
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	///

	explanationSprite_->Draw();
	resetSprite_->Draw();

	fade_->Draw(dxCommon_->GetCommandList());

	///
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::LightCreate(Light::GrowType type, Vector3 pos, uint32_t lightTextureHandle, int color) {
	Light* newLight = new Light();
	Vector3 scal = {0, 0, 0};
	if (type == Light::GrowType::Up) {
		scal = {-0.5f, 0.5f, 0.5f};
	}
	if (type == Light::GrowType::Down) {
		scal = {0.5f, 0.5f, 0.5f};
	}
	if (type == Light::GrowType::Right) {
		scal = {0.5f, 0.5f, 0.5f};
	}
	if (type == Light::GrowType::Left) {
		scal = {0.5f, 0.5f, -0.5f};
	}
	newLight->Initialize(lightTextureHandle, lightModel_, type, pos, scal, map_->Gettarget(), color);
	newLight->SetMapData(map_);
	/*lightSprite_->SetSize(newLight->GetSize());*/
	lights_.push_back(newLight);
}
