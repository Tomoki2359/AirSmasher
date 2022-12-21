#include "Time.h"
#include "Image.h"
#include "Math.h"
#include "Transform.h"

#include <string>

namespace Time
{
	//60進法
	const char HEX = 60;

	//表示桁数
	const char Dig = 2;

	//文字間の大きさ
	const float Interval = 0.1f;

	int hPict_[10];
	char Hours;
	char Minuts;
	double Seconds;
	bool OnlySec;	//秒のみの表記にするか
	bool Lock_;		//現在の状態で固定するか

	void Initialize()
	{
		std::string texS = "Assets\\Number";
		std::string texF = ".png";
		//画像データのロード
		for (int i = 0; i < 10; i++)
		{
			std::string data = texS + std::to_string(i) + texF;
			hPict_[i] = Image::Load(data);
			assert(hPict_[i] >= NULL);
		}
		Hours = NULL;
		Minuts = NULL;
		Seconds = NULL;
		OnlySec = false;
		Lock_ = true;
	}

	void Update(short FPS)
	{
		if (Lock_) { return; }	//Lockされていたら更新しない
		float fps = (FPS - 1) * 1.0005f;
		Seconds += 1.0 / fps;
	}

	void Reset()
	{
		Hours = NULL;
		Minuts = NULL;
		Seconds = NULL;
	}

	void Lock()
	{
		Lock_ = true;
	}

	void UnLock()
	{
		Lock_ = false;
	}

	void SetDisplayMode(bool Mode)
	{
		OnlySec = Mode;
	}

	void Draw(Transform tr, int digit)
	{
		Transform Tr = tr;

		if (OnlySec)	//秒のみ表示の場合
		{
			int Digit = (int)log10(Seconds);

			//整数部分の表示
			for (int i = NULL; i <= Digit; i++)
			{
				int Pic = Math::GetDigits((int)Seconds, (Digit - i), (Digit - i));
				Tr.position_.x += Interval;
				Image::SetTransform(hPict_[Pic], Tr);
				Image::Draw(hPict_[Pic]);
			}
		}
		else
		{
			int sec = Seconds;

			sec %= HEX;

			//時/分の更新
			Minuts = Seconds / HEX;
			Hours = Minuts / HEX;
			Minuts %= HEX;

			if (Hours > NULL)	//Hoursを含めた表示
			{
				int Pic = Math::GetDigits(Hours, NULL, NULL);
				Tr.position_.x += Interval;
				Image::SetTransform(hPict_[Pic], Tr);
				Image::Draw(hPict_[Pic]);

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(Minuts, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(sec, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
			else if (Minuts > NULL)	//Minutsを含めた表示
			{
				int Digit = (int)log10(Minuts);
				for (int i = NULL; i <= Digit; i++)
				{
					int Pic = Math::GetDigits(Minuts, (Digit - i), (Digit - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}

				Tr.position_.x += Interval / 2;
				for (int i = 1; i <= Dig; i++)
				{
					int Pic = Math::GetDigits(sec, (Dig - i), (Dig - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
			else
			{
				int Digit = (int)log10(Seconds);

				//整数部分の表示
				for (int i = NULL; i <= Digit; i++)
				{
					int Pic = Math::GetDigits(Seconds, (Digit - i), (Digit - i));
					Tr.position_.x += Interval;
					Image::SetTransform(hPict_[Pic], Tr);
					Image::Draw(hPict_[Pic]);
				}
			}
		}

		//小数部分の表示
		const float Dec = 0.8f;		//小数点以下の表示は縮小する
		Tr.scale_ = { Dec, Dec, Dec };
		Tr.position_.y -= 0.02f;		//縮小した分下に下げる
		for (int i = 1; i <= digit; i++)
		{
			int Pic = Math::GetFraction((float)Seconds, i);
			Tr.position_.x += Interval;
			Image::SetTransform(hPict_[Pic], Tr);
			Image::Draw(hPict_[Pic]);
		}
	}

	float GetTime()
	{
		return Seconds;
	}
}