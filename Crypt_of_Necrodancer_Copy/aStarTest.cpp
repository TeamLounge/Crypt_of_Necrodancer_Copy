#include "stdafx.h"
#include "aStarTest.h"
#include "mapGenerator.h"

aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init(int enemyX, int enemyY, int playerX, int playerY , bool miniboss)
{
	_count = _damagecount=0;
	_start = false;
	damage = false;
	isMiniboss = miniboss;
	_TotaltileX = _map->getXSize();
	_TotaltileY = _map->getYSize();
	setTile(enemyX, enemyY,  playerX, playerY);
	time = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void aStarTest::release()
{

}

void aStarTest::update()
{
	
	if (ismove)
	{
		pathFinder(_startTile);
	}
	
	//if (_start)
	//{
	//	if (istime)
	//		start();
	//}
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}
	if (damage)
	{
		char str[128];
		sprintf_s(str, "hp깍임");
		TextOut(getMemDC(), _map->getRect(_endTile->getIdX(), _endTile->getIdY()).left, _map->getRect(_endTile->getIdX(), _endTile->getIdY()).top, str, strlen(str));
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			damage = false;
		}
	}
}
//타일 셋팅 함수
void aStarTest::setTile(int enemyX, int enemyY, int playerX, int playerY)
{
	_startTile = new tile;
	_startTile->setLinkRandomMap(_map);
	_startTile->init(enemyX, enemyY);
	_startTile->setAttribute("enemy");

	_endTile = new tile;
	_endTile->setLinkRandomMap(_map);
	_endTile->init(playerX, playerY);
	_endTile->setAttribute("player");

	_currentTile = _startTile;

	for (int i = 0; i < _TotaltileY; ++i)
	{
		for (int j = 0; j< _TotaltileX; ++j)
		{
	
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 0));
				_vTotalList.push_back(_startTile);
				continue;
			}
			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(255, 0, 255));
				_vTotalList.push_back(_endTile);
				continue;
			}
			tile* node = new tile;
			node->setLinkRandomMap(_map);
			node->init(j, i);
			if (isMiniboss) {
				if (_map->getTileObject(j, i) == WALL_END || _map->getTileObject(j, i) == WALL_GOLD)
				{
					node->setAttribute("wall");
				}
			}
			else
			{
				if (_map->getTileObject(j, i) == WALL_END || _map->getTileObject(j, i) == WALL_BASIC || _map->getTileObject(j, i) == WALL_CRACK || _map->getTileObject(j, i) == WALL_STONE || _map->getTileObject(j, i) == WALL_GOLD)
				{
					node->setAttribute("wall");
				}
			}
			if (_map->getTileTerrain(j, i) == EMPTY)
			{
				node->setAttribute("wall");
			}
			_vTotalList.push_back(node);
		}
	}

}
//갈수있는길추가함수
vector<tile*> aStarTest::addOpenList(tile * currentTile)
{
	
	int startX = currentTile->getIdX();
	int startY = currentTile->getIdY()-1;
	
	if (startY < _endTile->getIdY())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (i == 0 || i == 2)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX + (i*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}


				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);

			}
			if (i == 1)
			{

				tile* node = _vTotalList[(startY*_TotaltileX) + startX + i + (i*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);

				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}


				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);

			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX - 1 + ((i - 2)*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);

				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}

				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);
			}

		}
	}
	else
	{
		for (int i = 3; i >= 0; --i)
		{
			if (i == 0 || i == 2)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX + (i*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
		
				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);
		
			}
			if (i == 1)
			{
			
				tile* node = _vTotalList[(startY*_TotaltileX) + startX + i + (i*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
		
				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
		
				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);
		
			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*_TotaltileX) + startX-1 + ((i-2)*_TotaltileX)];
				//예외처리
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//현재 타일 계속 갱신해준다.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
		
				//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
				//현재 노드가 끝노드가아니면 색칠해준다
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//이미 체크된애는 건너뛴다
				if (!addObj) continue;
				//갈수있는 길은 백터에 저장된다
				_vOpenList.push_back(node);
			}
		
		}
	}
	return _vOpenList;
}
//길 찾는 함수
void aStarTest::pathFinder(tile * currentTile)
{
	//비교용 최종경로비용설정
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	//오픈리스트 백터안에서, 가장빠른경로를 뽑아낸다
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H값연산 (현재지점에서 끝지점까지)
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) + abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//현재 start기준 타일중점
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//오픈리스트의 해당 타일중점
		POINT center2 = _vOpenList[i]->getCenter();

		//G값연산 (처음지점에서 현재지점까지)
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y));

		//F = G + H 총값더하기
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getFromCost() + _vOpenList[i]->getToGoal());
		//그렇게 뽑아낸 총 경로 비용들을 임의의 경로비용과 연산하여 가장 작은값을 계속 뽑아낸다.
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			//그 작은타일값을 넣는다
			tempTile = _vOpenList[i];
		}

		//같은값인거 체크용
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			//이미 빠른길이라고 지정됬다면?
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		//재확인안하려고 Openfalse
		_vOpenList[i]->setIsOpen(false);
		//중복체크가아니라면
		if (!addObj) continue;
		//중복이안됬다면 새로 넣어준다
		_vOpenList.push_back(tempTile);
	}


	if (tempTile == nullptr)
	{ 
		return;
	}
	else if (tempTile->getAttribute() == "player")
	{
		//최단경로를 색칠해줘라
		while (_currentTile->getParentNode() != NULL)
		{
			_vCloseList.emplace_back(_currentTile);
			_vOpenList.clear();
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
			_start = true;
		}
		return;
	}

	//최단경로를 넣어놧으면
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//그 오픈리스트에서 삭제해줍시다
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
	pathFinder(_currentTile);
	
}	

