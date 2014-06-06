#include "GameScene.h"


GameScene::GameScene(void)
{
	for(int i=0;i<10;i++)
		for(int j=0;j<4;j++){
		    int a = rand()%4;
			enemyArray[i][j] = a;
		}
	enemyIndex = 0;
	hp=3;
	isBoos = false;
	createBossBullet = 20;
	coun = 0;
	
}

GameScene::~GameScene(void)
{
}
CCScene* GameScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		GameScene *layer = GameScene::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}
bool GameScene::init()
{
	this->setTouchEnabled(true);
	this->registerWithTouchDispatcher();

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		//背景
		Background *background = Background::create();
		this->addChild(background);
		//主角
		player = Player::player();
		player->addPlayer(false);
		this->addChild(player);
		//子彈
		pBullet = CCArray::create();
		pBullet->retain();
		//敵機机
		pEnemy = CCArray::create();
		pEnemy->retain();
		//爆炸效果
		pExplode = CCArray::create();
		pExplode->retain();
		//道具
		pTool = CCArray::create();
		pTool->retain();
		//血量
		pHp =CCArray::create();
		pHp->retain();
		//Boss
		pBoss = CCArray::create();
		pBoss->retain();
		//敵機子彈
		pBullet_E = CCArray::create();
		pBullet_E->retain();
		for(int i=0;i<hp;i++)
			addHp(i);

		this->schedule(schedule_selector(GameScene::update));
		this->schedule(schedule_selector(GameScene::addBullet),1.0f);
		this->schedule(schedule_selector(GameScene::addEnemy),3.0f);
		bRet = true;
	} while (0);

	return bRet;
}
void GameScene::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
	//取得觸控點
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location=touch->getLocation();
	player->acceptTouchesBegan(touch,pEvent);
}

void GameScene::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
{
	if (player->isDie)
		return;
	CCTouch *touch = (CCTouch*)(*(pTouches->begin()));
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location=touch->getLocation();
	player->acceptTouchesMoved(touch,pEvent);
}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch*)(pTouches->anyObject());
	//CCPoint location = touch->locationInView(touch->view());
	//location = CCDirector::sharedDirector()->convertToGL(location);
	CCPoint location=touch->getLocation();
	player->acceptTouchesEnded(touch,pEvent);
}

