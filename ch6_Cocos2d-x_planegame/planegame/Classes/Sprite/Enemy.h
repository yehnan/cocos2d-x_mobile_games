#ifndef __ENEMY_SCENE_H__
#define __ENEMY_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Global.h"
using namespace cocos2d;
class Enemy : public CCNode
{
public:
	Enemy(void);
	~Enemy(void);

	bool init();
	static Enemy* enemy();

	void update();
	void addEnemy(int type);

public:
	int spriteW,spriteH;
	float speed;
	float x,y;
	CCSprite* sEnemy;
	int type;
	int enemyHP;
	bool isTool;
	bool isDie;
	bool isShoot;
	static const int TYPE_aaa = 1;
	static const int TYPE_bbb = 2;
	static const int TYPE_ccc = 3;


};

#endif