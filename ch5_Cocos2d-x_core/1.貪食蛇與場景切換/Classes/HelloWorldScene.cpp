#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.
		///加入三個選單項目：進入遊戲 遊戲說明 退出遊戲
		CCLabelTTF * labelstart=CCLabelTTF::create("startGame","宋体",24);
		CCLabelTTF * labelhelp=CCLabelTTF::create("GameHelp","宋体",24);
        CCLabelTTF * labelexit=CCLabelTTF::create("exitGame","宋体",24);
		//定義選單項目
		CCMenuItemLabel *mi01=CCMenuItemLabel::create(labelstart,this,
			menu_selector(HelloWorld::menuCloseCallback));
		mi01->setTag(1);
		mi01->setPosition(ccp(100,200)); 
		CCMenuItemLabel *mi02=CCMenuItemLabel::create(labelhelp,this,
			menu_selector(HelloWorld::menuCloseCallback));
		mi02->setTag(2);
		mi02->setPosition(ccp(100,150));
		
        CCMenuItemLabel *mi03=CCMenuItemLabel::create(labelexit,this,
			menu_selector(HelloWorld::menuCloseCallback));
		mi03->setTag(3);
        mi03->setPosition(ccp(100,50));
		// Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
		pCloseItem->setTag(4);
        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(mi01,mi02,mi03,pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	switch(((CCNode*)pSender)->getTag())
	{case 1:// 進入遊戲
	     CCLog("go to game");
	     CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
	   break;
	 case 2:// 進入說明
	    CCLog("go to help");
	    CCDirector::sharedDirector()->replaceScene(GameHelp::scene());
		break;
	 case 3:
	 case 4:
		CCDirector::sharedDirector()->end();
	
	
	};    
}

bool GameHelp::init(){
	if(!CCLayer::init())
	{return false;}
	CCLabelTTF * labhelp=CCLabelTTF::create("please click screen to game","宋体",15);
	labhelp->setPosition(ccp(0,280));
	this->addChild(labhelp);
	CCLabelTTF * labback=CCLabelTTF::create("MainMenu","宋体",15);
	CCMenuItemLabel * miback=CCMenuItemLabel::create(labback,this,
		menu_selector(GameHelp::menuBackToMain));
	miback->setPosition(ccp(0,0));
	CCMenu * pm=CCMenu::create(miback,NULL);
	this->addChild(pm);
	return true;
}
cocos2d::CCScene * GameHelp::scene(){
	CCScene * scene=CCScene::create();
	CCLayer * hl=GameHelp::create();
	scene->addChild(hl);
	return scene;
}//取得說明畫面
void GameHelp::menuBackToMain(CCObject *pSender)//返回主選單
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

bool GameLayer::init(){
	if(!CCLayer::init())
	{return false;}
	CCLabelTTF * labhelp=CCLabelTTF::create("this is game","宋体",15);
	labhelp->setPosition(ccp(0,340));
	this->addChild(labhelp);
	CCLabelTTF * labback=CCLabelTTF::create("MainMenu","宋体",15);
	CCMenuItemLabel * miback=CCMenuItemLabel::create(labback,this,
		menu_selector(GameLayer::menuBackToMain));
	miback->setPosition(ccp(360,200));
	//CCMenu * pm=CCMenu::create(miback,NULL);
	//pm->setPosition(ccp(0,0));
	//this->addChild(pm);
	/////
	 chead=::CCTextureCache::sharedTextureCache()->addImage("head.png");
	
	///接收觸控事件
	this->setTouchEnabled(true);
	//this->setAccelerometerEnabled(true);
	//this->setKeypadEnabled(true);
	//初始化蛇頭座標與食物座標
	sHead=new SnakeNode();
	sHead->row=rand()%10;
	sHead->col=rand()%10;
	//初始化食物座標
	sFood=new SnakeNode();
	sFood->row=rand()%10;
	sFood->col=rand()%10;
	//初始化蛇的身體
	this->allBody=cocos2d::CCArray::create();
	this->allBody->retain();
	//執行排成任務
	this->schedule(schedule_selector(GameLayer::logic01),0.5);
	return true;
}
cocos2d::CCScene * GameLayer::scene(){
	CCScene * scene=CCScene::create();
	CCLayer * hl=GameLayer::create();
	scene->addChild(hl);
	return scene;
}//取得說明畫面
void GameLayer::menuBackToMain(CCObject *pSender)//返回主選單
{
	CCDirector::sharedDirector()->replaceScene(
		HelloWorld::scene());
}

