#pragma once

class Transform;

namespace Time
{
	//初期化(Mainで初期化)
	void Initialize();

	//更新(Mainで更新)
	void Update(short FPS);

	void Reset();

	void Lock();

	void UnLock();

	//秒のみ表示にするかどうか
	//true = 秒のみ
	//false = 値に応じて時/分の表示
	void SetDisplayMode(bool Mode);

	//第一引数 : 表示するTransform 第二引数 : 小数点以下何桁を表示するか
	void Draw(Transform tr, int digit);

	//呼び出し時点の時間を取得
	float GetTime();
};

