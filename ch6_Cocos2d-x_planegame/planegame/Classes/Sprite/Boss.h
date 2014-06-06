#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
using namespace cocos2d;
class Boss :public CCNode
{
public:
	Boss(void);
	~Boss(void);

	static Boss* boss();
	bool init();

	void addBoss();
	void update();
public:
	CCSprite* sBoss;
	int hp;
	float x,y;
	float spriteW,spriteH;
	float speed;
	bool isCrazy;
	bool isShoot;
	int crazyTime;
	int count;
	bool isUp;
	bool isDie;
	bool isLeft;
};
#endif