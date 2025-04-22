#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}

GameScene::~GameScene() {

	delete playerModel_;
	delete player_;
	delete cameraAngle_;
	delete map_;
	delete color_;

	/*delete lightSprite_;*/
	for (Light* light : lights_) {
		delete light;
	}
}

void GameScene::Initialize(int stageNum) {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	playerModel_ = Model::Create();

	// プレイヤー関連
	player_ = new Player();
	player_->Initialize(playerModel_, textureHandle_, &camera_);
	player_->SetMap(map_);

	camera_.Initialize();

	KamataEngine::WorldTransform initialTransform;
	initialTransform.translation_ = {0.0f, 0.0f, 0.0f};
	initialTransform.rotation_ = {0.0f, 0.0f, 0.0f};
	initialTransform.scale_ = {1.0f, 1.0f, 1.0f};

	cameraAngle_ = new CameraAngle();
	cameraAngle_->Initialize(initialTransform, player_);

	colorModel_ = Model::CreateFromOBJ("cube", true);

	redTextureHandle_ = TextureManager::Load("color/red.png");
	blueTextureHandle_ = TextureManager::Load("color/blue.png");
	purpleTextureHandle_ = TextureManager::Load("color/purple.png");
	greenTextureHandle_ = TextureManager::Load("color/green.png");
	

	color_ = new Color();
	color_->Initialize(colorModel_, purpleTextureHandle_, redTextureHandle_, blueTextureHandle_, greenTextureHandle_);

	// colorGlass_ = new ColorGlass();
	// colorGlass_->Initialize(worldTra)

	lightTextureHandle_ = TextureManager::Load("white1x1.png");

	mapModel_ = Model::Create();

	map_ = new Map;

	map_->Initialize(mapModel_, textureHandle_, &camera_, stageNum, this);

	// ライトの初期化
	/*lightSprite_ = Sprite::Create(lightTextureHandle_, {});*/

	lightModel_ = Model::CreateFromOBJ("cube", true);

	Vector2 lightVelocity = {20.0f, 0.0f};

	std::vector<Vector3> initialPositions = map_->GetTilePositionsInRange(41, 44);
	std::vector<Light::GrowType> initialTypes = map_->GetMirrorTypesInRange();

	for (int i = 0; i < initialPositions.size(); i++) {
		Light* newLight = new Light();
		newLight->Initialize(lightTextureHandle_, lightModel_, initialTypes[i], initialPositions[i], {0.5f, 0.5f, 0.5f}, map_->Gettarget(), 0);
		newLight->SetMapData(map_);
		/*lightSprite_->SetSize(newLight->GetSize());*/
		lights_.push_back(newLight);
	}

	skydome_->Initialize(&camera_);
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
	color_->Draw(&camera_);
	

	
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
	///

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
		scal = {-0.5f, 0.5f, 0.5f};
	}
	if (type == Light::GrowType::Left) {
		scal = {0.5f, 0.5f, 0.5f};
	}
	newLight->Initialize(lightTextureHandle, lightModel_, type, pos, scal, map_->Gettarget(), color);
	newLight->SetMapData(map_);
	/*lightSprite_->SetSize(newLight->GetSize());*/
	lights_.push_back(newLight);
}
