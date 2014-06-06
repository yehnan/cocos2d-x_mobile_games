
#include "JH_Sprite.h"

using namespace cocos2d;

JH_Sprite* JH_Sprite::instance = NULL;

JH_Sprite::JH_Sprite()
{

}

JH_Sprite::~JH_Sprite()
{

}

//初始化堆疊空間
void JH_Sprite::Init()
{
    jh_imgs=JH_Image::Getinstance();
    jh_animation=JH_Animation::Getinstance();
    sprite_head=new Sprites();
    sprite_head->sprite_change=false;
    sprite_head->next=NULL;
    sprite_headid=0;	 
    sprite_run=false;
}

JH_Sprite* JH_Sprite::Getinstance()
{
    if (instance==NULL) {
        instance = new JH_Sprite();
        instance->Init();
    }
    return instance;
}

int JH_Sprite::AddSprite(int imgid,float x,float y,float img_x,float img_y,float img_width,float img_hight,int z)
{
    Sprites* addhead=sprite_head;
    while (sprite_head->next!=NULL) {
        sprite_head=sprite_head->next;
    }
    //精靈相關初始化
	sprite_head->next = NULL;
    sprite_head->next=new Sprites();
	sprite_head->next->sprite =new CCSprite();
	sprite_head->next->sprite->initWithTexture(jh_imgs->imgs[imgid],CCRectMake(img_x,img_y,img_width,img_hight));
    sprite_head->next->sprite->setPosition(ccp(x, y));
    sprite_head->next->sprite->retain();
    
    //串列相關處理 
    sprite_head->next->layertag=z;
    sprite_head->next->next=NULL;
    sprite_head->next->sprite_change=1;
    sprite_head->next->sprite_id=sprite_headid++;
    sprite_head=addhead;
    addhead=NULL;
    sprite_run=true;
    return sprite_headid-1;
}

int JH_Sprite::AddSprite(int imgid,float x,float y,float img_width,float img_height,int z)
{
    Sprites* addhead=sprite_head;
    while (sprite_head->next!=NULL) {
        sprite_head=sprite_head->next;
    }
    //精靈相關初始化
	sprite_head->next = NULL;
    sprite_head->next=new Sprites();
	sprite_head->next->sprite = new CCSprite();
    sprite_head->next->sprite->initWithTexture(jh_imgs->imgs[imgid]);   
    sprite_head->next->sprite->setPosition(ccp(x, y));
    sprite_head->next->sprite->retain();
    //串列相關處理
    sprite_head->next->layertag=z;
    sprite_head->next->next=NULL;
    sprite_head->next->sprite_change=1;
    sprite_head->next->sprite_id=sprite_headid++;
    sprite_head=addhead;
    addhead=NULL;
    sprite_run=true;
    return sprite_headid-1;
}

void JH_Sprite::DeleteSprite(int id)
{
    if (sprite_head->next==NULL) {
        return;
    }
    Sprites* head=sprite_head;
    sprite_head=sprite_head->next;
    while (sprite_head!=NULL) {
        if (sprite_head->sprite_id==id) {
            sprite_head->sprite_change=2;
            break;
        }
        sprite_head=sprite_head->next;
    }
    sprite_head=head;
    head=NULL;
    sprite_run=true;
}

void JH_Sprite::DeleteAllSprite()
{
    if (sprite_head->next==NULL) {
        return;
    }
    Sprites* head=sprite_head;
    sprite_head=sprite_head->next;
    while (sprite_head!=NULL) {
        sprite_head->sprite_change=2;
        sprite_head=sprite_head->next;
    }
    sprite_head=head;
    head=NULL;
    sprite_run=true;
}

//動態精靈相關方法