void aStarTest::endmove(int playerIndexX, int playerIndexY)
{
	RECT rc;
	tile* node;
	if (_endTile->getIdX() != playerIndexX || _endTile->getIdY() != playerIndexY)
	{
		ismove = true;
	}
	if (ismove) {
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "player")
			{
				if (_vTotalList[(playerIndexY*_TotaltileX + playerIndexX)]->getAttribute() == "enemy") break;
				node = new tile;
				node->setLinkRandomMap(_map);
				node->init(_endTile->getIdX(), _endTile->getIdY());
				_endTile->setIdX(playerIndexX);
				_endTile->setIdY(playerIndexY);

				rc = _map->getRect(_endTile->getIdX(), _endTile->getIdY());
				_endTile->setRect(rc);
				_endTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
				_vTotalList.erase(_vTotalList.begin() + i);
				_vTotalList.insert(_vTotalList.begin() + i, node);
				_vTotalList.erase(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX));
				_vTotalList.insert(_vTotalList.begin() + (playerIndexY*_TotaltileX + playerIndexX), _endTile);
				break;
			}
		}
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (!(_vTotalList[i]->getAttribute() == "player" || _vTotalList[i]->getAttribute() == "enemy"))
			{
				_vTotalList[i]->setParentNode(nullptr);
				_vTotalList[i]->setCostFromStart(0);
				_vTotalList[i]->setCostToGoal(0);
				_vTotalList[i]->setTotalCost(0);
				_vTotalList[i]->setColor(RGB(255, 255, 255));
				_vTotalList[i]->setIsOpen(true);
			}
		}
		_vCloseList.clear();
		_vOpenList.clear();
		_endTile->setIsOpen(true);
		_currentTile = _startTile;
	}
}

void aStarTest::start()
{
	
	if (_vCloseList.size() != 0) {
		if (!(_map->getTileObject(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY()) == WALL_BASIC ||
			_map->getTileObject(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY()) == WALL_GOLD ||
			_map->getTileObject(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY()) == WALL_STONE ||
			_map->getTileObject(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY()) == WALL_DOOR))
		{
			move(_vCloseList.back()->getIdX(), _vCloseList.back()->getIdY());
			if (_vCloseList.size() >= 1)
			{
				_damagecount = 0;
				_vCloseList.erase(_vCloseList.end() - 1);
			}
			if (_vCloseList.size() == 0)
			{
				if (_startTile->getIdX() == _endTile->getIdX())
				{
					if (_endTile->getIdY() == _startTile->getIdY() + 1)
					{
						//hp달게할꺼양
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = DOWN;
						}
					}
					else if (_endTile->getIdY() == _startTile->getIdY() - 1)
					{
						//hp달게할꺼양
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = UP;
						}
					}
				}
				else if (_startTile->getIdY() == _endTile->getIdY() && (_startTile->getIdX() + 1 || _startTile->getIdX() - 1))
				{
					if (_endTile->getIdX() == _startTile->getIdX() + 1)
					{
						//hp달게할꺼양
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = RIGHT;
						}
					}
					else if (_endTile->getIdX() == _startTile->getIdX() - 1)
					{
						//hp달게할꺼양
						_damagecount++;
						if (_damagecount > 1)
						{
							damage = true;
							_dir = LEFT;
						}
					}
				}
			}
		}
	}
	else if (_vCloseList.size() == 0)
	{
		if ((_startTile->getIdX() == _endTile->getIdX() && (_startTile->getIdY() + 1 || _startTile->getIdY() - 1)) ||
			(_startTile->getIdY() == _endTile->getIdY() && (_startTile->getIdX() + 1 || _startTile->getIdX() - 1)))
		{
			//hp달게할꺼양
			damage = true;
			if (_startTile->getIdX() == _endTile->getIdX())
			{
				if (_endTile->getIdY() == _startTile->getIdY() + 1)
				{
			
					_dir = DOWN;
				}
				else if (_endTile->getIdY() == _startTile->getIdY() - 1)
				{
			
					_dir = UP;
				}
			}
			else if (_startTile->getIdY() == _endTile->getIdY() && (_startTile->getIdX() + 1 || _startTile->getIdX() - 1))
			{
				if (_endTile->getIdX() == _startTile->getIdX() + 1)
				{
					_dir = RIGHT;
	
				}
				else if (_endTile->getIdX() == _startTile->getIdX() - 1)
				{
					_dir = LEFT;
			
				}
			}
		}
	}
	
}

