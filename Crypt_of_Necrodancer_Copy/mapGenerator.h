#pragma once
#include "gameNode.h"
#include "tileMap.h"
#define BOSSMAPX 13
#define BOSSMAPY 25

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

	POINT _shopKeeper;

	POINT _bossStair;

public:
	virtual HRESULT init(int width, int height);
	virtual void release();
	virtual void update(int tileX, int tileY);
	virtual void render(int tileX, int tileY, bool isTile);
	
	//맵 생성
	void generate(int maxFeatures);

	//보스 맵 생성
	void generateBossMap();

	//방 만들기
	bool makeRoom(int x, int y, ROOM_DIRECTION dir, bool firstRoom = false, int index = NULL);
	//통로 만들기
	bool makeCorridor(int x, int y, ROOM_DIRECTION dir);

	//상점 만들기
	bool makeShop();
	bool makeShop(int x, int y, ROOM_DIRECTION dir);

	bool placeTile(const tagRoom& room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop = false, ROOM_DIRECTION dir = DIRECTIONCOUNT);
	bool createFeature();
	bool createFeature(int x, int y, ROOM_DIRECTION dir, int index = NULL);

	TERRAIN getTileTerrain(int x, int y);

	OBJECT getTileObject(int x, int y);

	vector<tagRoom> getRoom() { return _rooms; }

	void deleteEmptyTiles(); //비어있는 타일들을 지움

	void moveMap(); //0,0 근처로 생성된 맵을 옮김

	void setEndBlock(); //맵의 가장자리에 END블록 설치
	void setEndEdge(); //모서리 빈 곳에 END블록 설치

	void setStone(); //stone 블록 랜덤 생성

	void setBossRoom(); //보스룸 정하기

	void setTorch(); //횃불 놓기

	void testObject(); //함정 테스트 용

	void settingTraps();

	void settingItemBox();

	//이거 쓰면 벡터가 큰데 그게 복사되서 프레임 떨어짐
	//vector<vector<tagTile>> getTiles() { return _tiles; }

	//설정자
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
	void setIsEnemy(int tileX, int tileY, bool b) { _tiles[tileY][tileX].isEnemy = b; }
	void setIsPlayer(int tileX, int tileY, bool b) { _tiles[tileY][tileX].isPlayer = b; }
	void setTileObjectFrameX(int tileX, int tileY, int objectFrameX) { _tiles[tileY][tileX].objectFrameX = objectFrameX; }
	void setTileObjectFrameY(int tileX, int tileY, int objectFrameY) { _tiles[tileY][tileX].objectFrameY = objectFrameY; }

	void setIsBombFired(int tileX, int tileY, bool b) { _tiles[tileY][tileX].isBombFired = b; }

	void setTileItem(int tileX, int tileY, MAP_ITEM item) { 
		_tiles[tileY][tileX].item = item; 
		if (item != MAP_ITEM_NONE && item != MAP_COIN10 && _tiles[tileY][tileX].itemDirection == NONE)
		{
			_tiles[tileY][tileX].itemDirection = UP;
		}
	}

	//접근자
	bool getIsSeen(int tileX, int tileY) { return _tiles[tileY][tileX].isSeen; }
	RECT getRect(int tileX, int tileY) { return _tiles[tileY][tileX].rc; }

	int getXSize() { return _width; }
	int getYSize() { return _height; }

	int getStartRoomX() { return _rooms[_startRoomIndex].x; };
	int getStartRoomY() { return _rooms[_startRoomIndex].y; };

	int getBossRoomX() { return _rooms[_bossRoomIndex].x; }
	int getBossRoomY() { return _rooms[_bossRoomIndex].y; }

	int getBossStairX() { return _bossStair.x; }
	int getBossStairY() { return _bossStair.y; }

	bool getIsHaveTorch(int tileX, int tileY) { return _tiles[tileY][tileX].isHaveTorch; }
	bool getIsEnemy(int tileX, int tileY) { return _tiles[tileY][tileX].isEnemy; }
	bool getIsPlayer(int tileX, int tileY) { return _tiles[tileY][tileX].isPlayer; }
	int getAlpha(int tileX, int tileY) { return _tiles[tileY][tileX].alpha; }
	
	tagTile* getTile(int tileX, int tileY) { return &_tiles[tileY][tileX]; }

	bool getIsBombFired(int tileX, int tileY) { return _tiles[tileY][tileX].isBombFired; }

	MAP_ITEM getTileItem(int tileX, int tileY) { return _tiles[tileY][tileX].item; }
	
	POINT getShopKeeperXY() { return _shopKeeper; }

	void setTileFrameY(int tileX, int tileY, int frameY) {
		for (int i = tileY - VISIONY / 2; i < tileY + VISIONY / 2; i++)
		{
			if (i < 0)continue;
			if (i >= _height) break;
			for (int j = tileX - VISIONX /2 + 5; j < tileX + VISIONX /2 + 5; j++)
			{
				if (j < 0) continue;
				if (j >= _width) break;
				if (_tiles[i][j].terrain == DIRT1 || _tiles[i][j].terrain == DIRT2 || _tiles[i][j].terrain == BOSS)
				{
					_tiles[i][j].terrainFrameY = frameY;
				}
			}
		}
	}
};

