#pragma once
namespace Option
{
	/// <summary>
	/// プレイヤーの得点を保存する
	/// </summary>
	/// <param name="p">プレイヤーの得点</param>
	void SetPlayerPoint(int p);

	/// <summary>
	/// プレイヤーの得点を取得する
	/// </summary>
	/// <returns>プレイヤーの得点</returns>
	int GetPlayerPoint();

	/// <summary>
	/// 敵の得点を保存する
	/// </summary>
	/// <param name="p">敵の得点</param>
	void SetEnemyPoint(int p);

	/// <summary>
	/// 敵の得点を取得する
	/// </summary>
	/// <returns>敵の得点</returns>
	int GetEnemyPoint();
};