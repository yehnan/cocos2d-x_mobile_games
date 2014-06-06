//
//  GameOver.h
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-7.
//
//

#ifndef __Angry_Squirrel__GameOver__
#define __Angry_Squirrel__GameOver__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class GameOver :public CCLayer
{
public:
    static CCScene *scene();
    bool init();
    CREATE_FUNC(GameOver);
   
};
#endif /* defined(__Angry_Squirrel__GameOver__) */
