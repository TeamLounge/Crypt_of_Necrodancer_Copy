#include "stdafx.h"
#include "redDragon.h"

HRESULT redDragon::init(int playerIndexX, int playerIndexY)
{
	minotaurAndDragon::init(playerIndexX, playerIndexY);		// == skeleton.cpp -> init() ��ü


	//redDragon class �������� ���� 
	_renderTime = _movingTime = TIMEMANAGER->getWorldTime();
	_hp = 6;
	_img = IMAGEMANAGER->findImage("dragonRed");
	_img->setFrameY(0);

	_x = (_rc.left + _rc.right) / 2 - (_img->getFrameWidth() / 2);
	_y = _rc.top - ((_rc.bottom - _rc.top) / 2) - (_img->getFrameHeight() / 2);
	isSameLine = false;	//�÷��̾�� ���� �� �� �ִ��� Ȯ���ϰ����ϴ� �Ұ�	//����巡�� Ŭ���� �ȿ��� ����

	_vFire.clear();	//���� ���� ������ �� ���ֱ�
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
			//���⼭ ȭ������ ��� �����Һ����� �� �����
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
	if (!isFire && isFind)	//ȭ������ ��»��°��ƴϸ鼭 ����Ž��������	//abs(_tilex - playerIndexX == 5)
	{							//������ �ʿ��� ��Ȳ�� Action�� �������� ��Ȳ������°�
		//if (!(_tiley == playerIndexY))	//���� y���� �ƴϸ� ->ȭ�������������� ���� �i�ư��ߵ�����

		if (_tiley == playerIndexY)	//���� y���̸�(�� ���̸�) -> ���� ��� �̹���
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
	//�� �ȿ� ī�޶� ���� �ʿ�
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

		//���ķ���
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
					if (_vFire[i].img == IMAGEMANAGER->findImage("dragonRedFireStarting"))		//�̹����� ��Ÿ���̳�
					{
						if (_indey == 0)	//�����̳�
						{
							_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 1);
						}
						else if (_indey == 1)	//�������̳�
						{
							_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 0);
						}
					}
					else if (_vFire[i].img == IMAGEMANAGER->findImage("dragonRedFire"))		//�̹����� �⺻ ȭ���� �̹�����
					{
						_vFire[i].img->frameRender(getMemDC(), _vFire[i].rc.left, _vFire[i].rc.top, _fireIndex, 0);
					}
				}
			}

			_img = IMAGEMANAGER->findImage("dragonRed");
			_img->frameRender(getMemDC(), _x , _y , _index, _indey);		//�̹��� ��ġ ����ֱ� ���� ���� �� ���ҽ�����
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
