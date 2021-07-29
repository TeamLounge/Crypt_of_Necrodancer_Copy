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

	_vFire.clear();	//벡터 안의 쓰레기 값 없애기
	_heart1 = _heart2 = _heart3 = _heart4 = _heart5 = _heart6 = IMAGEMANAGER->findImage("Enemy_heart");

	return S_OK;
}

void redDragon::release()
{
}

void redDragon::update(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::update(playerIndexX, playerIndexY);
	
	if (_index <= 1)
	{
		_count++;
		if (_count % 10 == 0)
		{
			_index++;
			if (_index > 1)	_index = 0;
			_count = 0;
		}
	}
	if (isFire && _index >= 2)
	{
		if (_index < 5)
		{	_count++;
			if (_count % 7 == 0)
			{
				_index++;
				_count = 0;
			}
		}
		else if (_index == 5)
		{
			//여기서 화염포를 쏘는 랜더불변수를 또 줘야함
			fireRender = true;

		}
		else if (_index == 6)
		{
			
			if (isTime)
			{
				_count++;
			}
			if (_count == 2)
			{
				_vFire.clear();
				isFire = false;
				_count = 0;

				_index = 0;
			}
		}
	}

	//
	if (!isFire && isFind)	//화염포를 쏘는상태가아니면서 적을탐지햇을때	//abs(_tilex - playerIndexX == 5)
	{							//실제로 필요한 상황은 Action이 켜져야할 상황을만드는것
		//if (!(_tiley == playerIndexY))	//같은 y축이 아니면 ->화염포를쏘지말고 적을 쫒아가야되잖음

		if (_tiley == playerIndexY)	//같은 y축이면(선 상이면) -> 광선 쏘는 이미지
		{
			isFire = true;
			_index = 2;

			if (_indey == 0)	//LEFT
			{
				for (int i = _tilex - 1; i > 0; --i)
				{
					if (_map->getTileObject(i, _tiley) == OBJ_NONE)
					{
						FIRE _fire;
						if (i == _tilex - 1)
						{

							_fire.img = IMAGEMANAGER->findImage("dragonRedFireStarting");
						}
						else
						{
							_fire.img = IMAGEMANAGER->findImage("dragonRedFire");
						}
						_fire.isAttack = true;
						_fire.tileX = i;
						_fire.tileY = _tiley;
						_fire.rc = _map->getRect(i, _tiley);
						_vFire.push_back(_fire);
					}
					else if (_map->getTileObject(i, _tiley) != OBJ_NONE)
					{
						break;
					}
	
				}
			}
			else if (_indey == 1)	//RIGHT
			{	
				for (int i = _tilex + 1; i < _map->getXSize(); i++)
				{
					if (_map->getTileObject(i, _tiley) == OBJ_NONE)
					{
						FIRE _fire;
						if (i == _tilex + 1)
						{

							_fire.img = IMAGEMANAGER->findImage("dragonRedFireStarting");
						}
						else
						{
							_fire.img = IMAGEMANAGER->findImage("dragonRedFire");
						}
						_fire.isAttack = true;
						_fire.tileX = i;
						_fire.tileY = _tiley;
						_fire.rc = _map->getRect(i, _tiley);

						_vFire.push_back(_fire);
					}
					else if (_map->getTileObject(i, _tiley) != OBJ_NONE)
					{
						break;
					}
				}
			}
		}

	}

	moveMotion();
	//이 안에 카메라 떨림 필요
	//CAMERAMANAGER->vibrateScreen((_shadow.left + _shadow.right) / 2, (_shadow.top + _shadow.bottom) / 2, 25.0f);


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

			if (fireRender) {
				for (int i = 0; i < _vFire.size(); i++)
				{
					if (_vFire[i].img == IMAGEMANAGER->findImage("dragonRedFireStarting"))		//이미지가 스타팅이냐
					{
						if (_indey == 0)	//왼쪽이냐
						{
							_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 1);
						}
						else if (_indey == 1)	//오른쪽이냐
						{
							_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 0);
						}
					}
					else if (_vFire[i].img == IMAGEMANAGER->findImage("dragonRedFire"))		//이미지가 기본 화염포 이미지냐
					{
						_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 0);
					}
				}
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
