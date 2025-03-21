#pragma once
#include <KamataEngine.h>
#include "3D/Model.h"
#include "3D/WorldTransform.h"
#include "3D/camera.h"
#include"math/Vector2.h"

class Target {

	public:
		void Initialize(int number, KamataEngine::WorldTransform* worldTransform);
		void Update();
		void Draw(KamataEngine::Camera* camera);

		bool GetHit() { 
			return Hit;
		}

		int Getcoad() { 
			return coad;
		}
	    int Getcolor() { return color; }

		void isHit() {
			Hit = true;
		}
	    void noHit() { Hit = false; }

		int Getnumber() { 
			return number_;
		}
	
	private:
	    KamataEngine::Model* targetmodel_;
		int coad;
	    int color;
		bool Hit;
	    KamataEngine::WorldTransform* worldTransform_;
	    int number_;
};
