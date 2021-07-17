#pragma once
#include "gameNode.h"
#include "tileMap.h"

enum DIRECTION
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	DIRECTIONCOUNT
};

struct tagRoom
{
	int x, y;
	int width, height;
	ROOMSTATE roomState;
};

class mapGenerator : public gameNode
{
private:
	vector<vector<tagTile>> _tiles;

	vector<tagRoom> _rooms;
	vector<tagRoom> _corridors;
	vector<tagRoom> _miniRooms;
	vector<tagRoom> _exits;
	int _width, _height;

	bool _isMakeRoom;
	bool _isHaveCorridor;

	int _start;

	DIRECTION _corridorDirection;

	vector<POINT> _newRoomXIndex;
	vector<POINT> _newRoomYIndex;

	vector<POINT> _newWallIndex;

	vector<POINT> _endBlockIndex;

public:
	virtual HRESULT init(int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();

	void generate(int maxFeatures);
	//�� �����
	bool makeRoom(int x, int y, DIRECTION dir, bool firstRoom = false, int index = NULL);
	//��� �����
	bool makeCorridor(int x, int y, DIRECTION dir);

	//���� �����
	bool makeShop();
	bool makeShop(int x, int y, DIRECTION dir);

	bool placeTile(const tagRoom& room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop = false, DIRECTION dir = DIRECTIONCOUNT);
	bool createFeature(int index);
	bool createFeature(int x, int y, DIRECTION dir, int index = NULL);

	TERRAIN getTileTerrain(int x, int y);

	OBJECT getObject(int x, int y);

	vector<tagRoom> getRoom() { return _rooms; }

	void deleteEmptyTiles(); //����ִ� Ÿ�ϵ��� ����

	void moveMap(); //0,0 ��ó�� ������ ���� �ű�

	void setEndBlock(); //���� �����ڸ��� END��� ��ġ
	void setEndEdge(); //�𼭸� �� ���� END��� ��ġ

	void setStone(); //stone ��� ���� ����

	void setBossRoom(); //������ ���ϱ�

	tagRoom getStartRoom();

	vector<vector<tagTile>> getTiles() { return _tiles; }
};