void aStarTest::move(int X, int Y)
{
	RECT rc;
	tile* node = new tile;
	node->setLinkRandomMap(_map);
	node->init(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setIdX(X);
	_startTile->setIdY(Y);
	rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	_startTile->setRect(rc);
	_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
	if (_vCloseList.size() >= 1)
	{
		_damagecount = 0;
		_vCloseList.erase(_vCloseList.end() - 1);
	}
	if (_vCloseList.size() == 0)
	{
		if (_startTile->getIdX() == _endTile->getIdX())
		{
			if (_endTile->getIdY() == _startTile->getIdY() + 1)
			{
				//hp달게할꺼양
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = DOWN;
				}
			}
			else if (_endTile->getIdY() == _startTile->getIdY() - 1)
			{
				//hp달게할꺼양
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = UP;
				}
			}
		}
		else if (_startTile->getIdY() == _endTile->getIdY() && (_startTile->getIdX() + 1 || _startTile->getIdX() - 1))
		{
			if (_endTile->getIdX() == _startTile->getIdX() + 1)
			{
				//hp달게할꺼양
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = RIGHT;
				}
			}
			else if (_endTile->getIdX() == _startTile->getIdX() - 1)
			{
				//hp달게할꺼양
				_damagecount++;
				if (_damagecount > 1)
				{
					damage = true;
					_dir = LEFT;
				}
			}
		}
	}
}

void aStarTest::actionMove(int X, int Y)
{
	RECT rc;
	tile* node = new tile;
	node->setLinkRandomMap(_map);
	node->init(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setIdX(X);
	_startTile->setIdY(Y);
	rc = _map->getRect(_startTile->getIdX(), _startTile->getIdY());
	_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
	_startTile->setRect(rc);
	_vTotalList.erase(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()));
	_vTotalList.insert(_vTotalList.begin() + (node->getIdY()*_TotaltileX + node->getIdX()), node);
	_vTotalList.erase(_vTotalList.begin() + (Y*_TotaltileX + X));
	_vTotalList.insert(_vTotalList.begin() + (Y*_TotaltileX + X), _startTile);
}

void aStarTest::callPathFinder()
{
	_vCloseList.clear();
	_vOpenList.clear();
	pathFinder(_startTile);
}

void aStarTest::enemyAttack()
{
	if (_startTile->getIdX() == _endTile->getIdX())
	{
		if (_endTile->getIdY() == _startTile->getIdY() + 1)
		{
			//hp달게할꺼양
			damage = true;
			_dir = DOWN;
		
		}
		else if (_endTile->getIdY() == _startTile->getIdY() - 1)
		{
			//hp달게할꺼양
			damage = true;
			_dir = UP;

		}
	}
	else if (_startTile->getIdY() == _endTile->getIdY())
	{
		if (_endTile->getIdX() == _startTile->getIdX() + 1)
		{
			//hp달게할꺼양
			damage = true;
			_dir = RIGHT;

		}
		else if (_endTile->getIdX() == _startTile->getIdX() - 1)
		{
			//hp달게할꺼양
			damage = true;
			_dir = LEFT;
			
		}
	}
}
