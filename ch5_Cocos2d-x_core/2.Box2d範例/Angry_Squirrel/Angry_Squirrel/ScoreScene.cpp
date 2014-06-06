//
//  ScoreScene.cpp
//  Angry_Squirrel
//
//  Created by Luo on 13-10-24.
//
//

#include "ScoreScene.h"
#include "MenuScene.h"
#pragma mark -
#pragma mark event methods
void ScoreScene::backMenu()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.5f, MenuScene::scene()));
}
#pragma mark -
#pragma mark init
CCScene *ScoreScene::scene ()
{
    CCScene *scene = CCScene::create();
    ScoreScene *layer = ScoreScene::create();
    scene->addChild(layer);
        return scene;
}
bool ScoreScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    //取得視窗尺寸
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //建立一個背景
    CCSprite *backGround = CCSprite::create("score_bg.png");
    backGround->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(backGround);
    //加入一個字串（取得儲存的積分）
    std::string scoreStr = "";
    //取得儲存的積分
    std::string score = CCUserDefault::sharedUserDefault()->getStringForKey("user_score","-1").c_str();
    //判斷目前是否有最高記錄
    if (atoi(score.c_str())!=-1)
    {
       //如果有最高記錄
        scoreStr+=score;
    }else
    {
        scoreStr = "0";
    }
    //把分數以Label加入到圖層並顯示
    CCLabelTTF* ttfAbout = CCLabelTTF::create(scoreStr.c_str(), "Helvetica", 23);
    ttfAbout->setPosition(ccp(winSize.width*0.5-50,winSize.height*0.5+40));
    ttfAbout->setColor(ccc3(255, 0, 0));
    addChild(ttfAbout);
    //加入一個按鈕，用於返回選單
    CCLabelTTF* ttback =CCLabelTTF::create("返回主選單", "Helvetica", 23);
    ttback->setColor(ccc3(255, 255, 0));
    CCMenuItemLabel* menuLabel= CCMenuItemLabel::create(ttback, this, menu_selector(ScoreScene::backMenu));
    menuLabel->setPosition(ccp(0,-200));
    CCMenu* menu =CCMenu::create(menuLabel,NULL);
   this->addChild(menu);

    return true;
}