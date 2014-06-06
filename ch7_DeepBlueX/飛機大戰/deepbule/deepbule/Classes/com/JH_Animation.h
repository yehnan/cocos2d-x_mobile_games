/* 
 動畫類別：該類別儲存遊戲中使用的全部動畫資源
  */


#ifndef __JH_ANIMATION_H__
#define __JH_ANIMATION_H__

#include "cocos2d.h"
#include "Animation.h"
#include "plistAnimation.h"
#define Ani_MAX 100

class JH_Animation{
public:
    JH_Animation();
    ~JH_Animation();
    
static JH_Animation* Getinstance();
    
    void Init();
    
    bool LoadAnimation(int _id,const char* imgname, const char* xmlname);
	bool LoadPlistAnimation(int _id,const char* imgname, const char* xmlname);
    void DeleteAnimation(int _id);
    void DeleteALLAnimation();
   
 
public:
    static JH_Animation* instance;
    Animation** AniX;

};

#endif 
