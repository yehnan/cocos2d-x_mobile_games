//
//  InputName.cpp
//  finalplane
//
//  Created by 沈 shen on 13-10-26.
//
//

#include "InputName.h"
#include "curl/curl.h"
#include "HelloWorldScene.h"
//#include "GameController.h"
//////////////////////////////////////////////////////////////////////////
// implement KeyboardNotificationLayer
//////////////////////////////////////////////////////////////////////////
static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}
KeyboardNotificationLayer::KeyboardNotificationLayer()
: m_pTrackNode(0)
{
    setTouchEnabled(true);
}

void KeyboardNotificationLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void KeyboardNotificationLayer::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
{
    CCLOG("TextInputTest:keyboardWillShowAt(origin:%f,%f, size:%f,%f)",
          info.end.origin.x, info.end.origin.y, info.end.size.width, info.end.size.height);
    
    if (! m_pTrackNode)
        {
        return;
        }
    
    CCRect rectTracked = getRect(m_pTrackNode);
    CCLOG("TextInputTest:trackingNodeAt(origin:%f,%f, size:%f,%f)",
          rectTracked.origin.x, rectTracked.origin.y, rectTracked.size.width, rectTracked.size.height);
    
    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
    if (! rectTracked.intersectsRect(info.end))
        {
        return;
        }
    
    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
    float adjustVert = info.end.getMaxY() - rectTracked.getMinY();
    CCLOG("TextInputTest:needAdjustVerticalPosition(%f)", adjustVert);
    
    // move all the children node of KeyboardNotificationLayer
    CCArray * children = getChildren();
    CCNode * node = 0;
    int count = children->count();
    CCPoint pos;
    for (int i = 0; i < count; ++i)
        {
        node = (CCNode*)children->objectAtIndex(i);
        pos = node->getPosition();
        pos.y += adjustVert;
        node->setPosition(pos);
        }
}
const char * KeyboardNotificationLayer::getContentText(){
    return this->getContentText();
}
// CCLayer function

bool KeyboardNotificationLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("++++++++++++++++++++++++++++++++++++++++++++");
    m_beginPos = pTouch->getLocation();
    return true;
}

void KeyboardNotificationLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (! m_pTrackNode)
        {
        return;
        }
    
    CCPoint endPos = pTouch->getLocation();
    
    float delta = 5.0f;
    if (::abs(endPos.x - m_beginPos.x) > delta
        || ::abs(endPos.y - m_beginPos.y) > delta)
        {
        // not click
        m_beginPos.x = m_beginPos.y = -1;
        return;
        }
    
    // decide the trackNode is clicked.
    CCRect rect;
    CCPoint point = convertTouchToNodeSpaceAR(pTouch);
    CCLOG("KeyboardNotificationLayer:clickedAt(%f,%f)", point.x, point.y);
    
    rect = getRect(m_pTrackNode);
    CCLOG("KeyboardNotificationLayer:TrackNode at(origin:%f,%f, size:%f,%f)",
          rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    this->onClickTrackNode(rect.containsPoint(point));
    CCLOG("----------------------------------");
}
///////////
std::string TextFieldTTFDefaultTest::subtitle()
{
    return "TextFieldTTF with default behavior test";
}
const char * TextFieldTTFDefaultTest::getContentText(){
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;

    return pTextField->getString();
}
void TextFieldTTFDefaultTest::onClickTrackNode(bool bClicked)
{
    CCTextFieldTTF * pTextField = (CCTextFieldTTF*)m_pTrackNode;
    if (bClicked)
        {
        // TextFieldTTFTest be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF attachWithIME");
        pTextField->attachWithIME();
        }
    else
        {
        // TextFieldTTFTest not be clicked
        CCLOG("TextFieldTTFDefaultTest:CCTextFieldTTF detachWithIME");
        pTextField->detachWithIME();
        }
}

void TextFieldTTFDefaultTest::onEnter()
{
    KeyboardNotificationLayer::onEnter();
    
    // add CCTextFieldTTF
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCTextFieldTTF * pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
                                                                           "宋体",
                                                                           24);
    addChild(pTextField);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // on android, CCTextFieldTTF cannot auto adjust its position when soft-keyboard pop up
    // so we had to set a higher position to make it visable
    pTextField->setPosition(ccp(s.width / 2, s.height/2 + 50));
