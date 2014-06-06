/* 
 文字類別：該類別封裝了遊戲文字處理的相關方法
 */

#ifndef __JH_STRING_H__
#define __JH_STRING_H__

#include "cocos2d.h"

using namespace cocos2d;

//常用文字字型
#define font_EN "Arial"
//常用文字大小
#define fontsize_big   32
#define fontsize_nomal 18
#define fontsize_small 12

struct Strings {
    int Str_id;
    int layertag;
    short Str_change;//變動请求(0-無變化，1-增加，2-删除)
    CCLabelTTF* label;
    Strings* next;
};

class JH_String
{
public:
    JH_String();
    ~JH_String();
    static JH_String* Getinstance();
    
    void Init();
    /*
     增加一個字串到螢幕中
    */
    int AddString(const char* str,float x,float y,int z,const char* font,float fontsize);
    void DeleteString(int id);
    void DeleteAllString();
 
public:
    static JH_String* instance;			//唯一實體
       
    Strings		*strings_head;				//字串表頭
   
	int			strings_headid;
    bool		strings_run;					//最佳化精靈的增加和删除操作
};

#endif
