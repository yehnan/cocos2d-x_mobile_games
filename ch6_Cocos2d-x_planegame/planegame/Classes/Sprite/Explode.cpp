#include "Explode.h"

Explode::Explode(void)
{
	isDie = false;
}

Explode::~Explode(void)
{
}
// 相當於create方法
Explode* Explode::explode()
{
	Explode* explode = new Explode();
	if(explode&&explode->init())
	{
		explode->autorelease();
		return explode;
	}
	CC_SAFE_DELETE(explode);
	return NULL;
}

bool Explode::init()
{
	bool bRet = false;
	do{

		bRet = true;
	}while(0);
	return bRet;
}

void Explode::addExplode(float x,float y){
	// 建立爆炸效果紋理與動畫
	CCTexture2D *texture =CCTextureCache::sharedTextureCache()->addImage("boom.png");
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.08f);
	for(int i=0;i<7;i++)
		animation->addSpriteFrameWithTexture(texture,CCRectMake(i*44,0,44,49));
	CCAnimate *animate=CCAnimate::create(animation);
	CCFiniteTimeAction *animateOver=CCCallFunc::create(this,callfunc_selector(Explode::explosionEndDid));
	CCFiniteTimeAction *seq=CCSequence::create(animate,animateOver,NULL);
	sExplode=CCSprite::createWithTexture(texture,CCRectMake(0,0,44,49));
	this->addChild(sExplode);
	sExplode->setPosition(ccp(x,y));
	sExplode->runAction(seq);
}

void Explode::explosionEndDid(){
	isDie = true;
}