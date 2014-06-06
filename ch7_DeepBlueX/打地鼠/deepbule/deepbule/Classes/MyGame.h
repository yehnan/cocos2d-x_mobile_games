#pragma once

#include "JH_GameBase.h"

//�[���B
enum GameState{
	JH_GAMESTATE_MENU  = 1,//�[���x��
	JH_GAMESTATE_PLAY  = 2,//�[���B
	JH_GAMESTATE_END = 3,//�P춠�B
};


class MyGame : public JH_GameBase
{
public:
	 static MyGame * instance;		//����Ψһ���w
	 GameState m_gamestate;				//�[���B
	 GameState m_oldgamestate;			//�ϴ��[���B
	 float	   m_curTime;
	 int	   m_enemyId;
	 CCPoint   m_enemyPos;
	 int       m_gamePoint;				//�[��÷�
	 int	   m_animationID;
public:
	MyGame();
	~MyGame();
	static MyGame* Getinstance();

	void start();					//��߉݋��ʽ���
	void LoadGameImage();			//�d���[���YԴ  
	void Paint();					//�[���L�u
	void GameChangeState(GameState g);  //��׃�[���B
	void drawPlayGround();
	void playGame(float dt);
	int run(float dt);				//�[�������߉݋
	int touchbegin(float px,float py);
	int touchmove(float px,float py);
	int touchend(float px,float py);

};