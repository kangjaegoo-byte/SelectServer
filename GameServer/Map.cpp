#include "pch.h"
#include "Map.h"
#include "GamePlayer.h"
Map::Map()
{
	m_map.resize(m_mapCount);
	m_map[0] = Region{ -1 ,0,0, 0,0 };	// �����
	m_map[1] = Region{ -1 ,10,1 ,0,10 };	// ����
	m_map[2] = Region{ -1 ,0,2 ,0,0 };	// ī�� �̱�
	m_map[3] = Region{ -1 ,20,3 ,0,20 };	// ����¡
	m_map[4] = Region{ -1 ,0,4 ,0 ,0 };	//����
	m_map[5] = Region{ -1 ,40,5 ,0 ,40 };	// Ÿ������
	m_map[6] = Region{ -1 ,45,6 ,0 ,45 };	// �ι���
	m_map[7] = Region{ -1 ,45,7 ,0 ,45 };	// ī�̷�
	m_map[8] = Region{ -1 ,0,8 ,0 ,0 };	// ���ε�
	m_map[9] = Region{ -1 ,0,9 ,0 ,0 };	// �߸�
	m_map[10] = Region{ -1 ,50,10 ,0 ,50 };	// ����
	m_map[11] = Region{ -1 ,55,11 ,0 ,55 };	// �õ��
	m_map[12] = Region{ -1 ,0,12 ,0 ,0 };	// ī��̱�
	m_map[13] = Region{ -1 ,60,13 ,0 ,60 };	// ����
	m_map[14] = Region{ -1 ,0,14 ,0 ,0 };	// �Ͽ���
	m_map[15] = Region{ -1 ,63,15 ,0 ,63 };	// ���Ŀ÷� 
	m_map[16] = Region{ -1 ,0,16 ,0 ,0 };	// �ø���
	m_map[17] = Region{ -1 ,65,17 ,0 ,65 };	// ������
	m_map[18] = Region{ -1 ,0,18 ,0 ,0 }; // Ǫ��
	m_map[19] = Region{ -1 ,70,19 ,0 ,70 }; // ������
	m_map[20] = Region{ -1 ,0,20 ,0 ,0 };	// ī��̱�
	m_map[21] = Region{ -1 ,80,21 ,0 ,80 }; // ��ũ��	
	m_map[22] = Region{ -1 ,90,22 ,0 ,90 };	// ���׹�
	m_map[23] = Region{ -1 ,90,23 ,0 ,90 };	// �θ�
	m_map[24] = Region{ -1 ,0,24 ,0 ,0 };	// ���迩��
	m_map[25] = Region{ -1 ,0,25 ,0 ,0 };	//����Ƽ
	m_map[26] = Region{ -1 ,120,26 ,0 ,120 }; // ����
	m_map[27] = Region{ -1 ,120,27 ,0 ,120 };	// �ĸ�
	m_map[28] = Region{ -1 ,0,28 ,0 ,0 }; // ī��̱�
	m_map[29] = Region{ -1 ,150,29 ,0 ,150 }; // ����
	m_map[30] = Region{ -1 ,0,30 ,0 ,0 }; // ����û
	m_map[31] = Region{ -1 ,240,31 ,0 ,240 }; // ����
}

Map::~Map()
{
}

void Map::BuyRegion(GamePlayer* _buyer, int _playerIdx)
{
	m_map[_buyer->GetPos()]._ownerPlayerIndx = _playerIdx;
	m_map[_buyer->GetPos()]._level += 1;
	if (m_map[_buyer->GetPos()]._level >= 3)
		m_map[_buyer->GetPos()]._level = 2;

	_buyer->SubMoney(m_map[_buyer->GetPos()]._passCost);
}

void Map::BuyRegion(GamePlayer* _buyer, GamePlayer* _seller, int _playerIdx)
{
	m_map[_buyer->GetPos()]._ownerPlayerIndx = _playerIdx;
	m_map[_buyer->GetPos()]._level += 1;
	if (m_map[_buyer->GetPos()]._level >= 3)
		m_map[_buyer->GetPos()]._level = 2;

	int cost = m_map[_buyer->GetPos()]._passCost;
	_buyer->SubMoney(cost);
	_seller->AddMoney(cost);

	m_map[_buyer->GetPos()]._passCost = cost * m_map[_buyer->GetPos()]._level;
}

void Map::DestoryRegionByPlayerIdx(int _playerIdx)
{
	for (int i = 0; i < 32; i++)
	{
		if (m_map[i]._ownerPlayerIndx == _playerIdx)
		{
			m_map[i]._level = 0;
			m_map[i]._passCost = m_map[i]._oriCost;
			m_map[i]._ownerPlayerIndx = -1;
		}
	}
}

void Map::BuyOtherRegion(GamePlayer* _buyer, int _playerIdx)
{
	m_map[_buyer->GetPos()]._ownerPlayerIndx = _playerIdx;
	int cost = m_map[_buyer->GetPos()]._passCost;
	_buyer->SubMoney(cost);
}

void Map::MapLevelUp(GamePlayer* _buyer)
{
	m_map[_buyer->GetPos()]._passCost = m_map[_buyer->GetPos()]._passCost * m_map[_buyer->GetPos()]._level;
}

void Map::BuyOtherRegion(GamePlayer* _buyer, GamePlayer* _seller, int _playerIdx)
{
	m_map[_buyer->GetPos()]._ownerPlayerIndx = _playerIdx;
	int cost = m_map[_buyer->GetPos()]._passCost;
	_buyer->SubMoney(cost);
	_seller->AddMoney(cost);
}

bool Map::CanPass(int _pos)
{
	if (_pos == 2 || _pos == 4 || _pos == 9 || _pos == 12 || _pos == 14 || _pos == 16 || _pos == 18 || _pos == 20 || _pos == 24 || _pos == 25 || _pos == 28 || _pos == 30 || _pos == 0)
		return true;
	else
		return false;
}

int Map::PlayerRegionSum(int _playerIndex)
{
	int sum = 0;
	for (int i = 0; i < m_map.size(); i++)
	{
		Region r = m_map[i];
		if (r._ownerPlayerIndx == _playerIndex)
		{
			sum += r._passCost;
		}
	}
	return sum;
}
