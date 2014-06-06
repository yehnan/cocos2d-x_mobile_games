//
//  MenuScene.h
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-6.
//
//

#ifndef __Angry_Squirrel__MenuScene__
#define __Angry_Squirrel__MenuScene__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class MenuScene :public CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(MenuScene);
    void MoveToOther();
    void animation();
private:
     CCSprite *backGround;
     CCParticleSystem*    m_emitter;
};
#endif /* defined(__Angry_Squirrel__MenuScene__) */
