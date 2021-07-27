#include "stdafx.h"
#include "enemyManager.h"


HRESULT enemyManager::init()
{

	setWhiteSkeleton();
	setGreenSkeleton();
	setBlackSkeleton();

	setSlimeGreen();
	setSlimeGold();
	setSlimeBlue();

	setGhost();

	setMimic();

	setMonkeyBasic();
	//setMonkeyWhite();

	setMinotaur();

	setZombie();

	//setRedDragon();
	attackoff = false;
	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	//여기는 무기공격판정렉트 계속 받는곳
	_vCollision = _weapon->getVCollision();
	_viCollision = _weapon->getVICollision();
	_weaponName = _weapon->getWeaponName();

	updateWhiteSkeleton();
	updateGreenSkeleton();
	updateBlackSkeleton();

	updateMimic();

	updateGhost();

	updateSlimeGreen();
	updateSlimeGold();
	updateSlimeBlue();

	updateMonkeyBasic();
	//updateMonkeyWhite();

	updateMinotaur();

	updateZombie();

	//updateRedDragon();
	_player->setAttack(false);
}

void enemyManager::render()
{

	renderWhiteSkeleton();
	renderGreenSkeleton();
	renderBlackSkeleton();

	renderMimic();

	renderGhost();

	renderSlimeGreen();
	renderSlimeGold();
	renderSlimeBlue();

	renderMonkeyBasic();
	//renderMonkeyWhite();

	renderMinotaur();

	renderZombie();

	//renderRedDragon();
}

HRESULT enemyManager::bossRoomInit()
{
	setGhostBossRoom(3, 8,true);
	setGhostBossRoom(9, 8, true);
	setGhostBossRoom(3, 12, true);
	setGhostBossRoom(9, 12, true);
	setDeathMetal();
	_isboss = true;
	return S_OK;
}

void enemyManager::bossRoomRelease()
{

}

void enemyManager::bossRoomUpdate()
{
	//여기는 무기공격판정렉트 계속 받는곳
	_vCollision = _weapon->getVCollision();
	_viCollision = _weapon->getVICollision();
	_weaponName = _weapon->getWeaponName();

	if (_isboss)
	{
		updateDeathMetal();
		if (_deathMetal->getHp()<=6 && _deathMetal->getHp()>=3)
		{
			if (_deathMetal->getIsAction())
			{
				if (_deathMetal->getHp() == 5 || _deathMetal->getHp() == 6)
				{
					setWhiteSkeleton(true);
				}
				else if (_deathMetal->getHp() == 3 || _deathMetal->getHp() == 4)
				{
					setGreenSkeleton(true);
				}
				_deathMetal->setIsAction(false);
			}
		}
		if (!_vGhost.empty())
		{
			updateGhost();
		}
		if (!_vWitheSkeleton.empty())
		{
			updateWhiteSkeleton();
		}
		if (!_vGreenSkeleton.empty())
		{
			updateGreenSkeleton();
		}
		if (!_isboss)
		{
			delete _deathMetal;
			
			for (int i = _map->getRoom()[1].y; i < _map->getRoom()[1].y + _map->getRoom()[1].height; ++i)
			{
				for (int j = _map->getRoom()[1].x; j < _map->getRoom()[1].x + _map->getRoom()[1].width; ++j)
				{
					_map->setIsEnemy(j, i, false);
				}
			}
			_vWitheSkeleton.clear();
			_vGreenSkeleton.clear();
			
			_map->setTileObject(4, 5, OBJ_NONE);
			_map->setTileObject(5, 5, OBJ_NONE);
			_map->setTileObject(6, 5, OBJ_NONE);
			_map->setTileObject(7, 5, OBJ_NONE);
			_map->setTileObject(8, 5, OBJ_NONE);
		}
	}
	_player->setAttack(false);
}

void enemyManager::bossRoomRender()
{
	if (_isboss)
	{
		renderDeathMetal();
		if (!_vGhost.empty())
		{
			renderGhost();
		}
		if (!_vWitheSkeleton.empty())
		{
			renderWhiteSkeleton();
		}
		if (!_vGreenSkeleton.empty())
		{
			renderGreenSkeleton();
		}
	}


}

