#pragma once
#include "gameNode.h"

class splashScene : public gameNode
{
private:
	image* _backGround;		 // ���� ��׶��� �̹���
	image* _splash;			 // ���÷��� �̹����� ���� ����
	int _alphaIdx;			 // ���İ��� �� ����
	int _count;				 // ���İ� ���̱����� ī��Ʈ
	int _alphaCount;		 // ���İ� ���̱����� ī��Ʈ2
	bool _isAlphaStart;		 // ���İ� ���̱����� ����

public:
	splashScene();
	~splashScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

