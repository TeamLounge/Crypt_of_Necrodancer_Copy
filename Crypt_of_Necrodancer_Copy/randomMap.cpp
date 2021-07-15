#include "stdafx.h"
#include "randomMap.h"
#include <list>
#include <random>
HRESULT randomMap::init()
{
	IMAGEMANAGER->addFrameImage("dirt1_tile", "image/object/tile/dirt1.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shop_tile", "image/object/tile/shop.bmp", 48, 48, 1, 1, true, RGB(255, 0, 255));
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
	_makeTile.clear();
	present = 0;
	isshop = false;
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
				//IMAGEMANAGER->frameRender("walls1", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
				//break;
			case WALL_GOLD:
			case WALL_STONE:
			case WALL_CRACK:
			case WALL_DOOR:
			case WALL_END:
				IMAGEMANAGER->frameRender("walls1", getMemDC(), _tiles[i][j].rc.left, _tiles[i][j].rc.top - (TILESIZE * 5) / 8, _tiles[i][j].objectFrameX, _tiles[i][j].objectFrameY);
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
			char str[128];
			sprintf_s(str,"%d",_tiles[i][j].obj);
			TextOut(getMemDC(), (_tiles[i][j].rc.right + _tiles[i][j].rc.left) / 2, (_tiles[i][j].rc.bottom + _tiles[i][j].rc.top) / 2,str,strlen(str));
		}
	}
	
	//for (int i = 0; i < _makeTile.size(); i++)
	//{
	//	sprintf_s(str, "lefttop : %d , present: %d , fromX: %d" , _makeTile[i].lefttop, _makeTile[i].present , _makeTile[i].left);
	//	TextOut(getMemDC(), _makeTile[i].left*TILESIZE-48, _makeTile[i].top*TILESIZE, str,strlen(str));
	//	sprintf_s(str, "righttop: %d, present: %d , toX : %d", _makeTile[i].righttop, _makeTile[i].present, _makeTile[i].right);
	//	TextOut(getMemDC(), _makeTile[i].right*TILESIZE-48, _makeTile[i].top*TILESIZE, str, strlen(str));
	//	sprintf_s(str, "leftbottom: %d, present: %d ,fromY: %d", _makeTile[i].leftbottom, _makeTile[i].present, _makeTile[i].top);
	//	TextOut(getMemDC(), _makeTile[i].left*TILESIZE + 48, _makeTile[i].bottom*TILESIZE, str, strlen(str));
	//	sprintf_s(str, "rightbottom: %d, present: %d, toY : %d", _makeTile[i].rightbottom, _makeTile[i].present, _makeTile[i].bottom);
	//	TextOut(getMemDC(), _makeTile[i].right*TILESIZE + 48, _makeTile[i].bottom*TILESIZE, str, strlen(str));
	//	sprintf_s(str, "present : %d", _makeTile[i].present);
	//	TextOut(getMemDC(), ((_makeTile[i].right + _makeTile[i].left) / 2)*TILESIZE , ((_makeTile[i].bottom + _makeTile[i].top) / 2 * TILESIZE), str,strlen(str));
	//}
}


void randomMap::generate()
{
	setTile();//일단모든타일을 바닥과 벽을칠해놓는다
	makeRooms(); // 방크기 정하고  정했다면 벽삭제해서 방을 만들어준다 
				// 사이즈가 7x7이라면 방크기는 5X5
	makePassage();//방과 방을 연결해준다
	removeUnusedWalls(); //연결하고 안쓰는 곳을 모든 벽,바닥을 삭제해준다
	makeTile();
	makewalls();
}

