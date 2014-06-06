/* 
    文字類別：該類別封裝了遊戲文字處理的相關方法
 */

#include "JH_String.h"

using namespace cocos2d;

JH_String* JH_String::instance = NULL;

JH_String::JH_String()
{

}

JH_String::~JH_String()
{

}

//初始化堆疊空間
void JH_String::Init()
{
    strings_head=new Strings();
    strings_head->Str_change=false;
    strings_head->next=NULL;
	
	strings_headid=0;
   
    strings_run=false;
}

JH_String* JH_String::Getinstance()
{
    if (instance==NULL) {
        instance = new JH_String();
        instance->Init();
    }
    return instance;
}

int JH_String::AddString(const char* str,float x,float y,int z,const char* font,float fontsize)
{
    Strings* addhead=strings_head;
    while (strings_head->next!=NULL) {
        strings_head=strings_head->next;
    }
    //精靈相關初始化
	//strings_head->next=NULL;
    strings_head->next=new Strings();
	strings_head->next->label=CCLabelTTF::create(str, font, fontsize);
   
    strings_head->next->label->setPosition(ccp(x, y));
    strings_head->next->label->retain();
    
    //串列相關處理 
    strings_head->next->layertag=z;
    strings_head->next->next=NULL;
    strings_head->next->Str_change=1;
    strings_head->next->Str_id=strings_headid++;
    strings_head=addhead;
    addhead=NULL;
    strings_run=true;
    return strings_headid-1;
}

void JH_String::DeleteString(int id)
{
    if (strings_head->next==NULL) {
        return;
    }
    Strings* head=strings_head;
    strings_head=strings_head->next;
    while (strings_head!=NULL) {
        if (strings_head->Str_id==id) {
            strings_head->Str_change=2;
            break;
        }
        strings_head=strings_head->next;
    }
    strings_head=head;
    head=NULL;
    strings_run=true;
}

void JH_String::DeleteAllString()
{
    if (strings_head->next==NULL) {
        return;
    }
    Strings* head=strings_head;
    strings_head=strings_head->next;
    while (strings_head!=NULL) {
        strings_head->Str_change=2;
        strings_head=strings_head->next;
    }
    strings_head=head;
    head=NULL;
    strings_run=true;
}
