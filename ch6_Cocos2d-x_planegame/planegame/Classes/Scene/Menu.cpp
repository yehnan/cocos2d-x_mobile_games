#include "Menu.h"
#include "GameScene.h"
#include "Global.h"
#include "AboutScene.h"
using namespace cocos2d;


Menu::Menu()
{
	x=0;
	y=0;
	time=0;
	speed=0;
	size = CCDirector::sharedDirector()->getWinSize();
	pSprite = CCSprite::create("menu.png");
	pSprite2 =  CCSprite::create("background2.png");

}
CCScene* Menu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        Menu *layer = Menu::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

bool Menu::init()
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
		
		this->schedule(schedule_selector(Menu::update));
		bRet = true;
    } while (0);

    return bRet;
}

void Menu::menuCloseCallback(CCObject* pSender)
{
    
    CCDirector::sharedDirector()->end();
}

void Menu::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
	//
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location =touch->getLocation();
	time = 0;
	tempx = location.x;
	
}

void Menu::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(*(pTouches->begin()));
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint location =touch->getLocation();
	x = location.x-tempx;
	
}

void Menu::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint location =touch->getLocation();
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

void Menu::update(float dt)
{
	time++;
	x+=speed;
	pSprite->setPosition(ccp(x,0));
	pSprite2->setPosition(ccp(x+size.width,0));
	if(speed>0)speed+=10;
	else if(speed<0)speed-=10;
	if(x<-size.width-speed){
        CCDirector::sharedDirector()->replaceScene(AboutScene::scene());
    }
    else if(x>size.width-speed){
		CCDirector::sharedDirector()->replaceScene(GameScene::scene());
	}

}