void randomMap::makeRooms()
{
	m_room.clear(); //방정보를 담을 백터 클리어
	
	int gridwidth = TILEX / gridX; // 전체 타일을  총 몇구역으로 나눌껀지
	int gridHeight = TILEY / gridY; // 전체 타일을 총 몇구역으로 나눌껀지

	for (int y = 0; y < gridY; ++y)
	{
		for (int x = 0; x < gridX; ++x)
		{
			ROOM room; //방정보 구조체
			int width = RND->getFromIntTo(roomWidthMin, gridwidth); // 최소 방크기에서 총제한구역으로 랜덤값생성
			int height = RND->getFromIntTo(roomHeightMin, gridHeight);

			if (!isshop && RND->getInt(gridX*gridY) == 0||(!isshop&&y==gridY-1&&x==gridX-1))//다생성하면 재미없으니까 조그만한 방도 만들어놓는다
			{
				width = 7;
				height = 9;
				isshop = true;
				room.shop = isshop;
			}

			int left = x * (gridwidth + 1) + RND->getInt(gridwidth - width); // 각방들의 첫x좌표 
			if (left == 0)left  += 1;
			int top = y * (gridHeight + 1) + RND->getInt(gridHeight - height);//각방들의 첫y좌표
			if (top == 0) top += 1;
			room.left = left; //값
			room.top = top; //다
			room.right = (left + width >=TILEX)? (TILEX) : left + width;//넣
			room.bottom = (top + height >= TILEY) ? (TILEY) : top + height;//어
			room.width = width;//이건 사실 없어도됌;;
			room.height = height; // 없어도됌;;

			if (x > 0)
				room.neighbors.emplace_back((x - 1) + y * gridX); // 근처에 방이 몇개있는지 체크하는 알고리즘
			if (x < gridX - 1)   
				room.neighbors.emplace_back((x + 1) + y * gridX); //구석이면1~2개 구석이아닐경우 2~3개
			if (y > 0)
				room.neighbors.emplace_back(x + (y - 1)*gridX);
			if (y < gridY - 1)
				room.neighbors.emplace_back(x + (y + 1)*gridX);
			placeRoom(room); // 실제로 방만들어주는 구간
			m_room.emplace_back(room); //방을 만들었으면 방정보담은 백터에 새롭게 추가해줍니다
	
		}
	}

}

void randomMap::makePassage()
{
	vector<size_t> unconnected; //연결이안된방을 체크해주는 백터 기본적으로 방생성을하면 다 연결이안되어있으니까 여기에 모든방을 넣는다
	vector<size_t> connected; //연결이 된방을 체크해주는 백터
	for (size_t i = 0; i < m_room.size(); ++i)
		unconnected.emplace_back(i); // 모든방을 일단 연결이안된방 백터에 넣는다

	//어떤연결안된방을 처음에 뽑을지 셔플로 결정
	shuffle(unconnected, unconnected.size());
	connected.emplace_back(unconnected.back());//그다음 맨마지막에 있는 무작위 방을 하나 뽑아서 넣는다. 

	unconnected.pop_back(); //그리고 연결안된방을 하나빼고
	 
	while (!unconnected.empty()) //모든방이 연결될때까지 돌려!
	{
		size_t i = connected[RND->getInt(connected.size())]; // 랜덤으로 연결된방하나 인덱스를 뽑고
		if (m_room[i].neighbors.empty())//예외처리를 해줍니다 인접한방이 없을 수 도있음
		{
			connected.erase(remove(connected.begin(), connected.end(), i), connected.end());
			continue;
		}
		size_t j= m_room[i].neighbors[RND->getInt(m_room[i].neighbors.size())];//그 연결하려는방 하나중 인접한거 하나를뽑아요

		connectRooms(i, j); // 그다음 연결해줍니다.
		unconnected.erase(remove(unconnected.begin(), unconnected.end(), j), unconnected.end());//연결이 끝나면 그 연결안된방을 안연결된백터에 지워주고
		connected.emplace_back(j);//그 방을 연결되었다고 표시해줍니다.
	}

}

