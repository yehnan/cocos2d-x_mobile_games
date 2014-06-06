//
//  Show.h
//  Angry_Squirrel
//
//  Created by Luo on 13-10-26.
//
//

#ifndef __Angry_Squirrel__Show__
#define __Angry_Squirrel__Show__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class Show :public CCLayer
{
public:
    virtual bool init();
    CREATE_FUNC(Show);
private:
    CCParticleSystemQuad *m_emitter;
};
#endif /* defined(__Angry_Squirrel__Show__) */
