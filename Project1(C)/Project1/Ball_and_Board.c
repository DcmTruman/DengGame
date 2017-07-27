#include<Windows.h>
#include"Ball.h"
#include<math.h>


/************* ȫ�ֱ��� ****************/
// С��
GAME_COORD ball;
//����
GAME_COORD prop;
// ���ӣ�����
PLIST board_list;
// ��Ϸ�߽磨�������£�����Ϊ0,0��
GAME_COORD boundary;
// ��ʱ����ʱ���
double dwTimerElapse=150;
// ÿ���һ������ʱ��ʱ���������̵ı�����
DOUBLE dbLevelSpeedupRatio=0.8;
// �˱�����ʾ���ٸ���������һ������ÿ25������
DWORD dwOneLevelScores=25;
int BoardUp = 0;//ÿ����ʱ�����ڰ�������һ��,ÿһ��ʱ�����ڣ�δ�ڰ��С������
int UpNum = 0;//����ÿ����3�Σ�����һ���°���//ÿ����������ӣ�����+1
int CreatNum=0;
int Status ;//��ʼС���Ƿ�λ��ľ��
Type TypeBoard;//��С���������İ�������
int LIFE; //����4��������������������������ĩβ���Ӹ���������꣬��Ϸ����
int Score;//�ȷ�
int tempScore=0;//ÿ����������ӣ�����+1
int GameOver = 0;//��LIFEΪ0ʱ����Ϊ1
int JumpNum=0;//�������������ǵ�������
int GameDiffculty;//��Ϸ�Ѷ�
int flag = 0;//���ڼ�¼����
int MoveStep = 4;
int openmusic = 1;//����
int opensndefct = 1;//��Ч
int b = 0;
HWND HHHH;

/*------------����Ҫ��ʼд������!--------------*/
//���߲�������
int SlowFlag;//���ٵ����õ��ı�����10s
int SpeedFlag;//����ʱ�õ��ĵ���
int InvincibleFlag;//�޵�ʱ�õ��ĵ��ߣ�10s
int OldMoveStep;//���ٹ���ظ�ԭ���ٶ�
//int MoveFlag=-1;//���ڼ�¼�����ƶ��İ���
PGAME_COORD MoveFlag;
BOOL PropWorking = FALSE;
BOOL BeginSlow = FALSE;//���ڿ�ʼ���ٵı�־������ͳ��ʱ��
BOOL BeginSpeedUp = FALSE;
BOOL BeginInvincible = FALSE;
DWORD WINAPI PlayGetLife(LPVOID lpParam)
{
	if (opensndefct)
	{
		mciSendString("close glife", 0, 0, 0);
		mciSendString(TEXT("open GetLife.wav alias glife "), NULL, 0, NULL);
		mciSendString("play glife ", 0, 0, 0);
	}
	return 0;
}

void CreatProp()
{
	//PGAME_COORD p = GetBoardTail();
	prop.x = 0;
	prop.y =0;
	prop.type = NoneProp;
}


