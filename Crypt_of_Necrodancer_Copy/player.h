#pragma once
#include "gameNode.h"
#include "mapGenerator.h"
#include "vision.h"
#include "randomMap.h"
#include "enemyManager.h"
#include "UIManager.h"
#include "bomb.h"

#define SHADOWMARGIN 30
#define BODYMARGIN 17
#define BASICVISION 5
#define EFFECTVOLUME 0.6f

class weapon;
class shovel;
class enemyManager;

class player : public gameNode
{
private:
	RECT _head; //얼굴
	RECT _body; //몸통
	RECT _shadow; //그림자
	float _x, _y; //플레이어 몸통 중심 좌표

	int _tileX; //플레이어가 현재 있는 타일 x인덱스
	int _tileY; //플레이어가 현재 있는 타일 y인덱스
	int _tileRenderX;//렌더용 x인덱스
	int _tileRenderY;//렌더용 y인덱스
	RECT _tileRect; //현재 있는 타일 렉트
	string _headImageName; //머리 이미지 이름
	string _bodyImageName; //몸통 이미지 이름
	int _currentFrameX; //현재 프레임x
	int _currentFrameY; //현재 프레임y
	float _gravity;

	image* _miss;	//미스이미지 등록용
	bool _isMiss;	//미스했냐?
	float _missRange; //미스거리..
	float _missSpeed; //미스속도

	bool _isThrow; //던졌어??
	bool _isThrowReady; //던질준비됐어?

	bool _isHurtSoundOn; //맞는소리 냈어?

	mapGenerator* _map;

	vision* _vision;

	float _elapsedSec; //프레임 움직임 위해서
	bool _isMove;
	bool _isRush;
	bool _attack;
	PLAYER_ENEMY_DIRECTION _playerDirection;

	//zOrder용
	string _imgHeadName;
	string _imgBodyName;
	string _imgShadowName;

	//링크용
	weapon* _weapon;
	shovel* _shovel;

	bomb* _bomb;

	float _shopkeeperDistance;
	
	UIManager* _uiManager;

	int _alpha;
	bool _isAttacked;
	float _attackedElapsedTime;
	int _alphaCount;

	bool _isWall;
	bool _isTouchWall;

	float _shovelEffectElapsedTime;

	float _attackElapsedTime;
	string _foodName;

public:
	enemyManager* _em; //에너미 정보 가져오기

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(int tileX, int tileY);

	void damaged();
	void miss();
	void attackSound();
	void hurtSound();

	PLAYER_ENEMY_DIRECTION getDirection() { return _playerDirection; }
	void setDirection(PLAYER_ENEMY_DIRECTION dir) { _playerDirection = dir; }


	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }
	void setPlayerMapMemoryAddressLink(mapGenerator* map) { _map = map; };
	void setPlayerUIMemoryAddressLink(UIManager* ui) { _uiManager = ui; };
	void setupPlayerRect();
	void playerMovement(PLAYER_ENEMY_DIRECTION dir, int tileXIncreseRange, int tileYIncreseRange);


	int getTileX() { return _tileX; }
	int getTileY() { return _tileY; }

	void setTileX(int x) { _tileX = x; }
	void setTileY(int y) { _tileY = y; }

	bool getIsMove() { return _isMove; }
	bool getIsRush() { return _isRush; }
	void setIsMove(bool b) { _isMove = b; }

	int getRenderX() { return _tileRenderX; }
	int getRenderY() { return _tileRenderY; }

	RECT getTileRect() { return _tileRect; }

	bomb* getBomb() { return _bomb; }

	//겟타일 접근
	OBJECT getOBJ(int tileX, int tileY) { return _map->getTileObject(tileX, tileY); }

	//아이템링크
	void setWeaponMemoryAddressLink(weapon* weapon) { _weapon = weapon; }
	void setShovelMemoryAddressLink(shovel* shovel) { _shovel = shovel; }

	//바디 이미지 접근자 설정자
	string getBodyImageName() { return _bodyImageName; }
	void setBodyImageName(string s) { _bodyImageName = s; }

	vision* getVision() { return _vision; }
	
	bool getAttack() { return _attack; }
	void setAttack(bool attack) { _attack = attack; }

	void renderShovelEffect(int tileX, int tileY);

	bool getIsThrow() { return _isThrow; }
	void setIsThrow(bool isThrow) { _isThrow = isThrow; }

	bool getIsThrowReady() { return _isThrowReady; }
	void setIsThrowReady(bool isThrowReady) { _isThrowReady = isThrowReady; }

	RECT getShadowRect() { return _shadow; }

	void setFoodName(string food) { _foodName = food; }
	string getFoodName() { return _foodName; }
};

