#include<Windows.h>
#include <mmsystem.h>
#include"LinkList.h"
#pragma comment(lib, "winmm.lib")
//游戏一共有三个页面，主页面，开始游戏页面，设置页面
#define MainPage1        0    //主页面,选择框位于“开始游戏”
#define MainPage2        1    //主页面,选择框位于“选项”
#define MainPage3        2    //主页面,选择框位于“退出游戏”
#define GamePage         3   //游戏中界面
#define OptionPage1     4   //选项界面，选择框位于“难度”
#define OptionPage2     5  //选项界面，选择框位于“小球种类”
#define OptionPage3     6 //选项界面，选择框位于“音乐”
#define OptionPage4     7 //选项界面，选择框位于“音乐”
#define OptionPage5     8   //选项界面，位于“返回”
//板子种类
#define bNormal			    0  //普通板子，褐色
#define bWithTrap			1  //陷阱板子，灰色
#define bRmoving	        2  //向右移动的板子，
#define bLMoving          3  //向左移动的板子，
#define bJumping	        4  //弹跳板子，橘黄
#define bBroken		        5  //易碎板子，青色
#define bNone                6
//小球种类
#define Light                  0//轻小球 
#define Heavy                1//重小球
//难度
#define Easy    0//简单难度
#define Mid    1//中等难度
#define Hard   2//地狱难度

//小球状态
#define ON      0//在木板上
#define NotOn 1//不在木板
#define Lapped 2//重合bug

//道具种类
#define SlowTimeProp          0//时间变慢，持续10秒
#define SpeedUpProp           1//时间加快，持续5秒
#define ChangeAllProp         2//所有画面中所有板子（除了bNone）均变成普通板子
#define ChangeTailProp        3//最底部的板子变成陷阱板子
#define GetLifeProp              4//生命+1
#define InvincibleProp          5//无敌！持续5秒
#define CTTLight                   6//改变小球种类至轻小球
#define CTTHeavy                 7//改变小球种类至重小球
#define NoneProp                8//无道具




typedef int Type;  
typedef struct _GAME_COORD
{
	short x;
	short y;
	Type type;
}GAME_COORD, *PGAME_COORD;
typedef int Page;
DWORD WINAPI PlayMusic(LPVOID lpParam);
DWORD WINAPI StopMusic(LPVOID lpParam);
DWORD WINAPI PlayBorn(LPVOID lpParam);
DWORD WINAPI PlayJump(LPVOID lpParam);
DWORD WINAPI PlayBroken(LPVOID lpParam);
DWORD WINAPI PlayGameOver(LPVOID lpParam);


void CreateMain(HWND hwnd,int boundary_x, int boundary_y);
void CreateGame(HWND, int, int, int,int,int,HWND);
// 设置边界坐标
void SetBoundary(int x, int y);
void CreateBoard();
void CreateBall(int);
int GetBoardNum();
void BoardMove(HWND);//每次时间周期，向上移动
void OnTimer(HWND);
int StatusBall();
void MakeBoard(HWND);
int isGameOver();
int GetScore();
int GetLife();
void MoveLBall();
void MoveRBall();
void Destory();

PGAME_COORD GetBoardTail();
PGAME_COORD GetBallBody();
PGAME_COORD board_get_at(int i);
// 获得边界坐标
PGAME_COORD GetBoundary();
PGAME_COORD GetGameProp();
void GameProp();//游戏道具触发函数
void CreatProp();
BOOL GetAM();
int GetBallOneType();
BOOL isInvincible();