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
	//방 만들기
	bool makeRoom(int x, int y, DIRECTION dir, bool firstRoom = false, int index = NULL);
	//통로 만들기
	bool makeCorridor(int x, int y, DIRECTION dir);

	//상점 만들기
	bool makeShop();
	bool makeShop(int x, int y, DIRECTION dir);

	bool placeTile(const tagRoom& room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop = false, DIRECTION dir = DIRECTIONCOUNT);
	bool createFeature(int index);
	bool createFeature(int x, int y, DIRECTION dir, int index = NULL);

	TERRAIN getTileTerrain(int x, int y);

	OBJECT getObject(int x, int y);

	vector<tagRoom> getRoom() { return _rooms; }

	void deleteEmptyTiles(); //비어있는 타일들을 지움

	void moveMap(); //0,0 근처로 생성된 맵을 옮김

	void setEndBlock(); //맵의 가장자리에 END블록 설치
	void setEndEdge(); //모서리 빈 곳에 END블록 설치

	void setStone(); //stone 블록 랜덤 생성

	void setBossRoom(); //보스룸 정하기

	tagRoom getStartRoom();

	vector<vector<tagTile>> getTiles() { return _tiles; }

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
};

