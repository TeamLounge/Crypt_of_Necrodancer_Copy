#pragma once
#include "gameNode.h"
#include "mapGenerator.h"

class player : public gameNode
{
private:
	RECT _head; //��
	RECT _body; //����
	RECT _shadow; //�׸���
	int _tileX; //�÷��̾ ���� �ִ� Ÿ�� x�ε���
	int _tileY; //�÷��̾ ���� �ִ� Ÿ�� y�ε���

	mapGenerator* _map;
public:
	virtual HRESULT init(int tileX, int tileY);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setupPlayerRect();
};

