#include "stdafx.h"
#include "redDragon.h"

HRESULT redDragon::init(int playerIndexX, int playerIndexY)
{
	//_toRender = _damageRender = false;
	//_direction = LEFT;	//왼쪽 보고 태어나
	//_frameCount = 0;
	//_frameIndex = 0;

	//_isMove = false;		//시작하자마자 움직여
	//_isTime = false;

	//_gravity = 0;

	//_worldTime = TIMEMANAGER->getWorldTime();

	////맵에 뿌려주기
	//setArrangement();	//타일에 먼저 뿌리자

	//_img = IMAGEMANAGER->findImage("redDragon");	//자식
	//_rc = _map->getRect(_tileX, _tileY);
	//_map->setIsEnemy(_tileX, _tileY, true);
	//_x = _rc.left;
	//_y = _rc.top - (_rc.bottom - _rc.top) / 2;


	return S_OK;
}

void redDragon::update(int playerIndexX, int playerIndexY)
{
	setRedDragonFrame();
	moveRedDragon();
}

void redDragon::render()
{
	/*if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}

	_img->frameRender(getMemDC(), _x, _y, _currentFrameX, _currentFrameY);*/
}

void redDragon::setArrangement()
{
	////랜덤 배치
	//while (true)
	//{
	//	//랜덤방에 배치
	//	int random = RND->getInt(_map->getRoom().size());
	//	if (_map->getRoom()[random].roomState == ROOM_START ||
	//		_map->getRoom()[random].roomState == ROOM_SHOP)
	//		continue;	// 그 방이 플레이어방이거나 상점이면 컨티뉴

	//	//랜덤하게 찍은 방안의 좌표 중 벽이 있어도 컨티뉴
	//	_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
	//	_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
	//	if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1
	//		|| _map->getIsEnemy(_tileX, _tileY))		//복도 tile은 2지만, room으로 배치하니까 무관!
	//		continue;
	//	break;		//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져 나오기
	//}
}

void redDragon::setRedDragonFrame()
{
	//if (TIMEMANAGER->getWorldTime() - _worldTime > 0.5f)
	//{
	//	_worldTime = TIMEMANAGER->getWorldTime();
	//}

	//_frameCount++;
	//if (_frameCount % 8 == 0)
	//{
	//	_frameCount = 0;
	//	if (_currentFrameX >= IMAGEMANAGER->findImage("redDragon")->getMaxFrameX())
	//	{
	//		_currentFrameX = 0;
	//	}
	//	else
	//	{
	//		_currentFrameX++;
	//	}
	//	//방향 바꿔 보여주기
	//	if (_direction == LEFT)
	//	{
	//		_currentFrameY = 0;
	//	}
	//	else if (_direction == RIGHT)
	//	{
	//		_currentFrameY = 1;
	//	}
	//}
}

void redDragon::moveRedDragon()
{
}
