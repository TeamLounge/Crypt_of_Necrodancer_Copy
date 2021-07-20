#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY)
{
	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	skeleton::init();
	_astar = new aStarTest;
	_img = IMAGEMANAGER->findImage("whiteSkeleton");

	while (true) //������ġ
	{
		//int random = RND->getInt(2);
		//switch (random)
		//{
		//case 0:
		int random = RND->getInt(_map->getRoom().size());//�����濡 ��ġ
		if(_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// �� ���� �÷��̾���̰ų� �����̸� ��Ƽ��  
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y)!= OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue; //�����ϰ� ���� ����� ��ǥ �� �����־ ��Ƽ��
		break;//// ��� ��Ƽ�� �������� ����ٸ� ����������
		//case 1:
		//	random = RND->getInt(_map->getFloor().size());//���� ���̾ƴ� ����Ǿ ���� ���ʿ��� ����
		//	_x = RND->getFromIntTo(_map->getFloor()[random].left, _map->getFloor()[random].right);
		//	_y = RND->getFromIntTo(_map->getFloor()[random].top, _map->getFloor()[random].bottom);
		//	if (_map->getTiles()[_y][_x].obj != OBJ_NONE || _map->getTiles()[_y][_x].terrain != DIRT1)
		//		continue; //�����ϰ� ���� ����� ��ǥ �� �����־ ��Ƽ��

		//	bool pass = true; //����� �÷��̾��,������ ��ġ���� üũ�ϱ����ؼ�
		//	for (int i = 0; i< _map->getRoom().size(); ++i)
		//	{
		//		if (_map->getRoom()[random].roomState == ROOM_START ||
		//			_map->getRoom()[random].roomState == ROOM_SHOP)
		//		{
		//			if ((_map->getRoom()[i].left+2 <= _x && _map->getRoom()[i].right-2 >= _x) ||
		//				(_map->getRoom()[i].top+2 <= _y && _map->getRoom()[i].bottom-2 >= _y))
		//				pass = false; //�÷��̾��� ���� �� ���� ��ǥ��� false�� üũ
		//		}
		//	}
		//	if (!pass) // ���� ����!
		//		continue;
		//	break;// ��� ��Ƽ�� �������� ����ٸ� ����������
		//}
		//break;//�������Ӵٸ� ���⵵ ���ѷ��� ���������� ��ǥ�� �ùٸ��� �����Ǿ����ϴ�.
	}
	_rc = _map->getRect(_x,_y);
	_astar->setLinkrandomMap(_map);
	_astar->init(_x,_y,playerIndexX,playerIndexY);
	return S_OK;
}

void whiteSkeleton::update(int playerIndexX, int playerIndexY)
{
	//skeleton::update(playerIndexX, playerIndexY);
	//_astar->endmove(playerIndexX, playerIndexY);
	_astar->update();
	_astar->endmove(playerIndexX, playerIndexY);
	skeletonMove();
}

void whiteSkeleton::release()
{


}

void whiteSkeleton::render()
{
	Rectangle(getMemDC(), _rc);
	_img->frameRender(getMemDC(), _rc.left, _rc.top - (_rc.bottom-_rc.top)/2, 0, 0);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		skeleton::render();
	}
}
