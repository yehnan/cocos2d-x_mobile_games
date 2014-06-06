#include "Background.h"

Background::Background(void)
{
	x1=y1=x2=y2=0;
	speed1 = 0.5;
	speed2 = 1.5;

}

Background::~Background(void)
{
}

bool Background::init()
{
	bool bRet = false;
	do{
		background1 = CCSprite::create("background1.png");
		background1->setAnchorPoint(ccp(0,0));
		this->addChild(background1,1);
		background2 = CCSprite::create("background2.png");
		background2->setAnchorPoint(ccp(0,0));
		this->addChild(background2,0);

		background1s = CCSprite::create("background1.png");
		background1s->setAnchorPoint(ccp(0,0));
		this->addChild(background1s,1);
		background2s = CCSprite::create("background2.png");
		background2s->setAnchorPoint(ccp(0,0));
		this->addChild(background2s,0);
		
		schedule(schedule_selector(Background::update));
		bRet = true;
	}
	while(0);

	return bRet;

}

void Background::update(float dt)
{
	background1->setPosition(ccp(x1,y1));
	background2->setPosition(ccp(x2,y2));
	background1s->setPosition(ccp(x1,y1+background1s->getContentSize().height));
	background2s->setPosition(ccp(x2,y2+background2s->getContentSize().height));

	int value = 0;
	y1-=speed1;
	if(y1<-background1s->getContentSize().height){
		value = y1 + background1s->getContentSize().height;
		y1 = value;
	}
	int value2 = 0;
	y2-=speed2;
	if(y2<-background2s->getContentSize().height){
		value = y2 + background1s->getContentSize().height;
		y2 = value;
	}
	
}
