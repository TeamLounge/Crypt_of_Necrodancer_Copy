#pragma once
#include "singletonBase.h"
#define MINIMAP_TILE_SIZE 6

enum OBJECT
{
	OBJ_NONE, WALL_BASIC, WALL_GOLD, WALL_STONE, WALL_CRACK, WALL_DOOR, WALL_END,
	TR_BOMB, TR_UP, TR_DOWN, TR_LEFT, TR_RIGHT,
	TR_FAST, TR_SLOW, TR_JUMP, TR_DOOR, TR_SPIKE, RED_ITEM_BOX, BLACK_ITEM_BOX, BOX, BARREL
	, ENEMY
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

	void drawMiniMap(int tileX, int tileY, OBJECT obj = OBJ_NONE, bool isPlayer = false, bool isEnemy = false);
};