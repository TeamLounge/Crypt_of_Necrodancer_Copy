#include "stdafx.h"
#include "tile.h"
#include "aStarTest.h"

//¸â¹ö ÀÌ´Ï¼È¶óÀÌÁî
tile::tile()
	:_totalCost(0), _costFromStart(0),
	_costToGoal(0), _parentNode(NULL),_parentNodenumber(0),
	_idX(0), _idY(0), _isOpen(true) , _attribute("none")
{
}


tile::~tile()
{

}

HRESULT tile::init(int idX, int idY)
{
	_color = RGB(255,255, 255);
	_brush = CreateSolidBrush(_color);
	_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	_idX = idX;
	_idY = idY;
	_rc = _map->getRect(_idX, _idY);
	_center = PointMake((_rc.right+_rc.left)/2,(_rc.bottom+_rc.top)/2);
	return S_OK;
}

void tile::release()
{
	DeleteObject(_brush);
	DeleteObject(_pen);

}

void tile::update()
{

}

void tile::render()
{
	SelectObject(getMemDC(), (HBRUSH)_brush);
	FillRect(getMemDC(), &_rc, _brush);

	SelectObject(getMemDC(), (HPEN)_pen);
	Rectangle(getMemDC(), _rc);
}
