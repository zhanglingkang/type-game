#include "Game.h"
#include"GotoXY.h"
#include<Windows.h>
#include<iostream>
#include<string>
using namespace std;
//全局成员
CRITICAL_SECTION cs;
//static 成员
VOID CALLBACK Game::TimerProc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{

	if(gameState)
	{		
		const int n=1;
		count+=200*gameLevel;
		EnterCriticalSection( & cs);
		charManage.Down();
		charManage.RandBorn(n);	
		LeaveCriticalSection( & cs);
		totalCharNum+=n;	
	}
}
DWORD CALLBACK  Game::Thread(PVOID   pvoid)   
{   
	MSG  msg;   
	PeekMessage(&msg,NULL,WM_USER,WM_USER,PM_NOREMOVE);   
	UINT  timerid=SetTimer(NULL,111,200*gameLevel,TimerProc);   
	BOOL  bRet;   
	while(   (bRet = GetMessage(&msg,NULL,0,0))!=   0)   
	{     
		if(bRet==-1)   
		{   
			//   handle   the   error   and   possibly   exit   
		}   
		else   
		{    
			TranslateMessage(&msg);     
			DispatchMessage(&msg);     
		}   
		if(count/1000>=60*gameTime)
			return 0;
	}   
	KillTimer(NULL,timerid);    
	return   0;   
}
int Game::gameLevel=3;
int Game::gameTime=1;
double Game::count=0.0;
bool Game::gameState=false;
int Game::totalCharNum=0;
int Game::hitCharNum=0;
int Game::hitKeyBoard=0;
CharManage Game::charManage;
//非static成员
Game::Game(void)
{
	totalCharNum=0;
	hitCharNum=0;
	hitKeyBoard=0;
	this->Init();
	this->selectedView=1;	
	this->mainView.DisPlay();
	this->mainView.OutText("Enter:",MyPoint(28,12));//将光标设置在开始菜单上
	InitializeCriticalSection( & cs);
}
Game::~Game(void)
{
}
void Game::Run()
{
	
	while(true)
	{
		switch(this->selectedView)
		{
		case 1:
			this->ProcessToMain();
			break;
		case 2:
			this->ProcessToSetChoice();
			break;
		case 3:
			this->ProcessToSetTime();
			break;
		case 4:
			this->ProcessToSetLevel();
			break;
		case 5:
			this->ProcessToGame();
			break;
		case 6:
			this->ProcessToGameOver();
			break;
		}
	}
}
void Game::ProcessToMain()
{
	MyPoint selectedMenuPos(28,12);
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if(72==ch&&MyPoint(28,10)!=selectedMenuPos)
			{
				this->mainView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y-=2;
				this->mainView.OutText("Enter:",selectedMenuPos);
			}
			else if(80==ch&&MyPoint(28,14)!=selectedMenuPos)
			{
				this->mainView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y+=2;
				this->mainView.OutText("Enter:",selectedMenuPos);
			}
			else if(13==ch)
			{
				this->mainView.Jump(MyPoint(selectedMenuPos.x+10,selectedMenuPos.y));
				if(10==selectedMenuPos.y)
				{
					this->setChoiceView.OutText("Enter:",MyPoint(28,10));
					this->selectedView=2;
					return;
				}
				if(12==selectedMenuPos.y)
				{
					this->gameView.OutText("暂停:Space重新开始:Enter返回:Esc",MyPoint(0,0));
					this->gameView.OutText("已用时间:",MyPoint(66,0));
					DisplayTimePos.x=75;
					DisplayTimePos.y=0;
					this->selectedView=5;
					return;
				}
				exit(0);
			}
		}
	}
}
void Game::ProcessToSetChoice()
{
	MyPoint selectedMenuPos(28,10);
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if(72==ch&&MyPoint(28,10)!=selectedMenuPos)
			{
				this->setChoiceView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y-=2;
				this->setChoiceView.OutText("Enter:",selectedMenuPos);
			}
			if(80==ch&&MyPoint(28,14)!=selectedMenuPos)
			{
				this->setChoiceView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y+=2;
				this->setChoiceView.OutText("Enter:",selectedMenuPos);
			}
			if(13==ch)
			{
				this->setChoiceView.Jump(MyPoint(selectedMenuPos.x+10,selectedMenuPos.y));
				if(10==selectedMenuPos.y)
				{
					this->setLevelView.OutText("Enter:",MyPoint(28,10));
					this->selectedView=4;
					return;
				}
				if(12==selectedMenuPos.y)
				{
					this->setTimeView.OutText("Enter:",MyPoint(28,10));
					this->selectedView=3;
					return;
				}
				else 
				{
					this->mainView.OutText("Enter:",MyPoint(28,12));
					this->selectedView=1;
					return;
				}
			}
		}
	}
}
void Game::ProcessToSetLevel()
{
	MyPoint selectedMenuPos(28,10);
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if(72==ch&&MyPoint(28,10)!=selectedMenuPos)
			{
				this->setLevelView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y-=2;
				this->setLevelView.OutText("Enter:",selectedMenuPos);
			}
			if(80==ch&&MyPoint(28,14)!=selectedMenuPos)
			{
				this->setLevelView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y+=2;
				this->setLevelView.OutText("Enter:",selectedMenuPos);
			}
			if(13==ch)
			{	
				if(10==selectedMenuPos.y)
				{
					gameLevel=3;//容易
				}
				else if(12==selectedMenuPos.y)
				{
					gameLevel=2;//中等
				}
				else
					gameLevel=1;//困难
				this->setLevelView.Jump(MyPoint(selectedMenuPos.x+10,selectedMenuPos.y));
				this->setChoiceView.OutText("Enter:",MyPoint(28,10));
				this->selectedView=2;
				return;
			}
		}
	}
}
void Game::ProcessToSetTime()
{
	MyPoint selectedMenuPos(28,10);
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if(72==ch&&MyPoint(28,10)!=selectedMenuPos)
			{
				this->setTimeView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y-=2;
				this->setTimeView.OutText("Enter:",selectedMenuPos);
			}
			if(80==ch&&MyPoint(28,14)!=selectedMenuPos)
			{
				this->setTimeView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y+=2;
				this->setTimeView.OutText("Enter:",selectedMenuPos);
			}
			if(13==ch)
			{	
				if(10==selectedMenuPos.y)
				{
					gameTime=1;
				}
				else if(12==selectedMenuPos.y)
				{
					gameTime=3;
				}
				else
					gameTime=5;
				this->setTimeView.Jump(MyPoint(selectedMenuPos.x+10,selectedMenuPos.y));
				this->setChoiceView.OutText("Enter:",MyPoint(28,10));
				this->selectedView=2;
				return;
			}
		}
	}
}
void Game::ProcessToGame()
{
	totalCharNum=0;
	hitCharNum=0;
	hitKeyBoard=0;
	EnterCriticalSection( & cs);
	this->charManage.Clear();
	LeaveCriticalSection( & cs);
	count=0;
	GotoXY()(this->DisplayTimePos);
	cout<<count<<"s";
	charManage.Set(80,24,MyPoint(0,1));
	//创建发送及处理定时器消息的线程
	this->gameState=true;
	DWORD   dwThreadId;   
	HANDLE   hThread = CreateThread(NULL,0,Thread,0,0,&dwThreadId);
	while(gameTime*60>count/1000)
	{	
		if(kbhit())
		{
			int ch=getch();
			if(' '==ch)
			{
				this->gameView.OutText("继续:Space重新开始:Enter返回:Esc",MyPoint(0,0));
				this->gameState=false;
			}
			else if(13==ch)
			{
				EnterCriticalSection( & cs);
				charManage.Clear();
				LeaveCriticalSection( & cs);
				count=0.0;
				totalCharNum=0;
				hitCharNum=0;
				hitKeyBoard=0;

			}
			else if(27==ch)
			{
				this->gameState=false;
				count=Game::gameTime*61*1000;
				system("cls");
				this->mainView.DisPlay();
				this->mainView.OutText("Enter:",MyPoint(28,12));//将光标设置在开始菜单上
				this->selectedView=1;
				return;
			}
			else 
			{
				++hitKeyBoard;
				EnterCriticalSection( & cs);
				if(charManage.Delete(ch))
					++hitCharNum;
				LeaveCriticalSection( & cs);
			}
		}
		EnterCriticalSection( & cs);
		GotoXY()(this->DisplayTimePos);
		cout<<(int)(count/1000)<<"s  ";
		LeaveCriticalSection( & cs);
		while(!this->gameState)
		{
			if(kbhit())
			{
				char ch=getch();
				if(' '==ch)
				{
					this->gameView.OutText("暂停:Space重新开始:Enter返回:Esc",MyPoint(0,0));
					this->gameState=true;
				}
			}
		}
	}
	this->gameState=false;
	system("cls");
	this->gameOverView.DisPlay();
	GotoXY()(MyPoint(28,8));
	cout<<"你的命中率为:"<<this->hitCharNum*1.0/this->totalCharNum;
	GotoXY()(MyPoint(28,10));
	cout<<"你的正确率为:"<<this->hitCharNum*1.0/this->hitKeyBoard;
	this->gameOverView.OutText("Enter:",MyPoint(28,12));
	this->selectedView=6;
}
void Game::ProcessToGameOver()
{
	MyPoint selectedMenuPos(28,12);
	while(true)
	{
		if(kbhit())
		{
			char ch=getch();
			if(72==ch&&12!=selectedMenuPos.y)
			{
				this->mainView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y-=2;
				this->mainView.OutText("Enter:",selectedMenuPos);
			}
			else if(80==ch&&14!=selectedMenuPos.y)
			{
				this->mainView.OutText("      ",selectedMenuPos);
				selectedMenuPos.y+=2;
				this->mainView.OutText("Enter:",selectedMenuPos);
			}
			else if(13==ch)
			{
				this->gameOverView.Jump(MyPoint(selectedMenuPos.x+10,selectedMenuPos.y));
				if(12==selectedMenuPos.y)
				{
					this->gameView.OutText("暂停:Space重新开始:Enter返回:Esc",MyPoint(0,0));
					this->gameView.OutText("已用时间:",MyPoint(66,0));
					DisplayTimePos.x=75;
					DisplayTimePos.y=0;
					this->selectedView=5;
					return;
				}
				else exit(0);
			}
		}
	}
}
void Game::Init()
{
	//游戏主界面
	mainView.Set(80,25,MyPoint(0,0));
	mainView.AddMenu("设置",MyPoint(38,10),&setChoiceView);
	mainView.AddMenu("开始",MyPoint(38,12),&gameView);
	mainView.AddMenu("退出",MyPoint(38,14),NULL);
	//设置选择界面
	setChoiceView.Set(80,25,MyPoint(0,0));
	setChoiceView.AddMenu("难度",MyPoint(38,10),&setLevelView);
	setChoiceView.AddMenu("时间",MyPoint(38,12),&setTimeView);
	setChoiceView.AddMenu("返回",MyPoint(38,14),&mainView);
	//设置难度界面
	setLevelView.Set (80,25,MyPoint(0,0));
	setLevelView.AddMenu("容易",MyPoint(38,10),&setChoiceView);
	setLevelView.AddMenu("中等",MyPoint(38,12),&setChoiceView);
	setLevelView.AddMenu("困难",MyPoint(38,14),&setChoiceView);
	//设置时间界面
	setTimeView.Set (80,25,MyPoint(0,0));
	setTimeView.AddMenu("1分钟",MyPoint(38,10),&setChoiceView);
	setTimeView.AddMenu("3分钟",MyPoint(38,12),&setChoiceView);
	setTimeView.AddMenu("5分钟",MyPoint(38,14),&setChoiceView);
	//游戏界面
	gameView.Set(80,24,MyPoint(0,0));
	//游戏结束界面
	gameOverView.Set(80,25,MyPoint(0,0));
	gameOverView.AddMenu("继续",MyPoint(38,12),&gameView);
	gameOverView.AddMenu("退出",MyPoint(38,14),NULL);
	//设置窗口大小
	HANDLE hOut ;
	CONSOLE_SCREEN_BUFFER_INFO csbi ;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
	GetConsoleScreenBufferInfo(hOut, &csbi) ;
	COORD bufferSize = {80, 25};												
	::SetConsoleScreenBufferSize(hOut, bufferSize) ;	
}
