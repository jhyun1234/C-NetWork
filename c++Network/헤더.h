#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h> // 윈도우 소켓 버전 2.2
#include <iostream> // c++ cout, cin , endl;
#include <Ws2tcpip.h>


using namespace std;
void err_display(const char* mes);
int main()
{
    // IP주소와 Port번호를 지정
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0x8000);

    // addr.sin_addr에 IP addr 저장 방법
    if (inet_pton(AF_INET, "1.2.3.4", &addr.sin_addr) != 1)
    {
        err_display("inet_pton error");        //cout<<"inet_pton error"<<endl;
        return -1;
    }
    // addr에 저장되어 있는 IP주소와 port num을 화면에 출력
    // IP 출력
    char ipaddr[INET_ADDRSTRLEN]; // IPv4의 주소를 저장할 수 있는 공간마련 #define 22 
    if (inet_ntop(AF_INET, &addr.sin_addr, ipaddr, INET_ADDRSTRLEN) == nullptr)
    {
        err_display("inet_ntop error");   //cout << "inet_ntop error" << endl;
        return -1;
    }
    cout << "IP : " << ipaddr << " Port : " << std::hex << ntohs(addr.sin_port) << endl;
    return 0;



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
}#pragma once
