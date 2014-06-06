#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameOver : public cocos2d::CCLayer
{
public:

	GameOver(void);
	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void menuCloseCallback(CCObject* pSender);


	void update(float dt);

	//
	void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	CREATE_FUNC(GameOver);

private:

	float x,y;//
	float tempx;//
	int time;
	float speed;
	CCSprite* pSprite;
	CCSprite* pSprite2;

};

#endif  // __HELLOWORLD_SCENE_H__