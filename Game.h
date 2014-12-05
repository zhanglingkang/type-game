#pragma once
#include"View.h"
#include"CharManage.h"
#include   <windows.h>   
#include   <stdio.h>   
#include   <conio.h>
#include <conio.h>
class Game
{
public:
	Game(void);
	~Game(void);
	void Run();	

private:
	//����������Ӧ�Ĵ���.Ĭ����ʾ�ĵ�ǰ����
	void ProcessToMain();
	void ProcessToSetChoice();
	void ProcessToSetLevel();
	void ProcessToSetTime();
	void ProcessToGame();
	void ProcessToGameOver();
	void Init();//��������ĳ�ʼ��
	//�˺������������أ����̺߳����������ն�ʱ����Ϣ�����ɡ�
	static DWORD CALLBACK Thread(PVOID   pvoid);
	//���յ���ʱ����Ϣ�����Ĵ���
	static VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
private:	
	static int gameTime;//��Ϸʱ��
	static int gameLevel;//��Ϸ�Ѷ�
	static double count;//��ʱ
	static bool gameState;//��ʾ��Ϸ�����Ƿ���������
	static CharManage charManage;	
	static int totalCharNum;//һ��������ַ���
	static int hitCharNum;//������ַ���
	static int hitKeyBoard;//�ô���̴���
	int selectedView;//1,2,3,4,5,6�ֱ�������½���
	View mainView,
		setChoiceView,
		setTimeView,
		setLevelView,
		gameView,
		gameOverView;
	MyPoint DisplayTimePos;

};

