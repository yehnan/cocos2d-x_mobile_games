#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class Player :public CCNode
{
public:
	Player(void);
	~Player(void);

	static Player *player();
	bool init();

	void update();
    void addPlayer(bool isUp);

	void acceptTouchesBegan( cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	void acceptTouchesMoved( cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	void acceptTouchesEnded( cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);

	CREATE_FUNC(Player);

private:
	CCSprite *pSprite;
	
	
	float tempx,tempy;
public:
	int hp;
	float hx,hy;
	int spriteW,spriteH;
	float x,y;
	int type;
	int level;
	int bulletSum[2][4];
	bool isDie;

};
#endif