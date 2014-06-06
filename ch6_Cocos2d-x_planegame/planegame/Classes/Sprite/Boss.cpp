#include "Boss.h"

Boss::Boss(void)
{
	hp = 1000;
	speed = 6.0f;
	isCrazy = false;
	isShoot = false;

	crazyTime = 200;
	count = 0;
	isUp = true;
	isLeft = true;
	isDie = false;
}

Boss::~Boss(void)
{
}


Boss *Boss::boss()
{
	Boss *boss = new Boss();
	if (boss && boss->init())
	{
		boss->autorelease();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return NULL;
}

bool Boss::init()
{
	bool bRet = false;
	do 
	{
		
		bRet = true;
	} while (0);
	return bRet;
}

void Boss::addBoss()
{
	CCTexture2D *texture;
	if (isUp)//大BOSS
	{	
		sBoss = CCSprite::create("enemy_boss2.png");
		texture =CCTextureCache::sharedTextureCache()->addImage("enemy_boss2.png");
		spriteW = sBoss->getContentSize().width/10;
		spriteH = sBoss->getContentSize().height;
		x=spriteW/2;
		y=size.height-spriteH/2;
		hp = 1000;
		//建立幀序列

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.08f);
		for(int i=0;i<10;i++)
			animation->addSpriteFrameWithTexture(texture,CCRectMake(i*120,0,120,72));
		CCAnimate *animate=CCAnimate::create(animation);
		sBoss=CCSprite::createWithTexture(texture,CCRectMake(0,0,120,72));
		sBoss->runAction(CCRepeatForever::create(animate)); 
		this->addChild(sBoss);
	}else{//小BOSS
		
		sBoss = CCSprite::create("enemy_boss1.png");
		texture =CCTextureCache::sharedTextureCache()->addImage("enemy_boss1.png");
		spriteW = sBoss->getContentSize().width/10;
		spriteH = sBoss->getContentSize().height;
		if (isLeft)
		{
			x=-spriteW/2;
		}else
			x = size.width+spriteW/2;
		speed = 1;
		y = size.height-size.height/4;
		hp = 100;
		//建立幀序列

		CCAnimation *animation = CCAnimation::create();
		animation->setDelayPerUnit(0.08f);
		for(int i=0;i<10;i++)
			animation->addSpriteFrameWithTexture(texture,CCRectMake(i*45,0,45,31));
		CCAnimate *animate=CCAnimate::create(animation);
		sBoss=CCSprite::createWithTexture(texture,CCRectMake(0,0,45,31));
		sBoss->runAction(CCRepeatForever::create(animate)); 
		this->addChild(sBoss);
	}
	
	

	

}

void Boss::update(){

	if (isUp)
	{
		if (isCrazy == false) {
			x += speed;
			if (x >= size.width-spriteW/2) {
				x = size.width-spriteW/2;
				speed = -speed;
			} else if (x <= spriteW/2) {
				x = spriteW/2;
				speed = -speed;
			}
			count++;
			if (count %  crazyTime== 0) {
				isCrazy = true;
				speed = 26;
			}
			//瘋狂的狀態
		} else {	
			//當Boss回來時建立大量子彈
			if (speed == 0) {
				//加入8方向子彈
				isShoot = true;
			}
			speed -= 1;
			y -= speed;
			if (y >= size.height-spriteH/2) {
				//恢復正常狀態
				crazyTime = rand()%50+200;
				y = size.height-spriteH/2;
				isCrazy = false;
				isShoot = false;
				speed = 6;
			}
		}
	}else{
		if (isLeft)
		{
			isShoot = false;
			x+=speed;
			if(x>spriteW/2||x<-spriteW/2){
				
				speed = -speed;
				if (x>spriteW/2)
				{
					isShoot = true;
				}
		}
				
			
		}else{
			isShoot = false;
			x-=speed;
			if (x<size.width-spriteW/2||x>size.width+spriteW/2){
				speed = -speed;
				if (x<size.width-spriteW/2)
				{
					isShoot = true;
				}
			}
				
		}

	}
	if (hp<0)
	{
		isDie = true;
	}
	sBoss->setPosition(ccp(x,y));
}