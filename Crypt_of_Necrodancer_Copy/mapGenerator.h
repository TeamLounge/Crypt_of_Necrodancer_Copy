#pragma once
#include "gameNode.h"
#include "tileMap.h"

enum ROOM_DIRECTION
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

	int _startRoomIndex;
	int _bossRoomIndex;

	ROOM_DIRECTION _corridorDirection;

	vector<POINT> _newRoomXIndex;
	vector<POINT> _newRoomYIndex;

	vector<POINT> _newWallIndex;

	vector<POINT> _endBlockIndex;

	bool _isEvenLight;

	float _worldTime;

	float _elapsedSec;

public:
	virtual HRESULT init(int width, int height);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(int tileX, int tileY);

	void generate(int maxFeatures);
	//�� �����
	bool makeRoom(int x, int y, ROOM_DIRECTION dir, bool firstRoom = false, int index = NULL);
	//��� �����
	bool makeCorridor(int x, int y, ROOM_DIRECTION dir);

	//���� �����
	bool makeShop();
	bool makeShop(int x, int y, ROOM_DIRECTION dir);

	bool placeTile(const tagRoom& room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop = false, ROOM_DIRECTION dir = DIRECTIONCOUNT);
	bool createFeature(int index);
	bool createFeature(int x, int y, ROOM_DIRECTION dir, int index = NULL);

	TERRAIN getTileTerrain(int x, int y);

	OBJECT getTileObject(int x, int y);

	vector<tagRoom> getRoom() { return _rooms; }

	void deleteEmptyTiles(); //����ִ� Ÿ�ϵ��� ����

	void moveMap(); //0,0 ��ó�� ������ ���� �ű�

	void setEndBlock(); //���� �����ڸ��� END��� ��ġ
	void setEndEdge(); //�𼭸� �� ���� END��� ��ġ

	void setStone(); //stone ��� ���� ����

	void setBossRoom(); //������ ���ϱ�

	void setTorch(); //ȶ�� ����

	void testObject(); //���� �׽�Ʈ ��

	//�̰� ���� ���Ͱ� ū�� �װ� ����Ǽ� ������ ������
	//vector<vector<tagTile>> getTiles() { return _tiles; }

	//������
	void setTileObject(int tileX, int tileY, OBJECT obj, int objectFrameX = 0, int objectFrameY = 0)
	{
		_tiles[tileY][tileX].obj = obj;
		_tiles[tileY][tileX].objectFrameX = objectFrameX;
		_tiles[tileY][tileX].objectFrameY = objectFrameY;
	};
	void setTileTerrain(int tileX, int tileY, TERRAIN terrain, int terrainFrameX = 0, int terrainFrameY = 0)
	{
		_tiles[tileY][tileX].terrain = terrain;
		_tiles[tileY][tileX].terrainFrameX = terrainFrameX;
		_tiles[tileY][tileX].terrainFrameY = terrainFrameY;
	};
	void setAlpha(int tileX, int tileY, int alpha)
	{
		_tiles[tileY][tileX].alpha = alpha;
	}
	void setIsSeen(int tileX, int tileY, bool b) { _tiles[tileY][tileX].isSeen = b; }
	void setIsHaveTorch(int tileX, int tileY, bool b){ _tiles[tileY][tileX].isHaveTorch = b; }

	void setTileObjectFrameX(int tileX, int tileY, int objectFrameX) { _tiles[tileY][tileX].objectFrameX = objectFrameX; }
	void setTileObjectFrameY(int tileX, int tileY, int objectFrameY) { _tiles[tileY][tileX].objectFrameY = objectFrameY; }

	void setIsBombFired(int tileX, int tileY, bool b) { _tiles[tileY][tileX].isBombFired = b; }

	//������
	bool getIsSeen(int tileX, int tileY) { return _tiles[tileY][tileX].isSeen; }
	RECT getRect(int tileX, int tileY) { return _tiles[tileY][tileX].rc; }

	int getXSize() { return _width; }
	int getYSize() { return _height; }

	int getStartRoomX() { return _rooms[_startRoomIndex].x; };
	int getStartRoomY() { return _rooms[_startRoomIndex].y; };

	int getBossRoomX() { return _rooms[_bossRoomIndex].x; }
	int getBossRoomY() { return _rooms[_bossRoomIndex].y; }

	bool getIsHaveTorch(int tileX, int tileY) { return _tiles[tileY][tileX].isHaveTorch; }

	int getAlpha(int tileX, int tileY) { return _tiles[tileY][tileX].alpha; }
	
	tagTile* getTile(int tileX, int tileY) { return &_tiles[tileY][tileX]; }

	bool getIsBombFired(int tileX, int tileY) { return _tiles[tileY][tileX].isBombFired; }
};

