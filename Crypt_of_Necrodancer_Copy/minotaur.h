#pragma 
#include "minotaurAndDragon.h"
class minotaur : public minotaurAndDragon
{
private:
	bool isCursh , isRun;
public:
	HRESULT init(int playerIndexX, int playerIndexY);
	void update(int playerIndexX, int playerIndexY);
	void release();
	void render();
};

