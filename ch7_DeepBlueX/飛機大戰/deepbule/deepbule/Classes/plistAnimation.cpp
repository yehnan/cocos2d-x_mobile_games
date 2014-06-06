#include "plistAnimation.h"

plistAnimation::plistAnimation()
{

}


plistAnimation::~plistAnimation()
{
	delete img;
	delete spriteFrame;
}

void plistAnimation::CreateAnimation(const char* _img, const char* _actionFile)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(_actionFile);
	spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(_img);
	img = spriteFrame->getTexture();
	CCLOG("12");

}
