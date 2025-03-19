#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include <input/Input.h>

class Map;

class Player {

public:

	~Player();

	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, Map* map);

	void Update(Map* map);

	void Draw(KamataEngine::Camera* camera);

	KamataEngine::Vector3 GetPosition() const { return worldTransform_.translation_; }

	// プレイヤーの位置を設定する
	void SetPosition(const KamataEngine::Vector3& position) { worldTransform_.translation_ = position; }

	KamataEngine::Vector3 GetRotation() const { return worldTransform_.rotation_; }

	void SetMap(Map* map) { map_ = map; }

	KamataEngine::Vector3 Getmove() { 
		return move;
	}

	/// <summary>
	/// 0ならカウントを減らし、1なら増やす(それ以外の数字でも可)
	/// </summary>
	/// <param name="i">
	/// 0で減少、1で増加
	/// </param>
	void SetCount(int i) {
		if (i == 0) {
			if (prismCount_ > 0) {
				prismCount_--;
			}
		} else if (i == 1) {
			prismCount_++;
		} else {
			prismCount_++;
		}
	}

	int GetCount() { return prismCount_; }

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;	
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	KamataEngine::Camera* camera_ = nullptr;

	//入力
	KamataEngine::Input* input_ = nullptr;

	Map* map_ = nullptr;

	KamataEngine::Vector3 move = {0, 0, 0};

	int prismCount_ = 0;

};