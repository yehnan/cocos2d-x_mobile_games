#include "HelloWorldScene.h"
#include "curl/curl.h"
#include "string.h"
#include "Player.h"
#include "stdio.h"
USING_NS_CC;
class  SPlayer :public CCObject  {
public:
    int m_socketid; //發送過來訊息的socket物件編號
    string m_name;//發送過來訊息的訊息内容
};

static HelloWorld *g_nowHelloWorld;
static CCArray * g_allPlayer;//所有玩家
static CCArray * g_newPlayertask;//加入新玩家
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    g_nowHelloWorld=this;
    g_allPlayer=new CCArray();//儲存所有玩家
    g_newPlayertask=new CCArray();
    this->setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    //////加入遊戲人物
    Player * player=Player::create();
    player->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height/2));
  
    player->setTag(10);
    player->setAnchorPoint(ccp(0,0));
    this->addChild(player);
    //定義排程任務
    schedule(schedule_selector(HelloWorld::run), 0.3);
    //透過Socket連接到遊戲伺服器
    //初始化Socket物件
    sock_client=new ODSocket();
    //連接到Socket伺服器，顯示從伺服器發送過來的内容到場景
    sock_client->Init();
    bool res= sock_client->Create(AF_INET, SOCK_STREAM,0);
    printf("Cocos2d-x客户端socket建立%d",res);
    //連接伺服器
    res=sock_client->Connect("10.2.145.86", 8889);
    printf("連接伺服器成功 %d",res);
    //首先發送一個Socket的登入訊息
    char buf[50];
    sprintf(buf,"@@%s\r\n", getUname().c_str());
    sock_client->Send(buf, sizeof(buf));
    //接收從伺服器發過來的訊息
    if(res==1)
        {//啟動執行緒
            pthread_t tid;
            //1建立執行緒物件
            bool ok= pthread_create(&tid,NULL, HelloWorld::getMessage, NULL);
            std::cout << "執行緒啟動结果"<<ok<<endl;
            
        }

    return true;
}
//接收從伺服器發送過來的資料
void * HelloWorld::getMessage(void *){
    char buf[1024];
    while (1) {
        //buf[0]=0;
        g_nowHelloWorld->sock_client->Recv(buf, sizeof(buf));
        if(strlen(buf)>5)
        { //解析資料
          //命令1 新玩家登入
          //id name px py
          //命令2 玩家位置改變
          //id px py
            printf("\n%s",buf);
          if(buf[0]=='*'&&buf[1]=='*')//從伺服器回傳目前玩家的編號
          { //**10000\r\n\0
            char tmp[10];
              for(int i=0;i<strlen(buf);i++)
             {if(buf[i+2]=='\r')
                {
                  tmp[i]='\0';
                  break;
                }
                 else
               {
               tmp[i]=buf[i+2];
               }
             }
            int pid=std::atoi(tmp);
            Player *p=(Player *)g_nowHelloWorld->getChildByTag(10);
            p->m_playerID=pid;
          }
          else if(buf[0]=='@'&&buf[1]=='@')//新的玩家登入
          {//加入g_allPlayer列表中
              //取得玩家id
              int pid=0;
              int position=0;
              //得到pid
              char tmp[10];
              for(int i=0;i<strlen(buf);i++)
                  {if(buf[i+2]==',')
                      {
                      position=i+2;
                      tmp[i]='\0';
                      break;
                      }
                  else
                      {
                      tmp[i]=buf[i+2];
                      }
                  }
              pid=std::atoi(tmp);
              //得到px
              for (int i=position+1; i<strlen(buf); i++) {
                  if(buf[i]=='\r')
                      {
                      position=i;
                      tmp[i-position-1]='\0';
                      break;
                      }
                  else
                      {
                      tmp[i-position-1]=buf[i];
                      }
              }
            //加入到視窗
            SPlayer *  np=new SPlayer();
            np->autorelease();
              np->m_name=tmp;
              np->m_socketid=pid;
              g_newPlayertask->addObject(np);
           
          }
          else if(buf[0]=='$'&&buf[1]=='$')//玩家位置改變
          {   //$$10000,0.0000,-5.000\r\n
              //取得玩家id
              int pid=0;
              int px=0;
              int py=0;
              int position=0;
              //得到pid
              char tmp[10];
              for(int i=0;i<strlen(buf);i++)
                  {if(buf[i+2]==',')
                      {
                      position=i+2;
                      tmp[i]='\0';
                      break;
                      }
                  else
                      {
                      tmp[i]=buf[i+2];
                      }
                  }
              pid=std::atoi(tmp);
              //得到px
              for (int i=position+1; i<strlen(buf); i++) {
                  if(buf[i]==',')
                      {
                      position=i;
                      tmp[i-position-1]='\0';
                      break;
                      }
                  else
                      {
                      tmp[i-position-1]=buf[i];
                      }
              }
              px=std::atoi(tmp);
              //得到py
              for (int i=position+1; i<strlen(buf); i++) {
                  if(buf[i]=='\r')
                      {
                      position=i;
                      tmp[i-position-1]='\0';
                      break;
                      }
                  else
                      {
                      tmp[i-position-1]=buf[i];
                      }
              }
              py=std::atoi(tmp);

            //修改玩家的位置
              for(int i=0;i<g_allPlayer->count();i++)
                {Player *p=(Player *)g_allPlayer->objectAtIndex(i);
                 if(p->m_playerID==pid)
                    {//修改這個玩家的座標為px,py
                        p->m_px=px;
                        p->m_py=py;
                    }
                }
          }
          
        }
    }
}
Player * HelloWorld::addPlayer(std::string uname,int pid){
    Player *p=Player::create();
    p->setName(uname);
    p->m_playerID=pid;
    p->setTag(p->m_playerID);
    p->setPosition(ccp(100,100));
    p->setAnchorPoint(ccp(0,0));
    return p;
}
//char* substring(char* ch,int pos,int length)
//{
//    char* pch=ch;
//    //定義一個字元指標，指向傳遞進來的ch位址。
//    char* subch=calloc(sizeof(char),length+1);
//    //透過calloc來配置一個length長度的字元陣列，回傳的是字元指標。
//    int i;
//    //只有在C99下for迴圈中才可以宣告變數，這裡寫在外面，提高相容性。
//    pch=pch+pos;
//    //是pch指標指向pos位置。
//    for(i=0;i<length;i++)
//        {
//            subch[i]=*(pch++);
//            //迴圈迭代賦值陣列。
//        }
//    subch[length]='\0';//加上字串结束符。
//    return subch;       //回傳配置的字元陣列位址。
//}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif
    //實作網路連線，判斷用户名嗎
