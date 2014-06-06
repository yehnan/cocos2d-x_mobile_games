/* 
 系统呼叫的主要方法都封裝在此類別中
 */

#include "JH_GameBase.h"

short coordinate=1;//0-cocos2d預設座標系,1-遊戲思維座標系

JH_GameBase::JH_GameBase()
{
    
}

JH_GameBase::~JH_GameBase()
{
    
}

void JH_GameBase::Init()
{
    jh_imgs=JH_Image::Getinstance();
    jh_sprite=JH_Sprite::Getinstance();
    jh_animation=JH_Animation::Getinstance();
    jh_string=JH_String::Getinstance();
}


/*圖片相關方法*/
bool JH_GameBase::jh_LoadImage(int imgid,const char* filename)
{
    return jh_imgs->LoadImage(imgid, filename);
}
bool JH_GameBase::jh_unLoadImage(int imgid)
{
    return jh_imgs->unLoadImage(imgid);
}
void JH_GameBase::jh_unLoadAllImage()
{
    jh_imgs->unLoadAllImage();
}



/*精靈相關方法*/
int JH_GameBase::jh_AddSprite(int imgid,float x,float y,float img_x,float img_y,float img_width,float img_hight,int z)
{
    ChangeCoordinate(&x, &y, img_width, img_hight);
	int i = jh_sprite->AddSprite(imgid, x, y, img_x, img_y, img_width, img_hight,z);
    return i;
}
int JH_GameBase::jh_AddSprite(int imgid,float x,float y,float img_width,float img_height,int z)
{
    ChangeCoordinate(&x, &y, img_width, img_height);
    return jh_sprite->AddSprite(imgid, x, y, img_width,img_height,z);
}
void JH_GameBase::jh_DeleteSprite(int id)
{
    jh_sprite->DeleteSprite(id);
}
void JH_GameBase::jh_DeleteSprite(int id,float x,float y)
{
//	jh_sprite->DeleteSprite(id,x,y);
}
void JH_GameBase::jh_DeleteAllSprite()
{
    jh_sprite->DeleteAllSprite();
}

/*動畫相關方法*/
bool JH_GameBase::jh_LoadAnimation(int _id,const char* filename,const char* xmlname)
{
    return jh_animation->LoadAnimation(_id,filename,xmlname);
}
bool JH_GameBase::jh_LoadPlistAnimation(int _id,const char* filename,const char* xmlname)
{
	return jh_animation->LoadPlistAnimation(_id,filename,xmlname);
}
void JH_GameBase::jh_DeleteAnimation(int _id)
{
    jh_animation->DeleteAnimation(_id);
}
void JH_GameBase::jh_DeleteAllAnimation()
{
    jh_animation->DeleteALLAnimation();
}
int JH_GameBase::jh_AddAnimation(int xmlid,float x,float y,int z)
{
    ChangeCoordinate(&x, &y, 0, 0);
    return jh_sprite->AddAnimation(xmlid, x, y, z);
}
int JH_GameBase::jh_AddAnimation(int xmlid,float x,float y,int z,int actionId)
{
    ChangeCoordinate(&x, &y, 0, 0);
	
    int n=jh_sprite->AddAnimation(xmlid, x, y, z);
    jh_sprite->SetAnimationAction(n, actionId, true);
    return n;
}

int JH_GameBase::jh_AddPlistAnimation(int xmlid,float x,float y,int z,int actionId,bool loop)
{
	ChangeCoordinate(&x, &y, 0, 0);

	int n=jh_sprite->AddPlistAnimation(xmlid, x, y, z);
	jh_sprite->SetPlistAnimationAction(n, actionId, loop);
	return n;
}

void JH_GameBase::jh_setAnimationAction(int spriteid,int actionId,bool loop)
{
    jh_sprite->SetAnimationAction(spriteid, actionId, loop);
}

/*精靈相關操作方法*/
void JH_GameBase::jh_setSpriteScale(int spriteid,float ScaleX,float ScaleY,int Rotation)
{
    jh_sprite->SetSpriteScale(spriteid,ScaleX,ScaleY,Rotation);
}
void JH_GameBase::jh_SetSpriteColor(int spriteid,int r,int g,int b)
{
    jh_sprite->SetSpriteColor(spriteid, r, g, b);
}
CCPoint JH_GameBase::jh_GetSpritePosition(int spriteid)
{
    return jh_sprite->GetSpritePosition(spriteid);
}
float JH_GameBase::jh_GetSpritePositionX(int spriteid)
{
    CCPoint m=jh_sprite->GetSpritePosition(spriteid);
    return m.x;
}
float JH_GameBase::jh_GetSpritePositionY(int spriteid)
{
    CCPoint m=jh_sprite->GetSpritePosition(spriteid);
    return screenheigth-m.y;
}
void JH_GameBase::jh_SetSpritePosition(int spriteid,float x,float y)
{
    ChangeCoordinate(&x, &y, 0, 0);
    jh_sprite->SetSpritePosition(spriteid, x,y);
}
void JH_GameBase::jh_MoveSpritePosition(int spriteid,float x,float y)
{
    CCPoint m=jh_sprite->GetSpritePosition(spriteid);
    jh_sprite->SetSpritePosition(spriteid, m.x+x,m.y-y);
}
void JH_GameBase::jh_SetSpriteAutoPosition(int spriteid,float x,float y,float speed)
{
    ChangeCoordinate(&x, &y, 0, 0);
    jh_sprite->SetSpriteAutoTo(spriteid, x, y, speed);
}
void JH_GameBase::jh_MoveSpriteAutoPosition(int spriteid,float x,float y,float speed)
{
    CCPoint m=jh_sprite->GetSpritePosition(spriteid);
    jh_sprite->SetSpriteAutoTo(spriteid, m.x+x, m.y-y, speed);
}

/*文字操作相關方法*/
int JH_GameBase::jh_AddString(const char* str,float x,float y,float z)
{
    int h=fontsize_nomal;
    int w=strlen(str);
    w=w*fontsize_nomal/2;
    ChangeCoordinate(&x, &y, w, h);
    return jh_string->AddString(str, x, y, z, font_EN, fontsize_nomal);
}
int JH_GameBase::jh_AddString(const char* str, float x, float y, float z,int fontsize)
{
    int h=fontsize;
    int w=strlen(str);
    w=w*fontsize/2;
    ChangeCoordinate(&x, &y, w, h);
    return jh_string->AddString(str, x, y, z, font_EN, fontsize);
}
int JH_GameBase::jh_AddString(const char* str, float x, float y, float z,const char* font,int fontsize)
{
    int h=fontsize;
    int w=strlen(str);
    w=w*fontsize/2;
    ChangeCoordinate(&x, &y, w, h);
    return jh_string->AddString(str, x, y, z, font, fontsize);
}
void JH_GameBase::jh_DeleteString(int id)
{
    jh_string->DeleteString(id);
}
void JH_GameBase::jh_DeleteAllString()
{
    jh_string->DeleteAllString();
}

//座標系轉換

void JH_GameBase::ChangeCoordinate(float *x,float *y,float width,float height)
{
	if (coordinate==1) 
	{
		*x+=width/2;
		*y+=height/2;
		float f=screenheigth-*y;
		*y=f;
	}
}