#include "Bullet.h"

Bullet::Bullet(void)
{
	pSan[0][0] = 0.0f;
	pSan[0][1] = 1.0f;
	pSan[1][0] = 0.423f;
	pSan[1][1] = 0.906f;
	pSan[2][0] = -0.423f;
	pSan[2][1] = 0.906f;
	pSan[3][0] = 0.766f;
	pSan[3][1] = 0.643f;
	pSan[4][0] = -0.766f;
	pSan[4][1] = 0.643f;
	pSan[5][0] = 0.966f;
	pSan[5][1] = 0.259f;
	pSan[6][0] = -0.966f;
	pSan[6][1] = 0.259f;
	float W = size.width;
	pLaser[0][0] = 0.0f;
	pLaser[0][1] = W/11.0f;
	pLaser[1][0] = -W/32.0f;
	pLaser[1][1] = W/16.0f;
	pLaser[2][0] = W/32.0f;
	pLaser[2][1] = W/16.0f;
	pLaser[3][0] = -W/16.0f;
	pLaser[3][1] = W/32.0f;
	pLaser[4][0] = W/16.0f;
	pLaser[4][1] = W/32.0f;
	pLaser[5][0] = -W/10.0f;                                                              
	pLaser[5][1] = 0.0f;                                        
	pLaser[6][0] = W/10.0f;
	pLaser[6][1] = 0.0f;
	isDie = false;
	bulletType = BULLET_PLAYER;
}

Bullet::~Bullet(void)
{
}

Bullet* Bullet::bullet()
{
	Bullet* bullet = new Bullet();
	if(bullet&&bullet->init())
	{
		bullet->autorelease();
		
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

bool Bullet::init()
{
	bool bRet = false;
	do{
		
		bRet = true;
	}while(0);
	return bRet;
}
//加入主角子彈
void Bullet::addBullet(Player *pSprite,int id)
{
	bulletType = BULLET_PLAYER;
	type = pSprite->type;
	if (type==1)
	{
		bullet1 = CCSprite::create("bullet2.png");
	}else
		bullet1 = CCSprite::create("bullet.png");
	
	spriteW = bullet1->getContentSize().width;
	spriteH = bullet1->getContentSize().height;

	this->addChild(bullet1);
	//level = pSprite.level;
	if(type==1){
		speed = 12.0f;

		x = pSprite->x;
		y = pSprite->y;
		//不同的速度方向
		speedx = speed*pSan[id-1][0];
		speedy = speed*pSan[id-1][1];
	}
	//激光束
	else if(type == 2){
		//是否加速
		var = 0.0;
		speed = 5.0f;
		//不同級別不同發射點
		x = pSprite->x+pLaser[id-1][0];
		y = pSprite->y+pLaser[id-1][1];	

	}
	this->setPosition(ccp(x,y));
}
//加入Boss1子彈
void Bullet::addBullet(Boss* boss,int _id,int ai){
	bullet1 = CCSprite::create("bullet3.png");
	spriteW = bullet1->getContentSize().width;
	spriteH = bullet1->getContentSize().height;
	this->addChild(bullet1);
	bulletType = BULLET_BOSS1;
	AI = ai;
	id = _id;
	if(AI == 1){
		x = boss->x;
		y = boss->y;
		speed = 10;
	}
	else if(AI == 3){
		speed = 6;
		x = boss->x;
		y = boss->y;
		speedx = speed*pSan[id-1][0];
		speedy = speed*pSan[id-1][1];
	}
	this->setPosition(ccp(x,y));
}
void Bullet::addBullet(Boss *boss, Player *player)
{
	bulletType = BULLET_BOSS2;
	bullet1 = CCSprite::create("bullet_enemy.png");
	CCTexture2D *texture =CCTextureCache::sharedTextureCache()->addImage("bullet_enemy.png");
	spriteW = bullet1->getContentSize().width/4;
	spriteH = bullet1->getContentSize().height;
	x = boss->x;
	y = boss->y;
    speed = 5;
	track(player->x,player->y);
	//建立幀序列
	
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.08f);
	for(int i=0;i<4;i++)
		animation->addSpriteFrameWithTexture(texture,CCRectMake(i*20,0,20,20));
	CCAnimate *animate=CCAnimate::create(animation);
	bullet1=CCSprite::createWithTexture(texture,CCRectMake(0,0,20,20));
	bullet1->runAction(CCRepeatForever::create(animate)); 
	this->addChild(bullet1);
	this->setPosition(ccp(x,y));

}
void Bullet::update()
{
	if (x>size.width+spriteW||x<0-spriteW||y<0-spriteH||y>size.height+spriteH)
	{
		isDie = true;
	}else if (bulletType==BULLET_PLAYER)
	{
		this->setPosition(ccp(x,y));

		if(type==1){
			x -= speedx;
			y += speedy;
		}
		else if(type==2){
			y += speed+var;
			var += 1.5f;
		}
	}else if (bulletType==BULLET_ENEMY)
	{
		
	}else if (bulletType==BULLET_BOSS1)
	{
		if(AI == 1){
			//Boss瘋狂狀態下的子彈發射邏輯待實作
			switch (id) {
				case 1:
					y += speed;
					break;
				case 2:
					y -= speed;
					break;
				case 3:
					x -= speed;
					break;
				case 4:
					x += speed;
					break;
				case 5:
					y += speed;
					x -= speed;
					break;
				case 6:
					x += speed;
					y += speed;
					break;
				case 7:
					x -= speed;
					y -= speed;
					break;
				case 8:
					y -= speed;
					x += speed;
					break;
			}
		}
	    else if(AI==3){
			x += speedx;
			y -= speedy;
		}
	
	}else if (bulletType==BULLET_BOSS2)
	{
		x += speedx;
		y += speedy;
	}
	this->setPosition(ccp(x,y));
	
}

void Bullet::track(float targetX,float targetY){
	speedx = targetX -x;
	speedy = targetY - y;
	float temp = (float) sqrt(speedx*speedx+speedy*speedy);
	float ver = temp/speed;
	if(ver > 1){
		speedx /= ver;
		speedy /= ver;
	}
}