void enemyManager::setWhiteSkeleton(bool boss)
{
	for (int i = 0; i < 3; i++)
	{
		whiteSkeleton* _skeleton = new whiteSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY() , boss);
		_vWitheSkeleton.emplace_back(_skeleton);
	}
}
void enemyManager::updateWhiteSkeleton()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end();)
	{
		if (_player->getAttack())
		{//플레이어 공격!
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viWitheSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viWitheSkeleton)->setHp((*_viWitheSkeleton)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viWitheSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viWitheSkeleton)->setHp((*_viWitheSkeleton)->getHp() - 1);
					}
				}
			}
		}
		//만약에 해당에너미가 hp=0이라면?
		if ((*_viWitheSkeleton)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viWitheSkeleton)->getX(), (*_viWitheSkeleton)->getY(), false);
			//이거 삭제!
			_viWitheSkeleton = _vWitheSkeleton.erase(_viWitheSkeleton);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viWitheSkeleton)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이	
			++_viWitheSkeleton;
		}
	}
}
void enemyManager::renderWhiteSkeleton()
{
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->render();
	}
}

void enemyManager::setGreenSkeleton(bool boss)
{
	for (int i = 0; i < 3; i++)
	{
		greenSkeleton* _skeleton = new greenSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY(), boss);
		_vGreenSkeleton.emplace_back(_skeleton);
	}

}
void enemyManager::updateGreenSkeleton()
{
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end();)
	{//플레이어 공격!
			//공격렉트중에
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viGreenSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viGreenSkeleton)->setHp((*_viGreenSkeleton)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viGreenSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viGreenSkeleton)->setHp((*_viGreenSkeleton)->getHp() - 1);
					}
				}
			}
		}
		//만약에 해당에너미가 hp=0이라면?
		if ((*_viGreenSkeleton)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viGreenSkeleton)->getX(), (*_viGreenSkeleton)->getY(), false);
			//이거 삭제!
			_viGreenSkeleton = _vGreenSkeleton.erase(_viGreenSkeleton);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viGreenSkeleton)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viGreenSkeleton;
		}
	}
}
void enemyManager::renderGreenSkeleton()
{
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->render();
	}
}

void enemyManager::setBlackSkeleton()
{
	for (int i = 0; i < 3; i++)
	{
		blackSkeleton* _skeleton = new blackSkeleton;
		_skeleton->setTileMapLinK(_map);
		_skeleton->init(_player->getTileX(), _player->getTileY());
		_vBlackSkeleton.emplace_back(_skeleton);
	}
}
void enemyManager::updateBlackSkeleton()
{
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end();)
	{//플레이어 공격!
			//공격렉트중에
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viBlackSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viBlackSkeleton)->setHp((*_viBlackSkeleton)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viBlackSkeleton)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viBlackSkeleton)->setHp((*_viBlackSkeleton)->getHp() - 1);
					}
				}
			}
		}
		//만약에 해당에너미가 hp=0이라면?
		if ((*_viBlackSkeleton)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viBlackSkeleton)->getX(), (*_viBlackSkeleton)->getY(), false);
			//이거 삭제!
			_viBlackSkeleton = _vBlackSkeleton.erase(_viBlackSkeleton);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viBlackSkeleton)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viBlackSkeleton;
		}
	}
}
void enemyManager::renderBlackSkeleton()
{
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->render();
	}
}

void enemyManager::bosspatten()
{
	_deathMetal->update(_player->getTileX(), _player->getTileX());
}

void enemyManager::setSlimeGreen()
{
	for (int i = 0; i < 5; i++)
	{
		slimeGreen* _slimeGreen = new slimeGreen;
		_slimeGreen->setTileMapLink(_map);
		_slimeGreen->init(_player->getTileX(), _player->getTileY());
		_vSlimeGreen.push_back(_slimeGreen);		//emplace_back..?
	}
}
void enemyManager::updateSlimeGreen()
{
	for (_viSlimeGreen = _vSlimeGreen.begin(); _viSlimeGreen != _vSlimeGreen.end();)
	{
		if (_player->getAttack())
		{//플레이어 공격!
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeGreen)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viSlimeGreen)->setHp((*_viSlimeGreen)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeGreen)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viSlimeGreen)->setHp((*_viSlimeGreen)->getHp() - 1);
					}
				}
			}
		}
		//만약에 해당에너미가 hp=0이라면?
		if ((*_viSlimeGreen)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viSlimeGreen)->getTileX(), (*_viSlimeGreen)->getTileY(), false);
			//이거 삭제!
			_viSlimeGreen = _vSlimeGreen.erase(_viSlimeGreen);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viSlimeGreen)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viSlimeGreen;
		}
	}

}
void enemyManager::renderSlimeGreen()
{
	for (_viSlimeGreen = _vSlimeGreen.begin(); _viSlimeGreen != _vSlimeGreen.end(); ++_viSlimeGreen)
	{
		(*_viSlimeGreen)->render();
	}
}

