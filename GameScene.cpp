#include "GameScene.h"

using namespace KamataEngine;
GameScene::GameScene() {}


GameScene::~GameScene() {

	delete playerModel_;
	delete player_;
	delete cameraAngle_;
	

GameScene::~GameScene() { 
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

	camera_.Initialize();


	KamataEngine::WorldTransform initialTransform;
	initialTransform.translation_ = { 0.0f, 0.0f, 0.0f };
	initialTransform.rotation_ = { 0.0f, 0.0f, 0.0f };
	initialTransform.scale_ = { 1.0f, 1.0f, 1.0f };

	cameraAngle_ = new CameraAngle();
	cameraAngle_->Initialize(initialTransform);

}

	lightTextureHandle_ = TextureManager::Load("uvChecker.png");

//ライトの初期化
	/*lightSprite_ = Sprite::Create(lightTextureHandle_, {});*/


	Light* newLight = new Light();

	Vector3 initialPos = {3.0f, 2.0f, 0.0f};
	/*Light::GrowType type = Light::Right;*/
	
	Vector2 lightVelocity = {20.0f, 0.0f};
	newLight->Initialize(lightTextureHandle_, initialPos,lightVelocity);
	/*lightSprite_->SetSize(newLight->GetSize());*/
	lights_.push_back(newLight);
}

	player_->Update();
	cameraAngle_->Update();

	camera_.matView = cameraAngle_->GetCamera().matView;
	camera_.matProjection = cameraAngle_->GetCamera().matProjection;
	camera_.TransferMatrix();


void GameScene::Update() { 

	for (Light* light : lights_) {
		light->Update();
		/*lightSprite_->SetSize(light->GetSize());*/

		//// 反射した場合、新しいLightを作成
		if (light->CanReflect()) {
			light->SetRefrected();
			Vector3 newInitialPos = light->GetEndPosition(); // 反射したライトの現在位置を取得
			LightCreate(light->GetNewVelocity(), newInitialPos);
			
		}
	}

	/*for (auto it = lights_.rbegin(); it != lights_.rend(); ++it) {
		Light* light = *it;
		light->Update();
		lightSprite_->SetSize(light->GetSize());

		if (light->GetGrowType() == Light::Reflection) {
			Vector3 newInitialPos = light->GetEndPosition();
			Light::GrowType newType = light->GetNewType();
			light->SetGrowType(Light::NO);
			LightCreate(newType, newInitialPos);
		}
	}*/

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
	for (Light* light : lights_) {
		light->Draw();
	}
	/// 
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::LightCreate(Vector2 velocity,Vector3 pos) {
	Light* newLight = new Light();

	Vector3 initialPos = {3.0f, 2.0f, 0.0f};
	newLight->Initialize(lightTextureHandle_, pos, velocity);
	/*lightSprite_->SetSize(newLight->GetSize());*/
	lights_.push_back(newLight);
}
