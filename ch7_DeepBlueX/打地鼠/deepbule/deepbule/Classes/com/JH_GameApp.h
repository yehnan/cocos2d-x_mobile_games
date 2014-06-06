//
//  HelloWorldScene.h
//  jhwy
//
//  Created by 沈 shen on 11-7-26.
//

#ifndef __JH_GAMEAPP_H__

#define __JH_GAMEAPP_H__


#include "cocos2d.h"
//#include "JH_game.h"
#include "JH_Image.h"
#include "JH_Sprite.h"
#include "JH_String.h"
#include "MyGame.h"

class JH_GAMEAPP : public cocos2d::CCLayer {
public:
    JH_GAMEAPP();
    ~JH_GAMEAPP();

    static cocos2d::CCScene* scene();
    
    void Run(float dt);
    virtual void onEnter();

    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent *event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent *event);
    
   CREATE_FUNC(JH_GAMEAPP);
    
private:
    bool init();
    
public:
   
    JH_Sprite *jh_sprite;
    JH_String *jh_string;
//	 JH_GAME *jh_game;
	 MyGame * myGame;
};

#endif