void enemyManager::setSlimeGold()
{
	for (int i = 0; i < 3; i++)
	{
		slimeGold* _slimeGold = new slimeGold;
		_slimeGold->setTileMapLink(_map);
		_slimeGold->init(_player->getTileX(), _player->getTileY());
		_vSlimeGold.push_back(_slimeGold);
	}
}
void enemyManager::updateSlimeGold()
{
	for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end();)
	{
		if (_player->getAttack())
		{//플레이어 공격!
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeGold)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viSlimeGold)->setHp((*_viSlimeGold)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeGold)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viSlimeGold)->setHp((*_viSlimeGold)->getHp() - 1);
					}
				}
			}
		}//만약에 해당에너미가 hp=0이라면?
		if ((*_viSlimeGold)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viSlimeGold)->getTileX(), (*_viSlimeGold)->getTileY(), false);
			//이거 삭제!
			_viSlimeGold = _vSlimeGold.erase(_viSlimeGold);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viSlimeGold)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viSlimeGold;
		}
	}

}
void enemyManager::renderSlimeGold()
{
	for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->render();
	}
}

void enemyManager::setSlimeBlue()
{
	for (int i = 0; i < 4; i++)
	{
		slimeBlue* _slimeBlue = new slimeBlue;
		_slimeBlue->setTileMapLink(_map);
		_slimeBlue->init(_player->getTileX(), _player->getTileY());
		_vSlimeBlue.push_back(_slimeBlue);
	}
}
void enemyManager::updateSlimeBlue()
{

	for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end();)
	{
		if (_player->getAttack())
		{//플레이어 공격!
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeBlue)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viSlimeBlue)->setHp((*_viSlimeBlue)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{	//닿앗다면?
					if (IntersectRect(&rc, &(*_viSlimeBlue)->getRect(), &_viCollision->rc))
					{
						(*_viSlimeBlue)->setHp((*_viSlimeBlue)->getHp() - 1);
						
					}
				}
			}
		}//만약에 해당에너미가 hp=0이라면?
		if ((*_viSlimeBlue)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viSlimeBlue)->getTileX(), (*_viSlimeBlue)->getTileY(), false);
			//이거 삭제!
			_viSlimeBlue = _vSlimeBlue.erase(_viSlimeBlue);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viSlimeBlue)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viSlimeBlue;
		}
	}

}
void enemyManager::renderSlimeBlue()
{
	for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->render();
	}
}



void enemyManager::setGhost()
{
	for (int i = 0; i < 1; i++)
	{
		ghost* _ghost = new ghost;
		_ghost->setTileMapLinK(_map);
		_ghost->init(_player->getTileX(), _player->getTileY());
		_vGhost.emplace_back(_ghost);
	}
}
void enemyManager::setGhostBossRoom(int x, int y, bool boss)
{
	ghost* _ghost = new ghost;
	_ghost->setTileMapLinK(_map);
	_ghost->init(_player->getTileX(), _player->getTileY(), x, y, boss);
	_vGhost.emplace_back(_ghost);
}
void enemyManager::updateGhost()
{
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end();)
	{
		if (_player->getAttack() && (*_viGhost)->getIsFind())
		{//플레이어 공격! && 고스트와 미믹은 기믹이 붙어야 되기 때문에 미믹이 발견 했는지도 추가가 됫어용
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viGhost)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viGhost)->setHp((*_viGhost)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viGhost)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viGhost)->setHp((*_viGhost)->getHp() - 1);

					}
				}
			}
		}
		//만약에 해당에너미가 hp=0이라면?
		if ((*_viGhost)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viGhost)->getX(), (*_viGhost)->getY(), false);
			//이거 삭제!
			_viGhost = _vGhost.erase(_viGhost);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viGhost)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viGhost;
		}
	}
}
void enemyManager::renderGhost()
{
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		(*_viGhost)->render();
	}
}

