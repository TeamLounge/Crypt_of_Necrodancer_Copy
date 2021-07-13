#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include <set>
#include <vector>

#define TILESIZEX 24
#define TILESIZEY 24

#define TILEX WINSIZEX/TILESIZEX
#define TILEY WINSIZEY/TILESIZEY


enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class randomMap : public gameNode
{
private:
	struct ROOM
	{
		int  x, y;

		int left = 0;
		int top = 0;
		int right = 0;
		int bottom = 0;
		int width = right - left;
		int height = bottom - top;

		vector<size_t> neighbors;
	};
	vector<vector<tagTile>> _tiles;
	vector<ROOM> m_room;
	tagTile m_wall;
	tagTile m_floor;
	tagTile m_passage;

	int gridX = 5;
	int gridY = 3;

	int roomWidthMin = 5;
	int roomHeightMin = 5;


public:
	randomMap(){}
	HRESULT init(int tileX, int tileY);
	void update();
	void release();
	void render();


	void generate();
	void makeRooms();
	void makePassage();
	void removeUnusedWalls();

	void placeRoom(const ROOM& room);
	void connectRooms(size_t i, size_t j);

	void shuffle(vector<size_t>& unconnected, size_t size);
	

	TERRAIN getTile(int x, int y);
	void setTile();
};

