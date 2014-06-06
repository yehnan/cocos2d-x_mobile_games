#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ODSocket.h"
#include "Player.h"
using namespace std;
using namespace cocos2d;
static std::string uname;//玩家暱稱

class HelloWorld : public cocos2d::CCLayer
{
public:
    ODSocket * sock_client;//定義socket物件
    static void * getMessage(void *);//接收從伺服器發送過來的資料
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    static void setUname(string n);
    static string getUname();
    virtual bool init();
    Player * addPlayer(std::string uname,int uid);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
     // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void run(float t);
};

#endif // __HELLOWORLD_SCENE_H__
