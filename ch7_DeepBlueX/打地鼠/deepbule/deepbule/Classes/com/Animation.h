/* 
    動畫類別：該方法負責讀取動畫的xml檔
 */


#ifndef __Animation_H__

#define __Animation_H__


#include "cocos2d.h"
#include "JH_Image.h"
#include "ReadXMLFile.h"
#include "tinyxml.h"


struct Ani_Module {
    int imgid;
    int x;
    int y;
    int w;
    int h;
};


struct Ani_Sprite {
    int flip;
    float px;
    float py;
    int module_id;
};


struct Ani_Frame {
    int _id;//幀ID
    int ab;
    int al;
    int ar;
    int at;
    int cb;
    int cl;
    int cr;
    int ct;
    char *name;
    Ani_Sprite **Sprite;
    int Sprite_Count;
};

struct Ani_Sequence {
    int _id;
    int duration;
};

struct Ani_Action {
    int _id;//動作ID編號
    char *name;
    int ax;
    int ay;
    int flag;
    int vx;
    int vy;
    Ani_Sequence** frames;
    int frames_Count;
};

class Animation {
    
public:
    //基本節點
    Ani_Module** Moudle;
    int Moudle_Count;
    
    Ani_Frame** Frame;
    int Frame_Count;
    
    Ani_Action** Action;
    int Action_Count;
    
    //圖片
    cocos2d::CCTexture2D* img;
	cocos2d::CCSpriteFrame *   spriteFrame;
public:
    
    Animation();
    Animation(const char* _img, const char* _actionFile);
    virtual  ~Animation();
    
    virtual void CreateAnimation(const char* _img, const char* _actionFile);
    virtual int GetElementCount(TiXmlElement *element);
};

#endif