void JH_Sprite::SetAnimationAction(int spriteid,int actionId,bool loop)
{
    Sprites* findhead=sprite_head->next;
    while (findhead!=NULL) {
        if (findhead->sprite_id==spriteid) {
            break;
        }
        findhead=findhead->next;
    }
    //找到對應的精靈，為其配置動畫
    findhead->sprite->stopAllActions();
    CCAnimation* animation =CCAnimation::create();
	
	animation->setDelayPerUnit(0.05f);
    int xmlid=findhead->xmlid;
    int begin,end;
    int img_x,img_y,img_width,img_hight;
    int py_x,py_y;
    begin=0;
    end=jh_animation->AniX[xmlid]->Action[actionId]->frames_Count;
    for (int i=begin; i<end; i++) 
	{
        int frame_id=jh_animation->AniX[xmlid]->Action[actionId]->frames[i]->_id;

        for (int j=0; j<jh_animation->AniX[xmlid]->Frame[frame_id]->Sprite_Count; j++) 
		{
            int Moudle_id=jh_animation->AniX[xmlid]->Frame[frame_id]->Sprite[j]->module_id; 
            int flip=jh_animation->AniX[xmlid]->Frame[frame_id]->Sprite[j]->flip;
            float px=jh_animation->AniX[xmlid]->Frame[frame_id]->Sprite[j]->px;
            float py=-jh_animation->AniX[xmlid]->Frame[frame_id]->Sprite[j]->py;

            //if (i==begin) {
                img_x=jh_animation->AniX[xmlid]->Moudle[Moudle_id]->x;
                img_y=jh_animation->AniX[xmlid]->Moudle[Moudle_id]->y;
                img_width=jh_animation->AniX[xmlid]->Moudle[Moudle_id]->w;
                img_hight=jh_animation->AniX[xmlid]->Moudle[Moudle_id]->h;
           // }
			animation->addSpriteFrameWithTexture(jh_animation->AniX[xmlid]->img,CCRectMake(img_x,img_y,img_width,img_hight));
			
 //          animation->addFrameWithTexture(jh_animation->AniX[xmlid]->img,CCRectMake(img_x,img_y,img_width,img_hight),CCPointMake(px, py));       
            
        }
    }
    
    CCActionInterval* action=CCAnimate::create(animation);

    if (loop) {
        CCRepeatForever* repeat=CCRepeatForever::create(action);
;		findhead->sprite->runAction(repeat);
//      findhead->sprite->runAction( CCSequence::actions(repeat, NULL, NULL));
    }else{
		findhead->sprite->runAction(action);
//      findhead->sprite->runAction( CCSequence::actions(action, NULL, NULL));
    }

    findhead=NULL;
}

