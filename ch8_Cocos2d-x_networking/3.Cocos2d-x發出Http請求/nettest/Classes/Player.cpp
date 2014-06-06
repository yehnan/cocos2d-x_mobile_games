//
//  Player.cpp
//  nettest
//
//  Created by 沈 shen on 13-11-2.
//
//

#include "Player.h"
#include "HelloWorldScene.h"
bool Player::init(){
    CCLayer::init();
    //建立當前的玩家精靈
    CCTexture2D * tplayer=
    CCTextureCache::sharedTextureCache()->addImage("player.png");
    CCSpriteFrame * frame01=
    CCSpriteFrame::createWithTexture(tplayer, CCRect(0,0,32,48));
    this->m_playerSprite=CCSprite::createWithSpriteFrame(frame01);
    m_playerSprite->setAnchorPoint(ccp(0,0));
    this->addChild(m_playerSprite);
    m_name=HelloWorld::getUname();//設定玩家暱稱
    //加入玩家暱稱在精靈圖片的頂部
    m_playerLabelName=CCLabelTTF::create(this->m_name.c_str(), "宋体",20);
    m_playerLabelName->setTag(111);
    m_playerLabelName->setAnchorPoint(ccp(0,0));
//    m_playerLabelName->setPosition(ccp(m_playerSprite->getPositionX(),m_playerSprite->getPositionY()+48));
//
    this->addChild(m_playerLabelName);
    //建立當前玩家的動畫
    return true;
}
void Player::setName(std::string name){
    this->m_playerLabelName->setString(name.c_str());
}
void Player::moveTo(int x,int y)//移動到某一點
{
    this->setPosition(ccp(x,y));
    //this->setPosition(ccp(x,y+48));
    this->m_px=x;
    this->m_py=y;
}
void Player::moveToDex()//移動到目標點
{   int x,y;
    x=this->getPositionX();
    y=this->getPositionY();
    if(x<m_dx)
    {   x+=5;
    }else{
        x-=5;
    }
    if(y<m_dy)
    {
      y+=5;
    }else
    { y-=5;
    }
    moveTo( x, y);
}