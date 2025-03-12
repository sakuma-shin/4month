#pragma once
#include "KamataEngine.h"
#include "Target.h"
#include "Light.h"

using namespace KamataEngine;

class Prism {
public:
	void Initialize(int key, WorldTransform* worldTransform);

	void Update();

	void Draw( Camera* camera);

	/// <summary>
	/// 光との当たり判定の結果を返す
	/// </summary>
	int CheckLight2Direction();

	/// <summary>
	/// 光の反射の際の処理
	/// </summary>
	void ReflectLight();

	/// <summary>
	/// 光の分解の際の処理
	/// </summary>
	void DecompositionLight();

	void Broken();

	void Set();

	Light::GrowType SetGrowType() { return prismDirection_; }

private:
	Model* model_ = nullptr;

	bool isSet_ = true;

	int key_;

	WorldTransform* worldTransform_;

	Light::GrowType prismDirection_;
};
