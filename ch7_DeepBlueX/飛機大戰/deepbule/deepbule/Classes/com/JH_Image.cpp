/* 
 圖片類別：該類別儲存遊戲中使用的主要圖片資源，這些圖片資源主要用於建立靜態精靈
 */


#include "JH_Image.h"

using namespace cocos2d;

JH_Image* JH_Image::instance = NULL;

JH_Image::JH_Image()
{

}

JH_Image::~JH_Image()
{
    unLoadAllImage();
}

//初始化堆疊空間
void JH_Image::Init()
{
    imgs = new cocos2d::CCTexture2D*[IMG_MAX];
    memset(imgs, 0, sizeof(cocos2d::CCTexture2D*)*IMG_MAX);
    imgsname = new char*[IMG_MAX];
    memset(imgsname, 0, sizeof(char*)*IMG_MAX);
}

JH_Image* JH_Image::Getinstance()
{
    if (instance==NULL) {
        instance = new JH_Image();
        instance->Init();
    }
    return instance;
}

bool JH_Image::LoadImage(int id,const char *filename)
{
    if (id>=IMG_MAX) {
        return false;
    }
    if (imgs[id]!=NULL) {
        delete imgs[id];
        imgs[id]=NULL;
    }
    if (imgsname[id]!=NULL) {
        delete imgsname[id];
        imgsname[id]=NULL;
    }
    imgs[id]=CCTextureCache::sharedTextureCache()->addImage(filename);
    if (imgs[id]!=NULL) {
        imgsname[id]=(char*)malloc(30);
        memset(imgsname[id], 0, sizeof(imgsname[id]));
        strcpy(imgsname[id], filename);
    }else
    {
        return false;
    }
    return true;
}

bool JH_Image::unLoadImage(int imgid)
{
    if (imgid>=IMG_MAX) {
        return false;
    }
    if (imgs[imgid]!=NULL) {
        delete imgs[imgid];
        imgs[imgid]=NULL;
    }
    if (imgsname[imgid]!=NULL) {
        delete imgsname[imgid];
        imgsname[imgid]=NULL;
    }
    return true;
}

void JH_Image::unLoadAllImage()
{
    for (int i=0; i<IMG_MAX; i++) {
        if (imgs[i]!=NULL) {
            delete imgs[i];
        }
        if (imgsname[i]!=NULL) {
            delete imgsname[i];
        }
    }
}
