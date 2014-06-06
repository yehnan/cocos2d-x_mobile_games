//
//  ScoreScene.h
//  Angry_Squirrel
//
//  Created by Luo on 13-10-24.
//
//

#ifndef __Angry_Squirrel__ScoreScene__
#define __Angry_Squirrel__ScoreScene__
#include "cocos2d.h"
#include <iostream>
using namespace cocos2d;
class ScoreScene :public CCLayer
{
public:
    static CCScene *scene ();
    virtual bool init();
    CREATE_FUNC(ScoreScene);
private:
    void backMenu();
};
#endif /* defined(__Angry_Squirrel__ScoreScene__) */
