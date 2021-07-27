#include "stdafx.h"
#include "slime.h"

HRESULT slime::init(int playerIndexX, int playerIndexY)
{

	_toRender = _damageRender = false;
	//_direction = NONE;
	_frameCount = 0;
	_frameIndex = 0;

	_isMove = false;		//시작하자마자 움직여
	_isTime = false;

	_gravity = 0;
	_beatSpeed = 1.0f;

	_worldTime = TIMEMANAGER->getWorldTime();


	//맵에 뿌려주기
	/////////////////////////////////////////////////////////////////// 순서 잘 잡아라 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	setArrangement();	//타일에 먼저 뿌리고

	_rc = _map->getRect(_tileX, _tileY);		//자리 잡고 나서 갱신해줘야지
	_map->setIsEnemy(_tileX, _tileY, true);		//_map->setTileObject(_tileX, _tileY, ENEMY);  같은 거
	_x = _rc.left;								//_x, _y는 이미지를 움직이기 위한 _rc를 토대로 가져온 실제 좌표(정보 가져오기 위함)
	_y = _rc.top - (_rc.bottom - _rc.top) / 2;



	return S_OK;
}

void slime::release()
{
}

void slime::update(int playerIndexX, int playerIndexY)
{
	_playerIndexX = playerIndexX;
	_playerIndexY = playerIndexY;
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
		if (_map->getTileObject(_tileX, _tileY) != OBJ_NONE || _map->getTileTerrain(_tileX, _tileY) != DIRT1 
			|| _map->getIsEnemy(_tileX, _tileY))		//복도 tile은 2지만, room으로 배치하니까 무관!
			continue;
		break;		//// 모든 컨티뉴 지옥에서 벗어낫다면 빠져 나오기
	}
}
