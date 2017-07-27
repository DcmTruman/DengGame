import pygame,time
from pygame.locals import *
from random import randint
import random
from threading import *
from math import *
TIMER = pygame.USEREVENT+1
pygame.time.set_timer(TIMER,10)
PicOfStand = pygame.image.load("Stand.png")#玩家站立状态
Win =pygame.transform.scale( pygame.image.load("Win.png"), (1280, 720))
PicOfMove = []#玩家行走状态
Map = pygame.transform.scale(pygame.image.load("Map.png") , (1280, 720))
go = pygame.transform.scale(pygame.image.load("gameover.jpg") , (1280, 720))

for i in range(5) :
        temp = pygame.image.load("Move"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfMove.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfAttackOne = []
for i in range(6):
        temp = pygame.image.load("AttackOne"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfAttackOne.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfAttackTwo = []
for i in range(5):
        temp = pygame.image.load("AttackTwo"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfAttackTwo.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfAttackTh = []
for i in range(5):
        temp = pygame.image.load("AttackTh"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfAttackTh.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfAttackFour = []
for i in range(9):
        temp = pygame.image.load("AttackFour"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfAttackFour.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfAttack = []
PicOfAttack.append(PicOfAttackOne)
PicOfAttack.append(PicOfAttackTwo)
PicOfAttack.append(PicOfAttackTh)
PicOfAttack.append(PicOfAttackFour)
#按键状态
LeftPress = False
RightPress = False
UpPress = False
DownPress = False
AttackList = [] #使用list模拟Queue,表示4种普通攻击的顺序顺序，先进先出
AttackNumber = 0
POP = False
#人物状态
MOVE = 0
STAND = 1
ATTACK = 2
FALL = 3
LEFT = 0
RIGHT = 1
#任务状态类（血量）
def SetToFalse(List):
        for i in range(len(List)):
                List[i] = False
class People(object):
    def __init__(self,HP,MP,status,p,q,h):
        self.Hp = HP
        self.Mp = MP
        self.Status = status
        self.x = p
        self.y = q
        self.Head = h
    def lostBlood(self,number):
        self.Hp -= number
class peopleOfPlayer(People):
        def __init__(self,HP,MP,status,p,q,h):
                People.__init__(self,HP,MP,status,p,q,h)
                self.AttackJudge = []
                for i in range(10):
                        self.AttackJudge.append(False)


#精灵
class PlayerSprite(pygame.sprite.Sprite):
    global player
    def __init__(self,status,position,head):
        pygame.sprite.Sprite.__init__(self)
        self.Status = status
        self.Head = head
        self.MoveTemp = 0
        self.MoveClock = 0
        self.AttackTemp = 0
        self.AttackClock = 0
        self.Pop = False
        if self.Status == STAND and self.Head == RIGHT:
            t1,t2 = PicOfStand.get_size()
            self.image = pygame.transform.scale(PicOfStand,(t1*2,t2*2))
        elif self.Status == STAND and self.Head == LEFT:
            t1,t2 = PicOfStand.get_size()
            self.image = pygame.transform.flip(pygame.transform.scale(PicOfStand,(t1*2,t2*2)), True, False)
        self.rect = self.image.get_rect()
        self.rect.topleft = position
    def update(self,status,position,head,peopleOfPlayer):
        self.Status = status
        self.Head = head
        if self.Status == STAND and self.Head == RIGHT:
            t1,t2 = PicOfStand.get_size()
            self.image = pygame.transform.scale(PicOfStand,(t1*2,t2*2))
        elif self.Status == STAND and self.Head == LEFT:
            t1,t2 = PicOfStand.get_size()
            self.image = pygame.transform.flip(pygame.transform.scale(PicOfStand,(t1*2,t2*2)), True, False)
        elif self.Status == MOVE and self.Head == RIGHT:
            #t1,t2 = PicOfMove[self.MoveTemp].get_size()
            self.image = PicOfMove[self.MoveTemp]
        elif self.Status == MOVE and self.Head == LEFT:
            self.image = pygame.transform.flip(PicOfMove[self.MoveTemp],True,False)
        if self.Status == ATTACK:
                if self.Head == RIGHT:
                        self.image = PicOfAttack[AttackList[0]][self.AttackTemp]
                        self.rect = self.image.get_rect()
                        if AttackList[0] == 0:
                                a,b = position
                                self.rect.topleft = (a-80,b+30)
                        elif AttackList[0] == 1:
                                a,b=position
                                self.rect.topleft = (a-10,b+20)
                        elif AttackList[0] == 2:
                                a,b=position
                                self.rect.topleft = (a-10,b-150)
                        elif AttackList[0] == 3:
                                a,b=position
                                self.rect.topleft = (a-40,b-150)
                else :
                        self.image = pygame.transform.flip(PicOfAttack[AttackList[0]][self.AttackTemp],True,False)
                        self.rect = self.image.get_rect()
                        if AttackList[0] == 0:
                                a,b = position
                                self.rect.topleft = (a,b+30)
                        elif AttackList[0] == 1:
                                a,b=position
                                self.rect.topleft = (a-40,b+20)
                        elif AttackList[0] == 2:
                                a,b=position
                                self.rect.topleft = (a+10,b-150)
                        elif AttackList[0] == 3:
                                a,b=position
                                self.rect.topleft = (a-80,b-150)
        else :
               self.rect = self.image.get_rect()
               self.rect.topleft = position
        player.rect = self.rect#新增rect用来判定攻击范围
    def timetick(self):
        if self.Pop:
                self.Pop = False
        #每过一个时间周期，各种状态的动画效果
        if self.Status == MOVE:
            self.MoveClock += 1
            #print(self.MoceClock)
            if self.MoveClock >= 13:
                self.MoveClock = 0
                self.MoveTemp +=1
                if self.MoveTemp >=5:
                    self.MoveTemp =0
        elif self.Status == ATTACK:
                #print(self.AttackClock+self.AttackTemp)
                self.AttackClock+=1
                if self.AttackClock >=7:
                        self.AttackClock = 0
                        self.AttackTemp +=1
                        if AttackList[0] == 0  :
                                a=6
                        elif AttackList[0] == 1 or AttackList[0] == 2:
                                a=5
                        else:
                                a=9
                        if self.AttackTemp >=a:
                                        self.AttackTemp =0
                                        AttackList.pop(0)
                                        
                                        self.Pop = True
                                        if not len(AttackList):
                                                if LeftPress or RightPress or UpPress or DownPress:
                                                        player.Status = MOVE
                                                        if LeftPress:
                                                                player.Head = LEFT
                                                        if RightPress:
                                                                player.Head = RIGHT
                                                
                                                else :
                                                        player.Status = STAND
                                                self.AttackTemp = 0
                                                self.AttackClock = 0
#---------以下代码单独存发，这里只是测试------------
PicOfE1Move=[]
PicOfEMove = []
PicOfE1Fall=[]
PicOfE1Attack=[]
for i in range(8) :
        temp = pygame.image.load("EMove0-"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfE1Move.append(pygame.transform.scale(temp , (t1*2, t2*2)))
for i in range(12) :
        temp = pygame.image.load("EFall0-"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfE1Fall.append(pygame.transform.scale(temp , (t1*2, t2*2)))
for i in range(6) :
        temp = pygame.image.load("EAttack0-"+str(i)+".png")
        t1,t2 = temp.get_size()
        PicOfE1Attack.append(pygame.transform.scale(temp , (t1*2, t2*2)))
PicOfEStand0 = pygame.image.load("EStand0.png")#玩家站立状态
PicOfEHitten0 =pygame.transform.scale( pygame.image.load("EHitten0.png"), (pygame.image.load("EHitten0.png").get_size()[0]*2, pygame.image.load("EHitten0.png").get_size()[1]*2))
AttackMax = False
class EnemyOne(People):
        global AttackMax
        global player
        global playerSprite
        def __init__(self,HP,MP,status,p,q,h):
                People.__init__(self,HP,MP,status,p,q,h)
                if self.x!=player.x:
                        self.a = atan(abs(player.y-self.y)/abs(player.x-self.x))
                else :
                        self.a = 0
                self.SpeedX = abs (0.8*cos(self.a))
                self.SpeedY = abs (0.8*sin(self.a))
                self.MoveTemp = 0
                self.MoveClock = 0
                self.AttackTemp = 0
                self.AttackClock = 0
                self.FallTemp = 0
                self.FallClock = 0
                self.Hitten = 0
                self.HittenJudge = [False,False,False,False]
                if self.Head == RIGHT :
                        t1,t2 = PicOfStand.get_size()
                        self.image = pygame.transform.scale(PicOfEStand0,(floor(t1*2),floor(t2*2)))
                else :
                        t1,t2 = PicOfStand.get_size()
                        self.image = pygame.transform.flip(pygame.transform.scale(PicOfEStand0,(floor(t1*2),floor(t2*2))), True, False)
                self.rect = self.image.get_rect()
                self.rect.topleft = (self.x,self.y)
        def update(self):
                if self.x!=player.x:
                        self.a = atan(abs(player.y-self.y)/abs(player.x-self.x))
                else :
                        self.a = 0
                self.SpeedX = abs (0.8*cos(self.a))
                self.SpeedY = abs (0.8*sin(self.a))
                if self.Status == STAND and self.Head == RIGHT and not self.Hitten:
                    t1,t2 = PicOfEStand0.get_size()
                    self.image = pygame.transform.scale(PicOfEStand0,(floor(t1*2),t2*2))
                    if player.x <= self.x:
                            if not randint(0,100):
                                    self.Head = LEFT
                    else:
                            self.Status = MOVE
                elif self.Status == STAND and self.Head == LEFT and not self.Hitten:
                    t1,t2 = PicOfEStand0.get_size()
                    self.image = pygame.transform.flip(pygame.transform.scale(PicOfEStand0,(t1*2,t2*2)), True, False)
                    if player.x >= self.x:
                            if not randint(0,100):
                                    self.Head = RIGHT
                    else:
                            self.Status = MOVE
                elif self.Status == MOVE and self.Head == RIGHT and not self.Hitten:
            #t1,t2 = PicOfMove[self.MoveTemp].get_size()
                    self.image = PicOfE1Move[self.MoveTemp]
                    self.x +=self.SpeedX
                    if self.y > player.y:
                            self.y -= self.SpeedY
                    else :
                            self.y +=self.SpeedY
                    if self.x > player.x:
                            self.Head = LEFT
                elif self.Status == MOVE and self.Head == LEFT and not self.Hitten:
                    self.image = pygame.transform.flip(PicOfE1Move[self.MoveTemp],True,False)
                    self.x -= self.SpeedX
                    if self.y > player.y:
                            self.y -= self.SpeedY
                    else :
                            self.y +=self.SpeedY
                    if self.x < player.x:
                            self.Head = RIGHT
                if self.Hitten and self.Status !=FALL:
                        if self.Head == RIGHT:
                                self.image=PicOfEHitten0
                        else :
                                self.image = pygame.transform.flip(PicOfEHitten0,True,False)
                if len(AttackList):
                        if self.Hitten and AttackList[0] == 3 and player.Head != self.Head and self.AttackTemp<3:
                                self.Status = FALL
                        
                if self.Status == FALL:
                        #print(self.FallTemp)
                        if self.Head == RIGHT:
                                self.image = PicOfE1Fall[self.FallTemp]
                                if self.FallTemp <=6:
                                        self.x -= 3
                                        #self.y += randint(-2,2)
                        else :
                                self.image = pygame.transform.flip(PicOfE1Fall[self.FallTemp],True,False)
                                if self.FallTemp <= 6:
                                        self.x +=3
                        if self.FallTemp == 11:
                                self.Status = MOVE
                                self.FallTemp =0
                if player.Status == ATTACK and self.rect.colliderect(player.rect) and len(AttackList)and self.HittenJudge[AttackList[0]] !=True and player.Head != self.Head and  not AttackMax:
                        SetToFalse(self.HittenJudge)
                        self.HittenJudge[AttackList[0]] =True
                        self.Hitten =1
                        if self.Status != FALL:
                                self.lostBlood((AttackList[0]+1)*(AttackList[0]+1))
                        if player.x >= self.x:
                                self.Head = RIGHT
                        else:
                                self.Head = LEFT
                if player.Status != ATTACK or not self.rect.colliderect(player.rect) :
                        self.Hitten = 0
                if self.rect.colliderect(player.rect) and self.Status == MOVE:
                        self.Status = ATTACK
                if self.Status == ATTACK and self.Hitten == 0:
                        if self.Head == LEFT:
                                self.image = pygame.transform.flip(PicOfE1Attack[self.AttackTemp],True,False)
                        else:
                                self.image = PicOfE1Attack[self.AttackTemp]
                if player.Status !=ATTACK and True in self.HittenJudge:
                        SetToFalse(self.HittenJudge)
                self.rect = self.image.get_rect()
                self.rect.topleft = (self.x,self.y)
                if self.FallTemp >= 3:
                        self.rect.topleft = (self.x,self.y+120)
                if self.Hitten and self.Status!=FALL :
                        if self.Hitten>4 and self.Hitten <8:
                                if self.Head == LEFT:
                                        self.rect.topleft = (self.x+10,self.y-10)
                                else :
                                        self.rect.topleft = (self.x-10,self.y-10)
                        elif self.Hitten>=8 and self.Hitten <12:
                                if self.Head == LEFT:
                                        self.rect.topleft = (self.x+20,self.y-20)
                                else :
                                        self.rect.topleft = (self.x-20,self.y-20)
                        elif self.Hitten>=12 and self.Hitten <16:
                                if self.Head == LEFT:
                                        self.rect.topleft = (self.x+10,self.y-10)
                                else :
                                        self.rect.topleft = (self.x-10,self.y-10)
                        
        def timetick(self):
        #每过一个时间周期，各种状态的动画效果
                if self.Status == MOVE:
                    self.MoveClock += 1
            #print(self.MoceClock)
                    if self.MoveClock >= 13:
                        self.MoveClock = 0
                        self.MoveTemp +=1
                        if self.MoveTemp >=8:
                            self.MoveTemp =0
                if self.Hitten :
                        self.Hitten +=1
                        #print(self.Hitten)
                        if playerSprite.Pop:
                                #print(self.Hitten)
                                self.Hitten = 0
                                playerSprite.Pop = False
                if self.Status == FALL :
                        self.FallClock +=1
                        if self.FallClock >=18:
                                self.FallClock = 0
                                self.FallTemp +=1
                                if self.FallTemp >= 12:
                                        self.FallTemp = 0
                if self.Status == ATTACK:
                        self.AttackClock+=1
                        if self.AttackClock >= 15:
                                self.AttackClock = 0
                                self.AttackTemp += 1
                                if self.AttackTemp >= 6:
                                        self.AttackTemp = 0
                                        self.Status = MOVE
                           
def UPDATE(DATA):
        global player
        for i in range(len(DATA)):
                DATA[i].update()
        
        a = 0
        for i in range(len(DATA)):
                if DATA[i].Hitten != 0 :
                        a +=1
                        if a>4 :
                             DATA[i].Hitten = 0
                             DATA[i].Status = MOVE
        L = []
        for i in range(len(DATA)):      
                        if DATA[i].Hp <=0:
                                L.append(i)
        for i in range (len(L)):
           if len(L):
                DATA.pop(L[i])
                player.AttackJudge.pop(i)
        for i in range (len(DATA)):
                if DATA[i].Status == ATTACK:
                        if(DATA[i].rect.colliderect(player.rect)) and DATA[i].AttackTemp >=3 and not player.AttackJudge[i]:
                                player.lostBlood(10)
                                player.AttackJudge[i] = True
                else:
                        player.AttackJudge[i] = False
                #if DATA[i].AttackTemp ==5 :
                        #player.AttackJudge[i] = False
                        
def TIMETICK(DATA):
        for i in range(len(DATA)):
                DATA[i].timetick()
def BLIT(DATA):
        global screen
        for i in range(len(DATA)):
                screen.blit(DATA[i].image,DATA[i].rect)

#----------------------------------------------------------
                                        
pygame.init()
player = peopleOfPlayer(500,100,STAND,400,300,RIGHT)
playerSprite = PlayerSprite(player.Status,(player.x,player.y),player.Head)
#ttt = EnemyOne(100,100,STAND,800,100,RIGHT)
Enemy=[]
for i in range(10):
        Enemy.append(EnemyOne(100,100,STAND,randint(0,1300),randint(200,800),randint(0,1)))
screen = pygame.display.set_mode((1280,720),0,32)
screen.fill((255,255,255))
background = Map.convert()
win = Win.convert()
Go = go.convert()
while True:
     for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
        if event.type == KEYDOWN:
            if event.key == K_LEFT :
                LeftPress = True
                #RightPress = False
                if player.Head !=LEFT:
                    playerSprite.MoveClock = 0
                    playerSprite.MoveTemp = 0
                if player.Status != ATTACK:
                        player.Status = MOVE
                        player.Head = LEFT
            if event.key == K_RIGHT:
                RightPress = True
                #LeftPress = False
                if player.Head != RIGHT:
                    playerSprite.MoveClock = 0
                    playerSprite.MoveTemp = 0
                if player.Status != ATTACK:
                        player.Status = MOVE
                        player.Head = RIGHT
            if event.key ==K_UP:
                UpPress = True
                #LeftPress = False
                if player.Status != MOVE:
                    playerSprite.MoveClock = 0
                    playerSprite.MoveTemp = 0
                player.Status = MOVE
            if event.key ==K_DOWN:
                DownPress = True
                #LeftPress = False
                if player.Status != MOVE:
                    playerSprite.MoveClock = 0
                    playerSprite.MoveTemp = 0
                player.Status = MOVE
            if event.key == K_x:
                    if len(AttackList) <=3 :
                            if len(AttackList) == 0:
                                    AttackNumber = 0
                                    AttackList.append(AttackNumber)
                            else:
                                    AttackNumber +=1
                                    if AttackNumber <4 and 3 not in AttackList:
                                            AttackList.append(AttackNumber)
                                    else:
                                            AttackNumber = 0
                    
        if event.type == KEYUP:
            playerSprite.MoveClock = 0
            playerSprite.MoveTemp = 0
            if event.key == K_LEFT:
                LeftPress = False
                if RightPress == True:
                    player.Head = RIGHT
                elif UpPress or DownPress:
                    player.Status = MOVE
                else:
                    player.Status = STAND
                    player.Head = LEFT
            if event.key == K_RIGHT:
                RightPress = False
                if LeftPress == True:
                    player.Head = LEFT
                elif UpPress or DownPress:
                    player.Status = MOVE
                else:
                    player.x +=100
                    player.Status = STAND
                    player.Head = RIGHT
            if event.key == K_UP:
                UpPress = False
                if RightPress or LeftPress or DownPress:
                    player.Status = MOVE
                else:
                    player.Status = STAND
            if event.key == K_DOWN:
                DownPress = False
                if RightPress or LeftPress or UpPress:
                    player.Status = MOVE
                else:
                    player.Status = STAND
        if event.type == TIMER:
            #screen.fill((255,255,255))
            if not len(Enemy) and player.Hp >0:
                while True:
                        screen.blit(win,(0,0)) 
                        for event in pygame.event.get():
                                if event.type == QUIT:
                                    pygame.quit()
                        pygame.display.update()
            if player.Hp <=0 :
                while True:
                        screen.blit(Go,(0,0))
                        pygame.display.update()
                        for event in pygame.event.get():
                                if event.type == QUIT:
                                    pygame.quit()
                        
            screen.blit(background,(0,0)) 
            if LeftPress and player.Status ==MOVE and player.Head == LEFT:
                player.x -= 3
                if player.x<0:
                    player.x=0
            elif RightPress and player.Status==MOVE and player.Head == RIGHT:
                player.x += 3
                if player.x>1280-250:
                    player.x=1280-250
            if UpPress and player.Status==MOVE:
                player.y-=3
                if player.y < 200:
                    player.y = 200
            if DownPress and player.Status==MOVE:
                player.y += 3
                if player.y > 720-120:
                    player.y = 720-120
            #print(player.x)
            if  len(AttackList):
                    player.Status = ATTACK
                    #print("dx")

            
            playerSprite.update(player.Status,(player.x,player.y),player.Head,player)
            #print(playerSprite.MoveClock)
            UPDATE(Enemy)
            playerSprite.timetick()
            TIMETICK(Enemy)
         
        BLIT(Enemy)
        screen.blit(playerSprite.image,playerSprite.rect)
        tempRect = Rect((30,30),(1280-60,30))
        pygame.draw.rect(screen,(255,255,255),tempRect,1)
        if player.Hp >=0:
                tempRect2 = Rect((31,31),((player.Hp/500)*1280-62,28))
                pygame.draw.rect(screen,(220,20,60),tempRect2,0)
        
     pygame.display.update()
     
