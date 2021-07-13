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
		if (_count % 10 == 0)
		{
			pathFinder(_currentTile);
		
			_count = 0;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if(PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(0, 0, 0));
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				_vTotalList[i]->setIsOpen(true);
				_vTotalList[i]->setAttribute("none");
				_vTotalList[i]->setColor(RGB(255, 255, 255));
			}
		}
	}
	
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
		char str[12];
		sprintf_s(str," %d",_vTotalList[i]->getparentNumber());
		TextOut(getMemDC(), _vTotalList[i]->getCenter().x - 10, _vTotalList[i]->getCenter().y - 10,str,strlen(str));
	}
}
//Ÿ�� ���� �Լ�
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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));
		
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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));
		
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
				if (node->getAttribute() == "start") continue;
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
				//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));
		
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
	else if (tempTile->getAttribute() == "end")
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
	//_vCloseList.push_back(tempTile);
	
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
		if (_vTotalList[i]->getAttribute() == "start")
		{
			
			_vOpenList.clear();
			RECT rc;
			tile* node = new tile;
			node->init(_startTile->getIdX(), _startTile->getIdY());
			//node->setIsOpen(false);
			_startTile->setIdX(_currentTile->getIdX());
			_startTile->setIdY(_currentTile->getIdY());
			_startTile->setCetner(PointMake(_currentTile->getIdX()* TILEWIDTH + (TILEWIDTH / 2),
				_currentTile->getIdY()*TILEHEIGHT + (TILEHEIGHT / 2)));
			rc = RectMakeCenter(_startTile->getCenter().x, _startTile->getCenter().y, TILEWIDTH, TILEHEIGHT);
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
				if (_vTotalList[(nextIdy*TILENUMX + nextIdx)]->getAttribute() == "wall")break;
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
