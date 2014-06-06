#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
typedef enum {
UP=1,
DOWN,
LEFT,
RIGHT
}DIR_DEF;
class SnakeNode :public cocos2d::CCObject{
public:
	int row;
	int col;
	int dir;
};
//遊戲歡迎畫面
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();//取得歡迎畫面的Scene
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

//遊戲說明畫面
class GameHelp :public cocos2d::CCLayer{
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	static cocos2d::CCScene * scene();//取得幫助畫面的Scene
	CREATE_FUNC(GameHelp);
	void menuBackToMain(CCObject *pSender);//返回主選單
};

//遊戲畫面
class GameLayer :public cocos2d::CCLayer{
protected:
	SnakeNode *sHead;  //貪食蛇px py
	SnakeNode *sFood;  //食物
	cocos2d::CCArray * allBody;//蛇的身體
	cocos2d::CCTexture2D * chead;
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();//繪製當前的Layer
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void logic01(float t);
	static cocos2d::CCScene * scene();//取得遊戲畫面
	CREATE_FUNC(GameLayer);
	void menuBackToMain(CCObject *pSender);//返回主選單
};
#endif  // __HELLOWORLD_SCENE_H__