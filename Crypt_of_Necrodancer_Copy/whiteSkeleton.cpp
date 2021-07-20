#include "stdafx.h"
#include "whiteSkeleton.h"

HRESULT whiteSkeleton::init(int playerIndexX, int playerIndexY)
{
	IMAGEMANAGER->addFrameImage("whiteSkeleton", "image/enemy/skeletonBasic.bmp", 576, 177, 8, 2, true, RGB(255, 0, 255));
	skeleton::init();
	_astar = new aStarTest;
	_img = IMAGEMANAGER->findImage("whiteSkeleton");

	while (true) //랜덤배치
	{
		//int random = RND->getInt(2);
		//switch (random)
		//{
		//case 0:
		int random = RND->getInt(_map->getRoom().size());//랜덤방에 배치
		if(_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;// 그 방이 플레이어방이거나 상점이면 컨티뉴  
		_x = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_y = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_x, _y)!= OBJ_NONE || _map->getTileTerrain(_x, _y) != DIRT1)
			continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴
		break;//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
		//case 1:
		//	random = RND->getInt(_map->getFloor().size());//랜덤 방이아닌 연결되어서 생긴 방쪽에도 생성
		//	_x = RND->getFromIntTo(_map->getFloor()[random].left, _map->getFloor()[random].right);
		//	_y = RND->getFromIntTo(_map->getFloor()[random].top, _map->getFloor()[random].bottom);
		//	if (_map->getTiles()[_y][_x].obj != OBJ_NONE || _map->getTiles()[_y][_x].terrain != DIRT1)
		//		continue; //랜덤하게 찍은 방안의 좌표 중 벽이있어도 컨티뉴

		//	bool pass = true; //여기는 플레이어방,상점방 겹치는지 체크하기위해서
		//	for (int i = 0; i< _map->getRoom().size(); ++i)
		//	{
		//		if (_map->getRoom()[random].roomState == ROOM_START ||
		//			_map->getRoom()[random].roomState == ROOM_SHOP)
		//		{
		//			if ((_map->getRoom()[i].left+2 <= _x && _map->getRoom()[i].right-2 >= _x) ||
		//				(_map->getRoom()[i].top+2 <= _y && _map->getRoom()[i].bottom-2 >= _y))
		//				pass = false; //플레이어방과 상점 방 안의 좌표라면 false로 체크
		//		}
		//	}
		//	if (!pass) // 히히 못가!
		//		continue;
		//	break;// 모든 컨티뉴 지옥에서 벗어낫다면 빠져나오기
		//}
		//break;//빠져나왓다면 여기도 무한루프 빠져나오고 좌표가 올바르게 생성되었습니다.
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
