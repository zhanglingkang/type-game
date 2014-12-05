#pragma once
#include"CharManage.h"
#include<string>
//�����õ��Ľ�����
class View
{
public:
	View(void);
	~View(void);
	void Set(int xlength,int ylength,MyPoint leftUp);
	void AddMenu(std::string menuName,MyPoint menuPos,View *jumpView);//�ڽ��������һ���˵�
	void DisPlay();//��ʾ����ͬʱ���α궨λ��ĳ���˵���
	void Jump(MyPoint menuPos);//�����Ӧ�˵�����ת
	void OutText(std::string text,MyPoint point);//��point�����text;
	void ClearScrren();
	void SetColor(unsigned short color);
private:
	View & operator=(const View&){return *this;}
	View(const View&){} //��ֹ���ƺ͸�ֵ
private:
	unsigned short color;
	enum{maxmenunum=5};
	int menuNum;//�˽����еĲ˵���Ŀ
	std::string menuName[maxmenunum];//��Ӧ�˵�������
	MyPoint menuPos[maxmenunum]; ///��Ӧ�˵�����Ļ�ϵ�λ��
	View*jumpView[maxmenunum];  //ÿ���˵�Ҫ��ת�Ľ���
	int xlength,
		ylength;//����ĳ���
	MyPoint leftUp;//�������Ͻǵ�λ��
};

