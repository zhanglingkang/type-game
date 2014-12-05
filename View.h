#pragma once
#include"CharManage.h"
#include<string>
//程序用到的界面类
class View
{
public:
	View(void);
	~View(void);
	void Set(int xlength,int ylength,MyPoint leftUp);
	void AddMenu(std::string menuName,MyPoint menuPos,View *jumpView);//在界面上添加一个菜单
	void DisPlay();//显示界面同时将游标定位到某个菜单上
	void Jump(MyPoint menuPos);//完成相应菜单的跳转
	void OutText(std::string text,MyPoint point);//在point处输出text;
	void ClearScrren();
	void SetColor(unsigned short color);
private:
	View & operator=(const View&){return *this;}
	View(const View&){} //禁止复制和赋值
private:
	unsigned short color;
	enum{maxmenunum=5};
	int menuNum;//此界面中的菜单数目
	std::string menuName[maxmenunum];//相应菜单的名字
	MyPoint menuPos[maxmenunum]; ///相应菜单在屏幕上的位置
	View*jumpView[maxmenunum];  //每个菜单要跳转的界面
	int xlength,
		ylength;//界面的长宽
	MyPoint leftUp;//界面左上角的位置
};

