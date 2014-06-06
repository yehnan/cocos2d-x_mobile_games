#ifndef __BULLET_SCENE_H__
#define __BULLET_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Global.h"
#include "Boss.h"
#include "Enemy.h"
#include "Math.h"
#include "math.h"



using namespace cocos2d;
class Bullet:public CCNode
{
public:
	Bullet(void);
	~Bullet(void);

	static Bullet* bullet();
	bool init();

	void update();
	void addBullet(Player* player,int id);
	void addBullet(Boss* boss,int id,int ai);
	void addBullet(Boss* boss,Player* player);
	void addBullet(Enemy* enemy);

	void track(float targetX,float targetY);
public:
	CCSprite* bullet1;
	float x,y;
	int spriteW,spriteH;
	int type;
	int level;
	float speed;
	float speedx,speedy;
	float var;
	float pSan[7][2]; //
	float pLaser[7][2];
	bool isDie;
	static const int BULLET_PLAYER = 1;
	static const int BULLET_ENEMY = 2;
	static const int BULLET_BOSS1 = 3;
	static const int BULLET_BOSS2 = 4;
	int bulletType;
	int AI;
	int id;

};

#endif