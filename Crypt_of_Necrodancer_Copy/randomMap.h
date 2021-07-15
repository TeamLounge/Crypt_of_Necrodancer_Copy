#pragma once
#include "gameNode.h"
#include "tileMap.h"
#include <set>
#include <vector>

#define TILESIZEX 48
#define TILESIZEY 48

#define TILEX 31
#define TILEY 31

class randomMap : public gameNode
{
private:
	struct ROOM
	{
		int left = 0;
		int top = 0;
		int right = 0;
		int bottom = 0;
		int width =0;
		int height = 0;

		bool leftRoom =false;
		bool rightRoom = false;
		bool topRoom = false;
		bool bottomRoom = false;
		int leftX = 0;
		int leftY = 0;
		int rightX = 0;
		int rightY = 0;
		int topX = 0;
		int topY = 0;
		int bottomX = 0;
		int bottomY = 0;

		bool shop = false;
		bool player = false;
		bool boos = false;
		vector<size_t> neighbors;
	};
	struct floor
	{
		int left = 0;
		int top = 0;
		int right = 0;
		int bottom = 0;
		int lefttop;
		int righttop;
		int leftbottom;
		int rightbottom;
		int present = 0;
	};
	vector<vector<tagTile>> _tiles;
	vector<ROOM> m_room;
	vector<floor> _makeTile;
	int gridX = 3;
	int gridY = 2;
	int present;
	bool isshop;
	int roomWidthMin = 7;
	int roomHeightMin = 7;

public:
	randomMap(){}
	HRESULT init();
	void update();
	void release();
	void render();


	void generate();
	void makeRooms();
	void makePassage();
	void removeUnusedWalls();
	void makeTile();
	void makewalls();

	void placeRoom(const ROOM& room);
	void connectRooms(size_t i, size_t j);

	void shuffle(vector<size_t>& unconnected, size_t size);
	

	TERRAIN getTile(int x, int y);
	void setTile();
};

