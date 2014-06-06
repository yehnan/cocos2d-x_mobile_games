//
//  MenuScene.cpp
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-6.
//
//

#include "MenuScene.h"
#include "HelloWorldScene.h"
#include "ScoreScene.h"
#include "Show.h"
#define PTM_RATIO 32
#define FLOOR_HEIGHT 62.0f
#pragma mark -
#pragma mark eveth methods
void MenuScene::MoveToOther()
{
    
//    switch (item->getTag())
//    {
//        case 0:
//            
//            break;
//            
//        default:
//            break;
//    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(.05, HelloWorld::scene()));
    
}
#pragma mark -
#pragma mark init
bool MenuScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //加入背景
    CCSprite *addSprite = CCSprite::create("bg.png");
    addSprite->setAnchorPoint(CCPointZero);
    this->addChild(addSprite, -1);
    //加入雪地
    addSprite =CCSprite::create("fg.png");
    addSprite->setAnchorPoint(CCPointZero);
    this->addChild(addSprite, 10);
    //建立開始選單
    CCMenuItemFont  *menuStart = CCMenuItemFont::create("Start", this, menu_selector(MenuScene::MoveToOther));
    menuStart->setAnchorPoint(CCPointZero);
    menuStart->setPosition(ccp(50,50));
    menuStart->setTag(1);
    //見樂設定選單
    CCMenuItemFont *menuSet = CCMenuItemFont::create("Set", this, menu_selector(MenuScene::MoveToOther));
    menuSet->setAnchorPoint(CCPointZero);
    menuSet->setPosition(ccp(50,30));
    menuSet->setTag(2);
    //建立高分榜
    CCMenuItemFont *menuScore = CCMenuItemFont::create("Score", this, menu_selector(MenuScene::MoveToOther));
    menuScore->setAnchorPoint(CCPointZero);
    menuScore->setPosition(ccp(50,20));
    menuScore->setTag(3);
    //建立說明選單
    CCMenuItemFont *menuHelp = CCMenuItemFont::create("Help", this, menu_selector(MenuScene::MoveToOther));
    menuHelp->setAnchorPoint(CCPointZero);
    menuHelp->setPosition(ccp(50,0));
    menuHelp->setTag(4);
    CCMenu *menu = CCMenu::create(menuStart,menuSet,menuScore,menuHelp,NULL);
    this->addChild(menu);
    //小松鼠
    CCSprite *sprite = CCSprite::create("squirrel_2.png");
    sprite->setPosition(ccp(50, 100));
    this->addChild(sprite);
      //動畫
    this->schedule(schedule_selector(MenuScene::animation), 1.0f);
    //下雪
    m_emitter = CCParticleSnow::create();
    m_emitter->retain();
    this->addChild(m_emitter, 10);
    
    CCPoint p = m_emitter->getPosition();
    m_emitter->setPosition( ccp( p.x, p.y-110) );
    m_emitter->setLife(3);
    m_emitter->setLifeVar(1);
    
    // gravity
    m_emitter->setGravity(ccp(0,-10));
    
    // speed of particles
    m_emitter->setSpeed(130);
    m_emitter->setSpeedVar(30);
    
    
    ccColor4F startColor = m_emitter->getStartColor();
    startColor.r = 0.9f;
    startColor.g = 0.9f;
    startColor.b = 0.9f;
    m_emitter->setStartColor(startColor);
    
    ccColor4F startColorVar = m_emitter->getStartColorVar();
    startColorVar.b = 0.1f;
    m_emitter->setStartColorVar(startColorVar);
    
    m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
    
    m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("snow.png") );
    
     m_emitter->setPosition( ccp(winSize.width / 2, winSize.height ) );

    return true;
}
void MenuScene::animation()
{
    CCSprite *bullet = CCSprite::create("acorn.png");
    bullet->setPosition(ccp(0, 0));
    this->addChild(bullet);
    CCActionInterval *jumpTo = CCJumpTo::create(1.0f, ccp(480, 0), 150, 1);
    bullet->runAction(jumpTo);
}
 cocos2d::CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}