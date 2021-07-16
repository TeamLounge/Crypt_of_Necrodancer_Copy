#include "stdafx.h"
#include "mapGenerator.h"

HRESULT mapGenerator::init(int width, int height)
{
	_width = width;
	_height = height;

	_isMakeRoom = false;
	_isHaveCorridor = false;

	return S_OK;
}

void mapGenerator::release()
{
}

void mapGenerator::update()
{
}

void mapGenerator::render()
{
	for (int i = 0; i < _tiles.size(); ++i)
	{
		for (int j = 0; j < _tiles[i].size(); ++j)
		{
			switch (_tiles[i][j].terrain)
			{
			case DIRT1:
				IMAGEMANAGER->frameRender("dirt1_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case DIRT2:
				IMAGEMANAGER->frameRender("dirt2_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case BOSS:
				IMAGEMANAGER->frameRender("boss_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case WATER:
				IMAGEMANAGER->frameRender("water_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case SHOP:
				IMAGEMANAGER->frameRender("shop_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, 0, 0);
				break;
			case STAIR:
				IMAGEMANAGER->frameRender("stair_tile", getMemDC(),
					_tiles[i][j].rc.left, _tiles[i][j].rc.top, _tiles[i][j].terrainFrameX, _tiles[i][j].terrainFrameY);
				break;
			case EMPTY:
				break;
			}

			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				Rectangle(getMemDC(), _tiles[i][j].rc);
			}


			if (_tiles[i][j].obj == OBJ_NONE) continue;
			if (_tiles[i][j].obj == WALL_BASIC)
			{
				IMAGEMANAGER->frameRender("walls1", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
			}
			else if (_tiles[i][j].obj == WALL_GOLD || _tiles[i][j].obj == WALL_STONE || _tiles[i][j].obj == WALL_CRACK
				|| _tiles[i][j].obj == WALL_DOOR || _tiles[i][j].obj == WALL_END)
			{
				IMAGEMANAGER->frameRender("walls2", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
			}

		}
	}

	for (int i = 0; i < _rooms.size(); i++)
	{
		char str[128];
		if (_rooms[i].roomState == ROOM_START)
		{
			sprintf_s(str, "start");
			TextOut(getMemDC(), _tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, str, strlen(str));
		}
		if (_rooms[i].roomState == ROOM_BOSS)
		{
			sprintf_s(str, "boss");
			TextOut(getMemDC(), _tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, str, strlen(str));
		}
	}
}

void mapGenerator::generate(int maxFeatures)
{
	//���Ⱑ ����
	_tiles.clear();
	_rooms.clear();
	_corridors.clear();
	_exits.clear();
	for (int i = 0; i < _height; ++i)
	{
		vector<tagTile> vTile;
		for (int j = 0; j < _width; ++j)
		{
			tagTile tile;
			tile.rc = RectMake(j * TILESIZE, i * TILESIZE + 30, TILESIZE, TILESIZE);
			tile.terrain = EMPTY;
			tile.obj = OBJ_NONE;
			tile.terrainFrameX = NULL;
			tile.terrainFrameY = NULL;
			tile.objectFrameX = NULL;
			tile.objectFrameY = NULL;
			vTile.push_back(tile);
		}
		_tiles.push_back(vTile);
	}

	if (!makeRoom(_width / 2, _height / 2, static_cast<Direction>(RND->getInt(4), true)))
	{
		return;
	}
	//��ŸƮ ���� ���� ����
	while (1)
	{
		_start = RND->getFromIntTo(1, (maxFeatures - 2) * 2);
		if (_start % 2 == 0)
		{
			break;
		}
	}
	//����� �����
	for (int i = 1; i < (maxFeatures - 1) * 2 - 1; ++i)
	{
		if (i % 2 != 0)
		{
			_isMakeRoom = false;
		}
		else
		{
			_isMakeRoom = true;
		}
		if (!createFeature(i))
		{
			break;
		}
	}
	//�������� ������ �����
	makeShop();

	//��� ���� �� ������ Ÿ�� ä���

	//y������ ����
	for (int j = 0; j < _tiles[0].size(); j++)
	{
		bool _isEmptyRoom = false;;
		for (int i = 0; i < _tiles.size() - 1; i++)
		{
			if (_tiles[i][j].terrain == DIRT1)
			{
				if (_tiles[i + 1][j].terrain == EMPTY)
				{
					POINT p;
					p.x = j;
					p.y = i + 1;
					_newRoomYIndex.push_back(p);
					_isEmptyRoom = true;
				}
			}
			else if (_isEmptyRoom)
			{
				if (_tiles[i + 1][j].terrain == DIRT1)
				{
					POINT p;
					p.x = j;
					p.y = i + 1;
					_newRoomYIndex.push_back(p);
					_isEmptyRoom = false;
				}
			}
		}
		if (_isEmptyRoom)
		{
			_newRoomYIndex.pop_back();
		}
	}

	//Ÿ�� ����
	for (int i = 0; i < _newRoomYIndex.size(); i++)
	{
		if (i % 2 == 0)
		{
			if (_newRoomYIndex[i + 1].y - _newRoomYIndex[i].y >= 5) continue;
			for (int j = _newRoomYIndex[i].y; j < _newRoomYIndex[i + 1].y; j++)
			{
				_tiles[j][_newRoomYIndex[i].x].terrain = DIRT1;
				_tiles[j][_newRoomYIndex[i].x].terrainFrameX = 0;
				_tiles[j][_newRoomYIndex[i].x].terrainFrameY = 0;
				_tiles[j][_newRoomYIndex[i].x].obj = OBJ_NONE;
				_tiles[j][_newRoomYIndex[i].x].objectFrameX = NULL;
				_tiles[j][_newRoomYIndex[i].x].objectFrameY = NULL;
			}
		}
	}
	vector<POINT>::iterator iter;
	for (iter = _newRoomYIndex.begin(); iter != _newRoomYIndex.end();)
	{
		if ((iter + 1)->y - iter->y >= 5)
		{
			iter = _newRoomYIndex.erase(iter);
			iter = _newRoomYIndex.erase(iter);
		}
		else
		{
			iter += 2;
		}
	}

	//�̴Ϸ뿡 �߰�
	for (int i = 0; i < _newRoomYIndex.size();)
	{
		tagRoom room;
		room.x = _newRoomYIndex[i].x;
		room.y = _newRoomYIndex[i].y;
		room.width = 1;
		room.height = _newRoomYIndex[i + 1].y - _newRoomYIndex[i].y;
		int j = i + 2;
		for (; j < _newRoomYIndex.size();)
		{
			if (_newRoomYIndex[i].y == _newRoomYIndex[j].y && _newRoomYIndex[i].x + (j - i) / 2 == _newRoomYIndex[j].x)
			{
				room.width++;
				j += 2;
			}
			else
			{
				break;
			}
		}
		i = j;
		_miniRooms.push_back(room);
	}

	//x������ ����
	for (int i = 0; i < _tiles.size(); i++)
	{
		bool _isEmptyRoom = false;;
		for (int j = 0; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == DIRT1)
			{
				if (_tiles[i][j + 1].terrain == EMPTY)
				{
					POINT p;
					p.x = j + 1;
					p.y = i;
					_newRoomXIndex.push_back(p);
					_isEmptyRoom = true;
				}
			}
			else if (_isEmptyRoom)
			{
				if (_tiles[i][j + 1].terrain == DIRT1)
				{
					POINT p;
					p.x = j + 1;
					p.y = i;
					_newRoomXIndex.push_back(p);
					_isEmptyRoom = false;
				}
			}
		}
		if (_isEmptyRoom)
		{
			_newRoomXIndex.pop_back();
		}
	}
	//Ÿ�� ����
	for (int i = 0; i < _newRoomXIndex.size(); i++)
	{
		if (i % 2 == 0)
		{
			if (_newRoomXIndex[i + 1].x - _newRoomXIndex[i].x >= 5) continue;
			for (int j = _newRoomXIndex[i].x; j < _newRoomXIndex[i + 1].x; j++)
			{
				_tiles[_newRoomXIndex[i].y][j].terrain = DIRT1;
				_tiles[_newRoomXIndex[i].y][j].terrainFrameX = 0;
				_tiles[_newRoomXIndex[i].y][j].terrainFrameY = 0;
				_tiles[_newRoomXIndex[i].y][j].obj = OBJ_NONE;
				_tiles[_newRoomXIndex[i].y][j].objectFrameX = NULL;
				_tiles[_newRoomXIndex[i].y][j].objectFrameY = NULL;
			}
		}
	}


	for (iter = _newRoomXIndex.begin(); iter != _newRoomXIndex.end();)
	{
		if ((iter + 1)->x - iter->x >= 5)
		{
			iter = _newRoomXIndex.erase(iter);
			iter = _newRoomXIndex.erase(iter);
		}
		else
		{
			iter += 2;
		}
	}



	//�̴Ϸ����� �߰�
	for (int i = 0; i < _newRoomXIndex.size();)
	{
		tagRoom room;
		room.x = _newRoomXIndex[i].x;
		room.y = _newRoomXIndex[i].y;
		room.width = _newRoomXIndex[i + 1].x - _newRoomXIndex[i].x;
		room.height = 1;
		int j = i + 2;
		for (; j < _newRoomXIndex.size();)
		{
			if (_newRoomXIndex[i].x == _newRoomXIndex[j].x && _newRoomXIndex[i].y + (j - i) / 2 == _newRoomXIndex[j].y)
			{
				room.height++;
				j += 2;
			}
			else
			{
				break;
			}
		}
		i = j;
		_miniRooms.push_back(room);
		_miniRooms[0].x;
	}

	//ä�� ����� ���� �� �ױ�(y������)
	for (int i = 1; i < _tiles.size() - 1; i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i - 1][j].terrain == DIRT1 && _tiles[i - 1][j].obj == OBJ_NONE)
				{
					_tiles[i][j].terrain = DIRT1;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
					_tiles[i][j].obj = WALL_BASIC;
					_tiles[i][j].objectFrameX = 0;
					_tiles[i][j].objectFrameY = 0;
				}
				if (_tiles[i + 1][j].terrain == DIRT1 && _tiles[i + 1][j].obj == OBJ_NONE)
				{
					_tiles[i][j].terrain = DIRT1;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
					_tiles[i][j].obj = WALL_BASIC;
					_tiles[i][j].objectFrameX = 0;
					_tiles[i][j].objectFrameY = 0;
				}
			}
		}
	}
	//x������
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i][j - 1].terrain == DIRT1 && _tiles[i][j - 1].obj == OBJ_NONE)
				{
					_tiles[i][j].terrain = DIRT1;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
					_tiles[i][j].obj = WALL_BASIC;
					_tiles[i][j].objectFrameX = 0;
					_tiles[i][j].objectFrameY = 0;
				}
				if (_tiles[i][j + 1].terrain == DIRT1 && _tiles[i][j + 1].obj == OBJ_NONE)
				{
					_tiles[i][j].terrain = DIRT1;
					_tiles[i][j].terrainFrameX = 0;
					_tiles[i][j].terrainFrameY = 0;
					_tiles[i][j].obj = WALL_BASIC;
					_tiles[i][j].objectFrameX = 0;
					_tiles[i][j].objectFrameY = 0;
				}
			}
		}
	}

	vector<tagRoom>::iterator roomIter;
	for (roomIter = _miniRooms.begin(); roomIter != _miniRooms.end();)
	{
		if (roomIter->height <= 1 || roomIter->width <= 1)
		{
			for (int j = roomIter->y; j < roomIter->y + roomIter->height; j++)
			{
				for (int k = roomIter->x; k < roomIter->x + roomIter->width; k++)
				{
					_tiles[j][k].obj = WALL_BASIC;
					_tiles[j][k].objectFrameY = 0;
					_tiles[j][k].objectFrameX = 0;
				}
			}
			roomIter = _miniRooms.erase(roomIter);
		}
		else
		{
			roomIter++;
		}
	}

	while (1)
	{
		if (_miniRooms.size() <= 3) break;
		else
		{
			int num = RND->getInt(_miniRooms.size());
			for (int i = _miniRooms[num].y; i < _miniRooms[num].y + _miniRooms[num].height; i++)
			{
				for (int j = _miniRooms[num].x; i < _miniRooms[num].x + _miniRooms[num].width; j++)
				{
					if (_tiles[i][j].obj == OBJ_NONE)
					{
						_tiles[i][j].obj = WALL_BASIC;
						_tiles[i][j].objectFrameY = 0;
						_tiles[i][j].objectFrameX = 0;
					}
				}
			}
			_miniRooms.erase(_miniRooms.begin() + num);
		}
	}

	//���ױ�
	for (int i = 1; i < _tiles.size() - 1; i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i - 1][j].terrain == DIRT1 || _tiles[i + 1][j].terrain == DIRT1)
				{
					_newWallIndex.emplace_back(POINT{ j, i });
				}
			}
		}
	}
	for (int i = 0; i < _newWallIndex.size(); i++)
	{
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrain = DIRT1;
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrainFrameX = 0;
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].terrainFrameY = 0;
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].obj = WALL_BASIC;
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].objectFrameX = 0;
		_tiles[_newWallIndex[i].y][_newWallIndex[i].x].objectFrameY = 0;
	}


	setEndBlock();
	setEndEdge();
	moveMap();
	setEndBlock();
	deleteEmptyTiles();
	setStone();
	setBossRoom();
}

