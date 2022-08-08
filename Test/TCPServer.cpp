//
// Created by yongnianliu on 2022/8/5.
//
#include <iostream>
#include "RoboCatPCH.h"

#define Port 12345
char buf[1024];
#if _WIN32
int main(int argc, const char** argv)
{
#else
    const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
    __argc = argc;
    __argv = argv;
#endif
    if (!SocketUtil::StaticInit()){
        std::cout << "SocketUtil::StaticInit() fail." << std::endl;
        return 1;
    }
    TCPSocketPtr socket = SocketUtil::CreateTCPSocket(SocketAddressFamily::INET);
    SocketAddress addr(INADDR_ANY, Port);
    if (socket->Bind(addr) != NO_ERROR){
        std::cout << "Bind fail." << std::endl;
        return 1;
    }
    if (socket->Listen(10) != NO_ERROR){
        std::cout << "Listen fail." << std::endl;
        return 1;
    }
    while ( true )
    {
        SocketAddress FromAddress;
        TCPSocketPtr ClientSocket = socket->Accept(FromAddress);
        if (!ClientSocket){
            continue;
        }
        memset(buf, 0, sizeof(buf));
        if (ClientSocket->Receive(buf, 1024) < 0){
            continue;
        }
        std::cout << buf << std::endl;
        char msg[] = "hello client\0";
        ClientSocket->Send(msg, sizeof(msg));
    }

    SocketUtil::CleanUp();
    return 0;
}