void GameScene::update(float dt)
{
	if(player->isDie){
		CCDirector::sharedDirector()->replaceScene(GameOver::scene());
	}
		
	player->update();
	
	CCRect playerRect = CCRectMake(player->x-player->spriteW/4,
								   player->y-player->spriteH/4,
								   player->spriteW-player->spriteW/4,
								   player->spriteH-player->spriteH/4);
	//CCArray::CCMutableArrayIterator it;
	//CCArray::CCMutableArrayIterator ite;
	//boss
	//CCArray::itCCMutableArrayIterator itBoss;
	
	//主角子彈
	for (int i=0;i < pBullet->count();i++)
	{
		Bullet *bullet = (Bullet*)pBullet->objectAtIndex(i);
		CCRect bulletRect = CCRectMake(bullet->x-bullet->spriteW/4,
									   bullet->y-bullet->spriteH/4,
									   bullet->spriteW-bullet->spriteW/4,
									   bullet->spriteH-bullet->spriteH/4);
		if (bullet->isDie)
		{
			pBullet->removeObject(bullet);
			this->removeChild(bullet,true);
			break;
		}else
		{
			bullet->update();
			//子彈與敵機碰撞
			for (int j=0;j< pEnemy->count();j++)//ite=pEnemy->begin();ite!=pEnemy->end();ite++){
			{	Enemy *enemy =(Enemy *)pEnemy->objectAtIndex(j);// *ite;
				CCRect enemyRect = CCRectMake(enemy	->x-enemy->spriteW/4,
											  enemy->y-enemy->spriteH/4,
										      enemy->spriteW-enemy->spriteW/4,
											  enemy->spriteH-enemy->spriteH/4);
				
				if(	bulletRect.intersectsRect( enemyRect)){
					if(--enemy->enemyHP<0)
						enemy->isDie = true;
					bullet->isDie = true;
				
				}
			}
			//子彈與Boss碰撞
			for (int k=0;k<pBoss->count();k++)//; itBoss = pBoss->begin();itBoss!=pBoss->end();itBoss++)
			{
				Boss *boss = (Boss *)pBoss->objectAtIndex(k);//*itBoss;
				CCRect bossRect = CCRectMake(boss->x-boss->spriteW/4,
					boss->y-boss->spriteH/4,
					boss->spriteW-boss->spriteW/4,
					boss->spriteH-boss->spriteH/4);
            if(	bulletRect.intersectsRect(bossRect)){
					boss->hp--;
					bullet->isDie = true;

				}
           			}
			
		}
	}

	//敵機
	for (int j=0;j<pEnemy->count();j++)
	{	Enemy *enemy =(Enemy *)pEnemy->objectAtIndex(j);
		CCRect enemyRect = CCRectMake(enemy	->x-enemy->spriteW/4,
									  enemy->y-enemy->spriteH/4,
									  enemy->spriteW-enemy->spriteW/4,
									  enemy->spriteH-enemy->spriteH/4);
		if (enemy->isDie)
		{
			addExplode(enemy->x,enemy->y);
			if (enemy->isTool)
			    this->addTool(enemy->x,enemy->y);
			pEnemy->removeObject(enemy);
			this->removeChild(enemy,true);
			break;
		}else
		{
			if(enemyRect.intersectsRect( playerRect)){
				enemy->isDie = true;
				subHp();
			}
			enemy->update();
			
		}	
	}
	//爆炸效果
	for (int i=0;i<pExplode->count();i++)
	{
		Explode *explode = (Explode *)pExplode->objectAtIndex(i);

		if (explode->isDie)
		{
			pExplode->removeObject(explode);
			this->removeChild(explode,true);
			break;
		}
	}

	//道具
	for (int i=0;i<pTool->count();i++)
	{	Tool *tool = (Tool *)pTool->objectAtIndex(i);

		if (tool->isDie)
		{
			pTool->removeObject(tool);
			this->removeChild(tool,true);
			break;
		}else{
			tool->update();
			CCRect toolRect = CCRectMake(tool->x-tool->spriteW/4,
				tool->y-tool->spriteH/4,
				tool->spriteW-tool->spriteW/4,
				tool->spriteH-tool->spriteH/4);
			if(toolRect.intersectsRect(playerRect)){
				tool->effect(player);
				if (player->hp>hp)
				{
					addHp(hp++);
				}
				tool->isDie = true;
				if (tool->isFlash)
				{
					for (int ite=pEnemy->count()-1;ite>=0;ite--){
						Enemy *enemy =(Enemy *)pEnemy->objectAtIndex(ite);
						enemy->enemyHP-=5;
					}
				}
			}
			
		}
	}
	//Boss
	for (int itBoss =pBoss->count()-1;itBoss>=0;itBoss--)
	{
		Boss *boss = (Boss*)pBoss->objectAtIndex(itBoss);

		if (boss->isDie)
		{
			pBoss->removeObject(boss);
			this->removeChild(boss,true);
			break;
		}else{
			boss->update();
			CCRect bossRect = CCRectMake(boss->x-boss->spriteW/4,
				boss->y-boss->spriteH/4,
				boss->spriteW-boss->spriteW/4,
				boss->spriteH-boss->spriteH/4);
			if(bossRect.intersectsRect(playerRect)){
			   	boss->hp--;
				subHp();
			}
			if (boss->isUp)
			{
				if (boss->isCrazy)
				{
					if (boss->isShoot)
					{

						for(int i=0;i<8;i++)
						{
							Bullet *bullet = Bullet::bullet();
							bullet->addBullet(boss,i+1,1);
							this->addChild(bullet);
							pBullet_E->addObject(bullet);
							boss->isShoot = false;
						}
					}
				}else if(++coun%createBossBullet==0)
				{
					for(int i=0;i<7;i++){
						Bullet *bullet = Bullet::bullet();
						bullet->addBullet(boss,i+1,3);
						this->addChild(bullet);
						pBullet_E->addObject(bullet);
						boss->isShoot = false;
					}
					
				}
			}else
			{
				if (boss->isShoot)
				{
					CCLOG("SADSD");
					Bullet *bullet = Bullet::bullet();
					bullet->addBullet(boss,player);
					this->addChild(bullet);
					pBullet_E->addObject(bullet);
					boss->isShoot = false;
				}
				
			}
			
		}
	}
	//敵機子彈
	
	for (int itBullet=0;itBullet<pBullet_E->count();itBullet++)
	{
		Bullet *bullet = (Bullet*)pBullet_E->objectAtIndex(itBullet);
		if (bullet->isDie)
		{
			this->removeChild(bullet,true);
			pBullet_E->removeObject(bullet);
			break;
		}else{
			bullet->update();
			CCRect bulletRect = CCRectMake(bullet->x-bullet->spriteW/4,
				bullet->y-bullet->spriteH/4,
				bullet->spriteW-bullet->spriteW/4,
				bullet->spriteH-bullet->spriteH/4);
			if(	bulletRect.intersectsRect(playerRect)){
				subHp();
				bullet->isDie = true;
			}
		}
	}
}

