#ifndef __TOOL_SCENE_H__
#define __TOOL_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
using namespace cocos2d;
class Tool : public CCNode
{
public:
	Tool(void);
	~Tool(void);
	static Tool* tool();
	bool init();

	void addTool(float x,float y);
	void effect(Player *player);

	void update();
private:
	static const int BULLET_S = 1;
	static const int BULLET_L = 2;
	static const int HPADD = 3;
	static const int FLASH = 4;
	
	CCSprite* sTool;
	
	
	int type;
	float speed;
	
public:
	bool isFlash;
	bool isDie;
	float x,y;
	int spriteW,spriteH;
};

#endif