void HelloWorld::onEnter(){
	CCLayer::onEnter();
  CCLog("HelloWorld onEnter");
}
void HelloWorld::onExit(){
   CCLog("HelloWorld onExit");
}
void GameHelp::onEnter(){
	CCLayer::onEnter();
  CCLog("GameHelp onEnter");
}
void GameHelp::onExit(){
   CCLog("GameHelp onExit");
}
void GameLayer::onEnter(){
	CCLayer::onEnter();
  CCLog("GameLayer onEnter");
}
void GameLayer::onExit(){
   CCLog("GameLayer onExit");
}
void GameLayer::draw(){
	///繪製形狀
	::glLineWidth(2);//設定畫線的寬度
	for(int i=0;i<11;i++)
	{
		::ccDrawLine(ccp(0,i*32),ccp(320,i*32));//繪製11條橫線
	    ::ccDrawLine(ccp(i*32,0),ccp(i*32,320));//繪製11條豎線
	}
	//                    RGBA
	//::ccDrawColor4B(ccc4(255,0,0,255));//設定畫線的顏色
	//繪製蛇頭
	::ccDrawSolidRect(ccp(sHead->col*32+2,sHead->row*32+2),ccp(sHead->col*32+32,sHead->row*32+32),ccc4FFromccc3B(ccc3(255,0,0)));
	//繪製食物
	::ccDrawSolidRect(ccp(sFood->col*32+2,sFood->row*32+2),ccp(sFood->col*32+32,sFood->row*32+32),ccc4FFromccc3B(ccc3(0,0,255)));
	//繪製身體
	for(int i=0;i<allBody->count();i++)
	{SnakeNode * node=(SnakeNode *)allBody->objectAtIndex(i);
	::ccDrawSolidRect(ccp(node->col*32+2,node->row*32+2),
		ccp(node->col*32+32,node->row*32+32),ccc4FFromccc3B(ccc3(0,0,255)));
	 
	}
	CCRect r(340,0,57,57);
	
	chead->drawInRect(r);
	CCLayer::draw();
	
}
void GameLayer::registerWithTouchDispatcher()
{
  CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}
bool GameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	//CCLayer::ccTouchBegan(pTouch,pEvent);
	CCPoint p=pTouch->getLocation();
	int nowrow;//玩家觸控點的行
	nowrow=((int)p.y)/32;
	int nowcol;////玩家觸控點的列
	nowcol=((int)p.x)/32;
	if(::abs(nowrow-sHead->row)>abs(nowcol-sHead->col)) //上下移動
	{
		if(nowrow>sHead->row)
		{
			sHead->dir=DIR_DEF::UP;
		}else
		{
			sHead->dir=DIR_DEF::DOWN;
		}
	  
	}else////左右移動
	{
		if(nowcol>sHead->col)
		{
			sHead->dir=DIR_DEF::RIGHT;
		}else
		{ sHead->dir=DIR_DEF::LEFT;
		}
	}

	CCLog("rand %d",rand());
	CCLog("you touchbegan%f,%f",p.x,p.y);
	return true;
}
void GameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint p=pTouch->getLocation();
	CCLog("you ccTouchMoved%f,%f",p.x,p.y);
}
void GameLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint p=pTouch->getLocation();
	CCLog("you ccTouchEnded%f,%f",p.x,p.y);
}
   
void GameLayer::logic01(float t)
{   
	//移動蛇的身體
	for(int i=allBody->count()-1;i>=0;i--)
	{ SnakeNode * sn=(SnakeNode *)allBody->objectAtIndex(i);
	 if(i>0) 
	  { SnakeNode * snpre=(SnakeNode *)allBody->objectAtIndex(i-1);
	 	  sn->dir=snpre->dir;
	  sn->row=snpre->row;
	  sn->col=snpre->col;}
	 else if(i==0)
	 {//移動第一個節點
		 sn->dir=sHead->dir;
		 sn->row=sHead->row;
		 sn->col=sHead->col;
	 }
	}
	//移動蛇頭
	switch(sHead->dir)
	{case DIR_DEF::UP:
	     sHead->row++;
		 if(sHead->row>=10){sHead->row=0;}
		 break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if(sHead->row<0){sHead->row=9;}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if(sHead->col<0){sHead->col=9;}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		 if(sHead->col>=10){sHead->col=0;}
		break;
   };
  
   
  //碰撞偵測
	if(sHead->row==sFood->row&&sHead->col==sFood->col)
	{ //食物消失
		sFood->row=rand()%10;
		sFood->col=rand()%10;
	  //加入身體到容器
		SnakeNode * sn=new SnakeNode();
		SnakeNode *lastNode=NULL;
		if(allBody->count()>0)
			lastNode=(SnakeNode *)allBody->lastObject();
		else
			lastNode=sHead;
		switch(lastNode->dir)
		{case DIR_DEF::UP:
		   sn->row=lastNode->row-1;
		   sn->col=lastNode->col;
		   break;
		 case DIR_DEF::DOWN:
		   sn->row=lastNode->row+1;
		   sn->col=lastNode->col;
		   break;
         case DIR_DEF::LEFT:
		   sn->row=lastNode->row;
		   sn->col=lastNode->col+1;
		   break;
         case DIR_DEF::RIGHT:
		   sn->row=lastNode->row;
		   sn->col=lastNode->col-1;
		   break;
		}
		this->allBody->addObject(sn);
	}

}