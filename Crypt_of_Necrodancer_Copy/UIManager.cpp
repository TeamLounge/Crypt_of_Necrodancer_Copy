#include "stdafx.h"
#include "UIManager.h"
#include "objectManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

HRESULT UIManager::init()
{
	_heartNum = 0;
	_elapsedSec = 0;
	_heartCnt = _vHeart.size() - 1;
	_count = _vHeart.size() - 1;
	_nextI = _nextJ = 0;
	_moneyNum = 0;
	_diaNum = 0;
	_isMoneyPlus = false;
	_isDiaPlus = false;
	_isBody = false;
	_isHead = false;
	_isFeet = false;
	_isTorch = false;
	_isRing = false;
	_isKey = false;
	_isItem = _isPack = _isPack2 = _isBomb =
		_isOnOff = _isReload = _isThrow =
		_isPress = _isHolster = _isHolster2 = false;
	_isSpell = _isSpell2 = _isSpell3 = false;

	_isIntersectJudge = false;
	return S_OK;
}

void UIManager::release()
{
}

void UIManager::update()
{
}

void UIManager::render()
{
}

void UIManager::setHeart(int heartNum)
{
	_heartNum = heartNum;

	for (int i = 0; i < _heartNum; ++i)
	{
		UI* heart;
		heart = new Heart;
		heart->init("heart", PointMake(CAMERAMANAGER->getCameraRIGHT() - 200 - i * 50,
			CAMERAMANAGER->getCameraTOP() + 50));

		_vHeart.push_back(heart);
	}
}

void UIManager::updateHeart()
{
	for (int i = 0; i < _vHeart.size(); ++i)
	{
		(*(_vHeart.begin() + i))->setRect(RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 200 - i * 50,
			CAMERAMANAGER->getCameraTOP() + 50,
			(*(_vHeart.begin() + i))->getImg()->getFrameWidth(),
			(*(_vHeart.begin() + i))->getImg()->getFrameHeight()));
	}

	_elapsedSec += TIMEMANAGER->getElapsedTime();

	if (_elapsedSec >= 0.24f)
	{
		_elapsedSec -= 0.24f;
		if ((*(_vHeart.begin() + _heartCnt))->getCurrentFrameX() == (*(_vHeart.begin() + _heartCnt))->getImg()->getMaxFrameX())
		{
			(*(_vHeart.begin() + _heartCnt))->setCurrentFrameX(0);
			_heartCnt--;
			if (_heartCnt < 0) _heartCnt = _vHeart.size() - 1;
		}

		else (*(_vHeart.begin() + _heartCnt))->setCurrentFrameX((*(_vHeart.begin() + _heartCnt))->getCurrentFrameX() + 1);
	}
}

void UIManager::renderHeart()
{
	for (_viHeart = _vHeart.begin(); _viHeart != _vHeart.end(); ++_viHeart)
	{
		(*_viHeart)->render();
	}
}

void UIManager::setHeartBeat(int heartBeatNum)
{
	_beatHeart = new beatHeart;
	_beatHeart->init("beatHeart", PointMake(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraBOTTOM() - 100));
	_heartBeatInterval = (int)((WINSIZEX / 2) / heartBeatNum);

	for (int i = 0; i < heartBeatNum; ++i)
	{
		UI* _heartBeatRight;
		_heartBeatRight = new heartBeat;
		_heartBeatRight->init("heartBeat", PointMake(CAMERAMANAGER->getCameraRIGHT() - i * _heartBeatInterval,
			CAMERAMANAGER->getCameraBOTTOM() - 100));

		_vHeartBeatRight.push_back(_heartBeatRight);
	}

	for (int i = 0; i < heartBeatNum; ++i)
	{
		UI* _heartBeatLeft;
		_heartBeatLeft = new heartBeat;
		_heartBeatLeft->init("heartBeat", PointMake(CAMERAMANAGER->getCameraLEFT() + i * _heartBeatInterval,
			CAMERAMANAGER->getCameraBOTTOM() - 100));

		_vHeartBeatLeft.push_back(_heartBeatLeft);
	}
}

