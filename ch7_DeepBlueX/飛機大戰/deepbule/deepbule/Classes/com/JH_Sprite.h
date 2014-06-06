/* 
 精靈類別：該類別封装了遊戲動態和靜態精靈的相關方法
*/
#pragma  once
#include "cocos2d.h"
#include "JH_Image.h"
#include "JH_Animation.h"
#ifndef NULL
#define  NULL 0
#endif
using namespace cocos2d;

struct Sprites {

	CCSprite* sprite;	//精靈
    int sprite_id;		//精靈ID
    int layertag;		//疊加位置 
    short sprite_change;//變動請求(0-無變化，1-增加，2-删除)
    int xmlid;			//動態精靈專用，用於記錄他所要使用的XML
    Sprites(){};
	Sprites * next;
};

class JH_Sprite
{
public:
    JH_Sprite();
    ~JH_Sprite();
    static JH_Sprite* Getinstance();
    
    void Init();
    /*
     增加一個精靈到螢幕中
     圖片ID,螢幕中的位置（x,y,z）,切圖(img_x, img_y,img_width,img_hight)
    */
    int AddSprite(int imgid,float x,float y,float img_x,float img_y,float img_width,float img_hight,int z);
    int AddSprite(int imgid,float x,float y,float img_width,float img_height,int z);     
	void DeleteAllSprite();//删除全部精靈
    void DeleteSprite(int id);//删除指定的精靈
    void DeleteSprite(int id,float x,float y);
    
    /*
        動畫相關方法
    */
	void SetPlistAnimationAction(int spriteid,int actionId,bool loop);
    void SetAnimationAction(int spriteid,int actionId,bool loop);
    int AddAnimation(int xmlid,float x,float y,int z);
	int AddPlistAnimation(int xmlid,float x,float y,int z);
    /*
        精靈操作相關方法（靜態和動態通用）
    */
	void SetSpritePosition(int spriteid,float x,float y);
    void SetSpriteScale(int spriteid,float ScaleX,float ScaleY,int Rotation);
    void SetSpriteColor(int spriteid,int r,int g,int b);    
    CCPoint GetSpritePosition(int spriteid);
    void SetSpriteAutoTo(int spriteid,float x,float y,float speed);
public:
    static JH_Sprite* instance;			//唯一實體
	int sprite_headid;
    JH_Image* jh_imgs;					//靜態精靈
   
    bool sprite_run;					//精靈的增加和删除
    Sprites *sprite_head;				//精靈表頭
    JH_Animation* jh_animation;			//動態精靈
   
};
