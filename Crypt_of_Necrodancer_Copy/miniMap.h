#pragma once
#include "singletonBase.h"
#define MINIMAP_TILE_SIZE 6

enum OBJECT
{
	OBJ_NONE, WALL_BASIC, WALL_GOLD, WALL_STONE, WALL_CRACK, WALL_DOOR, WALL_END,
	TR_BOMB, TR_UP, TR_DOWN, TR_LEFT, TR_RIGHT,
	TR_FAST, TR_SLOW, TR_JUMP, RED_ITEM_BOX, BLACK_ITEM_BOX, BOX, BARREL, TR_DOOR, TR_SPIKE,
	SHOPKEEPER
	
};

enum MAP_ITEM
{
	MAP_ITEM_NONE,
	MAP_TORCH_PLUS_1,
	MAP_TORCH_PLUS_2,
	MAP_TITANUM_SHOVEL,
	MAP_LEATHER_ARMOR,
	MAP_CHAIN_ARMOR,
	MAP_DAGGER,
	MAP_BROADSWORD,
	MAP_RAPIER,
	MAP_LONGSWORD,
	MAP_SPEAR,
	MAP_APPLE,
	MAP_CHEESE,
	MAP_COIN1,
	MAP_COIN2,
	MAP_COIN3,
	MAP_COIN4,
	MAP_COIN5,
	MAP_COIN6,
	MAP_COIN7,
	MAP_COIN8,
	MAP_COIN9,
	MAP_COIN10,
	MAP_BOMB
};

enum TERRAIN
{
	DIRT1, DIRT2, BOSS, WATER, SHOP, STAIR_BOSS, STAIR_NONE, EMPTY
};


class miniMap : public singletonBase<miniMap>
{
private:

	image* _miniMapBuffer;

	int _mapSizeX;
	int _mapSizeY;

	//vector<vector<tagMap>> _miniMap;

public :
	HRESULT init();
	void release();
	void render(HDC hdc);

	void setupMiniMap(int sizeX, int sizeY);

	void drawMiniMap(int tileX, int tileY, TERRAIN terrain, OBJECT obj = OBJ_NONE, MAP_ITEM item = MAP_ITEM_NONE, bool isEnemy = false);
	void drawPlayer(int tileX, int tileY);
};