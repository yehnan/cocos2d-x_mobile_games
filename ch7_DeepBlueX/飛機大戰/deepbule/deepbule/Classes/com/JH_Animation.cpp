/* 
 動畫類別：該類別儲存遊戲中使用的全部動畫資源
 */

#include "JH_Animation.h"

using namespace cocos2d;

JH_Animation* JH_Animation::instance = NULL;

JH_Animation::JH_Animation()
{

}

JH_Animation::~JH_Animation()
{

}

//初始化堆疊空間
void JH_Animation::Init()
{
    AniX = new Animation*[Ani_MAX];
    memset(AniX, 0, sizeof(Animation*)*Ani_MAX);
}

JH_Animation* JH_Animation::Getinstance()
{
    if (instance==NULL) {
        instance = new JH_Animation();
        instance->Init();
    }
    return instance;
}

bool JH_Animation::LoadAnimation(int _id,const char* imgname, const char* xmlname)
{
    if (_id>=Ani_MAX) {
        return false;
    }
    if (AniX[_id]!=NULL) {
        DeleteAnimation(_id);
    }
    AniX[_id] = new Animation(imgname, xmlname);
	AniX[_id]->CreateAnimation(NULL,xmlname);
    if (AniX[_id]==NULL) {
        return false;
    }
    return true;
}

bool JH_Animation::LoadPlistAnimation(int _id,const char* imgname, const char* xmlname)
{
	if (_id>=Ani_MAX) {
        return false;
    }
    if (AniX[_id]!=NULL) {
        DeleteAnimation(_id);
    }
    AniX[_id] = new plistAnimation(imgname, xmlname);
	AniX[_id]->CreateAnimation(imgname,xmlname);
    if (AniX[_id]==NULL) {
        return false;
    }
    return true;
}

void JH_Animation::DeleteAnimation(int _id)
{
	if (AniX[_id]!=NULL)
	{
		delete AniX[_id];
		AniX[_id]=NULL;
	}
   
}

void JH_Animation::DeleteALLAnimation()
{
    for (int i=0; i<Ani_MAX;i++) {
        delete AniX[i];
        AniX[i]=NULL;
    }
    AniX=NULL;
}
