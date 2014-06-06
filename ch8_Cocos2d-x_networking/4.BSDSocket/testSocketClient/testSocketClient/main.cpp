//
//  main.cpp
//  testSocketClient
//
//  Created by 沈 shen on 13-7-31.
//  Copyright (c) 2013年 沈 shen. All rights reserved.
//

#include <iostream>
#include "ODSocket.h"
#include <pthread.h>
//建立Socket
ODSocket s_client;
void * getMessage(void *ptr)
{//接收訊息
//    ODSocket *nowScoket=(ODSocket *)ptr;//接收執行緒傳遞過來的參數
    std::cout<<"執行緒啟動成功"<<endl;
    char buf[1024];
    char chr;
    while (true) {
        //接收伺服器訊息
        s_client.Recv(buf, sizeof(buf));
        
        std::cout << "recv"<<buf<<std::endl;
      
//        if(strcmp(buf, "quit"))
//        {break;
//            }
    }
     //  s_client.Close();
}
int main(int argc, const char * argv[])
{
    //建立socket
    s_client.Init();
   bool res= s_client.Create(AF_INET, SOCK_STREAM,0);
    std::cout << "client socke create"<<res<<std::endl;
    //連接伺服器
    res=s_client.Connect("127.0.0.1", 8867);
    std::cout << "client socke connect"<<res<<std::endl;
    char buf[1024];
    if(res==1)
    {//啟動執行緒
    pthread_t tid;
    bool ok= pthread_create(&tid, NULL, getMessage, NULL);
     std::cout << "執行緒啟動结果"<<ok<<endl;
       
    }
    char c[50];
    while (1) {
        std::cin>>c;
        s_client.Send(c,sizeof(c));
    }
    return 0;
}

