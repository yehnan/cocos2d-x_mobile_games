#include "Player.h"
#include "Global.h"

Player::Player(void)
{
	x=size.width/2;
	y=size.height/4;
	tempx=tempy=0;
	hp=3;
	type = 1;
	level = 0;
	for(int i=0;i<2;i++)
		for(int j=0;j<4;j++)
			bulletSum[i][j] =j*2+1; 
	isDie = false;

}

Player::~Player(void)
{
}

Player *Player::player()
{
	Player *player = new Player();

	if (player && player->init())
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

bool Player::init()
{

	bool bRet = false;
	do 
	{
		
		bRet = true;
	} while (0);

	return bRet;
}

void Player::addPlayer(bool isUp){
	this->removeChild(pSprite,true);
	CCTexture2D *texture;
	if (isUp)
	{
		pSprite = CCSprite::create("player2.png");
		texture =CCTextureCache::sharedTextureCache()->addImage("player2.png");
	}else{
		pSprite = CCSprite::create("player.png");
		texture =CCTextureCache::sharedTextureCache()->addImage("player.png");
	}
	spriteW = pSprite->getContentSize().width/4;
	spriteH = pSprite->getContentSize().height;


	//建立幀序列
	
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.08f);
	for(int i=0;i<4;i++)
		animation->addSpriteFrameWithTexture(texture,CCRectMake(i*47,0,47,56));
	pSprite=CCSprite::createWithTexture(texture,CCRectMake(0,0,47,56));
	pSprite->runAction(CCRepeatForever::create(CCAnimate::create(animation))); 
	this->addChild(pSprite);
}
void Player::acceptTouchesBegan(CCTouch *touch,CCEvent *pEvent)
{
	//取得觸控點
	//CCPoint location = touch->locationInView(touch->view());
	CCPoint location =touch->getLocation();// CCDirector::sharedDirector()->convertToGL(location);

	tempx = location.x;
	tempy = location.y;

}

void Player::acceptTouchesMoved(CCTouch *touch,CCEvent *pEvent)
{
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location =touch->getLocation();
	x += location.x-tempx;
	y += location.y-tempy;

	tempx=location.x;
	tempy=location.y;
	if (x<spriteW/2)
	    x = spriteW/2;
	else if (x>size.width-spriteW/2)
	    x = size.width-spriteW/2;
	else if(y<spriteH/2)
		y=spriteH/2;
	else if(y>size.height-spriteH/2)
		y=size.height-spriteH/2;
	
}

void Player::acceptTouchesEnded(CCTouch *touch, CCEvent *pEvent)
{
	///CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location =touch->getLocation();
}

void Player::update()
{
	pSprite->setPosition(ccp(x,y));
	

	if (hp<0)
	{
		isDie = true;
	}
}