void UIManager::updaetHeartBeat(float speed)
{
	_isIntersectJudge = false;

	_beatHeart->setRect(RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraBOTTOM() - 100,
		_beatHeart->getImg()->getFrameWidth(),
		_beatHeart->getImg()->getFrameHeight()));

	_beatHeart->setCurrentFrameX(0);

	_beatJudgement = RectMakeCenter(CAMERAMANAGER->getCameraCenterX(), CAMERAMANAGER->getCameraBOTTOM() - 100,
		_beatHeart->getImg()->getFrameWidth(),
		_beatHeart->getImg()->getFrameHeight());

	for (_viHeartBeatLeft = _vHeartBeatLeft.begin(); _viHeartBeatLeft != _vHeartBeatLeft.end(); ++_viHeartBeatLeft)
	{		
		if ((*_viHeartBeatLeft)->getCenterX() < WINSIZEX / 2)
		{
			(*_viHeartBeatLeft)->move(speed);
		}

		(*_viHeartBeatLeft)->setRect(RectMakeCenter(
			CAMERAMANAGER->getCameraCenterX() - (*_viHeartBeatLeft)->getCameraCenterX(),
			CAMERAMANAGER->getCameraBOTTOM() - 100,
			(*_viHeartBeatLeft)->getImg()->getFrameWidth(),
			(*_viHeartBeatLeft)->getImg()->getFrameHeight()));

		RECT temp;
		if (IntersectRect(&temp, &(*_viHeartBeatLeft)->getRect(), &_beatHeart->getRect()))
		{
			_beatHeart->setCurrentFrameX(1);
		}
	}

	for (_viHeartBeatRight = _vHeartBeatRight.begin(); _viHeartBeatRight != _vHeartBeatRight.end(); ++_viHeartBeatRight)
	{
		if ((*_viHeartBeatRight)->getCenterX() > WINSIZEX / 2)
		{
			(*_viHeartBeatRight)->move(-speed);
		}

		(*_viHeartBeatRight)->setRect(RectMakeCenter(
			CAMERAMANAGER->getCameraCenterX() + (*_viHeartBeatRight)->getCameraCenterX(),
			CAMERAMANAGER->getCameraBOTTOM() - 100,
			(*_viHeartBeatRight)->getImg()->getFrameWidth(),
			(*_viHeartBeatRight)->getImg()->getFrameHeight()));

		RECT temp;
		if (IntersectRect(&temp, &(*_viHeartBeatRight)->getRect(), &_beatHeart->getRect()))
		{
			_beatHeart->setCurrentFrameX(1);
		}
	}

	for (_viHeartBeatRight = _vHeartBeatRight.begin(); _viHeartBeatRight != _vHeartBeatRight.end(); ++_viHeartBeatRight)
	{
		RECT temp;
		if (IntersectRect(&temp, &(*_viHeartBeatRight)->getRect(), &_beatJudgement))
		{
			_isIntersectJudge = true;
			break;
		}
	}

	for (int i = 0; i < _vHeartBeatLeft.size(); ++i)
	{
		for (int j = 0; j < _vHeartBeatRight.size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &((*(_vHeartBeatLeft.begin() + i))->getRect()), &((*(_vHeartBeatRight.begin() + j))->getRect())))
			{
				_nextI = i + 1;
				_nextJ = j + 1;
				if (_nextI == _vHeartBeatLeft.size()) _nextI = 0;
				if (_nextJ == _vHeartBeatRight.size()) _nextJ = 0;

				//(*(_vHeartBeatLeft.begin() + i))->setCurrentFrameX(1);

				(*(_vHeartBeatLeft.begin() + i))->setCenterX((*(_vHeartBeatLeft.begin() + _nextI))->getCenterX() - _heartBeatInterval);
				(*(_vHeartBeatRight.begin() + j))->setCenterX((*(_vHeartBeatRight.begin() + _nextJ))->getCenterX() + _heartBeatInterval);
			}
		}
	}
}

void UIManager::renderHeartBeat()
{
	for (_viHeartBeatLeft = _vHeartBeatLeft.begin(); _viHeartBeatLeft != _vHeartBeatLeft.end(); ++_viHeartBeatLeft)
	{
		(*_viHeartBeatLeft)->render();
	}

	for (_viHeartBeatRight = _vHeartBeatRight.begin(); _viHeartBeatRight != _vHeartBeatRight.end(); ++_viHeartBeatRight)
	{
		(*_viHeartBeatRight)->render();
	}

	_beatHeart->render();
}

