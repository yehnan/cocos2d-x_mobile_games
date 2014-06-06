/* 
    動畫類別：該方法負責讀取動畫的xml檔
  */

#include "Animation.h"

using namespace cocos2d;

Animation::Animation()
{
    
}

Animation::Animation(const char* _img, const char* _actionFile)
{
    img=CCTextureCache::sharedTextureCache()->addImage(_img);
	
 //   CreateAnimation(NULL, _actionFile);
}

Animation::~Animation()
{
    for (int i=0; i<Moudle_Count; i++) {
        delete Moudle[i];
        Moudle[i]=NULL;
    }
    delete Moudle;
    Moudle=NULL;
    
    for (int i=0; i<Frame_Count; i++) {
        for (int j=0; j<Frame[i]->Sprite_Count; j++) {
            delete Frame[i]->Sprite[j];
            Frame[i]->Sprite[j]=NULL;
        }
        delete Frame[i]->name;
        Frame[i]->name=NULL;
        delete Frame[i];
        Frame[i]=NULL;
    }
    delete Frame;
    Frame=NULL;
    
    for (int i=0; i<Action_Count; i++) {
        for (int j=0; j<Action[i]->frames_Count; j++) {
            delete Action[i]->frames[j];
            Action[i]->frames[j]=NULL;
        }
        delete Action[i]->name;
        Action[i]->name=NULL;
        delete Action[i];
        Action[i]=NULL;
    }
    delete Action;
    Action=NULL;
    
    delete img;
    img=NULL;
}