void randomMap::removeUnusedWalls()
{
	for (int y = 0; y < TILEY; ++y)
	{
		for (int x = 0; x < TILEX; ++x)
		{
			int numWalls = 0; // 현재 탐색할 타일을 기준으로 주변에 쓰고있는 벽이있는지 탐색하기위한 변수

			for (int dy = -1; dy <= 1; ++dy)//
			{
				for (int dx = -1; dx <= 1; ++dx)//예를들어 0,0을기준으로 -1,-1부터 1,1까지 9번탐색합니다.
				{
					if (x + dx < 0 || y + dy < 0 || x + dx >= TILEX || y + dy >= TILEY)
						++numWalls; //주변이 맵밖을 나가는외곽이다 하면 ++
					else
					{
						const int tileNumber = _tiles[y + dy][x + dx].obj;
						const int tileshit = _tiles[y + dy][x + dx].terrain;
						if (tileNumber == WALL_BASIC || tileshit == EMPTY) //근처에 벽이나 텅 비어있는바닥이있으면 ++
							++numWalls;
					}
				}
			}
			if (numWalls == 9)//주변이 벽이거나 텅빈바닥이있는 쓸모없는타일이야! 하면 그곳을 텅 비워줍니다.
			{
				_tiles[y][x].obj = OBJ_NONE;
				_tiles[y][x].terrain = EMPTY;
			}
		}
	}
}

void randomMap::makeTile()
{
	int fromX;
	int fromY;
	int toX;
	int toY;
	int centerX;
	int centery;
	int lefttop;
	int righttop;
	int leftbottom;
	int rightbottom;
	bool targetX = false;
	bool targetY = false;
	for (int i = 0; i < m_room.size(); i++)
	{
		int count;
		if (i < 3) count = 1;
		if (i >= 3 && i<6) count =2;

		if (m_room[i].rightRoom && m_room[i].bottomRoom)
		{
			lefttop = i;
			for (int j = i + 1; j < count*gridX; j++)
			{
				if (m_room[j].leftRoom &&m_room[j].bottomRoom)
				{
					righttop = j;
					targetX = true;
					break;
				}
			}
			for (int j = i + gridX; j < gridX * 2; j += gridX)
			{
				if (m_room[j].rightRoom&& m_room[j].topRoom)
				{

					leftbottom = j;
					rightbottom = j + 1;
					targetY = true;
					break;
				}
			}
		}
		if (targetX && targetY)
		{
			fromY = (m_room[lefttop].rightY >= m_room[righttop].leftY) ? m_room[lefttop].rightY : m_room[righttop].leftY;
			fromX = (m_room[lefttop].bottomX >= m_room[leftbottom].topX) ? m_room[lefttop].bottomX : m_room[leftbottom].topX;
			toY = (m_room[leftbottom].rightY >= m_room[rightbottom].leftY) ? m_room[leftbottom].rightY : m_room[rightbottom].leftY;
			toX = (m_room[righttop].bottomX >= m_room[rightbottom].topX) ? m_room[rightbottom].topX : m_room[righttop].bottomX;
			for (int y = fromY; y <= toY; ++y)
			{
				for (int x = fromX; x <= toX; ++x)
				{
					_tiles[y][x].terrain = DIRT1;
				}
			}

			targetX = false;
			targetY = false;
			floor _floor;
			_floor.top = fromY;
			_floor.bottom = toY;
			_floor.left = fromX;
			_floor.right = toX;

			_floor.lefttop = lefttop;
			_floor.righttop = righttop;
			_floor.leftbottom = leftbottom;
			_floor.rightbottom = rightbottom;
			present += 1;
			_floor.present = present;
			_makeTile.push_back(_floor);
		}
	}



}

