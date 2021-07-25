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
	int _moneyHundred;   //100�� �ڸ�
	int _moneyTen;       //10�� �ڸ�
	int _moneyOne;       //1�� �ڸ�
	bool _isMoneyPlus;	//�Ӵ� �ջ��ߴ�������


	int _diaNum;
	int _diaHundred;   //100�� �ڸ�
	int _diaTen;       //10�� �ڸ�
	int _diaOne;       //1�� �ڸ�
	bool _isDiaPlus; // ���̾� �ջ��ߴ��� ����

	bool _isBody;
	bool _isHead;							//����ִ���Ȯ�ο�
	bool _isFeet;							//��Ʈ�ִ���Ȯ�ο�
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
	//  #### ��Ʈ UI ���� #####
	//////////////////////////////////
	void setHeart(int heartNum);
	void updateHeart();
	void renderHeart();

	//////////////////////////////////
	//  #### ��Ʈ��Ʈ UI ���� ######
	//////////////////////////////////
	void setHeartBeat(int heartBeatNum);
	void updaetHeartBeat(float speed);
	void renderHeartBeat();

	/////////////////////////////////
	//  #### �Ӵ� ���� ####
	/////////////////////////////////
	void setMoney();
	void updateMoney();
	void renderMoney();

	/////////////////////////////////
	//  #### ���̾Ƹ�� ���� ####
	////////////////////////////////
	void setDiamond();
	void updateDiamond();
	void renderDiamond();

	/////////////////////////////////
	// #### �Ӵ� �ѹ� ���� ####
	////////////////////////////////
	void setMoneyNumber();
	void updateMoneyNumber(int moneyNum, bool reset);
	void renderMoneyNumber();

	////////////////////////////////
	// ### ���̾� �ѹ� ���� ###
	///////////////////////////////
	void setDiaNumber();
	void updateDiaNumber(int diaNum, bool reset);
	void renderDiaNumber();

	///////////////////////////////
	// ### ������ HUD ���� ###
	///////////////////////////////
	void setItemHUD();
	void updateItemHUD();
	void plusItemHUD(ITEMTYPE itemType);
	void minusItemHUD(ITEMTYPE itemType);
	void renderItemHUD();


	///////////////////////////////
	// ###  ����, ���� ����  ###
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

