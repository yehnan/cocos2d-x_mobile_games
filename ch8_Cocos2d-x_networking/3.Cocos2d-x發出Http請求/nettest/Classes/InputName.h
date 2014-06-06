//
//  InputName.h
//  finalplane
//
//  Created by 沈 shen on 13-10-26.
//
//

#ifndef __finalplane__InputName__
#define __finalplane__InputName__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class KeyboardNotificationLayer : public CCLayer, public CCIMEDelegate
{
public:
    KeyboardNotificationLayer();
    //CREATE_FUNC(KeyboardNotificationLayer);
    //virtual bool init();
    virtual std::string subtitle() = 0;
    virtual void onClickTrackNode(bool bClicked) = 0;
    
    virtual void registerWithTouchDispatcher();
    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info);
    virtual const char * getContentText();
    // CCLayer
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
protected:
    CCNode * m_pTrackNode;
    CCPoint  m_beginPos;
};
class TextFieldTTFDefaultTest : public KeyboardNotificationLayer
{
public:
    // KeyboardNotificationLayer
    virtual std::string subtitle();
    virtual void onClickTrackNode(bool bClicked);
    const char * getContentText();
    // CCLayer
    virtual void onEnter();
};
class InputName : public CCLayer
{
public:
    KeyboardNotificationLayer *pContainerLayer;
    CREATE_FUNC(InputName);
    static CCScene *scene();
    virtual bool init();
    void menuCallBack(CCObject * pSender);
    static size_t processData(char *ptr,size_t size,size_t nmemb,std::string *stream);
    
};
#endif /* defined(__finalplane__InputName__) */
