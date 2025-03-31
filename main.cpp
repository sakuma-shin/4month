#include "ClearScene.h"
#include "GameScene.h"
#include "SelectScene.h"
#include "TitleScene.h"
#include "Explanation.h"
#include <KamataEngine.h>

using namespace KamataEngine;

TitleScene* titleScene = nullptr;
SelectScene* selectScene = nullptr;
GameScene* gameScene = nullptr;
ClearScene* clearScene = nullptr;
Explanation* explanation = nullptr;

enum class Scene {

	kUnknown = 0,

	kTitle,
	kSelect,
	kExplanation,
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
	win->CreateGameWindow();

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

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

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
		//	gameScene->Draw();
		DrawScene();

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
	delete explanation;
	delete gameScene;
	delete clearScene;

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}

void ChangeScene() {

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

		if (selectScene->IsFinished()) {
			scene = Scene::kGame;

			delete selectScene;
			selectScene = nullptr;

			gameScene = new GameScene();
			gameScene->Initialize();

		} else if (selectScene->IsExplanation()) {
			scene = Scene::kExplanation;

			delete selectScene;
			selectScene = nullptr;

			explanation = new Explanation();
			explanation->Initialize();

		}

		break;

	case Scene::kExplanation:

		if (explanation->IsFinished()) {

			scene = Scene::kSelect;

			delete explanation;
			explanation = nullptr;

			selectScene = new SelectScene();
			selectScene->Initialize();

		}

	case Scene::kGame:

		if (gameScene->IsFinished()) {

			scene = Scene::kClear;

			delete gameScene;

			gameScene = nullptr;

			clearScene = new ClearScene();

			clearScene->Initialize();
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

	case Scene::kExplanation:

		explanation->Update();

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

		titleScene->Draw();

		break;

	case Scene::kExplanation:

		explanation->Draw();

		break;

	case Scene::kGame:

		gameScene->Draw();

		break;

	case Scene::kClear:

		clearScene->Draw();

		break;
	}
}