//��Ϸ���ߴ�������
void GameProp()
{
	if (BeginSlow)
	{
		SlowFlag--;
		if (SlowFlag == 0)
		{
			MoveStep = OldMoveStep;
			PropWorking = FALSE;
			BeginSlow = FALSE;
		}
	}
	else if (BeginSpeedUp)
	{
		SpeedFlag--;
		if (SpeedFlag == 0)
		{
			MoveStep -= 4;
			PropWorking = FALSE;
			BeginSpeedUp = FALSE;
		}
	}
	else if (BeginInvincible)
	{
		InvincibleFlag--;
		if (InvincibleFlag == 0)
		{
			PropWorking = FALSE;
			BeginInvincible = FALSE;
		}
	}
	if (prop.type != NoneProp)
	{
		if (abs(ball.x - prop.x) < 20 && abs(ball.y - prop.y) < 20)
		{
			switch (prop.type)
			{
			case SlowTimeProp:
					OldMoveStep = MoveStep;
					MoveStep = 2;
					PropWorking = TRUE;
					BeginSlow = TRUE;
					SlowFlag = 1000;
				break;
			case SpeedUpProp:
					MoveStep += 4;
					PropWorking = TRUE;
					BeginSpeedUp = TRUE;
					SpeedFlag = 500;
				break;
			case ChangeAllProp:
				for (int i = 0; i < GetBoardNum(); i++)
				{
					PGAME_COORD temp = board_get_at(i);
					if (temp->type != bNone)
					{
						temp->type = bNormal;
					}
				}
				break;
			case ChangeTailProp:
				GetBoardTail()->type = bWithTrap;
				break;
			case GetLifeProp:
				LIFE++;
				CreateThread(NULL, 0, PlayGetLife, NULL, 0, NULL);
				break;
			case InvincibleProp:
				PropWorking = TRUE;
				BeginInvincible = TRUE;
				InvincibleFlag = 1000;
				break;
			case CTTLight:
				ball.type = Light;
				break;
			case CTTHeavy:
				ball.type = Heavy;
				break;
			default:
				break;
			}
			prop.x = 0;
			prop.y = 0;
			prop.type = NoneProp;
		}
		else if (BoardUp == 1)
		{
			prop.y -= MoveStep;
			if (prop.y < 0)
			{
				prop.x = 0;
				prop.y = 0;
				prop.type = NoneProp;
			}
		}
		if (MoveFlag != NULL)
		{
			
			switch (MoveFlag->type)
			{
			case bLMoving:
				if (prop.x > 0)
				{
					prop.x -= MoveStep;
				}
				else if (prop.x <= 0)
				{
					prop.x += MoveStep;
				}
				break;
			case bRmoving:
				if (prop.x < 280)
				{
					prop.x += MoveStep;
				}
				else if (prop.x >= 15)
				{
					prop.x -= MoveStep;
				}
				break;
			default:
				break;
			}
		}
	}

}
/*--------------- 2017��7��9��-----------------*/
BOOL AfterMusic = FALSE;
DWORD WINAPI PlayMusic(LPVOID lpParam)
{
	PlaySound(TEXT("Music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	AfterMusic = TRUE;
	return 0;
}
DWORD WINAPI StopMusic(LPVOID lpParam)
{
	PlaySound(NULL, NULL, NULL);
	return 0;
}
DWORD WINAPI PlayBorn(LPVOID lpParam)
{
	//PlaySound(TEXT("Born.wav"), NULL, SND_FILENAME);
	if (opensndefct)
	{
		if (b == 0 || BeginInvincible)
		{
			mciSendString("close born", 0, 0, 0);
			mciSendString(TEXT("open Born.wav alias born "), NULL, 0, NULL);
			mciSendString("play born ", 0, 0, 0);
			b++;
		}
		else
		{
			mciSendString("close dead", 0, 0, 0);
			mciSendString(TEXT("open Dead.wav alias dead "), NULL, 0, NULL);
			mciSendString("play dead ", 0, 0, 0);
		}
	}
	return 0;
}
DWORD WINAPI PlayJump(LPVOID lpParam)
{
	if (opensndefct)
	{
		mciSendString("close jump", 0, 0, 0);
		mciSendString(TEXT("open Jump.wav alias jump "), NULL, 0, NULL);
		mciSendString("play jump ", 0, 0, 0);
	}
	return 0;
}
DWORD WINAPI PlayBroken(LPVOID lpParam)
{
	if (opensndefct)
	{
		mciSendString("close broken", 0, 0, 0);
		mciSendString(TEXT("open Broken.wav alias broken "), NULL, 0, NULL);
		mciSendString("play broken ", 0, 0, 0);
	}
	return 0;
}
DWORD WINAPI PlayGameOver(LPVOID lpParam)
{
	PlaySound(TEXT("GameOver.wav"), NULL, SND_FILENAME| SND_ASYNC);
	return 0;
}


void CreateMain(HWND hwnd, int boundary_x, int boundary_y)
{
	//������������ӣ�����������ɰ���
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);
	//mciSendString(TEXT("open Born.wav alias born "), NULL, 0, NULL);
	//������Ϸ�߽磨������ģ�
	SetBoundary(boundary_x, boundary_y);
	

}
void CreateGame(HWND hwnd, int color, int diffculty, int balltype,int openm,int opene,HWND h)
{
	//CreatGame�в�û���õ�color������GamePaint�л��õ��������������ø��ˡ���������
	SlowFlag=1000;//���ٵ����õ��ı�����10s
	SpeedFlag=500;//����ʱ�õ��ĵ���
	InvincibleFlag=1000;//�޵�ʱ�õ��ĵ��ߣ�10s
	OldMoveStep;//���ٹ���ظ�ԭ���ٶ�
					//int MoveFlag=-1;//���ڼ�¼�����ƶ��İ���
	//PGAME_COORD MoveFlag;
	PropWorking = FALSE;
	BeginSlow = FALSE;//���ڿ�ʼ���ٵı�־������ͳ��ʱ��
	BeginSpeedUp = FALSE;
	BeginInvincible = FALSE;
	openmusic = openm;
	opensndefct = opene;
	if(openmusic) CreateThread(NULL, 0, PlayMusic, NULL, 0, NULL);
	MoveStep = 3;
	switch (diffculty) {
	case Easy:
		break;
	case Mid:
		MoveStep += 3;
		break;
	case Hard:
		MoveStep += 6;
		break;
	default:
		break;
	}//�����Ѷ�������Ϸ����
	GameDiffculty = diffculty;
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);//�������������
	if (balltype == Light)LIFE = 3;
	else LIFE = 6;
	Score = 0;
	CreatNum = 0;
	BoardUp = 0;
	UpNum = 0;
	tempScore = 0;
	GameOver = 0;
	JumpNum = 0;
	flag = 0;
	CreateBoard();
	CreateBall(balltype);
	SetTimer(hwnd, 12340,10, NULL);
	HHHH = h;
	SlowFlag = 1000;//���ٵ����õ��ı���
	b = 0;//0��ʱ�򲥷ų�������Ч����0����������Ч
	CreatProp();

}
void SetBoundary(int x, int y)
{
	boundary.x = x;
	boundary.y = y;
}
PGAME_COORD GetBoundary()
{
	return &boundary;
}
void CreateBoard()
{
	PGAME_COORD p;
	p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
	p->x =rand()%201;
	p->y = 600;
     p->type = bNormal;//�ٷ�֮��ʮ�ĸ��ʲ�����ͨ����
//�ٷ�֮��ʮ�ĸ��ʲ����������
	//�ٷ�֮ʮ�ĸ��ʲ���������
	board_list = ListCreate(NULL);
	ListPushFront(board_list, p);//��ͷ��������˵㣩������洢

}
void CreateBall(int balltype)
{
	CreateThread(NULL, 0, PlayBorn, NULL, 0, NULL);
	
	PGAME_COORD tail = GetBoardTail();
	ball.x = tail->x+40;//��������һ�����ӣ�����С���ڰ������м�
	ball.y = tail->y - 20;//С����Ȼ�����ڰ����Ϸ���
	tail->type = bNormal;//Ϊ����С���Զ���ɲ�ͬ����
	ball.type = balltype;
	
	
}
PGAME_COORD GetBoardTail()
{
	return (PGAME_COORD)ListGetAt(board_list, GetBoardNum() - 1);
}
int GetBoardNum()
{
	return ListSize(board_list);
}
PGAME_COORD board_get_at(int i)
{
	return (PGAME_COORD)ListGetAt(board_list, i);
}
//Ҫ�޸İ����ƶ����ԣ����ڴ˺�����
void BoardMove(HWND hwnd)
{
	for (int i = 0; i < GetBoardNum(); i++)
	{
		PGAME_COORD temp = board_get_at(i);
		//�����ƶ��ٶ�������
		//if (MoveStep < 0)MoveStep = -MoveStep;//�˴����ڽ��һ��Bug
		if (BoardUp == 1)
		{
			temp->y -= MoveStep;
		}
		if (temp->type == bRmoving)
		{
			if (temp->x >= 200)
			{
				temp->type = bLMoving;
				temp->x -= MoveStep;   //�����ƶ�����
				
			}
			else
			{
				temp->x += MoveStep;
				if (StatusBall() == Lapped)ball.y += MoveStep;
			}
		}
		else if(temp->type==bLMoving)
		{
			if (temp->x <= 0)
			{
				temp->type = bRmoving;
				temp->x += MoveStep;
			}
			else
			{
				temp->x -= MoveStep;
				if (StatusBall() == Lapped)ball.y += MoveStep;
			}
		}
	}
	if (BoardUp)
	{
		//UpNum += MoveStep;
		//if (UpNum >= 80)
		//{
		//	MakeBoard(hwnd);
		//	UpNum = 0;
		//}
		while (1)
		{
			PGAME_COORD temp = GetBoardTail();
			if (temp->y <= 520)
			{
				MakeBoard(hwnd);
				GetBoardTail()->y = temp->y + 80;
			}
			else {
				break;
			}
		}
		BoardUp = 0;
	}
	else
	{
		BoardUp = 1;
	}
	PGAME_COORD poshead = board_get_at(0);
	if (poshead->y <= 0)
	{
		PGAME_COORD temp=ListPopFront(board_list);
		free(temp);
	}
}
int StatusBall()
{
	int num = GetBoardNum();
	for (int i = 0; i < num; i++)
	{
		PGAME_COORD temp= board_get_at(i);
		if (temp->type != bNone)
		{
			if ((ball.y == (temp->y - 20))
				&& ((ball.x - temp->x) <= 90)
				&& ((ball.x - temp->x) >= -10))
			{
				TypeBoard = temp->type;
				if (TypeBoard == bBroken)flag = i;
				return ON;
			}
			else if ((20 > abs(temp->y - ball.y))
				&& ((ball.x - temp->x) >= -10)
				&& ((ball.x - temp->x) <= 90)
				)
			{
				//bug,���ľ���غ�
				flag = temp->y;
				return Lapped;
			}
		}
	}
	return NotOn;
}
void OnTimer(HWND hwnd)
{

	     GameProp();
		Status = StatusBall();
		switch (Status)
		{
		case ON:
			switch (TypeBoard)
			{
			case bNormal:
				MoveupBall();
				break;
			case bWithTrap:
				if (!BeginInvincible)
				{
					LIFE -= 1;
					if (LIFE == 0) {
						GameOver = 1;
						return;
					}
					else
					{
						CreateBall(ball.type);
						ball.y -= 20;
					}
				}
				else
				{
					MoveupBall();
				}
				break;
			case bLMoving:
				MoveupBall();
				if (ball.x > 0)
				{
					ball.x -= MoveStep;
				}
				else if (ball.x <= 0)
				{
					ball.x += MoveStep;
				}
				break;
			case bRmoving:
				MoveupBall();
				if (ball.x < 280)
				{
					ball.x += MoveStep;
				}
				else if (ball.x >= 15)
				{
					ball.x -= MoveStep;
				}
			break;
		case bJumping:
			if (ball.type == Light)
			{
				JumpNum = 1;
				MoveupBall();
			}
			else
			{
				MoveupBall();
			}
			break;
		case bBroken:
			switch (ball.type) {
			case Light:
				MoveupBall();
				break;
			case Heavy:
				MoveupBall();
				if (ball.y >= 600)
				{
					LIFE -= 1;
					if (LIFE == 0) {
						GameOver = 1;
						return;
					}
					else
					{
						CreateBall(ball.type);
						ball.y -= 20;
					}
				}
				board_get_at(flag)->type = bNone;
				CreateThread(NULL, 0, PlayBroken, NULL, 0, NULL);
				flag = 0;
				break;
			default:
				break;
			}
			//MoveupBall();
			break;
		default:
			break;
			}
			break;
		case NotOn:
			ball.y += MoveStep+1;
			if (ball.y >= 600)
			{
				if(!BeginInvincible)LIFE -= 1;
				if (LIFE == 0) {
					GameOver = 1;
					return;
				}
				else
				{
					CreateBall(ball.type);
					ball.y -=20;
				}
			}
			break;
		case Lapped:
			ball.y = flag - 20;
			flag = 0;
			MoveupBall();
			break;
		}
		BoardMove(hwnd);
		
	
}
int isGameOver() { return GameOver; }
int GetScore() { return Score; }
int GetLife() { return LIFE; }
void MakeBoard(HWND hwnd)
{

	CreatNum++;
	if (CreatNum >= 5)
	{
		Score++;
		tempScore++;
		if (tempScore >= dwOneLevelScores)
		{
			MoveStep += 1;
			LIFE++;
			tempScore = 0;
		}
		CreatNum = 0;
	}
	int i = rand() % 100;
	if (GameDiffculty == Easy)
	{

			PGAME_COORD p;
			p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
			p->x = rand() % 201;
			p->y = 600;
			if (i < 65)p->type = bNormal;//�ٷ�֮65�ĸ��ʲ�����ͨ����
			else if(i<78)p->type = bWithTrap;
			else if(i<90)
			{
				p->type = i % 4 + 2;//����������Ӳ���������ͬ
			}//�ٷ�֮��ʮ�ĸ��ʲ���������� //�ٷ�֮ʮ�ĸ��ʲ���������
			else p->type = bNone;
			ListPushBack(board_list, p);

	}
	else if (GameDiffculty == Mid)
	{

			PGAME_COORD p;
			p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
			p->x = rand() % 201;
			p->y = 600;
			if (i < 55)p->type = bNormal;//�ٷ�֮��ʮ�ĸ��ʲ�����ͨ����
			else if (i<72)p->type = bWithTrap;
			else if(i<80)
			{
				p->type = i % 5 + 1;//����������Ӳ���������ͬ
			}//�ٷ�֮��ʮ�ĸ��ʲ����������//�ٷ�֮ʮ�ĸ��ʲ���������
			else p->type = bNone;
			ListPushBack(board_list, p);
	
	}
	else
	{

			PGAME_COORD p;
			p = (PGAME_COORD)malloc(sizeof(GAME_COORD));
			p->x = rand() % 201;
			p->y = 600;
			if (i < 50)p->type = bNormal;//�ٷ�֮��ʮ�ĸ��ʲ�����ͨ����
			else if (i<72)p->type = bWithTrap;
			else if(i<75)
			{
				p->type = i % 5 + 1;//����������Ӳ���������ͬ
			}//�ٷ�֮��ʮ�ĸ��ʲ����������//�ٷ�֮ʮ�ĸ��ʲ���������
			else p->type = bNone;
			ListPushBack(board_list, p);
	}
	if (prop.type == NoneProp&&GetBoardTail()->type != bNone&&(PropWorking==FALSE||BeginInvincible==TRUE)&&(BeginSlow==FALSE&&BeginSpeedUp==FALSE))
	{
		int t = rand() % 100;
		if (t <5)
		{
			prop.x = GetBoardTail()->x + rand() % 80;
			prop.y = GetBoardTail()->y - 20;
			//if (BoardUp)prop.y -= MoveStep;
			prop.type = rand() % 8;
			if (GetBoardTail()->type == bRmoving || GetBoardTail()->type == bLMoving)
			{
				MoveFlag = GetBoardTail();
			}
			else
			{
				MoveFlag = NULL;
			}
			//prop.type = CTTHeavy;
		}
		
	}
}
PGAME_COORD GetBoardBody() { return board_list; }
PGAME_COORD GetBallBody() { return &ball; }
int MoveupBall()
{

		if (BoardUp == 1)
		{
			if (JumpNum == 0)
			{
				ball.y -= MoveStep;
			}
			else
			{
				CreateThread(NULL, 0, PlayJump, NULL, 0, NULL);
				ball.y -= (100);
				JumpNum = 0;
			}
			if (ball.y < 20) {
				if(!BeginInvincible)LIFE -= 1;
				if (LIFE == 0) {
					GameOver = 1;
					return 1;
				}
				else
				{
					
					CreateBall(ball.type);
					ball.y -= 20;
				}
			}
			//BoardUp = 0;
		}
	
	return 0;
}
void MoveLBall()
{
	if (ball.type == Light) {
		ball.x = ball.x -6;
		if (StatusBall() == Lapped)ball.x = ball.x + 6;
	}
	else
	{
		ball.x = ball.x - 4;
		if (StatusBall() == Lapped)ball.x = ball.x + 4;
	}
	if (ball.x < 0)
	{
		ball.x = 0;
	}
	

}
void MoveRBall()
{
	{
		if (ball.type == Light) {
			ball.x = ball.x + 6;
			if (StatusBall() == Lapped)ball.x = ball.x - 6;
		}
		else
		{
			ball.x = ball.x + 4;
			if (StatusBall() == Lapped)ball.x = ball.x -4;
		}
		if (ball.x > 280)
		{
			ball.x = 280;
		}
	}
}
void Destory()
{


	mciSendString("close born", 0, 0, 0);
	mciSendString("close dead", 0, 0, 0);
	mciSendString("close jump", 0, 0, 0);
	mciSendString("close broken", 0, 0, 0);
	ListDistoryAndFree(board_list);
}
BOOL GetAM()
{
	return AfterMusic;
}
PGAME_COORD GetGameProp()
{
	return &prop;
}
int GetBallOneType()
{
	return ball.type;
}
BOOL isInvincible()
{
	return BeginInvincible;
}
