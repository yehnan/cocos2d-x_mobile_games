//
//  Show.cpp
//  Angry_Squirrel
//
//  Created by Luo on 13-10-26.
//
//

#include "Show.h"
#pragma mark -
#pragma mark init 
 bool Show:: init()
{
    CCLayer::init();
    m_emitter = new CCParticleSystemQuad();
    //初始化900個粒子
    m_emitter->initWithTotalParticles(900);
    //加入紋理圖片
    m_emitter->setTexture(CCTextureCache::sharedTextureCache()->addETCImage("snowflake.png"));
    //設定發射粒子的持續時間，-1代表一直發射，0沒有意義，其他數值代表持續時間
    m_emitter->setDuration(-1);
    //設定中心方向，這個是相對發射點，x正向為右，y正向為上
    m_emitter->setGravity(CCPoint(0, -240));
    //設定角度，角度的變化率
    m_emitter->setAngle(90);
    m_emitter->setAngleVar(360);
    //設定度弳向加速度，弳向加速度變化率
    m_emitter->setRadialAccel(50);
    m_emitter->setRadialAccelVar(0);
    //設定粒子的切向加速度，切向加速度的變化率
    m_emitter->setTangentialAccel(30);
    m_emitter->setTangentialAccelVar(0);
    //設定粒子的位置，位置的變化率
    m_emitter->setPosition(CCPoint(400, 500));
    m_emitter->setPosVar(CCPoint(400,0));
    //設定粒子生命，生命的變化率
    m_emitter->setLife(4);
    m_emitter->setLifeVar(2);
    //設定粒子開始的自旋轉速度，開始自旋轉速度的變化率
    m_emitter->setStartSpin(30);
    m_emitter->setStartSpinVar(60);
    //設定结束時的自旋轉以及其變化率
    m_emitter->setEndSpin(60);
    m_emitter->setEndSpinVar(60);
    ccColor4F cc;
    cc.a = 1.0;
    cc.b = 255;
    cc.g = 255;
    cc.r = 255;
    ccColor4F cc2;
    cc2.a = 0;
    cc2.b = 0;
    cc2.g = 0;
    cc2.r = 0;
    //設定開始時的顏色以及顏色的變化率
    m_emitter->setStartColor(cc);
    m_emitter->setStartColorVar(cc2);
    //設定開始時粒子的大小，以及大小的變化率
    m_emitter->setStartSize(30);
    m_emitter->setStartSizeVar(0);
    //設定粒子结束時的大小，以及大小的變化率
    m_emitter->setEndSize(20);
    m_emitter->setEndSizeVar(0);
    //設定每秒產生粒子的數目
    m_emitter->setEmissionRate(100);
    this->addChild(m_emitter);
    return true;
}