bool mapGenerator::makeRoom(int x, int y, Direction dir, bool firstRoom, int index)
{
	int minRoomSize = 5;
	int maxRoomSize = 8;
	tagRoom room;
	if (index == _start)
	{
		room.roomState = ROOM_START;
		room.width = 5;
		room.height = 5;
	}
	else
	{
		room.width = RND->getFromIntTo(minRoomSize, maxRoomSize);
		room.height = RND->getFromIntTo(minRoomSize, maxRoomSize);
		room.roomState = ROOM_BASIC;
	}


	switch (dir)
	{
	case NORTH:
		room.x = x - room.width / 2;
		room.y = y - room.height;
		break;
	case SOUTH:
		room.x = x - room.width / 2;
		room.y = y + 1;
		break;
	case WEST:
		room.x = x - room.width;
		room.y = y - room.height / 2;
		break;
	case EAST:
		room.x = x + 1;
		room.y = y - room.height / 2;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (room.x < 3 || room.y < 3 || room.x + room.width + 2 >= _tiles[0].size() || room.y + room.height + 2 >= _tiles.size())
	{
		return false;
	}

	if (placeTile(room, OBJ_NONE, NULL, NULL))
	{
		_rooms.emplace_back(room);

		if (dir != SOUTH || firstRoom)
			_exits.emplace_back(tagRoom{ room.x, room.y - 1, room.width, 1 });
		if (dir != NORTH || firstRoom)
		{
			_exits.emplace_back(tagRoom{ room.x, room.y + room.height, room.width, 1 });
		}
		if (dir != EAST || firstRoom) // west side
			_exits.emplace_back(tagRoom{ room.x - 1, room.y, 1, room.height });
		if (dir != WEST || firstRoom) // east side
			_exits.emplace_back(tagRoom{ room.x + room.width, room.y, 1, room.height });
		return true;
	}
	return false;
}

bool mapGenerator::makeCorridor(int x, int y, Direction dir)
{
	int minCorridorLength = 0;
	int maxCorridorLength = 2;

	tagRoom corridor;
	corridor.x = x;
	corridor.y = y;

	switch (dir)
	{
	case NORTH:
		corridor.width = 1;
		corridor.height = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.height == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.y = y - corridor.height;
		break;
	case SOUTH:
		corridor.width = 1;
		corridor.height = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.height == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.y = y + 1;
		break;
	case WEST:
		corridor.height = 1;
		corridor.width = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.width == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.x = x - corridor.width;
		break;
	case EAST:
		corridor.height = 1;
		corridor.width = RND->getFromIntTo(minCorridorLength, maxCorridorLength);
		if (corridor.width == 0)
		{
			_isHaveCorridor = false;
			return true;
		}
		corridor.x = x + 1;
		break;
	default:
		break;
	}

	if (corridor.x < 3 || corridor.y < 3 || corridor.y + corridor.height + 2 >= _tiles.size() || corridor.x + corridor.width + 2 >= _tiles[0].size())
	{
		return false;
	}
	if (placeTile(corridor, OBJ_NONE, NULL, NULL))
	{
		_corridors.emplace_back(corridor);
		switch (dir)
		{
		case NORTH:
			_exits.emplace_back(tagRoom{ corridor.x, corridor.y - 1, corridor.width, 1 });
			_corridorDirection = NORTH;
			break;
		case SOUTH:
			_exits.emplace_back(tagRoom{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
			_corridorDirection = SOUTH;
			break;
		case WEST:
			_exits.emplace_back(tagRoom{ corridor.x - 1 , corridor.y, 1, corridor.height });
			_corridorDirection = WEST;
			break;
		case EAST:
			_exits.emplace_back(tagRoom{ corridor.x + corridor.width, corridor.y, 1, corridor.height });
			_corridorDirection = EAST;
			break;
		case DIRECTIONCOUNT:
			break;
		default:
			break;
		}
		_isHaveCorridor = true;
		return true;
	}

	return false;
}

bool mapGenerator::makeShop()
{
	for (int i = 0; i < 1000; ++i)
	{
		int r = RND->getInt(_exits.size());
		int x, y;
		if (_exits[r].width - 1 == 0)
		{
			x = _exits[r].x;
		}
		else
		{
			x = RND->getFromIntTo(_exits[r].x, _exits[r].x + _exits[r].width - 1);
		}
		if (_exits[r].height - 1 == 0)
		{
			y = _exits[r].y;
		}
		else
		{
			y = RND->getFromIntTo(_exits[r].y, _exits[r].y + _exits[r].height - 1);
		}
		for (int j = 0; j < DIRECTIONCOUNT; ++j)
		{
			if (makeShop(x, y, static_cast<Direction>(j)))
			{
				_exits.erase(_exits.begin() + r);
				return true;
			}
		}
	}
	return false;
}

bool mapGenerator::makeShop(int x, int y, Direction dir)
{
	tagRoom room;
	room.roomState = ROOM_SHOP;
	switch (dir)
	{
	case NORTH:
		room.width = 7;
		room.height = 8;
		room.x = x - room.width / 2;
		room.y = y - room.height;
		break;
	case SOUTH:
		room.width = 7;
		room.height = 8;
		room.x = x - room.width / 2;
		room.y = y + 1;
		break;
	case WEST:
		room.width = 6;
		room.height = 9;
		room.x = x - room.width;
		room.y = y - room.height / 2;
		break;
	case EAST:
		room.width = 6;
		room.height = 9;
		room.x = x + 1;
		room.y = y - room.height / 2;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (placeTile(room, OBJ_NONE, NULL, NULL, true, dir))
	{
		_rooms.emplace_back(room);

		if (dir != SOUTH)
			_exits.emplace_back(tagRoom{ room.x, room.y - 1, room.width, 1 });
		if (dir != NORTH)
		{
			_exits.emplace_back(tagRoom{ room.x, room.y + room.height, room.width, 1 });
		}
		if (dir != EAST) // west side
			_exits.emplace_back(tagRoom{ room.x - 1, room.y, 1, room.height });
		if (dir != WEST) // east side
			_exits.emplace_back(tagRoom{ room.x + room.width, room.y, 1, room.height });

		_tiles[y][x].obj = WALL_DOOR;
		_tiles[y][x].objectFrameY = 2;
		if (dir == WEST || dir == EAST)
		{
			_tiles[y][x].objectFrameX = 5;
		}
		else
		{
			_tiles[y][x].objectFrameX = 4;
		}
		return true;
		return true;
	}
	return false;
}

bool mapGenerator::placeTile(const tagRoom & room, OBJECT obj, int objectFrameX, int objectFrameY, bool _isShop, Direction dir)
{
	if (room.x < 1 || room.y < 1 || room.x + room.width > _width - 1 || room.y + room.height > _height - 1)
		return false;

	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			if (_tiles[y][x].terrain != EMPTY)
				return false;
		}
	}

	if (_isShop)
	{
		for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		{
			for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
			{
				_tiles[y][x].terrain = DIRT1;
				_tiles[y][x].terrainFrameX = 0;
				_tiles[y][x].terrainFrameY = 0;
				_tiles[y][x].obj = obj;
				_tiles[y][x].objectFrameX = objectFrameX;
				_tiles[y][x].objectFrameY = objectFrameY;
			}

			switch (dir)
			{
			case NORTH:
			case SOUTH:
			case WEST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_BASIC;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				_tiles[y][room.x].terrain = DIRT1;
				_tiles[y][room.x].terrainFrameX = 0;
				_tiles[y][room.x].terrainFrameY = 0;
				_tiles[y][room.x].obj = WALL_GOLD;
				_tiles[y][room.x].objectFrameX = 0;
				_tiles[y][room.x].objectFrameY = 0;
				break;
			case EAST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_GOLD;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				else
				{
					_tiles[y][room.x - 1].terrain = DIRT1;
					_tiles[y][room.x - 1].terrainFrameX = 0;
					_tiles[y][room.x - 1].terrainFrameY = 0;
					_tiles[y][room.x - 1].obj = WALL_BASIC;
					_tiles[y][room.x - 1].objectFrameX = 0;
					_tiles[y][room.x - 1].objectFrameY = 0;
				}
				break;
			default:
				break;
			}

			switch (dir)
			{
			case NORTH:
			case SOUTH:
			case EAST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x + room.width - 1].terrain = DIRT1;
					_tiles[y][room.x + room.width - 1].terrainFrameX = 0;
					_tiles[y][room.x + room.width - 1].terrainFrameY = 0;
					_tiles[y][room.x + room.width - 1].obj = WALL_GOLD;
					_tiles[y][room.x + room.width - 1].objectFrameX = 0;
					_tiles[y][room.x + room.width - 1].objectFrameY = 0;
				}
				_tiles[y][room.x + room.width].terrain = DIRT1;
				_tiles[y][room.x + room.width].terrainFrameX = 0;
				_tiles[y][room.x + room.width].terrainFrameY = 0;
				_tiles[y][room.x + room.width].obj = WALL_BASIC;
				_tiles[y][room.x + room.width].objectFrameX = 0;
				_tiles[y][room.x + room.width].objectFrameY = 0;
				break;
			case WEST:
				if (y != room.y - 1 && y != room.y + room.height)
				{
					_tiles[y][room.x + room.width].terrain = DIRT1;
					_tiles[y][room.x + room.width].terrainFrameX = 0;
					_tiles[y][room.x + room.width].terrainFrameY = 0;
					_tiles[y][room.x + room.width].obj = WALL_GOLD;
					_tiles[y][room.x + room.width].objectFrameX = 0;
					_tiles[y][room.x + room.width].objectFrameY = 0;
				}
				else
				{
					_tiles[y][room.x + room.width].terrain = DIRT1;
					_tiles[y][room.x + room.width].terrainFrameX = 0;
					_tiles[y][room.x + room.width].terrainFrameY = 0;
					_tiles[y][room.x + room.width].obj = WALL_BASIC;
					_tiles[y][room.x + room.width].objectFrameX = 0;
					_tiles[y][room.x + room.width].objectFrameY = 0;
				}
			default:
				break;
			}


		}
		for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
		{
			switch (dir)
			{
			case NORTH:
			case EAST:
			case WEST:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y][x].terrain = DIRT1;
					_tiles[room.y][x].terrainFrameX = 0;
					_tiles[room.y][x].terrainFrameY = 0;
					_tiles[room.y][x].obj = WALL_GOLD;
					_tiles[room.y][x].objectFrameX = 0;
					_tiles[room.y][x].objectFrameY = 0;
				}
				_tiles[room.y - 1][x].terrain = DIRT1;
				_tiles[room.y - 1][x].terrainFrameX = 0;
				_tiles[room.y - 1][x].terrainFrameY = 0;
				_tiles[room.y - 1][x].obj = WALL_BASIC;
				_tiles[room.y - 1][x].objectFrameX = 0;
				_tiles[room.y - 1][x].objectFrameY = 0;
				break;
			case SOUTH:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y - 1][x].terrain = DIRT1;
					_tiles[room.y - 1][x].terrainFrameX = 0;
					_tiles[room.y - 1][x].terrainFrameY = 0;
					_tiles[room.y - 1][x].obj = WALL_GOLD;
					_tiles[room.y - 1][x].objectFrameX = 0;
					_tiles[room.y - 1][x].objectFrameY = 0;
				}
				else
				{
					_tiles[room.y - 1][x].terrain = DIRT1;
					_tiles[room.y - 1][x].terrainFrameX = 0;
					_tiles[room.y - 1][x].terrainFrameY = 0;
					_tiles[room.y - 1][x].obj = WALL_BASIC;
					_tiles[room.y - 1][x].objectFrameX = 0;
					_tiles[room.y - 1][x].objectFrameY = 0;
				}
			default:
				break;
			}
			switch (dir)
			{
			case SOUTH:
			case EAST:
			case WEST:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y + room.height - 1][x].terrain = DIRT1;
					_tiles[room.y + room.height - 1][x].terrainFrameX = 0;
					_tiles[room.y + room.height - 1][x].terrainFrameY = 0;
					_tiles[room.y + room.height - 1][x].obj = WALL_GOLD;
					_tiles[room.y + room.height - 1][x].objectFrameX = 0;
					_tiles[room.y + room.height - 1][x].objectFrameY = 0;
				}
				_tiles[room.y + room.height][x].terrain = DIRT1;
				_tiles[room.y + room.height][x].terrainFrameX = 0;
				_tiles[room.y + room.height][x].terrainFrameY = 0;
				_tiles[room.y + room.height][x].obj = WALL_BASIC;
				_tiles[room.y + room.height][x].objectFrameX = 0;
				_tiles[room.y + room.height][x].objectFrameY = 0;
				break;
			case NORTH:
				if (x != room.x - 1 && x != room.x + room.width)
				{
					_tiles[room.y + room.height][x].terrain = DIRT1;
					_tiles[room.y + room.height][x].terrainFrameX = 0;
					_tiles[room.y + room.height][x].terrainFrameY = 0;
					_tiles[room.y + room.height][x].obj = WALL_GOLD;
					_tiles[room.y + room.height][x].objectFrameX = 0;
					_tiles[room.y + room.height][x].objectFrameY = 0;
				}
				else
				{
					_tiles[room.y + room.height][x].terrain = DIRT1;
					_tiles[room.y + room.height][x].terrainFrameX = 0;
					_tiles[room.y + room.height][x].terrainFrameY = 0;
					_tiles[room.y + room.height][x].obj = WALL_BASIC;
					_tiles[room.y + room.height][x].objectFrameX = 0;
					_tiles[room.y + room.height][x].objectFrameY = 0;
				}

				break;
			default:
				break;
			}
		}

		switch (dir)
		{
		case NORTH:
			_tiles[room.y + 3][room.x + 2].terrain = SHOP;
			_tiles[room.y + 3][room.x + 4].terrain = SHOP;
			break;
		case SOUTH:
			_tiles[room.y + 2][room.x + 2].terrain = SHOP;
			_tiles[room.y + 2][room.x + 4].terrain = SHOP;
			break;
		case WEST:
			_tiles[room.y + 3][room.x + 2].terrain = SHOP;
			_tiles[room.y + 3][room.x + 4].terrain = SHOP;
			break;
		case EAST:
			_tiles[room.y + 3][room.x + 1].terrain = SHOP;
			_tiles[room.y + 3][room.x + 3].terrain = SHOP;
			break;
		case DIRECTIONCOUNT:
			break;
		default:
			break;
		}
	}
	else
	{
		for (int y = room.y - 1; y < room.y + room.height + 1; ++y)
		{
			for (int x = room.x - 1; x < room.x + room.width + 1; ++x)
			{
				if (x == room.x - 1 || y == room.y - 1 || x == room.x + room.width || y == room.y + room.height)
				{
					_tiles[y][x].terrain = DIRT1;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = WALL_BASIC;
					_tiles[y][x].objectFrameX = 0;
					_tiles[y][x].objectFrameY = 0;
				}
				else
				{
					_tiles[y][x].terrain = DIRT1;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = obj;
					_tiles[y][x].objectFrameX = objectFrameX;
					_tiles[y][x].objectFrameY = objectFrameY;
				}
			}
		}
	}

	return true;
}

