#include "GameScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}


GameScene::~GameScene() {

	delete playerModel_;
	delete player_;
	delete cameraAngle_;
	delete map_;
	
	/*delete lightSprite_;*/
	for (Light* light : lights_) {
		delete light;
	}

}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//3Dモデルの生成
	playerModel_ = Model::Create();

	//プレイヤー関連
	player_ = new Player();
	player_->Initialize(playerModel_,textureHandle_,&camera_);
	player_->SetMap(map_);

	camera_.Initialize();


	KamataEngine::WorldTransform initialTransform;
	initialTransform.translation_ = { 0.0f, 0.0f, 0.0f };
	initialTransform.rotation_ = { 0.0f, 0.0f, 0.0f };
	initialTransform.scale_ = { 1.0f, 1.0f, 1.0f };

	cameraAngle_ = new CameraAngle();
	cameraAngle_->Initialize(initialTransform, player_);



	lightTextureHandle_ = TextureManager::Load("uvChecker.png");

	mapModel_ = Model::Create();

	map_ = new Map;

	map_->Initialize(mapModel_, textureHandle_, &camera_,stagenumber);

//ライトの初期化
	/*lightSprite_ = Sprite::Create(lightTextureHandle_, {});*/

	lightModel_ = Model::CreateFromOBJ("cube", true);
	

	std::vector<Vector3> initialPositions = map_->GetTilePositionsInRange(41, 44);
	std::vector<Light::GrowType> initialTypes = map_->GetMirrorTypesInRange();

	for (int i = 0; i < initialPositions.size(); i++) {
		Light* newLight = new Light();
		newLight->Initialize(lightTextureHandle_, lightModel_, initialTypes[i], initialPositions[i]);
		newLight->SetMapData(map_);
		/*lightSprite_->SetSize(newLight->GetSize());*/
		lights_.push_back(newLight);
	}
}

	


void GameScene::Update() { 

	for (Light* light : lights_) {
		light->Update();

		//// 反射した場合、新しいLightを作成
		if (light->CanReflect()) {
			light->SetRefrected();
			Vector3 newInitialPos = light->GetEndPosition(); // 反射したライトの現在位置を取得
			if (light->GetNewType() != Light::NO) {
				LightCreate(light->GetNewType(), newInitialPos);
			}

			if (light->GetNewType2() != Light::NO) {
				LightCreate(light->GetNewType2(), newInitialPos);
			}

		}
	}
  
	map_->Update(player_);
	player_->Update(map_);
	cameraAngle_->Update();

	camera_.matView = cameraAngle_->GetCamera().matView;
	camera_.matProjection = cameraAngle_->GetCamera().matProjection;
	camera_.TransferMatrix();

	if (input_->TriggerKey(DIK_SPACE)) {

		isFinished_ = true;

	}
	if (input_->TriggerKey(DIK_P) && stagenumber <= 5) {
		stagenumber++;
		Initialize();
	}
	if (input_->TriggerKey(DIK_O) && stagenumber > 0) {
		stagenumber--;
		Initialize();
	}

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

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

void GameScene::LightCreate(Light::GrowType type,Vector3 pos) {
	Light* newLight = new Light();
	newLight->Initialize(lightTextureHandle_, lightModel_, type,pos);
	newLight->SetMapData(map_);
	/*lightSprite_->SetSize(newLight->GetSize());*/
	lights_.push_back(newLight);
}
