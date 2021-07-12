#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILENUMX  (800/TILEWIDTH)
#define TILENUMY  (800/TILEHEIGHT)

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

	int _count;// �׳ɷ�����
	bool _start; // �׳� ���ۿ�


public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	void release();
	void update();
	void render();
	//Ÿ�� ���� �Լ�
	void setTile();
	//�� �� �ִ� ���� ã�� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);
	//�� ã�� �Լ�
	void pathFinder(tile* currentTile);
	void endmove();
};