bool mapGenerator::createFeature(int index)
{
	for (int i = 0; i < 1000; ++i)
	{
		if (_exits.empty())
			break;
		int r;
		if (_isMakeRoom && _isHaveCorridor)
		{
			r = _exits.size() - 1;
		}
		else
		{
			r = RND->getInt(_exits.size());
		}
		int x, y;
		if (_exits[r].width - 1 == 0)
		{
			x = _exits[r].x;
		}
		else
		{
			x = RND->getFromIntTo(_exits[r].x, _exits[r].x + _exits[r].width - 1);
		}
		if (_exits[r].height - 1 == 0)
		{
			y = _exits[r].y;
		}
		else
		{
			y = RND->getFromIntTo(_exits[r].y, _exits[r].y + _exits[r].height - 1);
		}
		if (_isMakeRoom && _isHaveCorridor)
		{
			if (createFeature(x, y, _corridorDirection))
			{
				_exits.erase(_exits.begin() + r);
				return true;
			}
		}
		else
		{
			for (int j = 0; j < DIRECTIONCOUNT; ++j)
			{
				if (createFeature(x, y, static_cast<Direction>(j)))
				{
					_exits.erase(_exits.begin() + r);
					return true;
				}
			}
		}
	}

	return false;
}

bool mapGenerator::createFeature(int x, int y, Direction dir, int index)
{
	int dx = 0;
	int dy = 0;

	switch (dir)
	{
	case NORTH:
		dy = 1;
		break;
	case SOUTH:
		dy = -1;
		break;
	case WEST:
		dx = 1;
		break;
	case EAST:
		dx = -1;
		break;
	case DIRECTIONCOUNT:
		break;
	default:
		break;
	}

	if (getTile(x + dx, y + dy) != DIRT1)
		return false;

	if (_isMakeRoom)
	{
		if (makeRoom(x, y, dir))
		{
			_tiles[y][x].obj = WALL_DOOR;
			_tiles[y][x].objectFrameY = 2;
			if (dir == WEST || dir == EAST)
			{
				_tiles[y][x].objectFrameX = 5;
			}
			else
			{
				_tiles[y][x].objectFrameX = 4;
			}
			return true;
		}
	}
	else
	{

		if (makeCorridor(x, y, dir))
		{
			if (_isHaveCorridor)
			{
				if (getTile(x + dx, y + dy) == DIRT1)
				{
					_tiles[y][x].obj = OBJ_NONE;
					_tiles[y][x].objectFrameX = NULL;
					_tiles[y][x].objectFrameY = NULL;
				}
				else
				{
					_tiles[y][x].terrain = DIRT2;
					_tiles[y][x].terrainFrameX = 0;
					_tiles[y][x].terrainFrameY = 0;
					_tiles[y][x].obj = OBJ_NONE;
					_tiles[y][x].objectFrameX = NULL;
					_tiles[y][x].objectFrameY = NULL;
				}
				return true;
			}
			else return true;
		}

	}

	return false;
}