void UIManager::setMoney()
{
	_money = new money;
	_money->init("money", PointMake(CAMERAMANAGER->getCameraRIGHT() - 130, CAMERAMANAGER->getCameraTOP() + 50));
}

void UIManager::updateMoney()
{
	_money->setRect(RectMakeCenter(
		CAMERAMANAGER->getCameraRIGHT() - 130,
		CAMERAMANAGER->getCameraTOP() + 50,
		_money->getImg()->getWidth(),
		_money->getImg()->getHeight()));
}

void UIManager::renderMoney()
{
	_money->imgDraw();
}

void UIManager::setDiamond()
{
	_diamond = new diamond;
	_diamond->init("diamond", PointMake(CAMERAMANAGER->getCameraRIGHT() - 130, CAMERAMANAGER->getCameraTOP() + 100));
}

void UIManager::updateDiamond()
{
	_diamond->setRect(RectMakeCenter(
		CAMERAMANAGER->getCameraRIGHT() - 130,
		CAMERAMANAGER->getCameraTOP() + 100,
		_diamond->getImg()->getWidth(),
		_diamond->getImg()->getHeight()));
}

void UIManager::renderDiamond()
{
	_diamond->imgDraw();
}


void UIManager::setMoneyNumber()
{
	for (int i = 0; i < 3; i++)
	{
		UI* _moneyNumber;
		_moneyNumber = new numberUI;
		_moneyNumber->init("number", PointMake(CAMERAMANAGER->getCameraRIGHT() - 45 - i * 15,
			CAMERAMANAGER->getCameraTOP() + 55));

		_vMoneyNumber.push_back(_moneyNumber);
	}

	_moneyX = new X;
	_moneyX->init("X", PointMake(CAMERAMANAGER->getCameraRIGHT() - 95, CAMERAMANAGER->getCameraTOP() + 58));
}

void UIManager::updateMoneyNumber(int moneyNum, bool reset)
{
	if (reset && !_isMoneyPlus)
	{
		_moneyNum = 0;
		_isMoneyPlus = true;
	}

	if (!reset && !_isMoneyPlus)
	{
		_moneyNum += moneyNum;
		_isMoneyPlus = true;
	}

	if (_isMoneyPlus)
	{
		_moneyHundred = _moneyNum / 100;
		_moneyTen = (_moneyNum / 10) % 10;
		_moneyOne = (_moneyNum % 10);

		//1의자리
		(*(_vMoneyNumber.begin() + 0))->setCurrentFrameX(_moneyOne);
		//10의 자리
		(*(_vMoneyNumber.begin() + 1))->setCurrentFrameX(_moneyTen);
		//100의 자리
		(*(_vMoneyNumber.begin() + 2))->setCurrentFrameX(_moneyHundred);

		for (int i = 0; i < 3; ++i)
		{
			(*(_vMoneyNumber.begin() + i))->setRect(RectMakeCenter(
				CAMERAMANAGER->getCameraRIGHT() - 45 - i * 15,
				CAMERAMANAGER->getCameraTOP() + 55,
				(*(_vMoneyNumber.begin() + i))->getImg()->getFrameWidth(),
				(*(_vMoneyNumber.begin() + i))->getImg()->getFrameHeight()));
		}

		_moneyX->setRect(RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 95, CAMERAMANAGER->getCameraTOP() + 58,
			_moneyX->getImg()->getWidth(), _moneyX->getImg()->getHeight()));
	}
}

void UIManager::renderMoneyNumber()
{
	for (int i = 0; i < 3; ++i)
	{
		if (_moneyHundred == 0 && i == 2) continue;
		if (_moneyTen == 0 && i == 1) continue;

		(*(_vMoneyNumber.begin() + i))->render();
	}

	_moneyX->imgDraw();
}

void UIManager::setDiaNumber()
{
	for (int i = 0; i < 3; i++)
	{
		UI* _diaNumber;
		_diaNumber = new numberUI;
		_diaNumber->init("number", PointMake(CAMERAMANAGER->getCameraRIGHT() - 45 - i * 15,
			CAMERAMANAGER->getCameraTOP() + 105));

		_vDiaNumber.push_back(_diaNumber);
	}

	_diaX = new X;
	_diaX->init("X", PointMake(CAMERAMANAGER->getCameraRIGHT() - 95, CAMERAMANAGER->getCameraTOP() + 108));
}

