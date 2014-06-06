
#ifndef __BACKGROUND_SCENE_H__
#define __BACKGROUND_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Background:public  CCLayer
{
public:
	Background(void);
	~Background(void);

	bool init();
	void update(float dt);

	CREATE_FUNC(Background);
private:
	CCSprite *background1;
	CCSprite *background2;
	CCSprite *background1s;
	CCSprite *background2s;
	float x1,y1,x2,y2;
	float speed1,speed2;

};
#endif
