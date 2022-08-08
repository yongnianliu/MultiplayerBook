//
// Created by yongnianliu on 2022/8/5.
//
#include <iostream>
#include "RoboCatPCH.h"

#define Host "127.0.0.1"
#define Port 12345

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
    u_long S_addr;
    if( inet_pton(AF_INET, Host, &S_addr) <= 0){
        std::cout << "inet_pton error." << std::endl;
        return 1;
    }
    SocketAddress addr(htonl(S_addr), Port);
    if (socket->Connect(addr) != NO_ERROR){
        std::cout << "Connect fail." << std::endl;
        return 1;
    }
    char msg[] = "hello server\0";
    if (socket->Send(msg, sizeof(msg)) < 0) {
        std::cout << "Send fail." << std::endl;
        return 1;
    }
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if (socket->Receive(buf, 1024) < 0){
        std::cout << "Receive fail." << std::endl;
        return 1;
    }
    std::cout << buf << std::endl;
    SocketUtil::CleanUp();
    return 0;
}