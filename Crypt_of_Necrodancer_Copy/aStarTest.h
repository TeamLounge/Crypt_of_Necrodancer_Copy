#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILENUMX  31
#define TILENUMY  31

class randomMap;

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

	randomMap* _map;
	
	int _count;// �׳ɷ�����
	float time;
	bool _start; // �׳� ���ۿ�
	bool ismove;
	
public:
	aStarTest();
	~aStarTest();

	HRESULT init(int enemyX, int enemyY, int playerX, int playerY);
	void release();
	void update();
	void render();
	//Ÿ�� ���� �Լ�
	void setTile(int enemyX, int enemyY, int playerX, int playerY);
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);
	void endmove(int playerIndexX, int playerIndexY);
	void startmove();
	void setLinkrandomMap(randomMap* map) { _map = map; }

	int getenemyTileX() { return _startTile->getIdX(); }
	int getenemyTileY() { return _startTile->getIdY(); }
};

