#include "CharManage.h"
#include"GotoXY.h"
#include<iostream>
#include<ctime>
using namespace std;
CharManage::CharManage(void)
{
	this->color=10;
}
CharManage::~CharManage(void)
{
}
void CharManage::Set(int xlength,int ylength,MyPoint leftUp)
{
	this->xlength=xlength;
	this->ylength=ylength;
	this->leftUp=leftUp;
}
void CharManage::Down()
{
	this->SetColor(this->color);
	for(int i=0;i<this->allChar.length();++i)
	{
		MyPoint point=this->charPos.Get(i+1);
		GotoXY()(point);
		cout<<" ";
		if(++point.y>=leftUp.y+ylength-2)
			this->Delete(this->allChar[i]);
		else
		{
			GotoXY()(point);
			cout<<this->allChar[i];
			this->charPos.Update(i+1,point);
		}
	}
}
bool CharManage::Delete(char ch)
{
	int i;
	for(i=0;i<this->allChar.length();++i)
	{
		if(ch==this->allChar[i])
		{
			break;
		}
	}
	if(i==this->allChar.length())
		return false;
	GotoXY()(this->charPos.Get(i+1));
	cout<<" ";
	this->allChar.erase(i,1);
	this->charPos.Delete(i+1);
	return true;
}
void CharManage::RandBorn(int n)
{
	this->SetColor(this->color);
	for(int i=0;i<n;++i)
	{	
		MyPoint randPoint(rand()%(xlength-2)+leftUp.x+1,leftUp.y+1);
		char randChar=rand()%('z'-'a'+1)+'a';
		GotoXY()(randPoint);
		std::cout<<randChar;
		this->allChar+=randChar;
		this->charPos.Insert(this->allChar.length(),randPoint);
	}
}
void CharManage::Clear()
{
	for(int i=0;i<this->allChar.length();++i)
	{
		GotoXY()(this->charPos.Get(i+1));
		cout<<" ";
	}
	this->allChar="";
	this->charPos.Clear();
}
void CharManage::SetColor(unsigned short color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}