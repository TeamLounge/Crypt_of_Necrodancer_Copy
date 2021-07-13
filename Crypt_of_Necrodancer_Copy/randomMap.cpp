#include "stdafx.h"
#include "randomMap.h"
#include <random>
HRESULT randomMap::init(int tileX , int tileY)
{
	for (int i = 0; i < tileY; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < tileX; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j * TILESIZEX, i * TILESIZEY + 30, TILESIZEX, TILESIZEY);
			tile.terrain = EMPTY;
			tile.obj = OBJ_NONE;
			tile.terrainFrameX = 0;
			tile.terrainFrameY = 0;
			vTile.push_back(tile);
		}
		_tiles.push_back(vTile);
	}


	return S_OK;
}

void randomMap::update()
{

}

void randomMap::release()
{

}

void randomMap::render()
{

}


void randomMap::generate()
{
	setTile();
	makeRooms();
	makePassage();
	removeUnusedWalls();
}

void randomMap::makeRooms()
{
	m_room.clear();
	
	int gridwidth = (TILESIZEX - gridX + 1) / gridX;
	int gridHeight = (TILESIZEY - gridY + 1) / gridY;

	for (int y = 0; y < gridY; ++y)
	{
		for (int x = 0; x < gridX; ++x)
		{
			int width = RND->getFromIntTo(roomWidthMin, gridwidth);
			int height = RND->getFromIntTo(roomHeightMin, gridHeight);

			if (RND->getInt(gridX*gridY) == 0)
			{
				width = height = 3;
			}

			int left = x * (gridwidth + 1) + RND->getFromIntTo(0, gridwidth - width);
			int top = y * (gridHeight + 1) + RND->getFromIntTo(0, gridwidth - height);

			ROOM room = { left, top, left + width , top + height };

			if (x > 0)
				room.neighbors.emplace_back((x - 1) + y * gridX);
			if (x < gridX - 1)
				room.neighbors.emplace_back((x + 1) + y * gridX);
			if (y > 0)
				room.neighbors.emplace_back(x + (y - 1)*gridX);
			if (y < gridY - 1)
				room.neighbors.emplace_back(x + (y + 1)*gridX);
			placeRoom(room);
			m_room.emplace_back(room);
		}
	}

}

void randomMap::makePassage()
{
	vector<size_t> unconnected;
	vector<size_t> connected;
	for (size_t i = 0; i < m_room.size(); ++i) 
		unconnected.emplace_back(i);
	//¼ÅÇÃºÎÅÍ

	connected.emplace_back(unconnected.back());

}

void randomMap::removeUnusedWalls()
{
}

void randomMap::placeRoom(const ROOM & room)
{
	for (int y = room.top + 1; y < room.bottom - 1; ++y)
	{
		for (int x = room.left + 1; x < room.right - 1 ;++x)
		{
			_tiles[y][x].terrain = DIRT1;
		}
	}
}

void randomMap::connectRooms(size_t i, size_t j)
{
}

void randomMap::shuffle(vector<size_t>& unconnected, size_t size)
{
	for (size_t i = 0; i < unconnected.size(); ++i)
	{
		size_t dest = RND->getInt(unconnected.size());
		size_t sour= RND->getInt(unconnected.size());
		size_t temp = unconnected[dest];
		unconnected[dest] = unconnected[sour];
		unconnected[sour] = temp;

	}
}

TERRAIN randomMap::getTile(int x, int y)
{
	return TERRAIN();
}

void randomMap::setTile()
{
	for (int y = 0; y < TILEY; ++y)
	{
		for (int x = 0; x < TILEX; ++x)
		{
			_tiles[y][x].terrain = DIRT1;
			_tiles[y][x].obj = WALL_BASIC;
		}
	}

}