void UIManager::updateDiaNumber(int diaNum, bool reset)
{
	if (reset && !_isDiaPlus)
	{
		_diaNum = 0;
		_isDiaPlus = true;
	}

	if (!reset && !_isDiaPlus)
	{
		_diaNum += diaNum;
		_isDiaPlus = true;
	}

	if (_isDiaPlus)
	{
		_diaHundred = _diaNum / 100;
		_diaTen = (_diaNum / 10) % 10;
		_diaOne = (_diaNum % 10);

		//1의자리
		(*(_vDiaNumber.begin() + 0))->setCurrentFrameX(_diaOne);
		//10의 자리
		(*(_vDiaNumber.begin() + 1))->setCurrentFrameX(_diaTen);
		//100의 자리
		(*(_vDiaNumber.begin() + 2))->setCurrentFrameX(_diaHundred);

		for (int i = 0; i < 3; ++i)
		{
			(*(_vDiaNumber.begin() + i))->setRect(RectMakeCenter(
				CAMERAMANAGER->getCameraRIGHT() - 45 - i * 15,
				CAMERAMANAGER->getCameraTOP() + 105,
				(*(_vDiaNumber.begin() + i))->getImg()->getFrameWidth(),
				(*(_vDiaNumber.begin() + i))->getImg()->getFrameHeight()));
		}

		_diaX->setRect(RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 95, CAMERAMANAGER->getCameraTOP() + 108,
			_diaX->getImg()->getWidth(), _diaX->getImg()->getHeight()));
	}
}

void UIManager::renderDiaNumber()
{
	for (int i = 0; i < 3; ++i)
	{
		if (_diaHundred == 0 && i == 2) continue;
		if (_diaTen == 0 && i == 1) continue;

		(*(_vDiaNumber.begin() + i))->render();
	}

	_diaX->imgDraw();
}

void UIManager::setItemHUD()
{
	for (int i = 0; i < 21; ++i)
	{
		UI* _itemHUD;
		_itemHUD = new itemHUD;
		_itemHUD->init("itemHUD", PointMake(CAMERAMANAGER->getCameraLEFT() + 60, CAMERAMANAGER->getCameraTOP() + 50));

		_vItemHUD.push_back(_itemHUD);
	}

	for (int i = 0; i < _vItemHUD.size(); ++i)
	{
		if (i == 0)
		{
			(*(_vItemHUD.begin() + i))->setItemType(SHOVEL);
		}
		if (i == 1)
		{
			 (*(_vItemHUD.begin() + i))->setItemType(ATTACK);
		}

		if (i > 1)
		{
			(*(_vItemHUD.begin() + i))->setItemType(NONE_TYPE);
		}
	}
}

