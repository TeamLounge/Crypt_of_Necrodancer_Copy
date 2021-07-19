#include "stdafx.h"
#include "aStarTest.h"
#include "randomMap.h"

aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{

}

HRESULT aStarTest::init(int enemyX, int enemyY, int playerX, int playerY)
{
	_count = 0;
	setTile(enemyX, enemyY,  playerX, playerY);


	return S_OK;
}

void aStarTest::release()
{

}

void aStarTest::update()
{
	_count++;
	if (_count % 5 == 0)
	{
		pathFinder(_currentTile);
		_count = 0;
	}
}

void aStarTest::render()
{
	for (int i = 0; i < _vOpenList.size(); ++i)
	{
		Rectangle(getMemDC(), _map->getTiles()[_vOpenList[i]->getIdX()][_vOpenList[i]->getIdY()].rc);
	}
}
//Ÿ�� ���� �Լ�
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

	for (int i = 0; i <TILENUMY; ++i)
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
			node->setLinkRandomMap(_map);
			node->init(j, i);
			if (_map->getTileObject(j,i) != OBJ_NONE)
			{
				node->setAttribute("wall");
			}
			if (_map->getTileTerrain(j, i) == EMPTY)
			{
				node->setAttribute("wall");
			}
			_vTotalList.push_back(node);
		}
	}

}
//�����ִ±��߰��Լ�
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
				tile* node = _vTotalList[(startY*TILENUMX) + startX + (i*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}


				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 1)
			{

				tile* node = _vTotalList[(startY*TILENUMX) + startX + i + (i*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);

				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}


				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				//if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);

			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*TILENUMX) + startX - 1 + ((i - 2)*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);

				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;

				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}

				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));

				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
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
				tile* node = _vTotalList[(startY*TILENUMX) + startX + (i*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				//node->setparentNumber(_currentTile->getparentNumber() + 1);
				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
		
				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				//if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);
		
			}
			if (i == 1)
			{
			
				tile* node = _vTotalList[(startY*TILENUMX) + startX + i + (i*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				node->setparentNumber(_currentTile->getparentNumber() + 1);
		
				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
		
				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				//if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);
		
			}
			if (i == 3)
			{
				tile* node = _vTotalList[(startY*TILENUMX) + startX-1 + ((i-2)*TILENUMX)];
				//����ó��
				if (!node->getIsOpen()) continue;
				if (node->getAttribute() == "enemy") continue;
				if (node->getAttribute() == "wall") continue;
				//���� Ÿ�� ��� �������ش�.
				node->setParentNode(_currentTile);
				node->setparentNumber(_currentTile->getparentNumber() + 1);
		
				//�ֺ�Ÿ�� �����ϸ鼭 üũ�ߴ��� ������ �˼��ְ� ������ �Ұ��� �ش�
				bool addObj = true;
		
				for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
				{
					if (*_viOpenList == node)
					{
						addObj = false;
						break;
					}
				}
		
				//���� ��尡 ����尡�ƴϸ� ��ĥ���ش�
				if (node->getAttribute() != "player") node->setColor(RGB(128, 64, 28));
		
				//�̹� üũ�Ⱦִ� �ǳʶڴ�
				if (!addObj) continue;
				//�����ִ� ���� ���Ϳ� ����ȴ�
				_vOpenList.push_back(node);
			}
		
		}
	}
	return _vOpenList;
}
//�� ã�� �Լ�
void aStarTest::pathFinder(tile * currentTile)
{
	//�񱳿� ������κ�뼳��
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	//���¸���Ʈ ���;ȿ���, ���������θ� �̾Ƴ���
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		//H������ (������������ ����������)
		_vOpenList[i]->setCostToGoal(
			(abs(_endTile->getIdX() - _vOpenList[i]->getIdX()) + abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//���� start���� Ÿ������
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		//���¸���Ʈ�� �ش� Ÿ������
		POINT center2 = _vOpenList[i]->getCenter();

		//G������ (ó���������� ������������)
		_vOpenList[i]->setCostFromStart(getDistance(center1.x, center1.y, center2.x, center2.y));

		//F = G + H �Ѱ����ϱ�
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getFromCost() + _vOpenList[i]->getToGoal());
		//�׷��� �̾Ƴ� �� ��� ������ ������ ��κ��� �����Ͽ� ���� �������� ��� �̾Ƴ���.
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			//�� ����Ÿ�ϰ��� �ִ´�
			tempTile = _vOpenList[i];
		}

		//�������ΰ� üũ��
		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			//�̹� �������̶�� ������ٸ�?
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		//��Ȯ�ξ��Ϸ��� Openfalse
		_vOpenList[i]->setIsOpen(false);
		//�ߺ�üũ���ƴ϶��
		if (!addObj) continue;
		//�ߺ��̾ȉ�ٸ� ���� �־��ش�
		_vOpenList.push_back(tempTile);
	}


	if (tempTile == nullptr)
	{ 
		return;
	}
	else if (tempTile->getAttribute() == "enemy")
	{
		//�ִܰ�θ� ��ĥ�����
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}
		//_start = false;
		return;
	}


	//�ִܰ��
	_vCloseList.push_back(tempTile);
	
	//�ִܰ�θ� �־�J����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//�� ���¸���Ʈ���� �������ݽô�
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;
	_currentTile->setColor(RGB(255, 0, 0));
	//pathFinder(_currentTile);
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		if (_vTotalList[i]->getAttribute() == "enemy")
		{
			_vOpenList.clear();
			RECT rc;
			tile* node = new tile;
			node->setLinkRandomMap(_map);
			node->init(_startTile->getIdX(), _startTile->getIdY());
			//node->setIsOpen(false);
			_startTile->setIdX(_currentTile->getIdX());
			_startTile->setIdY(_currentTile->getIdY());
			rc = _map->getRect(_startTile->getIdX(),_startTile->getIdY());
			_startTile->setCetner(PointMake((rc.left + rc.right) / 2, (rc.bottom + rc.top) / 2));
			_startTile->setRect(rc);
			//swap(_startTile, _vTotalList[_currentTile->getIdY()*TILEWIDTH + _currentTile->getIdX()]);
			_vTotalList.erase(_vTotalList.begin() + i);
			_vTotalList.insert(_vTotalList.begin() + i, node);
			_vTotalList.erase(_vTotalList.begin() + (_currentTile->getIdY()*TILENUMX + _currentTile->getIdX()));
			_vTotalList.insert(_vTotalList.begin() + (_currentTile->getIdY()*TILENUMX + _currentTile->getIdX()), _startTile);
			break;
		}
	}
}	