//    //1.初始化LibCURL
//    CURL *curl = curl_easy_init();
//    if(curl) {
//        
//        CURLcode res;
//        std::string recvbuf;
//        
//        //2.設定網路連線属性
//        res = curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1/testphp/checkLogin02.php?uname=wangyi&upass=22");
//        //設定資料接收方法
//        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,&In::processData);
//        //設定資料接收變數
//        curl_easy_setopt(curl,CURLOPT_WRITEDATA,&recvbuf);
//        
//        //3 連接網路
//        res = curl_easy_perform(curl);
//        //如果網路連線成功
//        if(CURLE_OK == res) {
//        //CCMessageBox(recvbuf.c_str(),"get response");
//            printf("\nresponse:%s",recvbuf.c_str());
////            CCLOG(recvbuf.c_str());
//        }
//        
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//    }
    
}
 void HelloWorld::setUname(string n){
    uname=n;
}
 string HelloWorld::getUname(){
    return uname;
}
void HelloWorld::registerWithTouchDispatcher(void){
    CCDirector::sharedDirector()->getTouchDispatcher()
    ->addTargetedDelegate(this,0,true);
}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    //設定玩家要移動到的目標點
    Player * player=(Player *)this->getChildByTag(10);
    player->m_dx=pTouch->getLocation().x;
    player->m_dy=pTouch->getLocation().y;
    printf("\n  %f,%f",player->m_dx,player->m_dy);
}
void HelloWorld::run(float t)
{   //移動自身玩家Player
    Player * player=(Player *)this->getChildByTag(10);
    player->moveToDex();//不斷趨近目標點
    //將玩家的座標發送给伺服器，讓伺服器廣播出去
    char buf[50];
    if(player->m_playerID>=10000)
    {
    sprintf(buf,"$$%d,%f,%f\r\n",player->m_playerID,player->m_px,player->m_py);
    sock_client->Send(buf, sizeof(buf));
    }
    //加入玩家圖層
    while (g_newPlayertask->count()>0) {
        SPlayer * np=(SPlayer *)g_newPlayertask->objectAtIndex(0);
       Player *player= this->addPlayer(np->m_name, np->m_socketid);
        this->addChild(player);
        g_allPlayer->addObject(player);
        g_newPlayertask->removeObjectAtIndex(0);
    }
    //繪製所有玩家g_allPlayer
    for(int i=0;i<g_allPlayer->count();i++)
    {Player * player=(Player *)g_allPlayer->objectAtIndex(i);
     
     player->moveTo(player->m_px, player->m_py);
    
    }
}
