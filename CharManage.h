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
//������Ļ�ϵ��ַ���
class CharManage
{
public:
	CharManage(void);
	~CharManage(void);
	void Set(int xlength,int ylength,MyPoint leftUp);
	void Down();//��Ļ�������ַ�����
	bool Delete(char ch);//����Ļ��ɾ��ch���������ڷ���false
	void RandBorn(int n);//�������n���ַ�������ʾ�ڽ������Ϸ�
	void Clear();//�����Ļ�������ַ�
	void SetColor(unsigned short color);
private:
	int xlength,
		ylength;//����ĳ���
	unsigned short color;
	MyPoint leftUp;//�������Ͻǵ�λ��
	std::string allChar;//��Ļ�ϵ������ַ�
	LinkList<MyPoint> charPos;//�����ַ�����Ļ�ϵ�λ��.
};

