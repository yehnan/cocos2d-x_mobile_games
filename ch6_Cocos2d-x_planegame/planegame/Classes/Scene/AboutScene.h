//
//  AboutScene.h
//  planegame
//
//  Created by 沈 shen on 13-10-7.
//
//

#ifndef __planegame__AboutScene__
#define __planegame__AboutScene__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class AboutScene : public cocos2d::CCLayer
{
public:
    
	AboutScene(void);
	virtual bool init();
	static cocos2d::CCScene* scene();
    
	virtual void menuCloseCallback(CCObject* pSender);
    
    
	void update(float dt);
    
	//¥•∆¡
	void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
	CREATE_FUNC(AboutScene);
    
private:
    
	float x,y;//
	float tempx;//
	int time;
	float speed;
	CCSprite* pSprite;
	CCSprite* pSprite2;
    
};
#endif /* defined(__planegame__AboutScene__) */
