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
#include <vector>

class objectManager;

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

	beatHeart* _beatHeart;
	money* _money;
	diamond* _diamond;
	X* _moneyX;
	X* _diaX;

	objectManager* _om;

	int _heartNum;
	float _elapsedSec;
	int _heartCnt;
	int _count;

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
public:
	UIManager();
	~UIManager();

	HRESULT init();
	void release();
	void update();
	void render();

	///////////////////////////////////
	//  #### 허트 UI 영역 #####
	//////////////////////////////////
	void setHeart(int heartNum);
	void updateHeart();
	void renderHeart();

	//////////////////////////////////
	//  #### 하트비트 UI 영역 ######
	//////////////////////////////////
	void setHeartBeat(int heartBeatNum);
	void updaetHeartBeat(float speed);
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

	void setOMMemoryAddressLink(objectManager* om) { _om = om; }
};

