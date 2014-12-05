#pragma once
#include <windows.h>
#include"CharManage.h"
class GotoXY
{
public:
	GotoXY(void);
	~GotoXY(void);
	void operator()(MyPoint point);
};

