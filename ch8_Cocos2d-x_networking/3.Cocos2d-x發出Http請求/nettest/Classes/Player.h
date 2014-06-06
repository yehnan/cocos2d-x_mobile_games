//
//  Player.h
//  nettest
//
//  Created by 沈 shen on 13-11-2.
//
//

#ifndef __nettest__Player__
#define __nettest__Player__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
//人物移动的方向
enum ENUM_PLAYER_DIR {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_STOP  //停止
};
class Player:public CCLayer
{public:
    CREATE_FUNC(Player);
    virtual bool init();
    int m_playerID;//玩家编号
    float m_px,m_py;//当前坐标
    float m_dx,m_dy;//目标点
    void moveTo(int x,int y);//移动到某一点
    void moveToDex();//移动到目标点
    void setName(std::string name);//设置玩家名字
    int m_dir;
    std::string m_name;//当前用户昵称
    CCSprite * m_playerSprite;//人物的精灵层
    CCLabelTTF * m_playerLabelName;//人物昵称的精灵层
    CCAnimation * m_playerAni[4];//上下左右4组动画
};
#endif /* defined(__nettest__Player__) */