TERRAIN mapGenerator::getTile(int x, int y)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return EMPTY;
	return _tiles[y][x].terrain;
}

OBJECT mapGenerator::getObject(int x, int y)
{
	if (x < 0 || y < 0 || x >= _width || y >= _height)
		return OBJ_NONE;
	return _tiles[y][x].obj;
}

void mapGenerator::deleteEmptyTiles()
{
	//���� �׷��� ����ū x, y ���ϱ�
	int maxX = 0;
	int	maxY = 0;

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				if (i >= maxY) maxY = i;
				if (j >= maxX) maxX = j;
			}
		}
	}
	//maxX, maxY���� ū �� Ÿ�ϵ� ����
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = _tiles[i].size() - 1; j > maxX; j--)
		{
			_tiles[i].erase(_tiles[i].begin() + j);
		}
	}

	for (int i = _tiles.size() - 1; i > maxY; i--)
	{
		_tiles.erase(_tiles.begin() + i);
	}
}

void mapGenerator::moveMap()
{
	//���� ȭ���� 0,0 ��ó�� �ű�ϴ�
	int minX = _tiles[0].size();
	int	minY = _tiles.size();

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				if (i <= minY) minY = i;
				if (j <= minX) minX = j;
			}
		}
	}
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = minX; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				tagTile temp;
				temp = _tiles[i][j];
				_tiles[i][j] = _tiles[i][j - minX];
				_tiles[i][j - minX] = temp;

				RECT rc;
				rc = _tiles[i][j].rc;
				_tiles[i][j].rc = _tiles[i][j - minX].rc;
				_tiles[i][j - minX].rc = rc;
			}
		}
	}

	for (int i = minY; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain != EMPTY)
			{
				tagTile temp;
				temp = _tiles[i][j];
				_tiles[i][j] = _tiles[i - minY][j];
				_tiles[i - minY][j] = temp;

				RECT rc;
				rc = _tiles[i][j].rc;
				_tiles[i][j].rc = _tiles[i - minY][j].rc;
				_tiles[i - minY][j].rc = rc;
			}
		}
	}

	for (int i = 0; i < _rooms.size(); i++)
	{
		_rooms[i].x = _rooms[i].x - minX;
		_rooms[i].y = _rooms[i].y - minY;
	}

	for (int i = 0; i < _corridors.size(); i++)
	{
		_corridors[i].x = _corridors[i].x - minX;
		_corridors[i].y = _corridors[i].y - minY;
	}
}