void enemyManager::setMimic()
{
	for (int i = 0; i < 1; i++)
	{
		mimic* _mimic = new mimic;
		_mimic->setTileMapLinK(_map);
		_mimic->init(_player->getTileX(), _player->getTileY());
		_vMimic.emplace_back(_mimic);
	}
}
void enemyManager::updateMimic()
{

	for (_viMimic = _vMimic.begin(); _viMimic != _vMimic.end();)
	{
		if (_player->getAttack() && (*_viMimic)->getIsFind())
		{//플레이어 공격! && 고스트와 미믹은 기믹이 붙어야 되기 때문에 미믹이 발견 했는지도 추가가 됫어용
			//공격렉트중에
			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;//혹시 무기가?....
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{//창?롱소드?레이피어?이라면?
					//닿앗다면?
					if (IntersectRect(&rc, &(*_viMimic)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viMimic)->setHp((*_viMimic)->getHp() - 1);
						//관통없이 하나만 해야하기 때문에 플레이어는 공격상태 꺼주자 
						_player->setAttack(false);
					}
				}
				else
				{//닿앗다면?
					if (IntersectRect(&rc, &(*_viMimic)->getRect(), &_viCollision->rc))
					{
						//까줍니다.
						(*_viMimic)->setHp((*_viMimic)->getHp() - 1);
					}
				}
			}
		}//만약에 해당에너미가 hp=0이라면?
		if ((*_viMimic)->getHp() == 0)
		{
			//에너미 map에 없애주고
			_map->setIsEnemy((*_viMimic)->getX(), (*_viMimic)->getY(), false);
			//이거 삭제!
			_viMimic = _vMimic.erase(_viMimic);
		}
		else
		{
			//만약에 아니면 이거 업데이트해라 
			(*_viMimic)->update(_player->getTileX(), _player->getTileY());
			//다음꺼 오라이
			++_viMimic;
		}
	}

}
void enemyManager::renderMimic()
{
	for (_viMimic = _vMimic.begin(); _viMimic != _vMimic.end(); ++_viMimic)
	{
		(*_viMimic)->render();
	}
}

void enemyManager::setMonkeyBasic()
{
	for (int i = 0; i < 1; i++)
	{
		monkeyBasic* _monkey = new monkeyBasic;
		_monkey->setTileMapLinK(_map);
		_monkey->init(_player->getTileX(), _player->getTileY());
		_vMonkeyBasic.emplace_back(_monkey);
	}
}
void enemyManager::updateMonkeyBasic()
{
	for (_viMonkeyBasic = _vMonkeyBasic.begin(); _viMonkeyBasic != _vMonkeyBasic.end();)
	{
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{
					if (IntersectRect(&rc, &(*_viMonkeyBasic)->getRect(), &_viCollision->rc))
					{
						(*_viMonkeyBasic)->setHp((*_viMonkeyBasic)->getHp() - 1);
						_player->setAttack(false);
					}
				}
				else
				{
					if (IntersectRect(&rc, &(*_viMonkeyBasic)->getRect(), &_viCollision->rc))
					{
						(*_viMonkeyBasic)->setHp((*_viMonkeyBasic)->getHp() - 1);
					}
				}
			}
		}
		if ((*_viMonkeyBasic)->getHp() == 0)
		{
			_map->setIsEnemy((*_viMonkeyBasic)->getX(), (*_viMonkeyBasic)->getY(), false);
			_viMonkeyBasic = _vMonkeyBasic.erase(_viMonkeyBasic);
		}
		else
		{
			(*_viMonkeyBasic)->update(_player->getTileX(), _player->getTileY());
			++_viMonkeyBasic;
		}
	}

}
void enemyManager::renderMonkeyBasic()
{
	for (_viMonkeyBasic = _vMonkeyBasic.begin(); _viMonkeyBasic != _vMonkeyBasic.end(); ++_viMonkeyBasic)
	{
		(*_viMonkeyBasic)->render();
	}
}

