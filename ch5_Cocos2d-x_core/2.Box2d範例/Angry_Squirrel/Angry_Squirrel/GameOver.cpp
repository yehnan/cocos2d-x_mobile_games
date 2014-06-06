//
//  GameOver.cpp
//  Angry_Squirrel
//
//  Created by Ljj on 13-11-7.
//
//

#include "GameOver.h"

bool GameOver::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    return true;
}
CCScene *GameOver::scene()
{
    CCScene *scene = CCScene::create();
    GameOver *game = GameOver::create();
    scene->addChild(game);
    return scene;
}