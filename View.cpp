
#include "View.h"
#include"GotoXY.h"
#include<iostream>

View::View(void)
{
	this->menuNum=0;
	this->color=9;
}
View::~View(void)
{
}
void View::Set(int xlength,int ylength,MyPoint leftUp)
{
	this->xlength=xlength;
	this->ylength=ylength;
	this->leftUp=leftUp;
}
void View::AddMenu(std::string menuNam,MyPoint menuPos,View *jumpView)
{
	this->menuName[this->menuNum]=menuNam;
	this->menuPos[this->menuNum]=menuPos;
	this->jumpView[this->menuNum++]=jumpView;
}
void View::DisPlay()
{
	this->SetColor(this->color);
	//打印第一行
	GotoXY()(MyPoint(leftUp.x,leftUp.y+1));
	for(int i=0;i<this->xlength;++i)
	{
		std::cout<<"-";
	}
	//打印最后一行
	GotoXY()(MyPoint(leftUp.x,leftUp.y+ylength-1));
	for( i=0;i<this->xlength;++i)
	{
		std::cout<<"-";
	}
	//打印左边
	GotoXY()(MyPoint(leftUp.x,leftUp.y+1));
	for(i=1;i<this->ylength-1;++i)
	{
		std::cout<<"|\n";
	}
	//打印右边	
	for( i=1;i<this->ylength-1;++i)
	{
		GotoXY()(MyPoint(leftUp.x+xlength-1,leftUp.y+i));
		std::cout<<"|";
	}
	//打印菜单
	for(i=0;i<this->menuNum;++i)
	{
		GotoXY()(this->menuPos[i]);
		std::cout<<this->menuName[i];
	}
}
void View::Jump(MyPoint menuPos)
{
	int i;
	for(i=0;i<this->menuNum;++i)
	{
		if(this->menuPos[i]==menuPos)
			break;
	}
	if(i!=this->menuNum&&NULL!=this->jumpView[i])
	{
		system("cls");
		this->jumpView[i]->DisPlay();
	}
}
void View::OutText(std::string text,MyPoint point)
{
	GotoXY()(point);
	std::cout<<text;
}
void View::ClearScrren()
{
	//清除第一行
	GotoXY()(this->leftUp);
	for(int i=0;i<this->xlength;++i)
	{
		std::cout<<" ";
	}
	//清除最后一行
	GotoXY()(MyPoint(leftUp.x,leftUp.y+ylength-1));
	for( i=0;i<this->xlength;++i)
	{
		std::cout<<" ";
	}
	//清除左边
	GotoXY()(MyPoint(leftUp.x,leftUp.y+1));
	for( i=1;i<this->ylength-1;++i)
	{
		std::cout<<" \n";
	}
	//清除右边	
	for( i=1;i<this->ylength-1;++i)
	{
		GotoXY()(MyPoint(leftUp.x+xlength-1,leftUp.y+i));
		std::cout<<" ";
	}
	//清除菜单
	for(i=0;i<this->menuNum;++i)
	{
		GotoXY()(this->menuPos[i]);
		std::cout<<"          ";
	}
}
void View::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}