void aStarTest::endmove(int playerIndexX, int playerIndexY)
{
	RECT rc;
	tile* node;
	bool ismove = false;
	if (_endTile->getIdX() != playerIndexX || _endTile->getIdY() != playerIndexY)
	{
		ismove = true;
	}
	//if (direction == RIGHT)
	//{
	//	nextIdx = _endTile->getIdX() + 1;
	//	nextIdy = _endTile->getIdY();
	//	ismove = true;
	//}
	//if (direction == UP)
	//{
	//	nextIdx = _endTile->getIdX();
	//	nextIdy = _endTile->getIdY()-1;
	//	ismove = true;
	//}
	//if (direction == LEFT)
	//{
	//	nextIdx = _endTile->getIdX()-1;
	//	nextIdy = _endTile->getIdY();
	//	ismove = true;
	//}
	//if (direction == DOWN)
	//{
	//	nextIdx = _endTile->getIdX();
	//	nextIdy = _endTile->getIdY()+1;
	//	ismove = true;
	//}
	if (ismove) {
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "player")
			{
				if (_vTotalList[(playerIndexY*TILENUMX + playerIndexX)]->getAttribute() == "enemy") break;
				if (_vTotalList[(playerIndexY*TILENUMX + playerIndexX)]->getAttribute() == "wall")break;
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
				_vTotalList.erase(_vTotalList.begin() + (playerIndexY*TILENUMX + playerIndexX));
				_vTotalList.insert(_vTotalList.begin() + (playerIndexY*TILENUMX + playerIndexX), _endTile);
				break;
			}
		}
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "none")
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
