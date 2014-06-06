
#ifndef __EXPLODE_SCENE_H__
#define __EXPLODE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class Explode : public CCNode
{
public:
	Explode(void);
	~Explode(void);

	static Explode* explode();
	bool init();

	void addExplode(float x,float y);
	void explosionEndDid();

private:
	CCSprite* sExplode;
public:	
	bool isDie;
};

#endif