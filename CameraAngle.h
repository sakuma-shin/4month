#pragma once
#include "math/Matrix4x4.h"
#include "math/Vector3.h"
#include "MathUtility.h"

class CameraAngle {

public:

    CameraAngle();

    void Update();

    KamataEngine::Matrix4x4 GetViewMatrix() const;

private:

    KamataEngine::Vector3 eye_;
    KamataEngine::Vector3 target_;
    KamataEngine::Vector3 up_;
    KamataEngine::Matrix4x4 viewMatrix_;

    // 視点行列を作成するヘルパー関数
    KamataEngine::Matrix4x4 MakeLookAtMatrix(const KamataEngine::Vector3& eye, const KamataEngine::Vector3& target, const KamataEngine::Vector3& up);

};