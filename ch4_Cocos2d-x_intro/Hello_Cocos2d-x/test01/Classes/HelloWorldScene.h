#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class SnakeNode :public cocos2d::CCObject{
public:
	int row;
	int col;
	int dir;
};
//�[��gӭ����
class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();//ȡ�Úgӭ�����Scene
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

//�[���f������
class GameHelp :public cocos2d::CCLayer{
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	static cocos2d::CCScene * scene();//ȡ�Î��������Scene
	CREATE_FUNC(GameHelp);
	void menuBackToMain(CCObject *pSender);//�������x��
};

//�[����
class GameLayer :public cocos2d::CCLayer{
protected:
	SnakeNode *sHead;  //؝ʳ��px py
	SnakeNode *sFood;  //ʳ��
	cocos2d::CCArray * allBody;//�ߵ����w
	cocos2d::CCTexture2D * chead;
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void draw();//�L�u��ǰ��Layer
	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void logic01(float t);
	static cocos2d::CCScene * scene();//ȡ���[����
	CREATE_FUNC(GameLayer);
	void menuBackToMain(CCObject *pSender);//�������x��
};
#endif  // __HELLOWORLD_SCENE_H__