void UIManager::updateItemHUD()
{
	for (int i = 0; i < _vItemHUD.size(); ++i)
	{
		for (int j = 0; j < _vItemHUD.size(); ++j)
		{
			if ((*(_vItemHUD.begin() + i))->getItemType() == NONE_TYPE) continue;
			if ((*(_vItemHUD.begin() + j))->getItemType() == NONE_TYPE) continue;

			switch ((*(_vItemHUD.begin() + i))->getItemType())
			{
				case SHOVEL:
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(0);
					(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
						CAMERAMANAGER->getCameraLEFT() + 70,
						CAMERAMANAGER->getCameraTOP() + 70,
						(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
						(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
				break;
				case ATTACK:
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(1);
					(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
						CAMERAMANAGER->getCameraLEFT() + 160,
						CAMERAMANAGER->getCameraTOP() + 70,
						(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
						(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
				break;
				case BODY:
					_isBody = true;

					(*(_vItemHUD.begin() + i))->setCurrentFrameX(2);
					(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
						CAMERAMANAGER->getCameraLEFT() + 250,
						CAMERAMANAGER->getCameraTOP() + 70,
						(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
						(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
				break;
				case HEAD:
					_isHead = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(3);

					if (_isBody)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BODY)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				
					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 250,
							CAMERAMANAGER->getCameraTOP() + 70,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case FEET:
					_isFeet = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(4);

					if (_isBody && !_isHead)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BODY)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isHead)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == HEAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 250,
							CAMERAMANAGER->getCameraTOP() + 70,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case TORCH:
					_isTorch = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(5);


					if (_isBody && !_isHead && !_isFeet)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BODY)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isHead && !_isFeet)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == HEAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isFeet)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == FEET)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 250,
							CAMERAMANAGER->getCameraTOP() + 70,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case RING:
					_isRing = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(6);

					if (_isBody && !_isHead && !_isFeet && !_isTorch)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BODY)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isHead && !_isFeet && !_isTorch)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == HEAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isFeet && !_isTorch)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == FEET)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isTorch)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == TORCH)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 250,
							CAMERAMANAGER->getCameraTOP() + 70,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case KEY:
					_isKey = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(7);

					if (_isBody && !_isHead && !_isFeet && !_isTorch && !_isRing)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BODY)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isHead && !_isFeet && !_isTorch && !_isRing)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == HEAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isFeet && !_isTorch && !_isRing)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == FEET)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isTorch && !_isRing)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == TORCH)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isRing)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == RING)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								(((*(_vItemHUD.begin() + j))->getRect().left + (*(_vItemHUD.begin() + j))->getRect().right) / 2) + 90,
								CAMERAMANAGER->getCameraTOP() + 70,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 250,
							CAMERAMANAGER->getCameraTOP() + 70,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case ITEM:
					_isItem = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(8);

					if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraLEFT() + 70,
							(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case PACK:
					_isPack = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(9);

					if (_isItem)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case PACK2:
					_isPack2 = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(10);

					if (_isItem && !_isPack)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case BOMB:
					_isBomb = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(11);

					if (_isItem && !_isPack && !_isPack2)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case ONOFF:
					_isOnOff = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(12);

					if (_isItem && !_isPack && !_isPack2 && !_isBomb)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 60,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 84,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case RELOAD:
					_isReload = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(13);

					if (_isItem && !_isPack && !_isPack2 && !_isBomb && !_isOnOff)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb && !_isOnOff)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb && !_isOnOff)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb && !_isOnOff)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isOnOff)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ONOFF)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case SPELL:
					_isSpell = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(14);

					(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
						CAMERAMANAGER->getCameraRIGHT() - 70,
						CAMERAMANAGER->getCameraTOP() + 200,
						(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
						(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
				break;
				case SPELL2:
					_isSpell2 = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(15);

					if (_isSpell)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SPELL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraRIGHT() - 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraRIGHT() - 70,
							CAMERAMANAGER->getCameraTOP() + 200,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case SPELL3:
					_isSpell3 = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(16);

					if (_isSpell && !_isSpell2)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SPELL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraRIGHT() - 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isSpell2)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SPELL2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraRIGHT() - 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
							CAMERAMANAGER->getCameraRIGHT() - 70,
							CAMERAMANAGER->getCameraTOP() + 200,
							(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
							(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
					}
				break;
				case THROW:
					_isThrow = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(17);

					if (_isItem && !_isPack && !_isPack2 && !_isBomb && !_isOnOff && !_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb && !_isOnOff && !_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb && !_isOnOff && !_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb && !_isOnOff && !_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isOnOff && !_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ONOFF)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isReload)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == RELOAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case PRESS:
					_isPress = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(18);

					if (_isItem && !_isPack && !_isPack2 &&
						!_isBomb && !_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb &&
						!_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb && !_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb && !_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ONOFF)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == RELOAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == THROW)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case HOLSTER:
					_isHolster = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(19);

					if (_isItem && !_isPack && !_isPack2 &&
						!_isBomb && !_isOnOff && !_isReload && !_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb &&
						!_isOnOff && !_isReload && !_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb && !_isOnOff &&
						!_isReload && !_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb && !_isOnOff && !_isReload && !_isThrow)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isOnOff && !_isReload && !_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ONOFF)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isReload && !_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == RELOAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isThrow && !_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == THROW)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPress)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PRESS)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
				case HOLSTER2:
					_isHolster2 = true;
					(*(_vItemHUD.begin() + i))->setCurrentFrameX(20);

					if (_isItem && !_isPack && !_isPack2 &&
						!_isBomb && !_isOnOff && !_isReload && !_isThrow && !_isPress &&
						!_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ITEM)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack && !_isPack2 && !_isBomb &&
						!_isOnOff && !_isReload && !_isThrow && !_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPack2 && !_isBomb && !_isOnOff &&
						!_isReload && !_isThrow && !_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PACK2)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isBomb && !_isOnOff && !_isReload && !_isThrow && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == BOMB)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isOnOff && !_isReload && !_isThrow && !_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == ONOFF)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isReload && !_isThrow && !_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == RELOAD)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isThrow && !_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == THROW)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isPress && !_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == PRESS)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else if (_isHolster)
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == HOLSTER)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}

					else
					{
						if ((*(_vItemHUD.begin() + j))->getItemType() == SHOVEL)
						{
							(*(_vItemHUD.begin() + i))->setRect(RectMakeCenter(
								CAMERAMANAGER->getCameraLEFT() + 70,
								(((*(_vItemHUD.begin() + j))->getRect().top + (*(_vItemHUD.begin() + j))->getRect().bottom) / 2) + 126,
								(*(_vItemHUD.begin() + i))->getImg()->getFrameWidth(),
								(*(_vItemHUD.begin() + i))->getImg()->getFrameHeight()));
						}
					}
				break;
			}
		}
	}
}

