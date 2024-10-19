#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <Ws2tcpip.h> // 윈도우 소켓 버전 2.2
#include <iostream> 
#include<stdio.h>

using namespace std;

int main()
{
    
    // 윈도우 소캣 초기화
    /*
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        err_display("WSAStartup");
        exit(-1);
    }
    //윈도우 소캣 종료
    WSACleanup();
    //err_display("socket");
    */


    //메모리 생성
    /*
    // IP, Port를 입력 ,IPV4
    // 1) struct sockaddr_in 타입의 메모리 생성
    SOCKADDR_IN saddr;

    // sockaddr_in 각 멤버에 정보를 입력
    saddr.sin_family = AF_INET;      // 주소체계 IPV4
    saddr.sin_port = htons(8000);
    // 점 10진수 IP 입력
    inet_pton(AF_INET, "1.2.3.4", &addr.sin_addr);
    */
    // IP주소와 Port번호를 지정
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    
    // addr.sin_addr에 IP addr 저장 방법
    if (inet_pton(AF_INET, "1.2.3.4", &addr.sin_addr) != 1)
    {
        err_display("inet_pton"); // cout<<"inet_pton error"<<endl;
        return -1;
    }
    // addr에 저장되어 있는 IP주소와 port num을 화면에 출력
    // IP 출력
    char ipaddr[INET_ADDRSTRLEN]; // IPv4의 주소를 저장할 수 있는 공간마련 #define 22 
    if (inet_ntop(AF_INET, &addr.sin_addr, ipaddr, INET_ADDRSTRLEN) == nullptr)
    {
        err_display("inet_ntop error");
        return -1;
    }
    cout << "IP : " << ipaddr<< "Port : "<< ntohs(addr.sin_port)<<endl;
    return 0;
}
void err_display(const char* mes)
{
    LPVOID buf = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM, nullptr, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
        , (LPSTR)&buf, 0, nullptr);
    cout << "[" << mes << "] " << (char*)buf;
    LocalFree(buf);
}

