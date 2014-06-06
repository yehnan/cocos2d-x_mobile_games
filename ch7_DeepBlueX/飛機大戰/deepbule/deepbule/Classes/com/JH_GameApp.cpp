//
//  HelloWorldScene.cpp
//  jhwy
//
//  Created by 沈 shen on 11-7-26.
//


#include "JH_GAMEAPP.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;
JH_GAMEAPP::JH_GAMEAPP()
{
}
JH_GAMEAPP::~JH_GAMEAPP()
{
}
CCScene* JH_GAMEAPP::scene()
{
        // 'scene' is an autorelease object.
        CCScene *scene = CCScene::create();
        // 'layer' is an autorelease object.
        JH_GAMEAPP *layer = JH_GAMEAPP::create();
        // add layer as a child to scene
        scene->addChild(layer);
        // return the scene
        return scene;
}
bool JH_GAMEAPP::init()
{
    bool ret = false;
    if (ret = CCLayer::init()) 
    {
        this->setTouchEnabled(true);
        CCSize wins = CCDirector::sharedDirector()->getWinSize();        
        jh_sprite= JH_Sprite::Getinstance();
        jh_game= JH_GAME::instance;
        jh_string= JH_String::Getinstance();
        jh_game->screenwidth=wins.width;
        jh_game->screenheigth=wins.height;
        jh_game->start();
        schedule(schedule_selector(JH_GAMEAPP::Run));
    }
    
    return ret;
}

void JH_GAMEAPP::onEnter()
{
        CCLayer::onEnter();
}

void JH_GAMEAPP::Run(float delta)
{
    int steps = 2;
    float dt = delta/(float)steps;
   
    //檢查是否有精靈變化
    if (jh_sprite->sprite_run) 
	{
        Sprites* spritehead;
        spritehead=jh_sprite->sprite_head->next;
        Sprites* spriteprevious=jh_sprite->sprite_head;
        while (spritehead!=NULL)
		{
            if (spritehead->sprite_change==1) 
			{
                addChild(spritehead->sprite,spritehead->layertag);
                spritehead->sprite_change=0;
            }else if(spritehead->sprite_change==2)
            {
                spriteprevious->next=spritehead->next;
                removeChild(spritehead->sprite,true);
                spritehead->sprite->release();
                spritehead->next=NULL;
                delete spritehead;
                spritehead=spriteprevious;
            }
            spriteprevious=spritehead;
            spritehead=spritehead->next;
        }
        spritehead=NULL;
        spriteprevious=NULL;
        jh_sprite->sprite_run=false;
    }
    //檢查是否有文字變化
    if (jh_string->strings_run) {
        Strings* spritehead;
        spritehead=jh_string->strings_head->next;
        Strings* spriteprevious=jh_string->strings_head;
        while (spritehead!=NULL) {
            if (spritehead->Str_change==1) {
                addChild(spritehead->label,spritehead->layertag);
                spritehead->Str_change=0;
            }else if(spritehead->Str_change==2)
                {
                spriteprevious->next=spritehead->next;
                removeChild(spritehead->label,true);
               // spritehead->label->release();
                spritehead->next=NULL;
                delete spritehead;
                spritehead=spriteprevious;
                }
            spriteprevious=spritehead;
            spritehead=spritehead->next;
        }
        spritehead=NULL;
        spriteprevious=NULL;
        jh_sprite->sprite_run=false;
    }
    
    jh_game->run(dt);
}

void JH_GAMEAPP::ccTouchesBegan(CCSet *touches, CCEvent *event)
{
    CCSetIterator it;
    CCTouch *touch;
    
    for (it = touches->begin(); it != touches->end(); it++) {
        touch = (CCTouch*)(*it);
        
        if (! touch) {
            break;
        }
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        jh_game->touchbegin(location.x, location.y);
    }
}

void JH_GAMEAPP::ccTouchesEnded(CCSet *touches, CCEvent *event)
{
        CCSetIterator it;
        CCTouch *touch;
        
        for (it = touches->begin(); it != touches->end(); it++) {
                touch = (CCTouch*)(*it);
                
                if (! touch) {
                        break;
                }
                
                CCPoint location = touch->getLocationInView();
                location = CCDirector::sharedDirector()->convertToGL(location);
                jh_game->touchend(location.x, location.y);
        }
    //removeAllChildrenWithCleanup(true);
}