#else
    pTextField->setPosition(ccp(s.width / 2, s.height / 2));
#endif
    
    m_pTrackNode = pTextField;
}

///////////////
bool InputName::init(){
    CCLayer::init();
    //加入輸入提示和輸入框
    CCLabelTTF * labelTitle=CCLabelTTF::create("請輸入暱稱", "宋体", 24);
    this->addChild(labelTitle);
    
    labelTitle->setPosition(ccp(80,300));
    CCLabelTTF * labelTitle02=CCLabelTTF::create("請輸入密碼", "宋体", 24);
    this->addChild(labelTitle02);
    
    labelTitle02->setPosition(ccp(80,200));
    //加入輸入框輸入用户名
    KeyboardNotificationLayer* inputLayerName = new TextFieldTTFDefaultTest();
    inputLayerName->autorelease();
    this->addChild(inputLayerName);
    inputLayerName->setPosition(ccp(80,100));
    //inputLayerName->setContentSize(CCSize(200, 100));
    inputLayerName->setTag(10);
    KeyboardNotificationLayer* inputLayerPass = new TextFieldTTFDefaultTest();
    inputLayerPass->autorelease();
    this->addChild(inputLayerPass);
    inputLayerPass->setPosition(ccp(80,
                                0));
    //inputLayerPass->setContentSize(CCSize(200, 100));
    inputLayerPass->setTag(11);

    //加入確定按鈕，進行網路連線
    CCMenuItemFont * itemok=CCMenuItemFont::create("確定",this,
                                                   menu_selector(InputName::menuCallBack));
    CCMenu * menu=CCMenu::create(itemok,NULL);
     menu->setPosition(ccp(200-itemok->getContentSize().width,100));
    
    this->addChild(menu);
    return true;
};
void InputName::menuCallBack(CCObject * pSender){
    TextFieldTTFDefaultTest* pUser=(TextFieldTTFDefaultTest*)this->getChildByTag(10);
    CCLog(">>>>>>>>>>>>>>name:%s",pUser->getContentText());
    TextFieldTTFDefaultTest* pPass=(TextFieldTTFDefaultTest*)this->getChildByTag(11);
    CCLog(">>>>>>>>>>>>>>pass%s",pPass->getContentText());
   
  //1。從UI介面取得用户輸入的用户名和密碼
  //2。網路連線
    CURL * curl=curl_easy_init();
    char url[1000];
    sprintf(url, "http://10.2.145.86/testphp/checkLogin02.php?uname=%s&upass=%s",pUser->getContentText(),pPass->getContentText());
    int res;
    res = curl_easy_setopt(curl, CURLOPT_URL, url);
    //設定資料接收方法
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&InputName::processData);
    //設定資料接收變數
    std::string recvbuf;//定義資料接收變數
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,&recvbuf);
    //連接網路
    res=curl_easy_perform(curl);
    if(CURLE_OK==res)
    {
      if(recvbuf.compare("1")==0)
        {
        //儲存用户的name
          HelloWorld::setUname(pUser->getContentText());
        //登入成功 切換到遊戲場景
            CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
         
        }else
        {
        CCMessageBox("登陆失败,请重新輸入","登陆結果");
            }
    }
    curl_easy_cleanup(curl);
  //3。根據網路連線回傳的結果實作切換和提示
}
CCScene * InputName::scene(){
    //建立場景
    CCScene * scene=CCScene::create();
    //建立圖層
    InputName * input=InputName::create();
    //將圖層加入到場景
    scene->addChild(input);
    return scene;
}
size_t InputName::processData(char *ptr,size_t size,size_t nmemb,std::string *stream)
{
    //	CCLOG("正在寫入資料");
	if (stream == NULL) return 0;
	size_t sizes = size*nmemb;
	stream->append(ptr, sizes);
    //	m_netMsg = string((char *)ptr);
	return sizes;
 
}
