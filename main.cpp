#include "ClearScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"
#include <KamataEngine.h>

using namespace KamataEngine;

TitleScene* titleScene = nullptr;
SelectScene* selectScene = nullptr;
GameScene* gameScene = nullptr;
ClearScene* clearScene = nullptr;

enum class Scene {

	kUnknown = 0,

	kTitle,
	kSelect,
	kGame,
	kClear

};

// 現在シーン
Scene scene = Scene::kUnknown;

void ChangeScene();

void UpdateScene();

void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow(L"3144_プリズムブレイク");

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	uint32_t BGMSoundHandle_ = audio->LoadWave("sounds/BGM.mp3");

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	titleScene = new TitleScene();
	titleScene->Initialize();

	scene = Scene::kTitle;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();

		// gameScene->Update();
		UpdateScene();
		ChangeScene();

		// 軸表示の更新
		axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		DrawScene();
		if (!audio->IsPlaying(BGMSoundHandle_)) {
			BGMSoundHandle_ = audio->PlayWave(BGMSoundHandle_, true, 0.5f);
		}

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();
	// scene解放
	delete titleScene;
	delete selectScene;
	delete gameScene;
	delete clearScene;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene() {
	int stageNum_ = 1;

	switch (scene) {

	case Scene::kTitle:

		if (titleScene->IsFinished()) {

			scene = Scene::kSelect;

			delete titleScene;

			titleScene = nullptr;

			selectScene = new SelectScene();

			selectScene->Initialize();
		}

		break;

	case Scene::kSelect:
		stageNum_ = selectScene->SelectStage();

		if (selectScene->IsFinished()) {

			scene = Scene::kGame;

			delete selectScene;

			selectScene = nullptr;

			gameScene = new GameScene();

			gameScene->SetStageNum(stageNum_);
			gameScene->Initialize(stageNum_);
			

			break;
		}

		break;

	case Scene::kGame:

		if (gameScene->IsFinished() || gameScene->IsFinished2()) {

			if (gameScene->IsFinished() || !gameScene->IsFinished2()) {
				scene = Scene::kClear;
				clearScene = new ClearScene();
				clearScene->Initialize();
			} else if (!gameScene->IsFinished() || gameScene->IsFinished2()) {
				scene = Scene::kSelect;
				selectScene = new SelectScene();
				selectScene->Initialize();
			}
			delete gameScene;

			gameScene = nullptr;
		}

		break;

	case Scene::kClear:

		if (clearScene->IsFinished()) {

			scene = Scene::kTitle;

			delete clearScene;

			clearScene = nullptr;

			titleScene = new TitleScene();

			titleScene->Initialize();
		}

		break;

	
	}
}

void UpdateScene() {

	switch (scene) {

	case Scene::kTitle:

		titleScene->Update();

		break;

	case Scene::kSelect:

		selectScene->Update();

		break;

	case Scene::kGame:

		gameScene->Update();

		break;

	case Scene::kClear:

		clearScene->Update();

		break;
	}
}

void DrawScene() {

	switch (scene) {

	case Scene::kTitle:

		titleScene->Draw();

		break;

	case Scene::kSelect:

		selectScene->Draw();

		break;

	case Scene::kGame:

		gameScene->Draw();

		break;

	case Scene::kClear:

		clearScene->Draw();

		break;
	}
}