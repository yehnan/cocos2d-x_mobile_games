//
//  HelloWorldScene.cpp
//  AngryBird
//
//  Created by wtrience on 13-7-8.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

enum ZOrder {
    bgZ = 0,
    gameZ = 1,
    };

enum Tag {
    bgTag = 10,
    birdTag = 11,
    };

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}

#pragma mark HelloWorld

HelloWorld::HelloWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );

    // init physics
    this->initPhysics();

    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();

    addChild(parent, 0, kTagParentNode);
    
    m_draging = false;
    m_isFlying = false;
    m_polePoint = ccp(200,200);
    m_lineRadius =100;
        
    this->addObstacles();
    this->addBirdAtPosition(ccp(200, 200));
    
    scheduleUpdate();

}

HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
    
    //delete m_debugDraw;
}

#pragma mark 初始化物理世界

void HelloWorld::initPhysics()
{

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, -25.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);

    world->SetContinuousPhysics(true);

//     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
//     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //m_debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom

    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

#pragma mark 加入各種物體

void HelloWorld::addBirdAtPosition(cocos2d::CCPoint p)
{
    CCSprite * bird = CCSprite::create("Icon-72.png");
    bird->setPosition(p);
    this->addChild(bird, gameZ, birdTag);
}

void HelloWorld::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    CCNode* parent = getChildByTag(kTagParentNode);
    
    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //just randomly picking one of the images
    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    PhysicsSprite *sprite = new PhysicsSprite();
    sprite->initWithTexture(m_pSpriteTexture, CCRectMake(32 * idx,32 * idy,32,32));
    sprite->autorelease();
    
    parent->addChild(sprite);
    
    sprite->setPosition( CCPointMake( p.x, p.y) );
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
}


void HelloWorld::addObstacles()
{
    this->addNewSpriteAtPosition(ccp(600,0));
    this->addNewSpriteAtPosition(ccp(600,32));
    this->addNewSpriteAtPosition(ccp(600,64));
    this->addNewSpriteAtPosition(ccp(600,96));
    this->addNewSpriteAtPosition(ccp(600,128));
    this->addNewSpriteAtPosition(ccp(600,160));
    this->addNewSpriteAtPosition(ccp(600,192));
    this->addNewSpriteAtPosition(ccp(600,224));
    this->addNewSpriteAtPosition(ccp(600,256));
    
    this->addNewSpriteAtPosition(ccp(650,0));
    this->addNewSpriteAtPosition(ccp(650,32));
    this->addNewSpriteAtPosition(ccp(650,64));
    this->addNewSpriteAtPosition(ccp(650,96));
    this->addNewSpriteAtPosition(ccp(650,128));
    this->addNewSpriteAtPosition(ccp(650,160));
    this->addNewSpriteAtPosition(ccp(650,192));
    this->addNewSpriteAtPosition(ccp(650,224));
    this->addNewSpriteAtPosition(ccp(650,256));
    
    this->addNewSpriteAtPosition(ccp(700,0));
    this->addNewSpriteAtPosition(ccp(700,32));
    this->addNewSpriteAtPosition(ccp(700,64));
    this->addNewSpriteAtPosition(ccp(700,96));
    this->addNewSpriteAtPosition(ccp(700,128));
    this->addNewSpriteAtPosition(ccp(700,160));
    this->addNewSpriteAtPosition(ccp(700,192));
    this->addNewSpriteAtPosition(ccp(700,224));
    this->addNewSpriteAtPosition(ccp(700,256));

}

#pragma mark draw 繪製函式

void HelloWorld::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
    
    //畫橡皮筋
    if (!m_isFlying) {
        glLineWidth(4.0f);
        ccDrawColor4B(255, 255, 255, 255);
        CCSprite * bird = (CCSprite*)this->getChildByTag(birdTag);
        ccDrawLine(m_polePoint, bird->getPosition());
    }
    
}

#pragma mark update 更新函式

void HelloWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}

#pragma mark 發射小鳥

void HelloWorld::shootBirdAtPosition(cocos2d::CCPoint p)
{
    //彈射之前給小鳥加剛體
    CCSprite * bird = (CCSprite*)this->getChildByTag(birdTag);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    bodyDef.userData = bird;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.5f, 1.5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 0.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution= 0.5f;
    body->CreateFixture(&fixtureDef);
    
    //加入剛體後 給剛體加力
    b2Vec2 force = b2Vec2(m_polePoint.x-p.x, m_polePoint.y-p.y);
    body->ApplyLinearImpulse(force, body->GetPosition());
    
}

#pragma mark 數學函數

bool HelloWorld::rectContainPoint(cocos2d::CCRect r,cocos2d::CCPoint p)
{
    printf("r.x %f r.y %f r.width %f p.x %f p.y %f \n" ,r.origin.x,r.origin.y,r.size.width,p.x,p.y);
    if (r.origin.x < p.x && r.origin.x+r.size.width > p.x && r.origin.y < p.y && r.origin.y+r.size.height > p.y) {
        return true;
    }
    else
    {
        return false;
    }
    
}

float HelloWorld::distance(cocos2d::CCPoint p1, cocos2d::CCPoint p2)
{
    float distx = p1.x - p2.x;
    float disty = p1.y - p2.y;
    float distance = sqrt(distx*distx + disty*disty);
    
    return distance;
}

cocos2d::CCPoint HelloWorld::finalPoint(cocos2d::CCPoint p)
{
    float distx = p.x - m_polePoint.x;
    float disty = p.y - m_polePoint.y;
    float distance = sqrt(distx*distx + disty*disty);
    
    float finalDistx = m_lineRadius/distance * distx;
    float finalDisty = m_lineRadius/distance * disty;
    
    cocos2d::CCPoint point = ccp(m_polePoint.x+finalDistx,m_polePoint.y+finalDisty);
    
    return point;
}

#pragma mark 觸控函式

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        CCSprite * bird = (CCSprite*)this->getChildByTag(birdTag);
        
        if (this->rectContainPoint(bird->boundingBox(), location)) {
            m_draging = true;
        }
        
    }
}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
        //讓小鳥跟著手動（不能超過橡皮筋的長度）
        if (m_draging) {
            CCSprite * bird = (CCSprite*)this->getChildByTag(birdTag);
            
            if (this->distance(m_polePoint, location) <= m_lineRadius) {
                bird->setPosition(location);
            }
            else
            {
                bird->setPosition(this->finalPoint(location));
            }
        }
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        
        location = CCDirector::sharedDirector()->convertToGL(location);
        
    }
    //放手彈射小鳥
    if (m_draging) {
        CCSprite * bird = (CCSprite*)this->getChildByTag(birdTag);
        this->shootBirdAtPosition(bird->getPosition());
        m_isFlying = true;
    }
    m_draging = false;
}

#pragma mark scene

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
