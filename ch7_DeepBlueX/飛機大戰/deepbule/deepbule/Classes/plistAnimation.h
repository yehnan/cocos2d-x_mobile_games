#pragma once

#include "cocos2d.h"
#include "Animation.h"
using namespace cocos2d;

class plistAnimation : public Animation
{
public:
	plistAnimation();
	plistAnimation(const char* _img, const char* _actionFile) {};
	~plistAnimation();
	 void CreateAnimation(const char* _img, const char* _actionFile);
public:
	 cocos2d::CCTexture2D*		img;
	 
};