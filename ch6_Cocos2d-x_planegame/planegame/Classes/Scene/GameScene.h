
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

	void update(float dt);            // 定時更新
	void addBullet(float dt);         // 加入子彈
	void addEnemy(float dt);          // 加入敵機
	
	void addExplode(float x,float y); // 加入爆炸效果
	void addTool(float x,float y);    // 加入道具
	void addHp(float hp);             // 增加生命
	void subHp();                     // 減少生命
	void addBoss(bool isSmall);       // 加入Boss

	//そ
	void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	CREATE_FUNC(GameScene);
private:
	Player *player;          // 主角飛機
	CCArray *pBullet;        // 主角子彈
	CCArray *pBullet_E;      // 敵機子彈
	CCArray *pEnemy;         // 敵機
	CCArray *pExplode;       // 爆炸效果
	CCArray *pTool;          // 道具
	CCArray *pHp;            // 生命
	CCArray *pBoss;          // Boss
	bool isBoos;
	int enemyArray[10][4];
	int enemyIndex;
	int hp;
	int createBossBullet;
	int coun;
	
};

#endif
