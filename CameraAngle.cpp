#include "CameraAngle.h"
using namespace KamataEngine;

CameraAngle::CameraAngle()
{

	eye_ = { 0.0f, 50.0f, 0.0f };
	target_ = { 0.0f, 0.0f, 0.0f };
	up_ = { 0.0f, 1.0f, 0.0f };
    viewMatrix_ = MakeLookAtMatrix(eye_, target_, up_);

}

void CameraAngle::Update()
{

	Vector3 forward = VectorSubtract(target_, eye_);
	Normalize(forward);

}

KamataEngine::Matrix4x4 CameraAngle::GetViewMatrix() const
{
	return viewMatrix_;
}

KamataEngine::Matrix4x4 CameraAngle::MakeLookAtMatrix(const KamataEngine::Vector3& eye, const KamataEngine::Vector3& target, const KamataEngine::Vector3& up)
{

    // 目の位置とターゲットの位置を使って前方ベクトル (Z軸方向) を計算
    Vector3 forward = VectorSubtract(target, eye);
    Normalize(forward); // 正規化して方向を一致させる

    // 上方向ベクトル (Y軸方向) を使って右方向ベクトル (X軸方向) を計算
    Vector3 right = VectorSubtract(up, forward);  // 上方向 - 前方向で右方向を算出
    Normalize(right);

    // 上方向ベクトル (Y軸方向) を再計算
    Vector3 newUp = VectorSubtract(forward, right);  // 前方向 - 右方向で上方向を調整
    Normalize(newUp);

    // LookAt行列を構成
    Matrix4x4 matrix;
    matrix.m[0][0] = right.x;
    matrix.m[1][0] = right.y;
    matrix.m[2][0] = right.z;
    matrix.m[0][1] = newUp.x;
    matrix.m[1][1] = newUp.y;
    matrix.m[2][1] = newUp.z;
    matrix.m[0][2] = -forward.x;
    matrix.m[1][2] = -forward.y;
    matrix.m[2][2] = -forward.z;
    matrix.m[0][3] = -(right.x * eye.x + right.y * eye.y + right.z * eye.z);  // 位置情報をカメラ空間に変換
    matrix.m[1][3] = -(newUp.x * eye.x + newUp.y * eye.y + newUp.z * eye.z);
    matrix.m[2][3] = -(forward.x * eye.x + forward.y * eye.y + forward.z * eye.z);
    matrix.m[3][3] = 1.0f;

    return matrix;

}