void enemyManager::setMonkeyWhite()
{
	for (int i = 0; i < 1; i++)
	{
		monkeyWhite* _monkey = new monkeyWhite;
		_monkey->setTileMapLinK(_map);
		_monkey->init(_player->getTileX(), _player->getTileY());
		_vMonkeyWhite.emplace_back(_monkey);
	}
}
void enemyManager::updateMonkeyWhite()
{
	for (_viMonkeyWhite = _vMonkeyWhite.begin(); _viMonkeyWhite != _vMonkeyWhite.end();)
	{
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{
					if (IntersectRect(&rc, &(*_viMonkeyWhite)->getRect(), &_viCollision->rc))
					{
						(*_viMonkeyWhite)->setHp((*_viMonkeyWhite)->getHp() - 1);
						_player->setAttack(false);
					}
				}
				else
				{
					if (IntersectRect(&rc, &(*_viMonkeyWhite)->getRect(), &_viCollision->rc))
					{
						(*_viMonkeyWhite)->setHp((*_viMonkeyWhite)->getHp() - 1);
					}
				}
			}
		}
		if ((*_viMonkeyBasic)->getHp() == 0)
		{
			_map->setIsEnemy((*_viMonkeyWhite)->getX(), (*_viMonkeyWhite)->getY(), false);
			_viMonkeyWhite = _vMonkeyWhite.erase(_viMonkeyWhite);
		}
		else
		{
			(*_viMonkeyWhite)->update(_player->getTileX(), _player->getTileY());
			++_viMonkeyWhite;
		}
	}
}
void enemyManager::renderMonkeyWhite()
{
	for (_viMonkeyWhite = _vMonkeyWhite.begin(); _viMonkeyWhite != _vMonkeyWhite.end(); ++_viMonkeyWhite)
	{
		(*_viMonkeyWhite)->render();
	}
}

void enemyManager::setMinotaur()
{
	for (int i = 0; i < 1; i++)
	{
		minotaur* _minotaur = new minotaur;
		_minotaur->setTileMapLinK(_map);
		_minotaur->init(_player->getTileX(), _player->getTileY());
		_vMinotaur.emplace_back(_minotaur);
	}
}
void enemyManager::updateMinotaur()
{
	for (_viMinotaur = _vMinotaur.begin(); _viMinotaur != _vMinotaur.end();)
	{
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{
					if (IntersectRect(&rc, &(*_viMinotaur)->getRect(), &_viCollision->rc))
					{
						(*_viMinotaur)->setHp((*_viMinotaur)->getHp() - 1);
						_player->setAttack(false);
					}
				}
				else
				{
					if (IntersectRect(&rc, &(*_viMinotaur)->getRect(), &_viCollision->rc))
					{
						(*_viMinotaur)->setHp((*_viMinotaur)->getHp() - 1);
					}
				}
			}
		}
		if ((*_viMinotaur)->getHp() == 0)
		{
			_map->setIsEnemy((*_viMinotaur)->getX(), (*_viMinotaur)->getY(), false);
			_viMinotaur = _vMinotaur.erase(_viMinotaur);
		}
		else
		{
			(*_viMinotaur)->update(_player->getTileX(), _player->getTileY());
			++_viMinotaur;
		}
	}

}
void enemyManager::renderMinotaur()
{
	for (_viMinotaur = _vMinotaur.begin(); _viMinotaur != _vMinotaur.end(); ++_viMinotaur)
	{
		(*_viMinotaur)->render();
	}
}

void enemyManager::setZombie()
{
	for (int i = 0; i < 3; i++)
	{
		zombie* _zombie = new zombie;
		_zombie->setTileMapLink(_map);
		_zombie->init(_player->getTileX(), _player->getTileY());
		_vZombie.push_back(_zombie);
	}
}