void UIManager::plusItemHUD(ITEMTYPE itemType)
{
	for (int j = 0; j < _vItemHUD.size(); ++j)
	{
		if ((*(_vItemHUD.begin() + j))->getItemType() == itemType)
		{
			return;
		}
	}

	for (int i = 0; i < _vItemHUD.size(); ++i)
	{
		if ((*(_vItemHUD.begin() + i))->getItemType() != NONE_TYPE) continue;

		(*(_vItemHUD.begin() + i))->setItemType(itemType);
		break;
	}

}

void UIManager::minusItemHUD(ITEMTYPE itemType)
{
	for (int i = 0; i < _vItemHUD.size(); ++i)
	{
		if (itemType == BODY) _isBody = false;
		if (itemType == HEAD) _isHead = false;
		if (itemType == FEET) _isFeet = false;
		if (itemType == TORCH) _isTorch = false;
		if (itemType == RING) _isRing = false;
		if (itemType == KEY) _isKey = false;
		if (itemType == ITEM) _isItem = false;
		if (itemType == PACK) _isPack = false;
		if (itemType == PACK2) _isPack2 = false;
		if (itemType == BOMB) _isBomb = false;
		if (itemType == ONOFF) _isOnOff = false;
		if (itemType == RELOAD) _isReload = false;
		if (itemType == THROW) _isThrow = false;
		if (itemType == PRESS) _isPress = false;
		if (itemType == HOLSTER) _isHolster = false;
		if (itemType == HOLSTER2) _isHolster2 = false;
		if (itemType == SPELL) _isSpell = false;
		if (itemType == SPELL2) _isSpell2 = false;
		if (itemType == SPELL3) _isSpell3 = false;

		if ((*(_vItemHUD.begin() + i))->getItemType() == itemType)
		{
			(*(_vItemHUD.begin() + i))->setItemType(NONE_TYPE);
			break;
		}
	}
}

void UIManager::renderItemHUD()
{
	for (int i = 0; i < _vItemHUD.size(); ++i)
	{
		if ((*(_vItemHUD.begin() + i))->getItemType() == NONE_TYPE) continue;

		(*(_vItemHUD.begin() + i))->render();

		if ((*(_vItemHUD.begin() + i))->getItemType() == ATTACK)
		{
			UIMANAGER->render("weapon", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}

		if ((*(_vItemHUD.begin() + i))->getItemType() == SHOVEL)
		{
			UIMANAGER->render("shovel", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}

		if ((*(_vItemHUD.begin() + i))->getItemType() == BOMB)
		{
			UIMANAGER->render("bomb", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}

		if ((*(_vItemHUD.begin() + i))->getItemType() == BODY)
		{
			UIMANAGER->render("body", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}

		if ((*(_vItemHUD.begin() + i))->getItemType() == TORCH)
		{
			UIMANAGER->render("torch", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}

		if ((*(_vItemHUD.begin() + i))->getItemType() == ITEM)
		{
			UIMANAGER->render("food", getMemDC(), (*(_vItemHUD.begin() + i))->getRect().left + 10, (*(_vItemHUD.begin() + i))->getRect().top + 20, 0, 0);
		}
	}
}

