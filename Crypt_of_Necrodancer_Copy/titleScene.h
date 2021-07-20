#pragma once
#include "gameNode.h"


class titleScene : public gameNode
{
private:
	image* _title;
	image* _anyKey;

	float _y;			// �ƹ�Ű�� �������� y��
	int _count;			// �ƹ�Ű�� �������� y�� �����̵� �ø�����~
	int _alphaIdx;		// �ƹ�Ű�� �������� ���İ� �����Ϸ���

public:
	titleScene();
	~titleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

