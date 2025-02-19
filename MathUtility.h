#pragma once
#include "math/Matrix4x4.h"
#include "math/Vector3.h"
#include <cmath>

struct AABB {
	KamataEngine::Vector3 min; // 最小点
	KamataEngine::Vector3 max; // 最小点
};

// 加算
KamataEngine::Vector3 Add(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

KamataEngine::Vector3 Add2(const KamataEngine::Vector3 v1, const KamataEngine::Vector3 v2);

// 内積
float Dot(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 長さ
float Length(const KamataEngine::Vector3& v);

// 正規化
KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);

// 積
KamataEngine::Matrix4x4 Multiply(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

// 座標変換
KamataEngine::Vector3 TransForm(const KamataEngine::Vector3& vector3, const KamataEngine::Matrix4x4& matrix);

// 1.X軸回転行列
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);

// 2.Y軸回転行列
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);

// 3.Z軸回転行列
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

// 回転行列の合成
KamataEngine::Matrix4x4 RotateXYZMatrix(const KamataEngine::Vector3& radian);

// 3次元アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

KamataEngine::Vector3 Lerp(const KamataEngine::Vector3& a, const KamataEngine::Vector3& b, float t);

KamataEngine::Vector3 Multiply(float scalar, const KamataEngine::Vector3& v);

KamataEngine::Vector3 TransForm(const KamataEngine::Vector3& vector3, const KamataEngine::Matrix4x4& matrix);

bool IsCollision(const AABB& a, const AABB& b);

KamataEngine::Vector3 TransformNormal(const KamataEngine::Vector3& v, const KamataEngine::Matrix4x4& m);

// 代入演算子オーバーロード
// KamataEngine::Vector3の掛け算
KamataEngine::Vector3& operator*=(KamataEngine::Vector3& v, float s);

// 2項演算子オーバーロード
// KamataEngine::Vector3の掛け算
KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s);

// 代入演算子オーバーロード
// KamataEngine::Vector3の足し算
KamataEngine::Vector3& operator+=(KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

// 2項演算子オーバーロード
// KamataEngine::Vector3の足し算
const KamataEngine::Vector3 operator+(KamataEngine::Vector3& v1, KamataEngine::Vector3& v2);

KamataEngine::Vector3& operator-=(KamataEngine::Vector3& lhv, const KamataEngine::Vector3& rhv);

const KamataEngine::Vector3 operator-(KamataEngine::Vector3& v1, KamataEngine::Vector3& v2);

KamataEngine::Matrix4x4 operator*=(KamataEngine::Matrix4x4& m1, KamataEngine::Matrix4x4& m2);

KamataEngine::Matrix4x4 Inverse(const KamataEngine::Matrix4x4& m);
// 転置行列
KamataEngine::Matrix4x4 Transpose(const KamataEngine::Matrix4x4& m);

// 単位行列を作成
KamataEngine::Matrix4x4 MakeIdentity4x4();

// 平行移動行列
KamataEngine::Matrix4x4 MakeTraslateMatrix(const KamataEngine::Vector3& translate);

// 拡大縮小行列
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);