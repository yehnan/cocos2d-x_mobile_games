#pragma once

#include "JH_GameBase.h"

//遊戲狀態
enum GameState{
	JH_GAMESTATE_MENU  = 1,//遊戲選單
	JH_GAMESTATE_PLAY  = 2,//遊戲狀態
	JH_GAMESTATE_END = 3,//關於狀態
};


class MyGame : public JH_GameBase
{
public:
	 static MyGame * instance;		//建立唯一實體
	 GameState m_gamestate;				//遊戲狀態
	 GameState m_oldgamestate;			//上次遊戲狀態
	 float	   m_curTime;
	 int	   m_enemyId;
	 CCPoint   m_enemyPos;
	 int       m_gamePoint;				//遊戲得分
	 int	   m_animationID;
public:
	MyGame();
	~MyGame();
	static MyGame* Getinstance();

	void start();					//主邏輯程式入口
	void LoadGameImage();			//載入遊戲資源  
	void Paint();					//遊戲繪製
	void GameChangeState(GameState g);  //改變遊戲狀態
	void drawPlayGround();
	void playGame(float dt);
	int run(float dt);				//遊戲執行主邏輯
	int touchbegin(float px,float py);
	int touchmove(float px,float py);
	int touchend(float px,float py);

};