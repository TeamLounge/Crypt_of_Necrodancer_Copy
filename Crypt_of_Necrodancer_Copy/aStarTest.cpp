#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init()
{

	setTile();


	return S_OK;
}

void aStarTest::release()
{

}

void aStarTest::update()
{
	endmove();
	if (KEYMANAGER->isOnceKeyDown('S')) _start = true;
	if (_start)
	{
		_count++;
		if (_count % 15 == 0)
		{
			pathFinder(_currentTile);
		
			_count = 0;
		}
	}
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}
}
//타일 셋팅 함수
void aStarTest::setTile()
{
	_startTile = new tile;
	_startTile->init(4, 12);
	_startTile->setAttribute("start");

	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");

	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j<TILENUMX; ++j)
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
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}

}
//갈수있는길추가함수
vector<tile*> aStarTest::addOpenList(tile * currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tile* node = _vTotalList[(startY*TILENUMX) + startX + j + (i*TILENUMX)];
			//예외처리
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//현재 타일 계속 갱신해준다.
			node->setParentNode(_currentTile);
			//주변타일 검출하면서 체크했는지 유무를 알수있게 임의의 불값을 준다
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin() ; _viOpenList != _vOpenList.end() ; ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			//현재 노드가 끝노드가아니면 색칠해준다
		if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			//이미 체크된애는 건너뛴다
			if (!addObj) continue;
			//갈수있는 길은 백터에 저장된다
			_vOpenList.push_back(node);
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


	if (tempTile->getAttribute() == "end")
	{
		//최단경로를 색칠해줘라
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}
		_start = false;
		return;
	}

	//최단경로
	//_vCloseList.push_back(tempTile);
	//
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
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		if (_vTotalList[i]->getAttribute() == "start")
		{
			RECT rc;
			tile* node = new tile;
			node->init(_startTile->getIdX(), _startTile->getIdY());
			_startTile->setIdX(_currentTile->getIdX());
			_startTile->setIdY(_currentTile->getIdY());
			_startTile->setCetner(PointMake(_currentTile->getIdX()* TILEWIDTH + (TILEWIDTH / 2),
				_currentTile->getIdY()*TILEHEIGHT + (TILEHEIGHT / 2)));
			rc = RectMakeCenter(_startTile->getCenter().x, _startTile->getCenter().y, TILEWIDTH, TILEHEIGHT);
			_startTile->setRect(rc);
			_vTotalList.erase(_vTotalList.begin() + i);
			_vTotalList.insert(_vTotalList.begin() + i, node);
			_vTotalList.erase(_vTotalList.begin() + (_currentTile->getIdY()*TILENUMX + _currentTile->getIdX()));
			_vTotalList.insert(_vTotalList.begin() + (_currentTile->getIdY()*TILENUMX + _currentTile->getIdX()), _startTile);
			break;
		}
	}
}

void aStarTest::endmove()
{
	RECT rc;
	tile* node;
	int nextIdx;
	int nextIdy;
	bool ismove = false;
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		nextIdx = _endTile->getIdX() + 1;
		nextIdy = _endTile->getIdY();
		ismove = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		nextIdx = _endTile->getIdX();
		nextIdy = _endTile->getIdY()-1;
		ismove = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		nextIdx = _endTile->getIdX()-1;
		nextIdy = _endTile->getIdY();
		ismove = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		nextIdx = _endTile->getIdX();
		nextIdy = _endTile->getIdY()+1;
		ismove = true;
	}
	if (ismove) {
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "end")
			{
				if (_vTotalList[(nextIdy*TILENUMX + nextIdx)]->getAttribute() == "start") break;
				node = new tile;
				node->init(_endTile->getIdX(), _endTile->getIdY());
				_endTile->setIdX(nextIdx);
				_endTile->setIdY(nextIdy);
				_endTile->setCetner(PointMake(nextIdx* TILEWIDTH + (TILEWIDTH / 2),
					nextIdy*TILEHEIGHT + (TILEHEIGHT / 2)));
				rc = RectMakeCenter(_endTile->getCenter().x, _endTile->getCenter().y, TILEWIDTH, TILEHEIGHT);
				_endTile->setRect(rc);
				_vTotalList.erase(_vTotalList.begin() + i);
				_vTotalList.insert(_vTotalList.begin() + i, node);
				_vTotalList.erase(_vTotalList.begin() + (nextIdy*TILENUMX + nextIdx));
				_vTotalList.insert(_vTotalList.begin() + (nextIdy*TILENUMX + nextIdx), _endTile);
				break;
			}
		}
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "none")
			{
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
