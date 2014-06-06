
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Explode.h"
#include "Tool.h"
#include "GameOver.h"
#include "Boss.h"
using namespace cocos2d;
class GameScene: public cocos2d::CCLayer
{
public:
	GameScene(void);
	~GameScene(void);
	bool init();
	static CCScene* scene();

	void update(float dt);            // �w�ɧ�s
	void addBullet(float dt);         // �[�J�l�u
	void addEnemy(float dt);          // �[�J�ľ�
	
	void addExplode(float x,float y); // �[�J�z���ĪG
	void addTool(float x,float y);    // �[�J�D��
	void addHp(float hp);             // �W�[�ͩR
	void subHp();                     // ��֥ͩR
	void addBoss(bool isSmall);       // �[�JBoss

	//��
	void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	CREATE_FUNC(GameScene);
private:
	Player *player;          // �D������
	CCArray *pBullet;        // �D���l�u
	CCArray *pBullet_E;      // �ľ��l�u
	CCArray *pEnemy;         // �ľ�
	CCArray *pExplode;       // �z���ĪG
	CCArray *pTool;          // �D��
	CCArray *pHp;            // �ͩR
	CCArray *pBoss;          // Boss
	bool isBoos;
	int enemyArray[10][4];
	int enemyIndex;
	int hp;
	int createBossBullet;
	int coun;
	
};

#endif