void enemyManager::updateZombie()
{
	for (_viZombie = _vZombie.begin(); _viZombie != _vZombie.end();)
	{
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{
					if (IntersectRect(&rc, &(*_viZombie)->getRect(), &_viCollision->rc))
					{
						(*_viZombie)->setHp((*_viZombie)->getHp() - 1);
						_player->setAttack(false);
					}
				}
				else
				{
					if (IntersectRect(&rc, &(*_viZombie)->getRect(), &_viCollision->rc))
					{
						(*_viZombie)->setHp((*_viZombie)->getHp() - 1);
					}
				}
			}
		}
		if ((*_viZombie)->getHp() == 0)
		{
			_map->setIsEnemy((*_viZombie)->getTileX(), (*_viZombie)->getTileY(), false);
			_viZombie = _vZombie.erase(_viZombie);
		}
		else
		{
			(*_viZombie)->update(_player->getTileX(), _player->getTileY());
			++_viZombie;
		}
	}

}

void enemyManager::renderZombie()
{
	for (_viZombie = _vZombie.begin(); _viZombie != _vZombie.end(); ++_viZombie)
	{
		(*_viZombie)->render();
	}
}

void enemyManager::setRedDragon()
{
	for (int i = 0; i < 1; i++)
	{
		redDragon* _redDragon = new redDragon;
		_redDragon->setTileMapLinK(_map);
		_redDragon->init(_player->getTileX(), _player->getTileY());
		_vRedDragon.push_back(_redDragon);
	}
}

void enemyManager::updateRedDragon()
{
	for (_viRedDragon = _vRedDragon.begin(); _viRedDragon != _vRedDragon.end();)
	{
		if (_player->getAttack()) {

			for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
			{
				RECT rc;
				if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
				{
					if (IntersectRect(&rc, &(*_viRedDragon)->getRect(), &_viCollision->rc))
					{
						(*_viRedDragon)->setHp((*_viRedDragon)->getHp() - 1);
						_player->setAttack(false);
					}
				}
				else
				{
					if (IntersectRect(&rc, &(*_viRedDragon)->getRect(), &_viCollision->rc))
					{
						(*_viRedDragon)->setHp((*_viRedDragon)->getHp() - 1);
					}
				}
			}
		}
		if ((*_viRedDragon)->getHp() == 0)
		{
			_map->setIsEnemy((*_viRedDragon)->getX(), (*_viRedDragon)->getY(), false);
			_viRedDragon = _vRedDragon.erase(_viRedDragon);
		}
		else
		{
			(*_viRedDragon)->update(_player->getTileX(), _player->getTileY());
			++_viRedDragon;
		}
	}
}

void enemyManager::renderRedDragon()
{
	for (_viRedDragon = _vRedDragon.begin(); _viRedDragon != _vRedDragon.end(); ++_viRedDragon)
	{
		(*_viRedDragon)->render();
	}
}

void enemyManager::setEnemySpeed(float speed)
{
	for (_viSlimeGreen = _vSlimeGreen.begin(); _viSlimeGreen != _vSlimeGreen.end(); ++_viSlimeGreen)
	{
		(*_viSlimeGreen)->setBeatSpeed(speed);
	}
	for (_viSlimeGold = _vSlimeGold.begin(); _viSlimeGold != _vSlimeGold.end(); ++_viSlimeGold)
	{
		(*_viSlimeGold)->setBeatSpeed(speed);
	}
	for (_viSlimeBlue = _vSlimeBlue.begin(); _viSlimeBlue != _vSlimeBlue.end(); ++_viSlimeBlue)
	{
		(*_viSlimeBlue)->setBeatSpeed(speed);
	}
	for (_viWitheSkeleton = _vWitheSkeleton.begin(); _viWitheSkeleton != _vWitheSkeleton.end(); ++_viWitheSkeleton)
	{
		(*_viWitheSkeleton)->setBeatSpeed(speed);
	}
	for (_viGreenSkeleton = _vGreenSkeleton.begin(); _viGreenSkeleton != _vGreenSkeleton.end(); ++_viGreenSkeleton)
	{
		(*_viGreenSkeleton)->setBeatSpeed(speed);
	}
	for (_viBlackSkeleton = _vBlackSkeleton.begin(); _viBlackSkeleton != _vBlackSkeleton.end(); ++_viBlackSkeleton)
	{
		(*_viBlackSkeleton)->setBeatSpeed(speed);
	}
	for (_viGhost = _vGhost.begin(); _viGhost != _vGhost.end(); ++_viGhost)
	{
		(*_viGhost)->setBeatSpeed(speed);
	}
	for (_viMimic = _vMimic.begin(); _viMimic != _vMimic.end(); ++_viMimic)
	{
		(*_viMimic)->setBeatSpeed(speed);
	}
	for (_viMonkeyBasic = _vMonkeyBasic.begin(); _viMonkeyBasic != _vMonkeyBasic.end(); ++_viMonkeyBasic)
	{
		(*_viMonkeyBasic)->setBeatSpeed(speed);
	}
	for (_viMonkeyWhite = _vMonkeyWhite.begin(); _viMonkeyWhite != _vMonkeyWhite.end(); ++_viMonkeyWhite)
	{
		(*_viMonkeyWhite)->setBeatSpeed(speed);
	}
	for (_viMinotaur = _vMinotaur.begin(); _viMinotaur != _vMinotaur.end(); ++_viMinotaur)
	{
		(*_viMinotaur)->setBeatSpeed(speed);
	}
	for (_viZombie = _vZombie.begin(); _viZombie != _vZombie.end(); ++_viZombie)
	{
		(*_viZombie)->setBeatSpeed(speed);
	}
	for (_viRedDragon = _vRedDragon.begin(); _viRedDragon != _vRedDragon.end(); ++_viRedDragon)
	{
		(*_viRedDragon)->setBeatSpeed(speed);
	}
}

