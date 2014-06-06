//
///* 
//    遊戲主邏輯：遊戲的主要程式實作都在此類別內，以狀態機的方式控制
//*/
//
//
//#include "JH_GAME.h"
//
//JH_GAME* JH_GAME::instance;
//
//////////////////////////////////////////////////////////
////  遊戲相關變數
/////////////////////////////////////////////////////////
//
//int NPC_IMG_test1;
//int NPC_IMG_test2;
//int NPC_ACTION_test1;
//int NPC_ACTION_text2;
//short way=0;
//
////遊戲關卡資訊
//int map_widht=320*2;
//int map_height=768;
//float map_localx=0;
//float map_localy=0;//地圖視角
//struct NPC {
//    short id;//類型 0-主角 ,1-npc ,2-平台 ,3-轉向端點
//	float x;
//	float y;//地圖座標
//	int w;
//	int h;//npc的寬度和高度
//    int spriteid;//對應的精靈   
//    short oldway;
//    short way;//npc方向 0-上 1-下 2-左 3-右
//    
//	//對應的資料常數
//	
//	float speed_jumpB;//速度
//	float speed_walkB;//水平速度
//    float speed_x;//水平速度
//    float speed_y;//垂直速度
//  
//};
//const int npclist_countB=100;
//NPC npclist[npclist_countB];
//int npclist_count=0;
////物理世界資料
//const float phy_G=0.5f;//重力加速度
//const float phy_groundhight=50;//地面高度
//
//JH_GAME::JH_GAME()
//{
//    
//}
//
//JH_GAME::~JH_GAME()
//{
//    
//}
//
//JH_GAME* JH_GAME::Getinstance()
//{
//   if (instance==NULL) {
//       instance=new JH_GAME();
//       instance->Init();
//    }
//    return instance;
//}
//
////遊戲入口 主邏輯最先執行的方法
//void JH_GAME::start()
//{
//    LoadGameImage();
//    GameChangeState(JH_GAMESTATE_MENU);
//}
//
//
//
////載入遊戲資源
//void JH_GAME::LoadGameImage()
//{
//    //圖片資源
//    jh_LoadImage(IMG_menu, "HelloWorld.png");
//    jh_LoadImage(IMG_npc1, "npc1.png");
//    
//    //動畫資源
//    jh_LoadAnimation(XML_1, "guaiwu.png", "guaiwu.xml");
//    jh_LoadAnimation(XML_2, "jiqiangta.png", "jiqiangta.xml");
//    
//    jh_LoadAnimation(XML_role, "guaiwu.png", "guaiwu.xml");
//
//}
//
//
//void JH_GAME::GameChangeState(Gstate g)
//{
//	jh_DeleteAllSprite();
//	jh_DeleteAllString();
//	oldgamestate=gamestate;
//	gamestate=g;
//	switch (g) {
//	case JH_GAMESTATE_MENU:
//
//		break;
//	case JH_GAMESTATE_PLAY:
//
//		break;
//	case JH_GAMESTATE_ABOUT:
//
//		break;
//	}
//	Paint();
//}
//
////遊戲繪製<由於cocoa2d-x内部已封装繪製方法，此方法只作为加入圖片和動作的方法>
//void JH_GAME::Paint()
//{
//    switch (gamestate) 
//	{
//        case JH_GAMESTATE_MENU:
//            NPC_IMG_test1=jh_AddSprite(IMG_menu, 0,0,0,0,screenwidth/2,screenheigth/2,Layer_background);
//            NPC_IMG_test2=jh_AddSprite(IMG_menu, 100,30,0,0,screenwidth/2,screenheigth/2,Layer_background);
//            
//            NPC_ACTION_test1=jh_AddAnimation(XML_1, 100, 200, Layer_background, 0);
//            NPC_ACTION_text2=jh_AddAnimation(XML_1, 350, 200, Layer_background, 1);
//            
//            jh_AddString("http://www.baidu.comssd/zmaflyfly", 0, 0, Layer_font);
//            
//            jh_AddAnimation(XML_2, 100, 350, 5, 0);
//
//            break;
//        case JH_GAMESTATE_PLAY:
//            //地圖初始化
//            map_localx=0;
//            map_localy=-(map_height-screenheigth);
//            //加入主角資訊
//            AddNPC(0, 50, map_height-phy_groundhight*2,40,60, 3);
//            //加入地面
//            AddNPC(2, 0, map_height-phy_groundhight, map_widht,50, 0);
//
//
//            AddNPC(1, 0, 0, 0,0,0);
//            break;
//        case JH_GAMESTATE_ABOUT:
//            
//            break;
//    }
//}
//
////遊戲主邏輯
//int JH_GAME::run(float dt)
//{
//    switch (gamestate) 
//	{
//        case JH_GAMESTATE_MENU:
//            if (way==0) 
//			{
//               jh_MoveSpritePosition(NPC_ACTION_text2, 1, 0); 
//                if (jh_GetSpritePositionX(NPC_ACTION_text2)>=screenwidth-5) 
//				{
//                    way=1;
//                    jh_setAnimationAction(NPC_ACTION_text2, 2, true);
//                }
//            }else{
//               jh_MoveSpritePosition(NPC_ACTION_text2, -1, 0); 
//                if (jh_GetSpritePositionX(NPC_ACTION_text2)<=5) {
//                    way=0;
//                    jh_setAnimationAction(NPC_ACTION_text2, 1, true);
//                }
//            }
//            break;
//            
//		case JH_GAMESTATE_PLAY:
//            //遊戲AI邏輯
//            for (int i=0; i<npclist_count; i++) 
//			{
//                //位移處理
//                switch (npclist[i].id) 
//				{
//				case 0:
//                        switch (npclist[i].way) 
//						{
//						case 0://上
//							break;
//						case 1://下
//                            break;
//						case 2://左
//                            NpcMove(i,-npclist[i].speed_x, 0);
//                            if (npclist[i].x<10) 
//							{
//                                NpcChangeWay(0);
//                            }
//                            break;
//						case 3://右
//							NpcMove(i, npclist[i].speed_x, 0);
//							if (npclist[i].x>map_widht-10) {
//								NpcChangeWay(0);
//							} 
//							break;
//                        }
//                        //跳躍速度
//                        //if (npclist[i].speed_y!=0.0f) 
//                        {
//                            npclist[i].speed_y+=phy_G;
//                            //處理碰撞
//							for (int j=0; j<npclist_count; j++) 
//							{
//                            if (j!=i) 
//							{
//                                if (npclist[j].id==2) 
//								{//平台
//                                    if (npclist[i].speed_y>0 &&
//                                        npclist[i].y+npclist[i].h>=npclist[j].y-5 && 
//                                        npclist[i].x>npclist[j].x && 
//                                        npclist[i].x+npclist[i].w<npclist[j].y+npclist[j].w) {
//                                        npclist[i].speed_y=0;
//                                    }
//                                }
//
//                            }
//                        }
//                        NpcMove(i, 0, npclist[i].speed_y);
//                           /* if (npclist[i].y+npclist[i].speed_y>=map_height-phy_groundhight) {
//                                npclist[i].speed_y=0.0f;
//                                NpcMove(i, 0, map_height-phy_groundhight-npclist[i].y);
//                            }else
//                            {
//                                NpcMove(i, 0, npclist[i].speed_y);
//                            }*/
//                        }
//                        break;
//                }
//                
//            }
//            break;
//        case JH_GAMESTATE_ABOUT:
//            
//            break;
//    }
//    return 0;
//}
//
//int JH_GAME::touchbegin(float px,float py)
//{
//    switch (gamestate) {
//        case JH_GAMESTATE_MENU:
//            /*
//            jh_setSpriteScale(NPC_ACTION_test1, 1.2, 1.2,-60);
//            jh_SetSpriteColor(NPC_ACTION_text2, 255, 255, 0);
//            jh_SetSpritePosition(NPC_IMG_test1, 10, 10);
//            jh_MoveSpriteAutoPosition(NPC_ACTION_test1, 50, 30,2);
//            */
//            
//            //jh_DeleteAllAnimation();
//            GameChangeState(JH_GAMESTATE_PLAY);
//            break;
//        case JH_GAMESTATE_PLAY:
//            //跳躍
//           // npclist[0].oldway=npclist[0].way;
//            //npclist[0].way=0;
//            //npclist[0].speed=npclist[0].speed_jumpB;
//            //掉頭
//            if (px<screenwidth/2) {
//                npclist[0].speed_y=npclist[0].speed_jumpB;
//            }else{
//                NpcChangeWay(0);
//            }
//            break;
//        case JH_GAMESTATE_ABOUT:
//            
//            break;
//    }
//    return 0;
//}
//
//int JH_GAME::touchmove(float px,float py)
//{
//    return 0;
//}
//
//int JH_GAME::touchend(float px,float py)
//{
//    return 0;
//}
//
///** 通緝犯相關函式 **/
////加入NPC
//
//int JH_GAME::AddNPC(int id,float x,float y,int w,int h,int way)
//{
//    npclist[npclist_count].id=id;
//    npclist[npclist_count].x=x;
//    npclist[npclist_count].y=y;
//    npclist[npclist_count].way=way;
//    npclist[npclist_count].w=w;//40;
//    npclist[npclist_count].h==h;//60;
//    switch(id)
//	{
//	case 0:			//主角
//		npclist[npclist_count].speed_walkB=1;
//		npclist[npclist_count].speed_jumpB=-15;
//		npclist[npclist_count].speed_x=npclist[npclist_count].speed_walkB;
//		npclist[npclist_count].speed_y=0;
//		npclist[npclist_count].spriteid=jh_AddAnimation(XML_role, x+map_localx, y+map_localy-npclist[npclist_count].h/2, Layer_role, 1);
//		break;
//
//	case 1://npc
//		npclist[npclist_count].spriteid=jh_AddSprite(IMG_npc1, x+map_localx, y+map_localy, 1024, 768, Layer_backrole);
//		break;
//
//	case 2://平台
//		npclist[npclist_count].spriteid=jh_AddSprite(IMG_menu, x+map_localx, y+map_localy, 0,0,480, 30, Layer_npc);
//		break;
//	}
//   
//    npclist_count++;
//    return npclist_count-1;
//}
//
////負責NPC移動
//void JH_GAME::NpcMove(int id,float x,float y)
//{
//    npclist[id].x+=x;
//    npclist[id].y+=y;
//	switch(id)
//	{
//	case 0:
//		//x軸方向
//		if (x!=0.0f) 
//		{
//			if ((npclist[id].way==3 && (npclist[id].x<screenwidth/2 || npclist[id].x>map_widht-screenwidth/2)) || 
//				(npclist[id].way==2 && (npclist[id].x<screenwidth/2 || npclist[id].x>map_widht-screenwidth/2)))
//			{
//				jh_MoveSpritePosition(npclist[id].spriteid, x, 0);
//			}else{
//				MapMove(-x, 0);
//			}
//		}
//
//		//y軸方向
//		if (y!=0.0f) 
//		{
//			if (npclist[id].y>map_height-screenheigth/2 || npclist[id].y<screenheigth/2) 
//			{
//				jh_MoveSpritePosition(npclist[id].spriteid, 0, y);
//			}else{   
//				MapMove(0, -y);
//			}
//		}
//		break;
//	}
//    
//}
//
////地圖移動    
//void JH_GAME::MapMove(float x,float y)
//{
//    map_localx+=x;
//    map_localy+=y;
//    for (int i=1; i<npclist_count; i++) {
//        jh_MoveSpritePosition(npclist[i].spriteid, x, y);
//    }
//}
//
////NPC掉頭
//void JH_GAME::NpcChangeWay(int id)
//{
//    switch (npclist[id].id) {
//        case 0://主角
//            npclist[0].oldway=npclist[0].way;
//            npclist[0].way=(3-npclist[0].way)+2;
//            if (npclist[0].way==2) {
//                jh_setAnimationAction(npclist[0].spriteid, 0, true);
//            }else if(npclist[0].way==3){
//                jh_setAnimationAction(npclist[0].spriteid, 1, true);
//            }
//            break;
//            
//        default:
//            break;
//    }
//}