#pragma once
#include "gameNode.h"

class introScene : public gameNode
{
private:
	bool _isSkip;		// ��Ʈ�ο��� ��ŵ�ϱ����� �Ұ�
	int _count;			// ������� ī��Ʈ���ְ� ��ŵ�����ϰ�

public:
	introScene();
	~introScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();	

};

