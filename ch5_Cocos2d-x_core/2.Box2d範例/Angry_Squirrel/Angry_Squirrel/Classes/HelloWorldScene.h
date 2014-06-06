//
//  HelloWorldScene.h
//  Angry_Squirrel
//
//  Created by Luo on 13-10-17.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "MyContactListener.h"
using namespace cocos2d;
//主要用於把将int float等數字轉換成string型別
template<typename T>
string ConvertToString(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;
};

class HelloWorld : public cocos2d::CCLayer {
public:
    //建構式與解構式
    ~HelloWorld();
    HelloWorld();
    static cocos2d::CCScene* scene();
    //飛行路徑
    void tick(CCTime dt);
    void initPhysics();
    // 觸控註冊
    virtual void registerWithTouchDispatcher(void);
    //多點觸控方法
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    bool attachBullet();
    //生命週期函式
    virtual void onExit();
    virtual void draw();
    void update(float dt);
    //建立松果
    void createBUllets(int count);
    //重置松果
    void resetBullet();
    //重置遊戲
    void resetGame();
    //建立目標
    void createTargets();
    void createTarget(const char *imageName, CCPoint position, float rotation, bool isCircle, bool isStatic, bool isEnemy);
    void backMenu();
private:
    //分數
    int scoreValue;
    //松果
    std::vector<b2Body *> bullets;
    //目標
    std::vector<b2Body *> targets;
    //敵人
    std::vector<b2Body *> enemies;
    //目前的松果
    int currentBullet;
    //判斷是否鬆開彈臂
    bool releasingArm;
    //松果剛體
    b2Body *bulletBody;
    //焊機關節
    b2WeldJoint *bulletJoint;
    b2Fixture *armFixture;//彈臂夾具
    b2Body *armBody;//宣告一個彈臂
    b2Body *groundBody;//宣告一個地面
    b2RevoluteJoint *armJoint;//宣告一個向外翻捲的關節
    b2MouseJoint *mouseJoint;//宣告一個游標關節
    b2World* world;//宣告一個世界
    cocos2d::CCTexture2D* m_pSpriteTexture;
    //建立一個碰撞偵測衝擊力的監聽迭代器
    MyContactListener *contactListener;
};

#endif // __HELLO_WORLD_H__
