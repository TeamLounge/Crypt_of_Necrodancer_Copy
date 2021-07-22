#include "stdafx.h"
#include "slime.h"

HRESULT slime::init()
{
	_worldTime = TIMEMANAGER->getWorldTime();

	_rc = _map->getRect(_tileX, _tileY);
	_map->setTileObject(_x, _y, ENEMY);

	_direction = NONE;
	_isRight = true;
	_frameCount = 0;
	_frameIndex = 0;


	_gravity = 0;
	_jumpPower = 0;

	//맵에 뿌려주기
	setArrangement();

	return S_OK;
}

void slime::release()
{
}

void slime::update()
{
	//플레이어 위치 파악
	//따라가기 혹은 제자리 뛰기
}

void slime::render()
{

}

void slime::setArrangement()
{
	//랜덤 배치
	while (true)
	{

		//랜덤방에 배치
		int random = RND->getInt(_map->getRoom().size());
		if (_map->getRoom()[random].roomState == ROOM_START ||
			_map->getRoom()[random].roomState == ROOM_SHOP)
			continue;	// 그 방이 플레이어방이거나 상점이면 컨티뉴

		//_map->getTileObject	//object인 거 받아오기
		//_map->getTileTerrain	//terrain인 거 받아오기
		//_map->getRect			//타일 rect 받아오기
		//등등 다양한 정보 받아올 수 있으니 잘 쓰자!!!!


		//랜덤하게 찍은 방안의 좌표 중 벽이 있어도 컨티뉴
		_tileX = RND->getFromIntTo(_map->getRoom()[random].x, _map->getRoom()[random].x + _map->getRoom()[random].width);
		_tileY = RND->getFromIntTo(_map->getRoom()[random].y, _map->getRoom()[random].y + _map->getRoom()[random].height);
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1)
			continue;
		break;		//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져 나오기

	}
}

void slime::slimeMove()
{
	_map->setTileObject(_tileX, _tileY, OBJ_NONE);
	_rc = _map->getRect(_tileX, _tileY);	//slime의 _x, _y 좌표를 타일 값으로 받아온다
	_map->setTileObject(_tileX, _tileY, ENEMY);
}
