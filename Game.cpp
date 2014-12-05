#include "Game.h"
#include"GotoXY.h"
#include<Windows.h>
#include<iostream>
#include<string>
using namespace std;
//ȫ�ֳ�Ա
CRITICAL_SECTION cs;
//static ��Ա
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
//��static��Ա
Game::Game(void)
{
	totalCharNum=0;
	hitCharNum=0;
	hitKeyBoard=0;
	this->Init();
	this->selectedView=1;	
	this->mainView.DisPlay();
	this->mainView.OutText("Enter:",MyPoint(28,12));//����������ڿ�ʼ�˵���
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
					this->gameView.OutText("��ͣ:Space���¿�ʼ:Enter����:Esc",MyPoint(0,0));
					this->gameView.OutText("����ʱ��:",MyPoint(66,0));
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
					gameLevel=3;//����
				}
				else if(12==selectedMenuPos.y)
				{
					gameLevel=2;//�е�
				}
				else
					gameLevel=1;//����
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
	//�������ͼ�����ʱ����Ϣ���߳�
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
				this->gameView.OutText("����:Space���¿�ʼ:Enter����:Esc",MyPoint(0,0));
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
				this->mainView.OutText("Enter:",MyPoint(28,12));//����������ڿ�ʼ�˵���
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
					this->gameView.OutText("��ͣ:Space���¿�ʼ:Enter����:Esc",MyPoint(0,0));
					this->gameState=true;
				}
			}
		}
	}
	this->gameState=false;
	system("cls");
	this->gameOverView.DisPlay();
	GotoXY()(MyPoint(28,8));
	cout<<"���������Ϊ:"<<this->hitCharNum*1.0/this->totalCharNum;
	GotoXY()(MyPoint(28,10));
	cout<<"�����ȷ��Ϊ:"<<this->hitCharNum*1.0/this->hitKeyBoard;
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
					this->gameView.OutText("��ͣ:Space���¿�ʼ:Enter����:Esc",MyPoint(0,0));
					this->gameView.OutText("����ʱ��:",MyPoint(66,0));
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
	//��Ϸ������
	mainView.Set(80,25,MyPoint(0,0));
	mainView.AddMenu("����",MyPoint(38,10),&setChoiceView);
	mainView.AddMenu("��ʼ",MyPoint(38,12),&gameView);
	mainView.AddMenu("�˳�",MyPoint(38,14),NULL);
	//����ѡ�����
	setChoiceView.Set(80,25,MyPoint(0,0));
	setChoiceView.AddMenu("�Ѷ�",MyPoint(38,10),&setLevelView);
	setChoiceView.AddMenu("ʱ��",MyPoint(38,12),&setTimeView);
	setChoiceView.AddMenu("����",MyPoint(38,14),&mainView);
	//�����ѶȽ���
	setLevelView.Set (80,25,MyPoint(0,0));
	setLevelView.AddMenu("����",MyPoint(38,10),&setChoiceView);
	setLevelView.AddMenu("�е�",MyPoint(38,12),&setChoiceView);
	setLevelView.AddMenu("����",MyPoint(38,14),&setChoiceView);
	//����ʱ�����
	setTimeView.Set (80,25,MyPoint(0,0));
	setTimeView.AddMenu("1����",MyPoint(38,10),&setChoiceView);
	setTimeView.AddMenu("3����",MyPoint(38,12),&setChoiceView);
	setTimeView.AddMenu("5����",MyPoint(38,14),&setChoiceView);
	//��Ϸ����
	gameView.Set(80,24,MyPoint(0,0));
	//��Ϸ��������
	gameOverView.Set(80,25,MyPoint(0,0));
	gameOverView.AddMenu("����",MyPoint(38,12),&gameView);
	gameOverView.AddMenu("�˳�",MyPoint(38,14),NULL);
	//���ô��ڴ�С
	HANDLE hOut ;
	CONSOLE_SCREEN_BUFFER_INFO csbi ;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
	GetConsoleScreenBufferInfo(hOut, &csbi) ;
	COORD bufferSize = {80, 25};												
	::SetConsoleScreenBufferSize(hOut, bufferSize) ;	
}