void GameScene::addBullet(float dt){

	//定時建立主角子彈
	for(int i=0;i<player->bulletSum[player->type-1][player->level];i++){
		Bullet *bullet = Bullet::bullet();
		bullet->addBullet(player,i+1);
		this->addChild(bullet);
		pBullet->addObject(bullet);
	}
				

}
void GameScene::addEnemy(float dt){
	if(isBoos){	
		return;
	}		
	for(int i=0;i<4;i++){
		if (enemyArray[enemyIndex][i]==0)
			continue;
		Enemy *enemy = Enemy::enemy();
		enemy->addEnemy(enemyArray[enemyIndex][i]);
		this->addChild(enemy);
		pEnemy->addObject(enemy);
	}
	if(enemyIndex!=9)
		enemyIndex++;
	else{
		isBoos = true;	
		addBoss(true);
		addBoss(false);
	}
}

void GameScene::addExplode(float x,float y)
{
	Explode *explode = Explode::explode();
	explode->addExplode(x,y);
	this->addChild(explode);
	pExplode->addObject(explode);
}

void GameScene::addTool(float x,float y)
{
	Tool *tool = Tool::tool();
	tool->addTool(x,y);
	this->addChild(tool);
	pTool->addObject(tool);
}

void GameScene::addHp(float hp)
{
	CCSprite* sHp = CCSprite::create("hp.png");
	sHp->setPosition(ccp(hp*35+35/2,size.height-33/2));
	this->addChild(sHp);
	pHp->addObject(sHp);
}

void GameScene::subHp(){
	player->hp--;
	hp--;
	CCSprite* sHp = (CCSprite*)pHp->lastObject();
	pHp->removeObject(sHp);
	this->removeChild(sHp,true);
	if (hp==3)
	{
		player->addPlayer(false);
	}
}

void GameScene::addBoss(bool isSmall){	
		Boss* boss = Boss::boss();
		boss->isUp = isSmall;
		boss->isLeft = true;
		boss->addBoss();
		this->addChild(boss);
		pBoss->addObject(boss);
	if (!isSmall)
	{
		Boss* boss = Boss::boss();
		boss->isUp = isSmall;
		boss->isLeft = false;
		boss->addBoss();
		this->addChild(boss);
		pBoss->addObject(boss);
	}
}