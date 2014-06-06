#include "Enemy.h"

Enemy::Enemy(void)
{
	isTool = false;
	isDie = false;
}

Enemy::~Enemy(void)
{
}
Enemy *Enemy::enemy()
{
	Enemy *enemy= new Enemy();

	if (enemy && enemy->init())
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Enemy::init()
{

	bool bRet = false;
	do 
	{
		bRet = true;
	} while (0);

	return bRet;
}

void Enemy::addEnemy(int _type)
{
	this->type = _type;
	switch(type){//敵機種類分配
		case TYPE_aaa:
			sEnemy = CCSprite::create("aaa.png");
			spriteW = sEnemy->getContentSize().width;
			spriteH = sEnemy->getContentSize().height;
			this->addChild(sEnemy);
			enemyHP = 2;
		
			speed = rand()%3+3;
			x = (int)rand()%(int)(size.width-spriteW/2)+spriteW/2;
			y = size.height-spriteH/2;
			
			if(rand()%4 == 0)//死後是否掉落道具
				isTool = true;
			this->setPosition(ccp(x,y));
			break;
		case TYPE_bbb:
			sEnemy = CCSprite::create("bbb.png");
			spriteW = sEnemy->getContentSize().width;
			spriteH = sEnemy->getContentSize().height;
			this->addChild(sEnemy);
			enemyHP = 1;

			speed = rand()%3+2;
			if (rand()%2==0)
			    x = (int)rand()%(int)size.width/4+spriteW/2;
			else
				x= (int)rand()%(int)size.width/4+size.width/4*3-spriteW/2;
			y = -this->getContentSize().height;
			if(rand()%3 == 0)//死後是否掉落道具
				isTool = true;
			this->setPosition(ccp(x,y));
			break;
			break;
		case TYPE_ccc:
			sEnemy = CCSprite::create("ccc.png");
			spriteW = sEnemy->getContentSize().width;
			spriteH = sEnemy->getContentSize().height;
			this->addChild(sEnemy);
			enemyHP = 2;

			speed = rand()%3+1;
			x = -spriteW/2;
			y = rand()%(int)size.height/2+size.height/2-spriteH/2;
			if(rand()%4 == 0)//死後是否掉落道具
				isTool = true;
			this->setPosition(ccp(x,y));
			break;
	}
	
	
}

void Enemy::update()
{
	if(isDie)//敵機是否死亡
		return;

		switch(type){//種類有相對應的性格對照相對應的行為
		case TYPE_aaa:
			y -= speed;
			if(y<-spriteH/2)//離開螢幕後死亡
				isDie = true;
			
			break;
		case TYPE_bbb:
			speed+=0.1f;
			y +=speed;
			if(y>size.height+spriteH/2)
				isDie = true;
			break;
		case TYPE_ccc:
			x += speed;
			if(x>size.width+spriteW/2)
				isDie = true;
			break;
		
		}
		this->setPosition(ccp(x,y));
	if(rand()%100==0)
		isShoot = true;//發射子彈
	else 
		isShoot = false;
	if(enemyHP<=0)
		isDie = true;

}