void mapGenerator::setEndBlock()
{
	_endBlockIndex.clear();

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if ((_tiles[i][j - 1].obj != WALL_END && _tiles[i][j - 1].terrain == DIRT1) || (_tiles[i][j + 1].obj != WALL_END && _tiles[i][j + 1].terrain == DIRT1))
			{
				_endBlockIndex.emplace_back(POINT{ j, i });
			}
		}
	}

	for (int i = 1; i < _tiles.size() - 1; i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{

				if ((_tiles[i - 1][j].obj != WALL_END && _tiles[i - 1][j].terrain == DIRT1) || (_tiles[i + 1][j].obj != WALL_END && _tiles[i + 1][j].terrain == DIRT1))
				{
					_endBlockIndex.emplace_back(POINT{ j, i });
				}
			}
		}
	}

	for (int i = 0; i < _endBlockIndex.size(); i++)
	{
		if (_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain != EMPTY) continue;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain = DIRT1;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameY = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].obj = WALL_END;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameY = 3;
	}
}

void mapGenerator::setEndEdge()
{
	_endBlockIndex.clear();
	for (int i = 0; i < _tiles.size() - 1; i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i + 1][j].obj == WALL_END)
				{
					if (_tiles[i][j - 1].obj == WALL_END || _tiles[i][j + 1].obj == WALL_END)
					{
						_endBlockIndex.emplace_back(POINT{ j, i });
					}
				}
			}
		}
	}

	for (int i = 1; i < _tiles.size(); i++)
	{
		for (int j = 1; j < _tiles[i].size() - 1; j++)
		{
			if (_tiles[i][j].terrain == EMPTY)
			{
				if (_tiles[i - 1][j].obj == WALL_END)
				{
					if (_tiles[i][j - 1].obj == WALL_END || _tiles[i][j + 1].obj == WALL_END)
					{
						_endBlockIndex.emplace_back(POINT{ j, i });
					}
				}
			}
		}
	}

	for (int i = 0; i < _endBlockIndex.size(); i++)
	{
		if (_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain != EMPTY) continue;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrain = DIRT1;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].terrainFrameY = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].obj = WALL_END;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameX = 0;
		_tiles[_endBlockIndex[i].y][_endBlockIndex[i].x].objectFrameY = 3;
	}
}

