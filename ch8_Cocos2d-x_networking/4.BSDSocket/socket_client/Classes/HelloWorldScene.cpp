#include "HelloWorldScene.h"
#include "ODSocket.h"
#include <pthread.h>
USING_NS_CC;
static HelloWorld * nowHelloWorld;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    nowHelloWorld=this;
    //初始化Socket物件
     sock_client=new ODSocket();
    //連線到Socket伺服器，顯示從伺服器發送過來的内容到場景
    sock_client->Init();
    bool res= sock_client->Create(AF_INET, SOCK_STREAM,0);
    printf("Cocos2d-x客户端socket建立%d",res);
    //連接伺服器
    res=sock_client->Connect("127.0.0.1", 8889);
    printf("連接伺服器成功 %d",res);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setTag(111);
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    //
    //接收從伺服器發過來的訊息
    if(res==1)
        {//啟動執行緒
            pthread_t tid;
            //1建立執行緒物件
            bool ok= pthread_create(&tid,NULL, HelloWorld::getMessage, NULL);
            std::cout << "執行緒啟動结果"<<ok<<endl;
            
        }
    this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
   
   
    //關閉和伺服器的連線
  //  sock_client->Close();
}
//2建立執行緒方法
void * HelloWorld::getMessage(void *){
    char buf[1024];
    while (1) {
        buf[0]=0;
    nowHelloWorld->sock_client->Recv(buf, sizeof(buf));
    
    if(strlen(buf)>10)
        {
        printf("\n%s",buf);
        nowHelloWorld->strmsg=buf;
        
        }
    }
}
void HelloWorld::update(float t){
    //在當前場景中顯示從伺服器發送過來的訊息
    CCLabelTTF * labelMsg=(CCLabelTTF *)
    nowHelloWorld->getChildByTag(111);
    labelMsg->setString(strmsg.c_str());

}