void randomMap::makewalls()
{
	for (int y = 0; y < TILEY; ++y)
	{
		for (int x = 0; x < TILEX; ++x)
		{
			bool numWalls = false; // 현재 탐색할 타일을 기준으로 주변에 쓰고있는 벽이있는지 탐색하기위한 변수

			for (int dy = -1; dy <= 1; ++dy)//
			{
				for (int dx = -1; dx <= 1; ++dx)//예를들어 0,0을기준으로 -1,-1부터 1,1까지 9번탐색합니다.
				{
					if (x + dx < 0 || y + dy < 0 || x + dx >= TILEX || y + dy >= TILEY)
						continue; //주변이 맵밖을 나가는외곽이다 하면 ++
					else
					{
						const int tileNumber = _tiles[y + dy][x + dx].obj;
						const int tileshit = _tiles[y + dy][x + dx].terrain;
						if (tileNumber == WALL_BASIC ||tileNumber==WALL_GOLD) //근처에 벽이나 텅 비어있는바닥이있으면 ++
							numWalls=true;
					}
				}
			}
			if (numWalls == true &&_tiles[y][x].terrain ==EMPTY)//주변이 벽이거나 텅빈바닥이있는 쓸모없는타일이야! 하면 그곳을 텅 비워줍니다.
			{
				_tiles[y][x].obj = WALL_END;
				_tiles[y][x].objectFrameY = 8;
				_tiles[y][x].terrain = EMPTY;
			}
		}
	}

	int fromX;
	int fromY;
	for (int i = 0; i < m_room.size(); ++i)
	{
		if (m_room[i].shop)
		{
			if (m_room[i].bottomRoom)
			{
				fromX = m_room[i].bottomX;
				fromY = m_room[i].bottomY + 1;
			}
			else if (!m_room[i].bottomRoom && m_room[i].rightRoom)
			{
				fromX = m_room[i].rightX + 1;
				fromY = m_room[i].rightY;
			}
			else if (!m_room[i].bottomRoom && !m_room[i].rightRoom && m_room[i].leftRoom)
			{
				fromX = m_room[i].leftX - 1;
				fromY = m_room[i].leftY;
			}

			for (int x = m_room[i].left; x < m_room[i].right; ++x)
			{
				if (_tiles[m_room[i].top][x].obj == OBJ_NONE)
				{
					_tiles[m_room[i].top][x].obj = WALL_GOLD;
				}
			}
			for (int y = m_room[i].top; y < m_room[i].bottom; ++y)
			{
				if (_tiles[y][y].obj == OBJ_NONE)
				{
					_tiles[y][y].obj = WALL_GOLD;
				}
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
			_tiles[y][x].obj = OBJ_NONE; // 벽삭제하고 방만들어줌
		}
	}
	if (room.shop)
	{
		for (int y = room.top; y < room.bottom; ++y)
		{
			for (int x = room.left ; x <room.right; ++x)
			{
				if (_tiles[y][x].obj == WALL_BASIC)
				{
					_tiles[y][x].obj = WALL_GOLD;
					_tiles[y][x].objectFrameY = 5;
				}
				if (y == room.top + 2 && (x == room.left + 2 || x == room.left + 4))
				{
					_tiles[y][x].terrain = SHOP;
				}
			}
		}
		//_tiles[room.top + 2][room.left + 2].terrain =SHOP;
		//_tiles[room.top + 2][room.left + 4].terrain = SHOP;
	}
}

void randomMap::connectRooms(size_t i, size_t j)
{
	if (j < i) // i는 연결출발점 j는 연결도착점이니까 출발점이 도착점보다 크다면
		swap(i, j); // 바꿔줍시다

	ROOM& from = m_room[i]; //출발할 방
	ROOM& to = m_room[j]; // 도착할방

	if (j - i == 1) //Horizontal passage 옆으로 이동
	{
		const int fromX = from.right - 1; // 오른쪽으로 출발하기때문에 
										 //출발할방의 바로 오른쪽 벽 한칸 뒤 x좌표가 시작점.
		const int fromY =  RND->getFromIntTo(from.top+1 , from.bottom -2); // 그 시작점의 y좌표는 랜덤으로 갖는다. 

		const int toX = to.left+1; // 도착할곳이 왼쪽으로 오기때문에 
									//도착할방의 바로 벽한칸 앞쪽 x좌표가 도착점.
		const int toY = RND->getFromIntTo(to.top+1 , to.bottom-2); //1자로 생기면 재미없으니까 여기도 랜덤하게 y좌표를 뽑는다.

	
		const int centerX = RND->getFromIntTo(fromX +1, toX -1); //서로다른Y좌표로 이동할 중점X좌표을 구함
		const int dy = toY > fromY ? 1 : -1; //그리고 도착점이 시작점보다 y좌표가 크면 +1씩 해줘야되고,
											//도착점이 시작점보다 y좌표가 작으면 -1씩해주어서 도착점에 y좌표를 맞춰야한다.

		for (int x = fromX; x < centerX; ++x) //출발점에서 y좌표를 바꿔야할 중점X좌표까지 오른쪽으로 이동 
		{
			for(int y = fromY; y <=fromY+1; ++y)
				//_tiles[fromY][x].obj = OBJ_NONE;
				_tiles[y][x].obj = OBJ_NONE;
		}
		for (int y = fromY; y != toY; y += dy) // 만약에 출발점과 도착점의 Y좌표가 같다면 무시 
		{										//아니라면 도착점에 맞춰 +1,-1씩해서 길을 만든다
			for(int x = centerX; x<=centerX+1; ++x)
				//_tiles[y][centerX].obj = OBJ_NONE; 
				_tiles[y][x].obj = OBJ_NONE; 
		}
		for (int x = centerX; x <= toX; ++x) // 중점X좌표를 경유했다면 이제 도착점까지 오른쪽으로이동
		{	
			for(int y = toY; y<=toY+1 ; ++y)
				//_tiles[toY][x].obj = OBJ_NONE;
				_tiles[y][x].obj = OBJ_NONE;
		}
		from.rightRoom = true;
		to.leftRoom = true;
		from.rightX = fromX;
		from.rightY = fromY;
		to.leftX = toX;
		to.leftY = toY;

	}
	else // Vertical passage //위아래로이동
	{
		const int fromX = RND->getFromIntTo(from.left +1 , from.right-2 ); //랜덤으로 출발점의 X좌표를 뽑는다. 
		const int fromY = from.bottom - 1; //아래쪽으로 이동하기때문에 출발방의 밑벽 한칸앞이 출발Y좌표.

		const int toX = RND->getFromIntTo(to.left +1, to.right -2); // 도착점도 마찬가지로 1직선으로 오면 재미없으니까 랜덤으로 X좌표 뽑아줌
		const int toY = to.top+1; //위쪽으로 출발점이 오기때문에 도착방 윗벽의 한칸 밑이 도착 Y좌표 


		const int centerY = RND->getFromIntTo(fromY+1, toY -1); // 마찬가지로 X좌표를 바꿔야할 경유Y좌표를 구한다.
		const int dx = toX > fromX ? 1 : -1; // 도착점 X좌표가 출발점 X좌표보다 크다면 +1, 아니면 -1이다.
		for (int y = fromY; y < centerY; ++y) //출발점에서 X좌표를 바꿔야할 중점Y좌표까지 아래로 이동 
		{
			for(int x= fromX; x<=fromX+1; ++x)
				//_tiles[y][fromX].obj = OBJ_NONE;
				_tiles[y][x].obj = OBJ_NONE;
		}
		for (int x = fromX; x != toX; x += dx)// 만약에 출발점과 도착점의 X좌표가 같다면 무시
		{									  //아니라면 도착점에 맞춰 +1,-1씩해서 길을 만든다
			for (int y = centerY; y <= centerY+1 ; ++y)
				//_tiles[centerY][x].obj = OBJ_NONE;
				_tiles[y][x].obj = OBJ_NONE;
		}
		for (int y = centerY; y <= toY; ++y)// 중점Y좌표를 경유했다면 이제 도착점까지 아래로이동
		{
			for(int x = toX; x<=toX+1; ++x)
			//_tiles[y][toX].obj = OBJ_NONE;
				_tiles[y][x].obj = OBJ_NONE;
		}
		from.bottomRoom = true;
		to.topRoom = true;
		from.bottomX = fromX;
		from.bottomY = fromY;
		to.topX = toX;
		to.topY = toY;
	}

	from.neighbors.erase(remove(from.neighbors.begin(), from.neighbors.end(), j), from.neighbors.end()); // 연결이 다됬다면 인접했던 각자방번호를 삭제해줍니다
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

