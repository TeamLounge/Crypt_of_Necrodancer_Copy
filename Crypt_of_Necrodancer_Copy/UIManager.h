#pragma once
#include "gameNode.h"
#include "Heart.h"
#include "heartBeat.h"
#include "beatHeart.h"
#include "money.h"
#include "numberUI.h"
#include "diamond.h"
#include "X.h"
#include "itemHUD.h"
#include "missed.h"
#include <vector>

class objectManager;
class weapon;
class player;

class UIManager : public gameNode
{
private: 
	typedef vector<UI*>				vUI;
	typedef vector<UI*>::iterator	viUI;
private:
	vUI _vHeart;
	viUI _viHeart;

	vUI _vHeartBeatRight;
	viUI _viHeartBeatRight;

	vUI _vHeartBeatLeft;
	viUI _viHeartBeatLeft;

	vUI _vMoneyNumber;
	viUI _viMoneyNumber;

	vUI _vDiaNumber;
	viUI _viDiaNumber;

	vUI _vItemHUD;
	viUI _viItemHUD;

	vUI _vMissed;
	viUI _viMissed;

	beatHeart* _beatHeart;
	money* _money;
	diamond* _diamond;
	X* _moneyX;
	X* _diaX;

	objectManager* _om;
	weapon* _weapon;
	player* _player;

	bool _isPlayerDead;		//플레이어 죽었어?
	bool _isDeathSoundOn;	//죽음의 소리가 들렸어?
	bool _isGod;			//신이야? (무적모드)

	int _heartNum;
	float _elapsedSec;
	int _heartCnt;
	int _count;
	int _damagedTotalCnt;	// 총 데미지 누적
	int _heartTotalCnt;		// 총 체력
	int _plusHealNum;		// 체력 보충 숫자
	int _damagedNum;		// 데미지 숫자

	int _heartBeatNum;
	float _HBElapsedSec;
	float _heartBeatInterval;
	int _HBCnt;
	int _nextI, _nextJ;

	int _moneyNum;
	int _moneyHundred;   //100의 자리
	int _moneyTen;       //10의 자리
	int _moneyOne;       //1의 자리
	bool _isMoneyPlus;	//머니 합산했는지여부

	int _leftWidthCnt;  //왼쪽 가로 허드 갯수
	int _leftHeightCnt; //왼쪽 세로 허드 갯수
	int _rightHeightCnt; //오른쪽 세로 허드 갯수

	int _diaNum;
	int _diaHundred;   //100의 자리
	int _diaTen;       //10의 자리
	int _diaOne;       //1의 자리
	bool _isDiaPlus; // 다이아 합산했는지 여부

	bool _isBody;
	bool _isHead;							//헤드있는지확인용
	bool _isFeet;							//피트있는지확인용
	bool _isTorch;
	bool _isRing;
	bool _isKey;
	bool _isItem;
	bool _isPack;
	bool _isPack2;
	bool _isBomb;
	bool _isOnOff;
	bool _isReload;
	bool _isThrow;
	bool _isPress;
	bool _isHolster;
	bool _isHolster2;
	bool _isSpell;
	bool _isSpell2;
	bool _isSpell3;

	bool _isIntersectJudge;
	RECT _beatJudgement;
	int _judgeRange;

	float _beatSpeed; //하트 비트 스피드

	string _songName;

	//미스 갯수, 사거리, 
	int _missMax;		//미스 갯수
	float _missRange;	//미스 사거리
	int _missAlpha;		//미스 알파값
	float _fireX;
	float _fireY;
public:
	UIManager();
	~UIManager();

	HRESULT init(string songName, float speed, int judgeRange);
	void release();
	void update();
	void render();

	///////////////////////////////////
	//  #### 허트 UI 영역 #####
	//////////////////////////////////
	void setHeart(int heartNum);
	void updateHeart();
	void minusHeart(int damagedNum);
	void plusHeart(int plusHealNum);
	void renderHeart();

	//////////////////////////////////
	//  #### 하트비트 UI 영역 ######
	//////////////////////////////////
	void setHeartBeat(int heartBeatNum);
	void updateHeartBeat();
	void renderHeartBeat();

	/////////////////////////////////
	//  #### 머니 영역 ####
	/////////////////////////////////
	void setMoney();
	void updateMoney();
	void renderMoney();

	/////////////////////////////////
	//  #### 다이아몬드 영역 ####
	////////////////////////////////
	void setDiamond();
	void updateDiamond();
	void renderDiamond();

	/////////////////////////////////
	// #### 머니 넘버 영역 ####
	////////////////////////////////
	void setMoneyNumber();
	void updateMoneyNumber(int moneyNum, bool reset);
	void renderMoneyNumber();

	////////////////////////////////
	// ### 다이아 넘버 영역 ###
	///////////////////////////////
	void setDiaNumber();
	void updateDiaNumber(int diaNum, bool reset);
	void renderDiaNumber();

	///////////////////////////////
	// ### 아이템 HUD 영역 ###
	///////////////////////////////
	void setItemHUD();
	void updateItemHUD();
	void plusItemHUD(ITEMTYPE itemType);
	void minusItemHUD(ITEMTYPE itemType);
	void renderItemHUD();

	///////////////////////////////
	// ### miss 영역 ###
	///////////////////////////////
	void setMissed();
	void updateMissed();
	void renderMissed();
	void fireMissed(float fireX, float fireY);
	void moveMissed();


	///////////////////////////////
	// ###  게터, 세터 설정  ###
	///////////////////////////////
	void setMoneyNum(int moneyNum) { _moneyNum = moneyNum; }
	int getMoneyNum() { return _moneyNum; }

	void setIsMoneyPlus(bool isMoneyPlus) { _isMoneyPlus = isMoneyPlus; }
	bool getIsMoneyPlus() { return _isMoneyPlus; }

	void setIsDiaPlus(bool isDiaPlus) { _isDiaPlus = isDiaPlus; }
	bool getIsDiaPlus() { return _isDiaPlus; }

	vector<UI*> getVItemHUD() { return _vItemHUD; }
	vector<UI*>::iterator getVIItemHUD() { return _viItemHUD; }

	vector<UI*> getVHeart() { return _vHeart; }
	vector<UI*>::iterator getVIHeart() { return _viHeart; }

	void setOMMemoryAddressLink(objectManager* om) { _om = om; }
	void setWeaponMemoryAddressLink(weapon* weapon) { _weapon = weapon; }
	void setPlayerMemoryAddressLink(player* player) { _player = player; }

	bool getIsIntersectJudge() { return _isIntersectJudge; }

	void setBeatSpeed(float speed) { _beatSpeed = speed; }

	bool getIsPlayerDead() { return _isPlayerDead; }
	void setIsPlayerDead(bool isPlayerDead) { _isPlayerDead = isPlayerDead; }

	bool getIsGod() { return _isGod; }
	void setIsGod(bool isGod) { _isGod = isGod; }
};