void enemyManager::setDeathMetal()
{
	_deathMetal = new deathMetal;
	_deathMetal->setTileMapLinK(_map);
	_deathMetal->init(_player->getTileX(), _player->getTileY());
}

void enemyManager::updateDeathMetal()
{

	if (_player->getAttack()) {

		for (_viCollision = _vCollision.begin(); _viCollision != _vCollision.end(); ++_viCollision)
		{
			RECT rc;
			if (_weaponName == "spear" || _weaponName == "longSword" || _weaponName == "rapier")
			{
				if (IntersectRect(&rc, &_deathMetal->getRect(), &_viCollision->rc))
				{
					if (_deathMetal->getHp() >= 7)
					{
						if (!((_player->getDirection() == LEFT && _deathMetal->getJudgMundetDirection() == RIGHT) ||
							(_player->getDirection() == RIGHT && _deathMetal->getJudgMundetDirection() == LEFT) ||
							(_player->getDirection() == UP && _deathMetal->getJudgMundetDirection() == DOWN) ||
							(_player->getDirection() == DOWN && _deathMetal->getJudgMundetDirection() == UP)))
						{
							_deathMetal->setHp(_deathMetal->getHp() - 1);
							_deathMetal->setIsDamaged(true);
							_player->setAttack(false);
						}
					}
					else
					{
						_deathMetal->setHp(_deathMetal->getHp() - 1);
						_deathMetal->setIsDamaged(true);
						_player->setAttack(false);
					}

				}
			}
			else
			{
				if (IntersectRect(&rc, &_deathMetal->getRect(), &_viCollision->rc))
				{
					if (_deathMetal->getHp() >= 7)
					{
						if (!((_player->getDirection() == LEFT && _deathMetal->getJudgMundetDirection() == RIGHT) ||
							(_player->getDirection() == RIGHT && _deathMetal->getJudgMundetDirection() == LEFT) ||
							(_player->getDirection() == UP && _deathMetal->getJudgMundetDirection() == DOWN) ||
							(_player->getDirection() == DOWN && _deathMetal->getJudgMundetDirection() == UP)))
						{
							_deathMetal->setHp(_deathMetal->getHp() - 1);
							_deathMetal->setIsDamaged(true);
							_player->setAttack(false);
						}
					}
					else
					{
						_deathMetal->setHp(_deathMetal->getHp() - 1);
						_deathMetal->setIsDamaged(true);
						_player->setAttack(false);
					}

				}
			}
		}
	}
	if (_deathMetal->getHp() == 0)
	{
		_map->setIsEnemy(_deathMetal->getX(), _deathMetal->getY(), false);
		_isboss = false;
	}
	else
	{
		_deathMetal->update(_player->getTileX(), _player->getTileY());
	}

}

void enemyManager::renderDeathMetal()
{
	_deathMetal->render();
}

void enemyManager::setGhostBossRoom()
{
	
}

void enemyManager::setWhiteSkeletonBossRoom()
{

}

void enemyManager::setGreenSkeletonBossRoom()
{

}

