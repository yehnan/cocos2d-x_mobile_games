/* 
 圖片類別：該類別儲存遊戲中使用的主要圖片資源，這些圖片資源主要用於建立靜態精靈
 */

#ifndef __JH_Image_H__
#define __JH_Image_H__

#include "cocos2d.h"

#define IMG_MAX 100 //最大圖片數量

class JH_Image{
public:
    JH_Image();
    ~JH_Image();
    static JH_Image* Getinstance();
    
    void Init();
    
    bool LoadImage(int id,const char *filename);//載入圖片
    bool unLoadImage(int imgid);//釋放圖片       
    void unLoadAllImage();//釋放全部圖片
public:
    static JH_Image* instance;
    
    cocos2d::CCTexture2D **imgs;//圖片資源紋理
    char **imgsname;//圖片資源名稱
};

#endif 
