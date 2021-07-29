#include "stdafx.h"
#include "redDragon.h"

HRESULT redDragon::init(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::init(playerIndexX, playerIndexY);		// == skeleton.cpp -> init() 전체


	//redDragon class 독립적인 선언 
	_renderTime = _movingTime = TIMEMANAGER->getWorldTime();
	_hp = 6;
	_img = IMAGEMANAGER->findImage("dragonRed");
	_img->setFrameY(0);

	_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	isSameLine = false;	//플레이어와 동일 선 상에 있는지 확인하고자하는 불값	//레드드래곤 클래스 안에서 선언
	_heart1 = _heart2 = _heart3 = _heart4 = _heart5 = _heart6 = IMAGEMANAGER->findImage("Enemy_heart");
	return S_OK;
}

void redDragon::release()
{
}

void redDragon::update(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::update(playerIndexX, playerIndexY);

	if (isFind && toRender)
	{
		if (_index >= 4)
		{
			_index = 0;
		}
		else
		{
			_index = 4;
		}
		toRender = false;
	}
	
	setRedDragonFrame();	//_count 증가시키고, _index 받아서 프레임 조절
	//moveRedDragon();

	//if (_index <= 3) {
	//	_count++;
	//	if (_count % 10 == 0)
	//	{
	//		_index++;
	//		if (_index > 3) _index = 0;
	//		_count = 0;
	//	}
	//}
	//if (isAction && _index >= 5)
	//{
	//	if (isTime)
	//	{
	//		_index++;
	//	}
	//	if (_index > 8)
	//	{
	//		_index = 0;
	//		isAction = false;
	//		_astar->callPathFinder(_tilex, _tiley);
	//	}
	//}
	//if (!isAction&&isFind)
	//{
	//	//액션
	//	if (_tilex == playerIndexX)
	//	{
	//		_index == 4;
	//		if (_tiley > playerIndexY)
	//		{
	//			isAction = true;
	//			_index == 4;
	//			_dir = UP;
	//			_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	//			_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	//		}
	//		else if (_tiley < playerIndexY)
	//		{
	//			isAction = true;

	//			_index == 4;
	//			_dir = DOWN;
	//			_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	//			_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	//		}
	//	}
	//	else if (_tiley == playerIndexY)
	//	{
	//		if (_tilex > playerIndexX)
	//		{
	//			isAction = true;
	//			_index == 4;
	//			_dir = LEFT;
	//			_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	//			_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	//		}
	//		else if (_tilex < playerIndexX)
	//		{
	//			isAction = true;
	//			_index == 4;
	//			_dir = RIGHT;
	//			_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	//			_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	//		}
	//	}
	//}
	moveMotion();

	if (playerIndexX < _tilex)
	{
		_indey = 0;
	}
	else
	{
		_indey = 1;
	}
	isTime = false;
	
	
	
}

void redDragon::render(int tileX, int tileY)
{
	if (tileX == _tilex && tileY == _tiley)
	{
		minotaurAndDragon::render();

		//알파렌더
		if (_map->getAlpha(_tilex, _tiley) <= 255 && _map->getAlpha(_tilex, _tiley) > 150)
		{
			if (_hp == 6)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 0);
			}
			if (_hp == 5)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 4)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 3)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 2)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 1)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 2);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			_img = IMAGEMANAGER->findImage("dragonRed");
			_img->frameRender(getMemDC(), _x , _y , _index, _indey);		//이미지 위치 잡아주기 위해 임의 값 감소시켜줌
		}
		else if (_map->getAlpha(_tilex, _tiley) <= 150 && _map->getAlpha(_tilex, _tiley) > 0)
		{
			if (_hp == 6)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 0);
			}
			if (_hp == 5)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 0);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 4)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 0);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 3)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 0);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 2)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 0);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			if (_hp == 1)
			{
				_heart1->frameRender(getMemDC(), _x + 3, _y - 25, 0, 0);
				_heart2->frameRender(getMemDC(), _x + 33, _y - 25, 0, 2);
				_heart3->frameRender(getMemDC(), _x + 63, _y - 25, 0, 2);
				_heart4->frameRender(getMemDC(), _x + 93, _y - 25, 0, 2);
				_heart5->frameRender(getMemDC(), _x + 123, _y - 25, 0, 2);
				_heart6->frameRender(getMemDC(), _x + 153, _y - 25, 0, 2);
			}
			_img = IMAGEMANAGER->findImage("dragonRed_dark");
			_img->frameRender(getMemDC(), _x , _y , _index, _indey);
		}
	}
}

void redDragon::setRedDragonFrame()
{
	////드래곤과 플레이어가 같은 줄이면
	//if (_tiley == _playerindey)
	//{
	//	isSameLine = true;
	//	if (!isdealy)
	//	{
	//		_index = 2;
	//		isdealy = true;
	//	}

	//}
	////드래곤과 플레이어가 같은 줄이 아니면
	//else isSameLine = false;

	////_count++;
	//if (isSameLine)
	//{
	//	_count++;
	//	if (_index >= 2 && _index <= 6)	//2 - 6		//광선 쏘기
	//	{
	//		if (_count % 5 == 0)
	//		{
	//			_index++;
	//			if (_index > 6)
	//			{
	//				isdealy =false;
	//				_index = 0;
	//			}
	//			_count = 0;
	//		}
	//		isSameLine = false;
	//	}
	//	
	//}
	//else
	//{
	//	_count++;
	//	_index = 0;
	//	if (_index >= 0 && _index <= 1)	//0, 1		//평상시 이동
	//	{
	//		if (_count % 10 == 0)
	//		{
	//			_index++;
	//			if (_index > 1) _index = 0;
	//			_count = 0;
	//		}
	//	}
	//}
}

void redDragon::moveRedDragon()
{

	//점프 이동 => 화이트 스켈레톤의 업데이트
	if (isMove)
	{
		switch (_dir)
		{
		case NONE:
			_gravity += 0.965f;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
			}
			break;

		case LEFT:
			_gravity += 0.965f;
			_x += cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			if (_x <= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
			}
			break;

		case RIGHT:
			_gravity += 0.965f;
			_x -= cosf(7 * PI / 9) * 9;
			_y += -sinf(7 * PI / 9) * 9 + _gravity;
			if (_x >= _rc.left)
			{
				_x = _rc.left;
				isMove = false;
				_gravity = 0;
				if (_y >= (_rc.top - (_rc.bottom - _rc.top) / 2))
				{
					_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				}
			}
			break;

		case UP:
			_gravity += 0.2f;
			_y += -sinf(PI / 2) * 9 + _gravity;
			if (_y <= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
			}
			break;

		case DOWN:
			_gravity += 1.2f;
			_y += -sinf(PI / 2) + _gravity;
			if (_y >= _rc.top - (_rc.bottom - _rc.top) / 2)
			{
				_y = _rc.top - (_rc.bottom - _rc.top) / 2;
				isMove = false;
				_gravity = 0;
			}
			break;
		}
	}
}
