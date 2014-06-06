//
//  HelloWorldScene.cpp
//  Angry_Squirrel
//
//  Created by Luo on 13-10-17.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "MenuScene.h"
#include "cocos-ext.h"
#include "CCControl.h"
#include "CCInvocation.h"
#include "CCScale9Sprite.h"
#define FLOOR_HEIGHT 62.0f
#define PTM_RATIO 32
using namespace cocos2d;
using namespace CocosDenshion;

enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

bool PhysicsSprite::isDirty(void)
{
    return true;
}

CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}

HelloWorld::HelloWorld()
{
    scoreValue = 0;
    setTouchEnabled( true );
    this->initPhysics();
    scheduleUpdate();
}

HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
}
#pragma mark -
#pragma mark init method
void HelloWorld::initPhysics()
{

      this->setTouchEnabled( true );
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // The body is also added to the world.
    groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom
    groundBox.Set(b2Vec2(0,FLOOR_HEIGHT/PTM_RATIO), b2Vec2(screenSize.width*2.0f/PTM_RATIO,FLOOR_HEIGHT/PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

    // top
    groundBox.Set(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width*2.0f/PTM_RATIO,screenSize.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
//    groundBox.Set(b2Vec2(screenSize.width*2.0f/PTM_RATIO,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width*2.0f/PTM_RATIO,0));
//    groundBody->CreateFixture(&groundBox,0);
    //加入背景
    CCSprite *addSprite = CCSprite::create("bg.png");
    addSprite->setAnchorPoint(CCPointZero);
    this->addChild(addSprite, -1);
    //加入石弩機架2
    addSprite = CCSprite::create("catapult_base_2.png");
    addSprite->setAnchorPoint(CCPointZero);
    addSprite->setPosition(CCPointMake(181.0f, FLOOR_HEIGHT));
    this->addChild(addSprite, 0);
    //加入小松鼠1
    addSprite = CCSprite::create("squirrel_1.png");
    addSprite->setAnchorPoint(CCPointZero);
    addSprite->setPosition(CCPointMake(11.0f, FLOOR_HEIGHT));
    this->addChild(addSprite, 0);
    //加入石弩機架1
    addSprite =CCSprite::create("catapult_base_1.png");
    addSprite->setAnchorPoint(CCPointZero);
    addSprite->setPosition(CCPointMake(181.0f, FLOOR_HEIGHT));
    this->addChild(addSprite, 9);
    //加入小松鼠2
    addSprite =CCSprite::create("squirrel_2.png");
    addSprite->setAnchorPoint(CCPointZero);
    addSprite->setPosition(CCPointMake(240.0f, FLOOR_HEIGHT));
    this->addChild(addSprite, 9);
    //加入雪地
    addSprite =CCSprite::create("fg.png");
    addSprite->setAnchorPoint(CCPointZero);
    this->addChild(addSprite, 10);
    //加入投射器
    CCSprite *arm = CCSprite::create("catapult_arm.png");
    this->addChild(arm, 1);
    b2BodyDef armBodyDef;//建立物體定義，這裡的物體是地面盒
    armBodyDef.type = b2_dynamicBody;//動態類型
    armBodyDef.linearDamping = 1;//直線衰減
    armBodyDef.angularDamping = 1;//固定衰减
    armBodyDef.position.Set(230.0f/PTM_RATIO, (FLOOR_HEIGHT+91.0f)/PTM_RATIO);//設定物體位置
    armBodyDef.userData =arm;
    armBody = world->CreateBody(&armBodyDef);//世界物件建立物體
    b2PolygonShape armBox;//建立一個多邊形物件
    b2FixtureDef armBoxDef;//建立夾具
    armBoxDef.shape = &armBox;
    armBoxDef.density = 0.3F;
    armBox.SetAsBox(11.0f/PTM_RATIO, 91.0f/PTM_RATIO);
    armFixture = armBody->CreateFixture(&armBoxDef);//使用物體物件建立夾具
    //
    b2RevoluteJointDef armJointDef;
    armJointDef.Initialize(groundBody, armBody, b2Vec2(233.0f/PTM_RATIO, FLOOR_HEIGHT/PTM_RATIO));
    armJointDef.enableLimit = true;
    armJointDef.enableMotor = true;//啟用馬達
    armJointDef.motorSpeed = -10;//馬達速度
    armJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(9);//彈射臂在9度的时候（稍微向左彎曲）會停止旋轉
    armJointDef.upperAngle = CC_DEGREES_TO_RADIANS(75);//在75度的时候（向左彎曲的程度更多）
    armJointDef.maxMotorTorque = 700;//最大馬達扭距
    armJoint = (b2RevoluteJoint*)world->CreateJoint(&armJointDef);
    //建立有一個0.5秒的動作延遲用於導彈的初始化位置擺放
    CCDelayTime *delayAction = CCDelayTime::create(0.5f);
    CCCallFunc *callSelectorAction =CCCallFunc::create(this, callfunc_selector(HelloWorld::resetGame));
    this->runAction(CCSequence::create(delayAction,callSelectorAction,NULL));
    schedule( schedule_selector(HelloWorld::tick) );
    contactListener = new MyContactListener();
    world->SetContactListener(contactListener);
    //下雪
    
    //分數欄
    CCLabelTTF *scoreLabel = CCLabelTTF::create("分數:", "Helvetica-Blod", 24);
    scoreLabel->setPosition(ccp(30,screenSize.height-22 ));
    this->addChild(scoreLabel);
    //返回按鈕
    
}
#pragma mark -
#pragma mark event methods
void HelloWorld::draw()
{
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
}


void HelloWorld::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    world->Step(dt, velocityIterations, positionIterations);
    
       for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}
//註冊觸控分發器
void HelloWorld::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}
//建立松果
void HelloWorld::createBUllets(int count)
{
    currentBullet = 0;
    float pos = 62.0f;
    
    if (count > 0)
    {
        float delta = (count > 1)?((165.0f - 62.0f - 30.0f) / (count - 1)):0.0f;
        
        
        for (int i=0; i<count; i++, pos += delta)
        {
            CCSprite *sprite = CCSprite::create("acorn.png");
            this->addChild(sprite, 1);
            
            b2BodyDef bulletBodyDef;
            bulletBodyDef.type = b2_dynamicBody;
            bulletBodyDef.bullet = true;
            bulletBodyDef.position.Set(pos/PTM_RATIO,(FLOOR_HEIGHT+15.0f)/PTM_RATIO);
            bulletBodyDef.userData = sprite;
            b2Body *bullet = world->CreateBody(&bulletBodyDef);
            bullet->SetActive(false);
            
            b2CircleShape circle;
            circle.m_radius = 15.0/PTM_RATIO;
            
            b2FixtureDef ballShapeDef;
            ballShapeDef.shape = &circle;
            ballShapeDef.density = 0.8f;
            ballShapeDef.restitution = 0.2f;
            ballShapeDef.friction = 0.99f;
            bullet->CreateFixture(&ballShapeDef);
            
            bullets.push_back(bullet);
        }
    }
}
//該方法用來加入導彈
bool HelloWorld::attachBullet()
{
    if (currentBullet<bullets.size())
    {
        bulletBody = (b2Body*)bullets.at(currentBullet++);
        bulletBody->SetTransform(b2Vec2(230.0f/PTM_RATIO, (155.0f+FLOOR_HEIGHT)/PTM_RATIO), 0.0f);//改變物體中心位置
        bulletBody->SetActive(true);
        b2WeldJointDef weldJointDef;//建立一個接頭關節,用來绑定彈射臂定點位置
        weldJointDef.Initialize(bulletBody, armBody, b2Vec2(230.0f/PTM_RATIO,(155.0f+FLOOR_HEIGHT)/PTM_RATIO));
        weldJointDef.collideConnected = false;//設定碰撞連接為false
        
        bulletJoint = (b2WeldJoint*)world->CreateJoint(&weldJointDef);
        return true;//如果有剩餘砲彈則回傳true

    }
    return false;//没有剩餘砲彈則回傳false
}
//建立目標
void HelloWorld::createTargets()
{
    targets.clear();
    enemies.clear();

    this->createTarget("brick_2.png", CCPointMake(675.0, FLOOR_HEIGHT), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(741.0, FLOOR_HEIGHT), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(741.0, FLOOR_HEIGHT+23.0f), 0.0f, false, false, false);
    this->createTarget("brick_3.png", CCPointMake(672.0, FLOOR_HEIGHT+46.0f), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(707.0, FLOOR_HEIGHT+58.0f), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(707.0, FLOOR_HEIGHT+81.0f), 0.0f, false, false, false);
    
    this->createTarget("head_dog.png", CCPointMake(702.0, FLOOR_HEIGHT), 0.0f, true, false, true);
    this->createTarget("head_cat.png", CCPointMake(680.0, FLOOR_HEIGHT+58.0f), 0.0f, true, false, true);
    this->createTarget("head_dog.png", CCPointMake(740.0, FLOOR_HEIGHT+58.0f), 0.0f, true, false, true);
    
    this->createTarget("brick_2.png", CCPointMake(770.0, FLOOR_HEIGHT), 0.0f, false, false, false);
    this->createTarget("brick_2.png", CCPointMake(770.0, FLOOR_HEIGHT+46.0f), 0.0f, false, false, false);
    this->createTarget("head_dog.png", CCPointMake(830.0, FLOOR_HEIGHT), 0.0f, true, false, true);
 
    this->createTarget("brick_platform.png", CCPointMake(839.0, FLOOR_HEIGHT), 0.0f, false, true, false);
    this->createTarget("brick_2.png", CCPointMake(854.0, FLOOR_HEIGHT+28.0f), 0.0f, false, false, false);
    this->createTarget("brick_2.png", CCPointMake(854.0, FLOOR_HEIGHT+28.0f+46.0f), 0.0f, false, false, false);
    this->createTarget("head_cat.png", CCPointMake(881.0, FLOOR_HEIGHT+28.0f), 0.0f, true, false, true);
    this->createTarget("brick_2.png", CCPointMake(909.0, FLOOR_HEIGHT+28.0f), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(909.0, FLOOR_HEIGHT+28.0f+46.0f), 0.0f, false, false, false);
    this->createTarget("brick_1.png", CCPointMake(909.0, FLOOR_HEIGHT+28.0f+46.0f+23.0f), 0.0f, false, false, false);
    this->createTarget("brick_2.png", CCPointMake(882.0, FLOOR_HEIGHT+108.0f), 90.0f, false, false, false);
    

}
//建立目標
 void HelloWorld::createTarget(const char *imageName, CCPoint position, float rotation, bool isCircle, bool isStatic, bool isEnemy)
{
    //建立精靈
    CCSprite *sprite = CCSprite::create(imageName);
    this->addChild(sprite,1);
    //建立物體定義
    b2BodyDef bodyDef;
    bodyDef.type = isStatic?b2_staticBody:b2_dynamicBody;//類型動態或者靜態
    //設定位置
    bodyDef.position.Set((position.x+sprite->getContentSize().width/2.0f)/PTM_RATIO,
                         (position.y+sprite->getContentSize().height/2.0f)/PTM_RATIO);
    //設定旋轉角度
    bodyDef.angle = CC_DEGREES_TO_RADIANS(rotation);
    bodyDef.userData = sprite;
    //世界物件建立物體
    b2Body *body = world->CreateBody(&bodyDef);
    //建立夾具
    b2FixtureDef boxDef;
    //判断是圓形還是多邊形
    if (isCircle)
    {
        b2CircleShape circle;
        circle.m_radius = sprite->getContentSize().width/2.0f/PTM_RATIO;
        boxDef.shape = &circle;
    }else
    {
        b2PolygonShape box;
        box.SetAsBox(sprite->getContentSize().width/2.0f/PTM_RATIO, sprite->getContentSize().height/2.0f/PTM_RATIO);
        boxDef.shape = &box;
    }
    if (isEnemy)
    {
        //userData用於標記敵人
        boxDef.userData = (void*)1;
        enemies.push_back(body);
    }
    
    boxDef.density = 0.5f;
    body->CreateFixture(&boxDef);
    
    targets.push_back(body);
}
//重置遊戲
void HelloWorld::resetGame()
{
    if (bullets.size()!=NULL)
    {
        for (vector<b2Body*>::iterator bulletPointer = bullets.begin(); bulletPointer!=bullets.end();++bulletPointer )
        {
            b2Body *bullet = (b2Body*)*bulletPointer;
            CCNode *node = (CCNode*)bullet->GetUserData();
            removeChild(node, true);
            world->DestroyBody(bullet);
        }
        bullets.clear(); 
    }
    if (targets.size() !=0)
    {
        for (vector<b2Body*>::iterator targetPointer = targets.begin(); targetPointer != targets.end(); targetPointer++)
        {
            b2Body *target = (b2Body*)*targetPointer;
            CCNode *node = (CCNode*)target->GetUserData();
            removeChild(node, true);
            world->DestroyBody(target);
        }
        targets.clear();
        enemies.clear();
        
    }
    this->createBUllets(4);
    this->attachBullet();
     this->createTargets();
    //開始執行1.5秒的向右查看場景的動作
    CCFiniteTimeAction *action1 = CCMoveTo::create(1.5f, ccp(-480.0f,0.0f));
    //在執行1秒的延遲
    CCDelayTime *action3 = CCDelayTime::create(1.0f);
    //最後回到彈射位置
    CCFiniteTimeAction *action4 = CCMoveTo::create(1.5f, CCPointZero);
    //執行動作
    this->runAction(CCSequence::create(action1,action3,action4,NULL));
}
//路徑
void HelloWorld::tick(CCTime dt)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (releasingArm && bulletJoint != NULL)
    {
        //判断判断彈射臂弧度是否小於10度
        if (armJoint->GetJointAngle()<=CC_DEGREES_TO_RADIANS(10))
        {
            //釋放夾具
            releasingArm = false;
            //釋放砲彈關節
            world->DestroyJoint(bulletJoint);
            bulletJoint = NULL;
            // 設定時間延遲
            CCDelayTime *delayAction = CCDelayTime::create(5);                       CCCallFunc *callSelectorAction = CCCallFunc::create(this, callfunc_selector(HelloWorld::resetBullet));
            // 執行動作
            this->runAction(CCSequence::create(delayAction,
                                               callSelectorAction,
                                               NULL));
        }

    }
    //導彈正在移動時
    if (bulletBody&&bulletJoint==NULL)
    {
        b2Vec2 position = bulletBody->GetPosition();
        CCPoint myPosition = this->getPosition();
        CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
        //移動攝影機
        if (position.x > screenSize.width / 2.0f / PTM_RATIO)
        {//如果松果運行中的座標大於螢幕一半在初一32，則當前螢幕向右移動
            myPosition.x = -MIN(screenSize.width * 2.0f - screenSize.width, position.x * PTM_RATIO - screenSize.width / 2.0f);
            this->setPosition(myPosition);
        }

    }
    //檢測衝擊力
    std::set<b2Body*>::iterator pos;
    //尋訪檢測衝擊力的監聽器
    for(pos = contactListener->contacts.begin();
        pos!= contactListener->contacts.end();++pos)
    {
        b2Body *body = *pos;
        CCNode *contactNode = (CCNode*)body->GetUserData();
        CCPoint position = contactNode->getPosition(); 
        //移除敵人
        this->removeChild(contactNode, true);
               world->DestroyBody(body);
        //分數加100
        scoreValue+=100;
        //分數數字加入layer中
        std::string strScore=ConvertToString(scoreValue);
        CCLabelTTF* labelScores = CCLabelTTF::create(strScore.c_str(), "Helvetica-Blod", 24);
        labelScores->setPosition(ccp(110,winSize.height-22));
        labelScores->setColor(ccc3(255, 255, 0));
        this->addChild(labelScores);

        CCLog("sffd%d",scoreValue);
        //粒子效果
        CCParticleSun *explosion = CCParticleSun::createWithTotalParticles(200);
        explosion->retain();
        explosion->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
        explosion->setAutoRemoveOnFinish(true);
        explosion->setStartSizeVar(10.0f);
        explosion->setSpeed(70);
        explosion->setAnchorPoint(ccp(0.5,0.5));
        explosion->setPosition(position);
        explosion->setDuration(1.0f);
        addChild(explosion, 11);
        explosion->release();
    }
    //從監聽器迭代器中移除
    contactListener->contacts.clear();

}
// 用於检查是否已经摧毁完敵人,如果摧毁完則執行松果重置
void HelloWorld::resetBullet()
{
    if (enemies.size() == 0)
    {
        CCDelayTime *delayAction = CCDelayTime::create(2.0f);
        CCCallFunc *callSelectorAction = CCCallFunc::create(this, callfunc_selector(HelloWorld::resetGame));
        this->runAction(CCSequence::create(delayAction,callSelectorAction,NULL));
    }
    else if (this->attachBullet())
    {
        this->runAction(CCMoveTo::create(2.0, CCPointZero));
    }
    else
    {
        CCDelayTime *delayAction = CCDelayTime::create(2.0f);
        CCCallFunc *callSelectorAction = CCCallFunc::create(this, callfunc_selector(HelloWorld::resetGame));
        this->runAction(CCSequence::create(delayAction,callSelectorAction,NULL));
        
    }
    
}
void HelloWorld:: backMenu()
{

}
#pragma mark -
#pragma mark touches methods
void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSetIterator item;
    for (item=touches->begin(); item!=touches->end(); item++)
    {
        if (mouseJoint != NULL)
        {
            return;
        }
        //取得觸控點
        CCTouch *myTouch = (CCTouch *)(*item);
        CCPoint location = myTouch->getLocationInView();
        //座標轉換
        location = CCDirector::sharedDirector()->convertToGL(location);
        b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
        
        if (locationWorld.x < armBody->GetWorldCenter().x + 50.0/PTM_RATIO)
        {
            b2MouseJointDef md;
            md.bodyA = groundBody;
            md.bodyB = armBody;
            md.target = locationWorld;
            md.maxForce = 2000;
            
            mouseJoint = (b2MouseJoint *)world->CreateJoint(&md);
        }
   
    }
}
void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCSetIterator item;
    for (item = touches->begin(); item!=touches->end(); item++)
    {
        if (mouseJoint == NULL)
        {
            return;
        }
        
        CCTouch *myTouch = (CCTouch *)(*item);
        CCPoint location = myTouch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
        
        mouseJoint->SetTarget(locationWorld);
    
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    if (mouseJoint != NULL)
    {
        if (armJoint->GetJointAngle() >= CC_DEGREES_TO_RADIANS(20))
        {
            releasingArm = true;
        }
        
        world->DestroyJoint(mouseJoint);
        mouseJoint = NULL;
        return;
    }
}
#pragma mark -
#pragma mark life
 void HelloWorld::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