void JH_Sprite::SetPlistAnimationAction(int spriteid,int actionId,bool loop)
{
	Sprites* findhead=sprite_head->next;
	while (findhead!=NULL) {
		if (findhead->sprite_id==spriteid) {
			break;
		}
		findhead=findhead->next;
	}
	//找到對應的精靈，為其配置動畫
	findhead->sprite->stopAllActions();
	CCAnimation* animation =CCAnimation::create();

	CCArray* animFrames = CCArray::createWithCapacity(4);
	char str[100] = {0};
	for(int i = 1; i < 12; i++)
	{
		int n1 = i%10;
		int n2 = i /10;
		sprintf(str, "0%i%i.Png", n2,n1);
		CCLOG(str);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	animation->initWithSpriteFrames(animFrames,0.05f);

	CCActionInterval* action=CCAnimate::create(animation);
	if (loop) {
		CCRepeatForever* repeat=CCRepeatForever::create(action);
		;		findhead->sprite->runAction(repeat);
	}else{
		findhead->sprite->runAction(action);
	}

	findhead=NULL;
}

int JH_Sprite::AddAnimation(int xmlid,float x,float y,int z)
{
	Sprites* addhead=sprite_head;
	while (sprite_head->next!=NULL) {
		sprite_head=sprite_head->next;
	}
	//精靈相關初始化
	sprite_head->next=new Sprites();
	sprite_head->next->sprite =new CCSprite();
	sprite_head->next->sprite->initWithTexture(jh_animation->AniX[xmlid]->img);//,CCRectMake(0,0,0,0));
	sprite_head->next->xmlid=xmlid;
	sprite_head->next->sprite->setPosition(ccp(x, y));
	sprite_head->next->sprite->retain();
	//串列相關處理
	sprite_head->next->layertag=z;
	sprite_head->next->next=NULL;
	sprite_head->next->sprite_change=1;
	sprite_head->next->sprite_id=sprite_headid++;
	sprite_head=addhead;
	addhead=NULL;
	sprite_run=true;
	return sprite_headid-1;
	

}//    精靈操作相關方法（靜態和動態通用）

int JH_Sprite::AddPlistAnimation(int xmlid,float x,float y,int z)
{
	Sprites* addhead=sprite_head;
	while (sprite_head->next!=NULL) {
		sprite_head=sprite_head->next;
	}
	//精靈相關初始化
	sprite_head->next=new Sprites();
	sprite_head->next->sprite =new CCSprite();
	sprite_head->next->sprite->initWithSpriteFrame(jh_animation->AniX[xmlid]->spriteFrame);//,CCRectMake(0,0,0,0));
	sprite_head->next->xmlid=xmlid;
	sprite_head->next->sprite->setPosition(ccp(x, y));
	sprite_head->next->sprite->retain();
	//串列相關處理
	sprite_head->next->layertag=z;
	sprite_head->next->next=NULL;
	sprite_head->next->sprite_change=1;
	sprite_head->next->sprite_id=sprite_headid++;
	sprite_head=addhead;
	addhead=NULL;
	sprite_run=true;
	return sprite_headid-1;
}

//放大、360度旋轉

//顏色混合
void JH_Sprite::SetSpriteColor(int spriteid,int r,int g,int b)
{
    Sprites* findhead=sprite_head->next;
    while (findhead!=NULL) {
        if (findhead->sprite_id==spriteid) {
            break;
        }
        findhead=findhead->next;
    }
    
    findhead->sprite->setColor( ccc3( r,g,b));
    
    findhead=NULL;
}
//改變位置
void JH_Sprite::SetSpritePosition(int spriteid,float x,float y)
{
    Sprites* findhead=sprite_head->next;
    while (findhead!=NULL) {
        if (findhead->sprite_id==spriteid) {
            break;
        }
        findhead=findhead->next;
    }

    if (findhead==NULL) {
        return;
    }
    findhead->sprite->setPosition( CCPointMake(x, y));
    
    findhead=NULL;
}

void JH_Sprite::SetSpriteScale(int spriteid,float ScaleX,float ScaleY,int Rotation)
{
	Sprites* findhead=sprite_head->next;
	while (findhead!=NULL) {
		if (findhead->sprite_id==spriteid) {
			break;
		}
		findhead=findhead->next;
	}
	findhead->sprite->setScaleX(ScaleX);
	findhead->sprite->setScaleY(ScaleY);
	findhead->sprite->setRotation(Rotation);

	findhead=NULL;
}
//精靈自動移動
void JH_Sprite::SetSpriteAutoTo(int spriteid,float x,float y,float speed)
{
	Sprites* findhead=sprite_head->next;
	while (findhead!=NULL) {
		if (findhead->sprite_id==spriteid) {
			break;
		}
		findhead=findhead->next;
	}

	findhead->sprite->runAction(CCMoveTo::create(speed, CCPointMake(x,y)));

	findhead=NULL;
}
//取得位置
CCPoint JH_Sprite::GetSpritePosition(int spriteid)
{
    Sprites* findhead=sprite_head->next;
    while (findhead!=NULL) {
        if (findhead->sprite_id==spriteid) {
            break;
        }
        findhead=findhead->next;
    }
    CCPoint m;
    if (findhead==NULL) {
        return m;
    }
    m=findhead->sprite->getPosition();
    
    findhead=NULL;
    return m;
}

/*void JH_Sprite::DeleteSprite(int id,float x,float y)
{
	if (sprite_head->next==NULL) {
		return;
	}
	Sprites* head=sprite_head;
	sprite_head=sprite_head->next;
	while (sprite_head!=NULL) 
	{
		if (sprite_head->sprite_id==id) 
		{
			if(GetSpritePosition(id).x==x && GetSpritePosition(id).y==y)
			sprite_head->sprite_change=2;
			break;
		}
		sprite_head=sprite_head->next;
	}
	sprite_head=head;
	head=NULL;
	sprite_run=true;
}*/