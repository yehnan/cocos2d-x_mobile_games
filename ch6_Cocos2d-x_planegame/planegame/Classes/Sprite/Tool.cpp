#include "Tool.h"

Tool::Tool(void)
{
	isDie = false;
	isFlash = false;
	speed = 0;
}

Tool::~Tool(void)
{

}
Tool *Tool::tool()
{
	Tool *tool= new Tool();

	if (tool && tool->init())
	{
		tool->autorelease();
		return tool;
	}
	CC_SAFE_DELETE(tool);
	return NULL;
}

bool Tool::init()
{

	bool bRet = false;
	do 
	{

		bRet = true;
	} while (0);

	return bRet;
}

void Tool::addTool(float _x,float _y){
	type = rand()%4+1;
	if (type == BULLET_S)
	{
		sTool = CCSprite::create("tools.png");

	}else if (type == BULLET_L)
	{
		sTool = CCSprite::create("tooll.png");
	}else if (type == HPADD)
	{
		sTool = CCSprite::create("toolh.png");
	}else if (type == FLASH)
	{
		sTool = CCSprite::create("toola.png");
	}

	x = _x;
	y = _y;
	spriteW = sTool->getContentSize().width;
	spriteH = sTool->getContentSize().height;
	this->addChild(sTool);
	this->setPosition(ccp(x,y));
	
}

void Tool:: update(){
	
	y--;
	x+=speed;
	if(--speed < -10){
		speed = 10;
	}
	this->setPosition(ccp(x,y));
	if(y < -spriteH){
		isDie = true;
	}
}

void Tool::effect(Player *player){
	if (type==BULLET_S)
	{
		if (player->type==BULLET_S)
		{
			if (++player->level>3)
				player->level = 3;	
		}
		else
			player->type=BULLET_S;
	} 
	else if(type==BULLET_L)
	{
	
		if (player->type==BULLET_L)
		{
			if (++player->level>3)
				player->level = 3;
		}
		else
			player->type=BULLET_L;
				
			
				
	}else if(type==HPADD){
		if (++player->hp==4){
			player->addPlayer(true);
			
		}else if(player->hp>5)
		    player->hp = 5;

	}else if (type==FLASH)
	{
		isFlash = true;
	}
}
