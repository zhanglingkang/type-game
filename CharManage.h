#pragma once
#include"LinkList.cpp"
#include<string>
struct MyPoint
{
	int x,
		y;
	MyPoint(){}
	MyPoint(int x,int y)
	{
		this->x=x;
		this->y=y;
	}
	bool operator==(MyPoint point)
	{
		return (this->x==point.x)&&(this->y==point.y);
	}
	bool operator!=(MyPoint point)
	{
		return !(*this==point);
	}
	MyPoint&operator=(const MyPoint&point)
	{
		this->x=point.x;
		this->y=point.y;
		return *this;
	}
};
//管理屏幕上的字符类
class CharManage
{
public:
	CharManage(void);
	~CharManage(void);
	void Set(int xlength,int ylength,MyPoint leftUp);
	void Down();//屏幕上所有字符下移
	bool Delete(char ch);//从屏幕上删除ch，若不存在返回false
	void RandBorn(int n);//随机生成n个字符，且显示在界面最上方
	void Clear();//清空屏幕上所有字符
	void SetColor(unsigned short color);
private:
	int xlength,
		ylength;//界面的长宽
	unsigned short color;
	MyPoint leftUp;//界面左上角的位置
	std::string allChar;//屏幕上的所有字符
	LinkList<MyPoint> charPos;//所有字符在屏幕上的位置.
};

