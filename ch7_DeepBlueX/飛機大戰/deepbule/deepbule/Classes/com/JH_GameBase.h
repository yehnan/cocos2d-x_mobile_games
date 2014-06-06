/* 
    系统呼叫的主要方法都封裝在此類別中
 */


#ifndef __JH_GAMEBASE_H__

#define __JH_GAMEBASE_H__


#include "cocos2d.h"

//#include "JH_Image.h"

#include "JH_Sprite.h"

//#include "JH_Animation.h"
#include "JH_String.h"


class JH_GameBase 
{

public:
	int screenwidth;//螢幕寬	
    int screenheigth;//螢幕高
   
	JH_Image *jh_imgs;  
	JH_Sprite *jh_sprite;   
	JH_Animation *jh_animation;    
	JH_String* jh_string;   
   
 
public:
    JH_GameBase();   
	 ~JH_GameBase();
    
	void Init();    

	void jh_unLoadAllImage();
	//釋放全部圖片資源
	bool jh_unLoadImage(int imgid);//釋放指定的圖片資源
   
	bool jh_LoadImage(int imgid,const char* filename);//載入圖片資源（圖片ID，圖片名）
   
	void ChangeCoordinate(float *x,float *y,float width,float height);
    

    /*
        靜態精靈（圖片）相關方法
    */
  
  //加入一個靜態精靈（圖片ID號，螢幕座標x y，切圖img_x img_y img_width img_hight，Z軸）
   
 //函式回傳精靈唯一ID
	void jh_DeleteSprite(int id);//删除給定ID的精靈
	void jh_DeleteAllSprite();//删除全部精靈
	void jh_DeleteSprite(int id,float x,float y);
    int  jh_AddSprite(int imgid,float x,float y,float img_x,float img_y,float img_width,float img_hight,int z);
    //不含切圖方法
    int jh_AddSprite(int imgid,float x,float y,float img_width,float img_height,int z);
   
    
    /*
        動態精靈（動畫）相關方法
    */
    //載入資源檔案（資源ID，圖片檔案名，XML檔案名）
    bool jh_LoadAnimation(int _id,const char* filename,const char* xmlname);  
	bool jh_LoadPlistAnimation(int _id,const char* filename,const char* xmlname); 
    //删除全部資源檔案
    void jh_DeleteAllAnimation();
	//删除給定ID的資源檔案
	void jh_DeleteAnimation(int _id);
  
  //函式回傳精靈唯一ID
    int jh_AddAnimation(int xmlid,float x,float y,int z);
    int jh_AddAnimation(int xmlid,float x,float y,int z,int actionId);
    int jh_AddAnimation(int xmlid,float x,float y,int z,int actionId,bool loop);
	int jh_AddPlistAnimation(int xmlid,float x,float y,int z,int actionId,bool loop);
    //為動態精靈設定動作
    void jh_setAnimationAction(int spriteid,int actionId,bool loop);
    
    /*
        精靈相關操作方法
    */
    //控制精靈：放大、縮小、旋轉
    //ScaleX：沿中心寬度放大,1.0為原始大小   ScaleY：沿中心高度放大,1.0為原始大小
    //Rotation:沿中心點旋轉度数，如：30  顺時針旋轉30度    -30  逆時針旋轉30度
    void jh_setSpriteScale(int spriteid,float ScaleX,float ScaleY,int Rotation);
    //控制精靈：顏色混合 採用RGB顏色
    void jh_SetSpriteColor(int spriteid,int r,int g,int b);
    //取得精靈的位置
    CCPoint jh_GetSpritePosition(int spriteid);
    float jh_GetSpritePositionX(int spriteid);
    float jh_GetSpritePositionY(int spriteid);
    /* 控制精靈：改變位置 */
    //瞬間移動到指定位置
    void jh_SetSpritePosition(int spriteid,float x,float y);
    //瞬間移動到相對於目前位置的差值
    void jh_MoveSpritePosition(int spriteid,float x,float y);
    //直線移動到指定位置
    void jh_SetSpriteAutoPosition(int spriteid,float x,float y,float speed);
    //直線移動到相對於目前位置的差值
    void jh_MoveSpriteAutoPosition(int spriteid,float x,float y,float speed);
    
    /*
        文字相關操作方法
    */
    int jh_AddString(const char* str,float x,float y,float z);
    int jh_AddString(const char* str, float x, float y, float z,int fontsize);
    int jh_AddString(const char* str, float x, float y, float z,const char* font,int fontsize);
    void jh_DeleteString(int id);
    void jh_DeleteAllString();
};

#endif
