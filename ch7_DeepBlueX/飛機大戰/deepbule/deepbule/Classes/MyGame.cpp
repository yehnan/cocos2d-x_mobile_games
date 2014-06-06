//
//  MyGame.cpp
//  deepblue
//
//  Created by 沈 shen on 13-10-28.
//
//

#include "MyGame.h"
JH_GAME* JH_GAME::instance;

////////////////////////////////////////////////////////
//  遊戲相關變數
///////////////////////////////////////////////////////

int Sprite_player;
int Sprite_npc;
int Sprite_menu;
int Sprite_background;

int nowlevel;

//遊戲關卡信息
int way;//方向
int map_widht=320;
int map_height=680;
JH_GAME* JH_GAME::Getinstance()
{
    if (instance==NULL) {
        instance=new JH_GAME();
        instance->Init();
    }
    return instance;
}
//遊戲入口 主邏輯最先執行的方法
void JH_GAME::start()
{
    LoadGameImage();
    GameChangeState(JH_GAMESTATE_MENU);
}
//載入遊戲資源
void JH_GAME::LoadGameImage()
{
    //圖片資源
    jh_LoadImage(IMG_menu, "menu.png");
    jh_LoadImage(IMG_back1, "background02.png");
    jh_LoadImage(IMG_Player1, "player.png");
    jh_LoadImage(IMG_npc1, "aaa.png");
    //動畫資源
    jh_LoadAnimation(XML_1, "guaiwu.png", "guaiwu.xml");
    jh_LoadAnimation(XML_2, "jiqiangta.png", "jiqiangta.xml");
}


void JH_GAME::GameChangeState(Gstate g)
{
	jh_DeleteAllSprite();
	jh_DeleteAllString();
	oldgamestate=gamestate;
	gamestate=g;
	switch (g) {
        case JH_GAMESTATE_MENU:
            
            break;
        case JH_GAMESTATE_PLAY:
            
            break;
        case JH_GAMESTATE_ABOUT:
            
            break;
	}
	Paint();
}
//遊戲繪製<由于cocoa2d-x内部已封装繪製方法，此方法只作为加入圖片和動作的方法>
void JH_GAME::Paint()
{
    switch (gamestate)
	{
        case JH_GAMESTATE_MENU:
        Sprite_menu=jh_AddSprite(IMG_menu, 0,0,0,0,screenwidth,screenheigth,Layer_background);
        jh_AddString("start Game", 50, 50, Layer_font);
        Sprite_npc=jh_AddAnimation(XML_1, 100, 200, Layer_background, 0);
        break;
        case JH_GAMESTATE_PLAY:
        //地圖初始化
//        map_localx=0;
//        map_localy=-(map_height-screenheigth);
//        //加入背景
//        AddBackground(0, 50, map_height-phy_groundhight*2,40,60, 3);
//        //加入飛機
//        AddNPC(2, 0, map_height-phy_groundhight, map_widht,50, 0);
        Sprite_background=jh_AddSprite(IMG_back1, 0,0,0,0,screenwidth,screenheigth,Layer_background);
        Sprite_player=jh_AddSprite(IMG_Player1, 20, 20, 0, 0, 40, 40, Layer_role);
        break;
        case JH_GAMESTATE_ABOUT:
        
        break;
    }
}

//遊戲執行主邏輯
int JH_GAME::run(float dt)
{
    switch (gamestate)
	{
        case JH_GAMESTATE_MENU:
        if (way==0)
			{
            jh_MoveSpritePosition(Sprite_npc, 1, 0);
            if(jh_GetSpritePositionX(Sprite_npc)>=screenwidth-5)
            {
                way=1;
                jh_setAnimationAction(Sprite_npc, 2, true);
            }
           }else{
                jh_MoveSpritePosition(Sprite_npc, -1, 0);
                if (jh_GetSpritePositionX(Sprite_npc)<=5) {
                    way=0;
                    jh_setAnimationAction(Sprite_npc, 1, true);
                }
            }
        break;
    	case JH_GAMESTATE_PLAY:
        //遊戲AI邏輯
        //背景移動
        //子彈自動
        //敵機移動
        //碰撞偵測
        break;
        case JH_GAMESTATE_ABOUT:
        
        break;
    }
    return 0;
}

int JH_GAME::touchbegin(float px,float py)
{
    switch (gamestate) {
        case JH_GAMESTATE_MENU:
            GameChangeState(JH_GAMESTATE_PLAY);
            break;
        case JH_GAMESTATE_PLAY:
            this->ChangeCoordinate(&px, &py, 0, 0);
            this->jh_SetSpritePosition(Sprite_player, px, py);
            break;
        case JH_GAMESTATE_ABOUT:
            
            break;
    }
    return 0;
}

int JH_GAME::touchmove(float px,float py)
{
    switch (gamestate) {
        case JH_GAMESTATE_MENU:
           
            break;
        case JH_GAMESTATE_PLAY:
            this->ChangeCoordinate(&px, &py, 0, 0);
            this->jh_SetSpritePosition(Sprite_player, px, py);
            break;
        case JH_GAMESTATE_ABOUT:
            
            break;
    }

    return 0;
}

int JH_GAME::touchend(float px,float py)
{
    return 0;
}


