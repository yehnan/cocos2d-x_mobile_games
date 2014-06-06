//
//  AboutScene.cpp
//  planegame
//
//  Created by 沈 shen on 13-10-7.
//
//

#include "AboutScene.h"
#include "GameOver.h"
#include "Menu.h"
#include "Global.h"

using namespace cocos2d;


AboutScene::AboutScene()
{
	x=0;
	y=0;
	time=0;
	speed=0;
	tempx=0;
	size = CCDirector::sharedDirector()->getWinSize();
	pSprite = CCSprite::create("about.png");
	pSprite2 =  CCSprite::create("menu.png");
    
}
CCScene* AboutScene::scene()
{
	CCScene * scene = NULL;
	do
        {
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		AboutScene *layer = AboutScene::create();
		CC_BREAK_IF(! layer);
        
		scene->addChild(layer);
        } while (0);
    
	return scene;
}

bool AboutScene::init()
{
	this->setTouchEnabled(true);
	this->registerWithTouchDispatcher();
    
	bool bRet = false;
	do
        {
		CC_BREAK_IF(! CCLayer::init());
        
		CC_BREAK_IF(! pSprite);
		CC_BREAK_IF(! pSprite2);
        
		pSprite->setAnchorPoint(ccp(0,0));
		pSprite2->setAnchorPoint(ccp(0,0));
		this->addChild(pSprite);
		this->addChild(pSprite2);
        
		this->schedule(schedule_selector(GameOver::update));
		bRet = true;
        } while (0);
    
	return bRet;
}

void AboutScene::menuCloseCallback(CCObject* pSender)
{
    
	CCDirector::sharedDirector()->end();
}

void AboutScene::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location=touch->getLocation();
	time = 0;
	tempx = location.x;
    
}

void AboutScene::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(*(pTouches->begin()));
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint location=touch->getLocation();
	if (tempx!=0)
        {
		x = location.x-tempx;
        }
	
    
}

void AboutScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint location=touch->getLocation();
	
	if(time<6){//
		if(x>0)
			speed=20;
		else if(x<0)
			speed =-20;
	}else if(x< -size.width/2){
		speed=-20;
	}else if(x> size.width/2){
		speed = 20;
	}else{
		x = 0;
	}
    
}

void AboutScene::update(float dt)
{
	time++;
	x+=speed;
	pSprite->setPosition(ccp(x,0));
	pSprite2->setPosition(ccp(x+size.width,0));
	if(speed>0)speed+=10;
	else if(speed<0)speed-=10;
	if(x<-size.width-speed||x>size.width-speed){
		CCDirector::sharedDirector()->replaceScene(Menu::scene());
	}
    
}