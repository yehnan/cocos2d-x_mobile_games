//
//  HelloWorldScene.h
//  AngryBird
//
//  Created by wtrience on 13-7-8.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    
    //加入小鳥
    void addBirdAtPosition(cocos2d::CCPoint p);
    //發射小鳥
    void shootBirdAtPosition(cocos2d::CCPoint p);
    //加入障礙物
    void addObstacles();
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    
    //是否正在拖動
    bool m_draging;
    //小鳥是否正在飛
    bool m_isFlying;
    //小鳥圍繞轉的點（彈弓點）
    cocos2d::CCPoint m_polePoint;
    //彈弓半徑
    int m_lineRadius;

    //數學函數
    //方形包括點
    bool rectContainPoint(cocos2d::CCRect r,cocos2d::CCPoint p);
    //計算兩點之間距離
    float distance(cocos2d::CCPoint p1,cocos2d::CCPoint p2);
    //計算小鳥在彈弓上面最終的點
    cocos2d::CCPoint finalPoint(cocos2d::CCPoint p);
    
};

#endif // __HELLO_WORLD_H__
