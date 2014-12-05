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
	//各个界面相应的处理.默认显示的当前界面
	void ProcessToMain();
	void ProcessToSetChoice();
	void ProcessToSetLevel();
	void ProcessToSetTime();
	void ProcessToGame();
	void ProcessToGameOver();
	void Init();//各个界面的初始化
	//此函数从网上下载，此线程函数用来接收定时器消息并分派。
	static DWORD CALLBACK Thread(PVOID   pvoid);
	//接收到定时器消息所作的处理
	static VOID CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime);
private:	
	static int gameTime;//游戏时间
	static int gameLevel;//游戏难度
	static double count;//计时
	static bool gameState;//表示游戏界面是否正在运行
	static CharManage charManage;	
	static int totalCharNum;//一共降落的字符数
	static int hitCharNum;//击落的字符数
	static int hitKeyBoard;//敲打键盘次数
	int selectedView;//1,2,3,4,5,6分别代表以下界面
	View mainView,
		setChoiceView,
		setTimeView,
		setLevelView,
		gameView,
		gameOverView;
	MyPoint DisplayTimePos;

};

