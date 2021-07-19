#pragma once
#include "gameNode.h"

#define TILEWIDTH 72
#define TILEHEIGHT 72


class tile : public gameNode
{
private:
	int _idX;
	int _idY;
	
	POINT _center;
	RECT _rc;
	//F = G + H 
	//F == 총 거리 비용 (TotalCost)
	//G == 시작점으로부터 현재 노드까지 경로비용(CostFromStart)
	//H == 현재노드로부터 도착점까지 경로비용(CostToGoal)

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen; // 갈수있는 타일인지 알아보자

	tile* _parentNode; //제일 상위 타일 

	COLORREF _color;
	HBRUSH   _brush;
	HPEN	 _pen;
	
	string _attribute;
	int _parentNodenumber;

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdX() { return _idX; }
	int getIdY() { return _idY; }
	RECT getRect() { return _rc; }
	float getTotalCost() { return _totalCost; }
	float getFromCost() { return _costFromStart; }
	float getToGoal() { return _costToGoal; }
	POINT getCenter() { return _center; }
	string getAttribute() { return _attribute; }
	tile* getParentNode() { return _parentNode; }
	bool getIsOpen() { return _isOpen; }
	int getparentNumber() { return _parentNodenumber; }

	void setIdX(int idx) { _idX = idx; }
	void setIdY(int idy) { _idY = idy; }
	void setRect(RECT rc) { _rc = rc; }
	void setCetner(POINT center) { _center = center; }
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	void setCostFromStart(float costFromStart) {  _costFromStart = costFromStart; }
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	void setParentNode(tile* t) { _parentNode = t; }
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	void setAttribute(string attribute) { _attribute = attribute; }
	void setparentNumber(int number) { _parentNodenumber = number; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

};