void mapGenerator::setStone()
{
	int num = RND->getFromIntTo(20, 40);
	int count = 0;
	while (1)
	{
		if (count == num) break;
		int y = RND->getInt(_tiles.size());
		int x = RND->getInt(_tiles[y].size());
		if (_tiles[y][x].obj == WALL_BASIC)
		{
			_tiles[y][x].obj = WALL_STONE;
			_tiles[y][x].objectFrameX = 2;
			_tiles[y][x].objectFrameY = 0;
			count++;
		}
	}
}

void mapGenerator::setBossRoom()
{
	int start = 0;
	int bossRoom = 0;
	int max = 0;
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (_rooms[i].roomState == ROOM_START)
		{
			start = i;
		}
	}
	for (int i = 0; i < _rooms.size(); i++)
	{
		if (i == start) continue;
		if (_rooms[i].roomState != ROOM_SHOP)
		{
			float distance = getDistance(_tiles[_rooms[i].y][_rooms[i].x].rc.left, _tiles[_rooms[i].y][_rooms[i].x].rc.top, _tiles[_rooms[start].y][_rooms[start].x].rc.left, _tiles[_rooms[start].y][_rooms[start].x].rc.top);
			if (distance > max)
			{
				max = distance;
				bossRoom = i;
			}
		}
	}
	_rooms[bossRoom].roomState = ROOM_BOSS;

	int x = RND->getFromIntTo(_rooms[bossRoom].x, _rooms[bossRoom].x + _rooms[bossRoom].width - 1);
	int y = RND->getFromIntTo(_rooms[bossRoom].y, _rooms[bossRoom].y + _rooms[bossRoom].height - 1);
	_tiles[y][x].terrain = STAIR;
	_tiles[y][x].terrainFrameX = 0;
	_tiles[y][x].terrainFrameY = 0;
	_tiles[y][x].obj = OBJ_NONE;
	_tiles[y][x].objectFrameX = 0;
	_tiles[y][x].objectFrameY = 0;
}