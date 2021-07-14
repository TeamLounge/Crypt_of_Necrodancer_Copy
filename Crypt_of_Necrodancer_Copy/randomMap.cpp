#include "stdafx.h"
#include "randomMap.h"
#include <list>
#include <random>
HRESULT randomMap::init()
{
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("walls1", "image/object/walls/walls.bmp", 384, 864, 8, 9, true, RGB(255, 0, 255));
	for (int i = 0; i < TILEY; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < TILEX; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j * TILESIZEX, i * TILESIZEY, TILESIZEX, TILESIZEY);
			tile.terrain = EMPTY;
			tile.obj = OBJ_NONE;
			tile.terrainFrameX = 0;
			tile.terrainFrameY = 0;
			vTile.push_back(tile);
		}
		_tiles.push_back(vTile);
	}

	generate();
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
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			Rectangle(getMemDC(), _tiles[i][j].rc);
			switch (_tiles[i][j].terrain)
			{
			case DIRT1:
				IMAGEMANAGER->frameRender("dirt1_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case DIRT2:
				IMAGEMANAGER->frameRender("dirt2_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case BOSS:
				IMAGEMANAGER->frameRender("boss_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case WATER:
				IMAGEMANAGER->frameRender("water_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, 0);
				break;
			case SHOP:
				IMAGEMANAGER->frameRender("shop_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
				break;
			}

			switch (_tiles[i][j].obj)
			{
			case OBJ_NONE:
				break;
			case WALL_BASIC:
				IMAGEMANAGER->frameRender("walls1", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case WALL_GOLD:
			case WALL_STONE:
			case WALL_CRACK:
			case WALL_DOOR:
			case WALL_END:
				IMAGEMANAGER->frameRender("walls2", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_BOMB:
				IMAGEMANAGER->frameRender("bomb_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("bomb_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_UP:
				IMAGEMANAGER->frameRender("up_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("up_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_DOWN:
				IMAGEMANAGER->frameRender("down_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("down_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_LEFT:
				IMAGEMANAGER->frameRender("left_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("left_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_RIGHT:
				IMAGEMANAGER->frameRender("right_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("right_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_FAST:
				IMAGEMANAGER->frameRender("fast_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("fast_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_SLOW:
				IMAGEMANAGER->frameRender("slow_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("slow_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_DOOR:
				IMAGEMANAGER->frameRender("door_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("door_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case TR_SPIKE:
				IMAGEMANAGER->frameRender("spike_trap", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("spike_trap")->getFrameHeight() / 2, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				break;
			case RED_ITEM_BOX:
				IMAGEMANAGER->frameRender("red_item_box", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("red_item_box")->getFrameHeight() / 2, 0, 0);
				break;
			case BLACK_ITEM_BOX:
				IMAGEMANAGER->frameRender("black_item_box", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("black_item_box")->getFrameHeight() / 2, 0, 0);
				break;
			case BOX:
				IMAGEMANAGER->frameRender("box", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("box")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("box")->getFrameHeight() / 2, 0, 0);
				break;
			case BARREL:
				IMAGEMANAGER->frameRender("barrel", getMemDC(),
					(_tiles[i][j].rc.left + _tiles[i][j].rc.right) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameWidth() / 2,
					(_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2 - IMAGEMANAGER->findImage("barrel")->getFrameHeight() / 2, 0, 0);
				break;
			}


		}
	}

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
	
	int gridwidth = TILEX / gridX;
	int gridHeight = TILEY / gridY;

	for (int y = 0; y < gridY; ++y)
	{
		for (int x = 0; x < gridX; ++x)
		{
			int width = RND->getFromIntTo(roomWidthMin, gridwidth);
			int height = RND->getFromIntTo(roomHeightMin, gridHeight);

			if (RND->getInt(gridX*gridY) == 0)
			{
				width = height = 4;
			}

			int left = x * (gridwidth + 1) + RND->getInt(gridwidth - width);
			int top = y * (gridHeight + 1) + RND->getInt(gridHeight - height);

			ROOM room;
			room.left = left;
			room.top = top;
			room.right = left + width;
			room.bottom = top + height;
			room.width = width;
			room.height = height;

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

	shuffle(unconnected, unconnected.size());
	connected.emplace_back(unconnected.back());

	unconnected.pop_back();

	while (!unconnected.empty())
	{
		size_t i = connected[RND->getInt(connected.size())];
		if (m_room[i].neighbors.empty())
		{
			connected.erase(remove(connected.begin(), connected.end(), i), connected.end());
			continue;
		}
		size_t j= m_room[i].neighbors[RND->getInt(m_room[i].neighbors.size())];

		connectRooms(i, j);
		unconnected.erase(remove(unconnected.begin(), unconnected.end(), j), unconnected.end());
		connected.emplace_back(j);
	}

}

void randomMap::removeUnusedWalls()
{
	for (int y = 0; y < TILEY; ++y)
	{
		for (int x = 0; x < TILEX; ++x)
		{
			int numWalls = 0;

			for (int dy = -1; dy <= 1; ++dy)
			{
				for (int dx = -1; dx <= 1; ++dx)
				{
					if (x + dx < 0 || y + dy < 0 || x + dx >= TILEX || y + dy >= TILEY)
						++numWalls;
					else
					{
						const int tileNumber = _tiles[y + dy][x + dx].obj;
						const int tileshit = _tiles[y + dy][x + dx].terrain;
						if (tileNumber == WALL_BASIC || tileshit == EMPTY)
							++numWalls;
					}
				}
			}
			if (numWalls == 9)
			{
				_tiles[y][x].obj = OBJ_NONE;
				_tiles[y][x].terrain = EMPTY;
			}
		}
	}
}

void randomMap::placeRoom(const ROOM & room)
{
	for (int y = room.top + 1 ; y < room.bottom - 1; ++y)
	{
		for (int x = room.left + 1; x < room.right - 1 ;++x)
		{
			_tiles[y][x].obj = OBJ_NONE;
		}
	}
}

void randomMap::connectRooms(size_t i, size_t j)
{
	if (j < i)
		swap(i, j);

	ROOM& from = m_room[i];
	ROOM& to = m_room[j];

	if (j - i == 1) //Horizontal passage
	{
		const int fromX = from.right - 1;
		//((from.top+1) -(from.bottom-2)==0) ? from.top+1 :(from.top +1, from.bottom -2)
		const int fromY =  RND->getFromIntTo(from.top+1 , from.bottom -2);

		const int toX = to.left+1;
		//((to.top + 1) - (to.bottom - 2)==0) ? to.top +1 : (to.top+1 , to.bottom-2)
		const int toY = RND->getFromIntTo(to.top+1 , to.bottom-2);

		//((fromX+1)-(toX-1)==0)? fromX+1 : (fromX +1, toX -1)
		const int centerX = RND->getFromIntTo(fromX +1, toX -1);
		const int dy = toY > fromY ? 1 : -1;

		for (int x = fromX; x < centerX; ++x)
		{
			_tiles[fromY][x].obj = OBJ_NONE;
		}
		for (int y = fromY; y != toY; y += dy)
		{
			_tiles[y][centerX].obj = OBJ_NONE;
		}
		for (int x = centerX; x <= toX; ++x)
		{	
			_tiles[toY][x].obj = OBJ_NONE;
		}

	}
	else // Vertical passage
	{
		//((from.left +1)-(from.right-2)==0)? from.left+1: 
		const int fromX = RND->getFromIntTo(from.left +1 , from.right-2 );
		const int fromY = from.bottom - 1;

		//((to.left+1) - (to.right-2)==0)? to.left+1: 
		const int toX = RND->getFromIntTo(to.left +1, to.right -2);
		const int toY = to.top+1;

		// ((fromY +1) - (toY-1)==0)? fromY+1:
		const int centerY = RND->getFromIntTo(fromY+1, toY -1);
		const int dx = toX > fromX ? 1 : -1;
		for (int y = fromY; y < centerY; ++y)
		{
			_tiles[y][fromX].obj = OBJ_NONE;
		}
		for (int x = fromX; x != toX; x += dx)
		{
			_tiles[centerY][x].obj = OBJ_NONE;
		}
		for (int y = centerY; y <= toY; ++y)
		{
			_tiles[y][toX].obj = OBJ_NONE;
		}
	}

	from.neighbors.erase(remove(from.neighbors.begin(), from.neighbors.end(), j), from.neighbors.end());
	to.neighbors.erase(remove(to.neighbors.begin(), to.neighbors.end(), i), to.neighbors.end());

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
	for (int y = 0; y < TILEY ; ++y)
	{
		for (int x = 0; x < TILEX; ++x)
		{
			_tiles[y][x].terrain = DIRT1;
			_tiles[y][x].obj = WALL_BASIC;
			_tiles[y][x].objectFrameX = 0;
			_tiles[y][x].objectFrameY = 0;
		}
	}
}

