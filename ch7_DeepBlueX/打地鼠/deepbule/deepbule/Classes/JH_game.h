//
///* 
//    遊戲主邏輯：遊戲的主要程式實作都在此類別內，以狀態機的方式控制
//*/
//
//
//#ifndef __JH_GAME_H__
//#define __JH_GAME_H__
//
//
//#include "cocos2d.h"
//#include "JH_GameBase.h"
//class JH_GameBase;
//
////遊戲狀態
//enum Gstate{
//    JH_GAMESTATE_MENU  = 1,//遊戲選單
//    JH_GAMESTATE_PLAY  = 2,//遊戲狀態
//    JH_GAMESTATE_ABOUT = 3,//關於狀態
//};
//
//
////遊戲層控制
//
//enum{
//    Layer_background = 0,//背景層
//    Layer_backrole   = 1,//通用固定NPC層
//    Layer_npc        = 2,
//    Layer_role       = 3,//主角層
//    Layer_font       = 4,//文字圖層
//};
//
////圖片ID
//enum {
//    IMG_menu = 0,
//    IMG_npc1 = 1,
//};
//
////動畫文件ID
//enum  {
//    XML_1 = 0,
//    XML_2 = 1,
//    XML_role = 2,//主角
//};
//
//class JH_GAME: public JH_GameBase
//{
//public:
//    static JH_GAME* instance;		//建立唯一實體
//    Gstate gamestate;				//遊戲狀態
//    Gstate oldgamestate;			//上次遊戲狀態
//
//public:
//    JH_GAME();
//    ~JH_GAME();
//    static JH_GAME* Getinstance();
//
//    void start();					//主邏輯程式入口
//    void LoadGameImage();			//加入遊戲資源   
//    
//    void Paint();					//遊戲繪製
//    int run(float dt);				//遊戲執行主邏輯
//    void GameChangeState(Gstate g); //切换遊戲狀態
//    
////觸控控制
//    int touchbegin(float px,float py);
//    int touchmove(float px,float py);
//    int touchend(float px,float py);
//    
// //   通缉犯
//    int AddNPC(int id,float x,float y,int w,int h,int way);
//    void MapMove(float x,float y);
//    void NpcMove(int id,float x,float y);
//    void NpcChangeWay(int id);
//};
//
//#endif 