void Animation::CreateAnimation(const char* _img, const char* _actionFile)
{
    int i,j;
    int count;
    TiXmlDocument doc = ReadXMLFile::initXMLFile(_actionFile);
    TiXmlElement* rootElement = doc.RootElement();  //Animation
    TiXmlElement* modulesElement = rootElement->FirstChildElement();  //Moduless
    //取得全部Module資訊
    TiXmlElement* moduleElement = modulesElement->FirstChildElement();
    count=GetElementCount(moduleElement);
    Moudle_Count=count;
    Moudle=new Ani_Module*[count];
    memset(Moudle, 0, sizeof(Ani_Module*)*count);
    i=0;
    while ( moduleElement ) {
		const TiXmlAttribute* attributeOfModule = moduleElement->FirstAttribute(); 
        Moudle[i]=new Ani_Module;
        memset(Moudle[i], 0, sizeof(Moudle[i]));
		while ( attributeOfModule ) {
			if(strcmp("h", attributeOfModule->Name())==0){
                Moudle[i]->h=atoi(attributeOfModule->Value());
            }else if(strcmp("x", attributeOfModule->Name())==0){
                Moudle[i]->x=atoi(attributeOfModule->Value());
            }else if(strcmp("y", attributeOfModule->Name())==0){
				Moudle[i]->y=atoi(attributeOfModule->Value());
			}else if(strcmp("w", attributeOfModule->Name())==0){
				Moudle[i]->w=atoi(attributeOfModule->Value());
			}else if(strcmp("image_id", attributeOfModule->Name())==0){
				Moudle[i]->imgid=atoi(attributeOfModule->Value());
            }
			attributeOfModule=attributeOfModule->Next();
		}
        i++;
        moduleElement = moduleElement->NextSiblingElement();
    }
    //取得全部Frames資訊
    TiXmlElement* FramesElement = modulesElement->NextSiblingElement();
    modulesElement=modulesElement->NextSiblingElement();
    TiXmlElement* FrameElement = FramesElement->FirstChildElement();
    count=GetElementCount(FrameElement);
    Frame_Count=count;
    Frame=new Ani_Frame*[count];
    memset(Frame, 0, sizeof(Ani_Frame*)*count);
    i=0;
    while ( FrameElement ) {
		const TiXmlAttribute* attributeOfModule = FrameElement->FirstAttribute(); 
        Frame[i]=new Ani_Frame;
        memset(Frame[i], 0, sizeof(Frame[i]));
		while ( attributeOfModule ) {
			if(strcmp("ab", attributeOfModule->Name())==0){
                Frame[i]->ab=atoi(attributeOfModule->Value());
            }else if(strcmp("al", attributeOfModule->Name())==0){
                Frame[i]->al=atoi(attributeOfModule->Value());
            }else if(strcmp("ar", attributeOfModule->Name())==0){
				Frame[i]->ar=atoi(attributeOfModule->Value());
			}else if(strcmp("at", attributeOfModule->Name())==0){
				Frame[i]->at=atoi(attributeOfModule->Value());
			}else if(strcmp("cb", attributeOfModule->Name())==0){
				Frame[i]->cb=atoi(attributeOfModule->Value());
            }else if(strcmp("cl", attributeOfModule->Name())==0){
				Frame[i]->cl=atoi(attributeOfModule->Value());
            }else if(strcmp("cr", attributeOfModule->Name())==0){
				Frame[i]->cr=atoi(attributeOfModule->Value());
            }else if(strcmp("ct", attributeOfModule->Name())==0){
				Frame[i]->ct=atoi(attributeOfModule->Value());
            }else if(strcmp("name", attributeOfModule->Name())==0){
				Frame[i]->name=(char*)malloc(sizeof(attributeOfModule->Value()));
                strcpy(Frame[i]->name, attributeOfModule->Value());
            }
			attributeOfModule=attributeOfModule->Next();
		}
        //傳遞Sprite資訊
        TiXmlElement *SpriteElement=FrameElement->FirstChildElement();
        if (SpriteElement) {
            int count2=GetElementCount(SpriteElement);
            Frame[i]->Sprite_Count=count2;
            Frame[i]->Sprite=new Ani_Sprite*[count2];
            memset(Frame[i]->Sprite, 0, sizeof(Ani_Sprite*)*count2);
            j=0;
            while ( SpriteElement ) {
                const TiXmlAttribute* attributeOfModule2 = SpriteElement->FirstAttribute(); 
                Frame[i]->Sprite[j]=new Ani_Sprite;
                memset(Frame[i]->Sprite[j], 0, sizeof(Ani_Sprite));
                while ( attributeOfModule2 ) {
                    if(strcmp("flip", attributeOfModule2->Name())==0){
                        Frame[i]->Sprite[j]->flip=atoi(attributeOfModule2->Value());
                    }else if(strcmp("px", attributeOfModule2->Name())==0){
                        Frame[i]->Sprite[j]->px=atof(attributeOfModule2->Value());
                    }else if(strcmp("py", attributeOfModule2->Name())==0){
                        Frame[i]->Sprite[j]->py=atof(attributeOfModule2->Value());
                    }else if(strcmp("module_id", attributeOfModule2->Name())==0){
                        Frame[i]->Sprite[j]->module_id=atoi(attributeOfModule2->Value());
                    }
                    attributeOfModule2=attributeOfModule2->Next();
                }
                j++;
                SpriteElement=SpriteElement->NextSiblingElement();
            }
        }
        i++;
		FrameElement = FrameElement->NextSiblingElement();
    }
    
    //取得全部Action資訊
    TiXmlElement* ActionsElement = modulesElement->NextSiblingElement();
    TiXmlElement* ActionElement = ActionsElement->FirstChildElement();
    count=GetElementCount(ActionElement);
    Action_Count=count;
    Action=new Ani_Action*[count];
    memset(Action, 0, sizeof(Ani_Action*)*count);
    i=0;
    while ( ActionElement ) {
		const TiXmlAttribute* attributeOfModule = ActionElement->FirstAttribute(); 
        Action[i]=new Ani_Action;
        memset(Action[i], 0, sizeof(Ani_Action));
		while ( attributeOfModule ) {
			if(strcmp("name", attributeOfModule->Name())==0){
				Action[i]->name=(char*)malloc(sizeof(attributeOfModule->Value()));
                strcpy(Action[i]->name, attributeOfModule->Value());
                Action[i]->_id=i;
            }
			attributeOfModule=attributeOfModule->Next();
		}
        //傳遞MechModel Sequence資訊
        TiXmlElement *SpriteElement=ActionElement->FirstChildElement();
        if (SpriteElement) {
            int count2=GetElementCount(SpriteElement);
            Action[i]->frames_Count=count2-1;
            Action[i]->frames=new Ani_Sequence*[count2-1];
            memset(Action[i]->frames, 0, sizeof(int*)*(count2-1));
            j=0;
            bool first=true;
            while ( SpriteElement ) {
                const TiXmlAttribute* attributeOfModule2 = SpriteElement->FirstAttribute(); 
                if (first) {
                    first=false;
                    while ( attributeOfModule2 ) {
                        if(strcmp("ax", attributeOfModule2->Name())==0){
                            Action[i]->ax=atof(attributeOfModule2->Value());
                        }else if(strcmp("ay", attributeOfModule2->Name())==0){
                            Action[i]->ay=atof(attributeOfModule2->Value());
                        }else if(strcmp("flag", attributeOfModule2->Name())==0){
                            Action[i]->flag=atof(attributeOfModule2->Value());
                        }else if(strcmp("vx", attributeOfModule2->Name())==0){
                            Action[i]->vx=atof(attributeOfModule2->Value());
                        }else if(strcmp("vy", attributeOfModule2->Name())==0){
                            Action[i]->vy=atof(attributeOfModule2->Value());
                        }
                        attributeOfModule2=attributeOfModule2->Next();
                    }
                    SpriteElement=SpriteElement->NextSiblingElement();
                    continue;
                }
                Action[i]->frames[j]=new Ani_Sequence;
                memset(Action[i]->frames[j], 0, sizeof(int));
                while ( attributeOfModule2 ) {
                    if(strcmp("id", attributeOfModule2->Name())==0){
                        Action[i]->frames[j]->_id=atoi(attributeOfModule2->Value());
                    }else if(strcmp("duration", attributeOfModule2->Name())==0){
                        Action[i]->frames[j]->duration=atoi(attributeOfModule2->Value());
                    }
                    attributeOfModule2=attributeOfModule2->Next();
                }
                j++;
                SpriteElement=SpriteElement->NextSiblingElement();
            }
        }
        i++;
		ActionElement = ActionElement->NextSiblingElement();
    }
}

int Animation::GetElementCount(TiXmlElement *element)
{
    int count=0;
    TiXmlElement *e=element;
    e->FirstChildElement();
    while (e) {
        count++;
        e=e->NextSiblingElement();
    }
    return count;
}
