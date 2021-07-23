#pragma once
#include "gameNode.h"
#include "mapGenerator.h"

class slime : public gameNode
{
protected:
	mapGenerator * _map;
	PLAYER_ENEMY_DIRECTION _direction;

	image * _img;
	RECT _rc;

	float _x, _y;	//���� ��ǥ�� //�÷��̾� ���� �߽� ��ǥ
	int _tileX; //���� �ִ� Ÿ�� x�ε���
	int _tileY; //���� �ִ� Ÿ�� y�ε���
	int _tileRenderX;	//���� ���� �� �����ͼ� �����ϱ� ����(������ �����ص�.. �׷��� ������ ���� ��Ƶ� ������ �÷��̾�� ���� ������ ��)
	int _tileRenderY;
	float _shadowX, _shadowY;


	int _hp;

	int _frameCount;
	int _frameIndex;
	int _currentFrameX, _currentFrameY;
	float _worldTime, _movingTime, _renderTime;

	float _gravity;
	float _jumpPower;


	bool _isMove;	//������?
	//������� ������
	bool _isMoveUp;
	bool _isMoveRight;

	bool _isTime;
	bool _toRender, _damageRender;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setArrangement();


	//get
	///////////////////////////////////////////////
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual float getShadowX() { return _shadowX; }
	virtual float getShadowY() { return _shadowY; }
	virtual image * getImage() { return _img; }
	inline RECT getRect() { return _rc; }

	virtual int getCurrentFrameX() { return _currentFrameX; }
	virtual int getCurrentFrameY() { return _currentFrameY; }


	//set
	///////////////////////////////////////////////
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }
	virtual void setShadowX(float shadowX) { _shadowX = shadowX; }
	virtual void setShadowY(float shadowY) { _shadowY = shadowY; }
	virtual void setImage(image * image) { _img = image; }
	virtual void setTileMapLink(mapGenerator* tileMap) { _map = tileMap; }

	virtual void setCurrentFrameX(int currentX) { _currentFrameX = currentX; }
	virtual void setCurrentFrameY(int currentY) { _currentFrameY = currentY; }

	//virtual void setRect(RECT rc) { _rc = rc; }
};

