//
//  main.cpp
//  socketServer
//
//  Created by 沈 shen on 13-8-1.
//  Copyright (c) 2013年 沈 shen. All rights reserved.
//

#include <iostream>
#include "ODSocket.h"
#include <pthread.h>
#include <unistd.h>
#include <list>
 list<ODSocket> allClient;//儲存所有的客户端socket物件
list<string> allMessage;//儲存所有要發送的聊天訊息

void * GetMessage(void *ptr)//用該執行緒方法實作和所有人聊天
{ 
    ODSocket *nowsock=(ODSocket *)ptr;
     char msg[1024];
    bzero(msg, sizeof(msg));
    while (1) {
    if(NULL==nowsock||NULL==nowsock->m_sock||nowsock->m_sock<=0){
        break;
    }
    nowsock->Recv(msg, sizeof(msg));
    strcat(msg, "\r\n");
      std::cout<<"接收訊息"<<msg<<endl;
        string msgstr=msg;
    allMessage.push_front(msgstr);
        }
}
void * DoSocket(void *ptr)//用該執行緒方法實作和所有人通訊
{
    std::cout<<"執行緒已经啟動"<<endl;
    while (1)
        {
//       
      if (allClient.size()>0)
        {
        
        if(allMessage.size()>0){
        list<string>::iterator nowmsg;
     for(nowmsg=allMessage.begin();nowmsg!=allMessage.end();nowmsg++)
         { char msg[1024];
//         strcpy(msg, *nowmsg);
//         std::cout<<"nowmsg"<<nowmsg->c_str()<<endl;
         list<ODSocket>::iterator nowsock;
        for(nowsock=allClient.begin();nowsock!=allClient.end();nowsock++)
            {
            if(nowsock->m_sock<0){break;}
            nowsock->Send(nowmsg->c_str(),nowmsg->length(),0);
            }
        }
        allMessage.clear();///清空
        }
    }
    sleep(100);//1秒群發一次
        }
}
int main(int argc, const char * argv[])
{   pthread_t ids;
    pthread_t id;//定義執行緒id
    int i,ret;
    ret=pthread_create(&id,NULL,DoSocket,NULL);//建立一個執行緒
    if(ret!=0){
        printf ("Create pthread error!\n");
        exit (1);
    }
    //建立Socket
    ODSocket sockServer;
    sockServer.Init();
    bool res=sockServer.Create(AF_INET, SOCK_STREAM,0);
    std::cout << "建立 socket "<<(res==1?"成功":"失败")<<"\n";
    //綁定連接埠
    res=sockServer.Bind(8867);
    std::cout << "綁定端口 "<<(res==1?"成功":"失败")<<"\n";
    //開始聆聽
    res=sockServer.Listen();
    std::cout << "侦听端口 "<<(res==1?"成功":"失败")<<"\n";
    char message[30];
    //接收客户端的連線
    int count=0;
    while (1)
    {
    //如果有客户端連線，建立客户端的socket
    ODSocket * p_sockClient=new ODSocket();
    char  * address=new char[20];
        sockServer.Accept(*p_sockClient,address);
    std::cout<<address<<"来了"<<endl;
    sprintf(message, "welcome %s",address);
    p_sockClient->Send(message, sizeof(message));
     
     //啟動執行緒接收資料
    ret=pthread_create(&ids,NULL,GetMessage,p_sockClient);//建立一個執行緒
    //每當有1個客户端連結上来，加入到List容器
    allClient.push_back(*p_sockClient);
    }
   //输入任意字元退出
    cin>>message;
   
    return 0;
}

