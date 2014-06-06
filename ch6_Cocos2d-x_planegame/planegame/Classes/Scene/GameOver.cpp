#include "GameOver.h"
#include "Menu.h"
#include "Global.h"

using namespace cocos2d;


GameOver::GameOver()
{
	x=0;
	y=0;
	time=0;
	speed=0;
	tempx=0;
	size = CCDirector::sharedDirector()->getWinSize();
	pSprite = CCSprite::create("end.png");
	pSprite2 =  CCSprite::create("menu.png");

}
CCScene* GameOver::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		GameOver *layer = GameOver::create();
		CC_BREAK_IF(! layer);

		scene->addChild(layer);
	} while (0);

	return scene;
}

bool GameOver::init()
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

void GameOver::menuCloseCallback(CCObject* pSender)
{

	CCDirector::sharedDirector()->end();
}

void GameOver::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
	//取得觸控點
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location=touch->getLocation();
	time = 0;
	tempx = location.x;

}

void GameOver::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
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

void GameOver::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
    CCPoint location=touch->getLocation();
	
	if(time<6){//快速捲動畫面
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

void GameOver::update(float dt)
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