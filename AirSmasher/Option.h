#pragma once
namespace Option
{
	/// <summary>
	/// �v���C���[�̓��_��ۑ�����
	/// </summary>
	/// <param name="p">�v���C���[�̓��_</param>
	void SetPlayerPoint(int p);

	/// <summary>
	/// �v���C���[�̓��_���擾����
	/// </summary>
	/// <returns>�v���C���[�̓��_</returns>
	int GetPlayerPoint();

	/// <summary>
	/// �G�̓��_��ۑ�����
	/// </summary>
	/// <param name="p">�G�̓��_</param>
	void SetEnemyPoint(int p);

	/// <summary>
	/// �G�̓��_���擾����
	/// </summary>
	/// <returns>�G�̓��_</returns>
	int GetEnemyPoint();
};