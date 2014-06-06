#include "MyGame.h"
#include <time.h>
MyGame * MyGame::instance;

enum {
	IMG_menu = 0,
	IMG_playGroud = 1,
	IMG_enemy = 2,
	IMG_hole = 3,
	IMG_end = 4,
};

enum{
	Layer_background = 0,//背景層
	Layer_backrole   = 1,//通用固定NPC層
	Layer_npc        = 2,
	Layer_role       = 3,//主角層
	Layer_font       = 4,//文字圖層
};

//∂Øª≠Œƒº˛ID
enum  {
	XML_1 = 0, 
	XML_2 = 1,
	XML_role = 2,//主角
};

MyGame::MyGame()
{
	m_curTime = 0;
	m_enemyId = 99999;
	m_gamePoint = 0;
	m_animationID = -1;
}

MyGame::~MyGame()
{

}
int score;
MyGame* MyGame::Getinstance()
{
	if (instance==NULL) {
		instance=new MyGame();
		instance->Init();
	}
	return instance;
}

void MyGame::start()
{
	
	srand(unsigned(time(0)));
	LoadGameImage();
	GameChangeState(JH_GAMESTATE_MENU);
}

void MyGame::GameChangeState(GameState g)
{
	jh_DeleteAllSprite();
	jh_DeleteAllString();
	m_oldgamestate = m_gamestate;
	m_gamestate = g;
	Paint();
}

void MyGame::LoadGameImage()
{
	 jh_LoadImage(IMG_menu, "start.png");
	 jh_LoadImage(IMG_playGroud,"background.png");
	 jh_LoadImage(IMG_enemy,"enemy02.png");
	 jh_LoadImage(IMG_hole,"hole.png");
	 jh_LoadImage(IMG_end,"GameEnd.png");
	
	 jh_LoadAnimation(XML_2, "guaiwu.png", "guaiwu.xml");
 jh_LoadPlistAnimation(XML_1,"001.Png","head.plist");
}

void MyGame::Paint()
{
	switch(m_gamestate)
	{
	case JH_GAMESTATE_MENU:
		jh_AddSprite(IMG_menu, 0,0,0,0,screenwidth,screenheigth,Layer_background);
		break;
	case JH_GAMESTATE_PLAY:
		m_curTime = 0;
		
		drawPlayGround();
        jh_AddString("Your point :",150,30,Layer_background);
		break;
	case  JH_GAMESTATE_END:
		jh_AddSprite(IMG_end, 0,0,0,0,screenwidth,screenheigth,Layer_background);
		break;
	}

}

void MyGame::drawPlayGround()
{
	jh_AddSprite(IMG_playGroud, 0,0,0,0,screenwidth,screenheigth,Layer_background);
	for (int i=0;i<5;i++)
	{
		for (int j=0;j<2;j++)
		{
			jh_AddSprite(IMG_hole, i*150+20,j*100+100,0,0,150,120,Layer_background);
		}
	}
}

int MyGame::run(float dt)
{
	switch(m_gamestate)
	{
	case JH_GAMESTATE_MENU:
	
		break;
	case JH_GAMESTATE_PLAY:
		char point[20] ;
		sprintf(point,"Your point :%d",m_gamePoint);
	    this->jh_DeleteString(score);
		score=jh_AddString(point,150,30,0);
		playGame(dt);
		
		break;
	case  JH_GAMESTATE_END:
		break;
	}
	return true;
}

void MyGame::playGame(float dt)
{
	m_curTime+=dt;
	if (m_curTime>=1.0f)
	{
		if(m_gamePoint>=50)
			GameChangeState(JH_GAMESTATE_END);
		jh_DeleteSprite(m_enemyId);
		int random = rand() %10;
		m_enemyId = jh_AddSprite(IMG_enemy,(random%5)*150-10,random/5*100+50,150,100,Layer_npc);
		m_enemyPos = ccp((random%5)*150-10,random/5*100+50);
		m_curTime=0;
		if (m_animationID!=-1)
		{
			jh_DeleteSprite(m_animationID);
			m_animationID = -1;
		}
		
	}
}

int MyGame::touchbegin(float px,float py)
{
	switch(m_gamestate)
	{
	case JH_GAMESTATE_MENU:
		GameChangeState(JH_GAMESTATE_PLAY);
		break;
	case JH_GAMESTATE_PLAY:
		 ChangeCoordinate(&px,&py,0,0);
		jh_DeleteAllString();
		if (px>m_enemyPos.x && px<m_enemyPos.x+150 && py>m_enemyPos.y && py<m_enemyPos.y+100)
		{
		
			jh_DeleteSprite(m_enemyId);
			m_animationID = jh_AddPlistAnimation(XML_1,m_enemyPos.x+80,m_enemyPos.y+20,0,0,false);
			m_gamePoint+=10;
		}
		break;
	case  JH_GAMESTATE_END:
		break;
	}
	return 0;
}

int MyGame::touchend(float px,float py)
{
	return 0;
}

int MyGame::touchmove(float px,float py)
{
	return 0;
} 