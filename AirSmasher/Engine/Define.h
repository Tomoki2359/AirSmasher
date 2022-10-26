#pragma once

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}			//デリートする
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}		//リリースする
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}	//配列をデリートする