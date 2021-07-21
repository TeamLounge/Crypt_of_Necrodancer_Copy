#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

class mapGenerator;

class aStarTest : public gameNode
{
private:
	//��ü Ÿ�� ���� ����
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;
	//�� �� �ִ� Ÿ�� ���� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;
	//���� ����� ��θ� ���� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile; //����Ÿ�� 
	tile* _endTile; //��Ÿ��
	tile* _currentTile; //���� Ÿ��

	mapGenerator* _map;
	
	int _count;// �׳ɷ�����
	int _damagecount;
	float time;
	bool _start; // �׳� ���ۿ�
	bool ismove;
	bool hp;
	int _TotaltileX,_TotaltileY;

public:
	aStarTest();
	~aStarTest();

	HRESULT init(int enemyX, int enemyY, int playerX, int playerY);
	void release();
	void update(bool istime);
	void render();
	//Ÿ�� ���� �Լ�
	void setTile(int enemyX, int enemyY, int playerX, int playerY);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);
	void endmove(int playerIndexX, int playerIndexY);
	void startmove();
	void setLinkrandomMap(mapGenerator* map) { _map = map; }

	int getenemyTileX() { return _startTile->getIdX(); }
	int getenemyTileY() { return _startTile->getIdY(); }
};

