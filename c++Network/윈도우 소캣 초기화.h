#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <Ws2tcpip.h> // ������ ���� ���� 2.2
#include <iostream> 
#include<stdio.h>

using namespace std;

int main()
{
    
    // ������ ��Ĺ �ʱ�ȭ
    /*
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        err_display("WSAStartup");
        exit(-1);
    }
    //������ ��Ĺ ����
    WSACleanup();
    //err_display("socket");
    */


    //�޸� ����
    /*
    // IP, Port�� �Է� ,IPV4
    // 1) struct sockaddr_in Ÿ���� �޸� ����
    SOCKADDR_IN saddr;

    // sockaddr_in �� ����� ������ �Է�
    saddr.sin_family = AF_INET;      // �ּ�ü�� IPV4
    saddr.sin_port = htons(8000);
    // �� 10���� IP �Է�
    inet_pton(AF_INET, "1.2.3.4", &addr.sin_addr);
    */
    // IP�ּҿ� Port��ȣ�� ����
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    
    // addr.sin_addr�� IP addr ���� ���
    if (inet_pton(AF_INET, "1.2.3.4", &addr.sin_addr) != 1)
    {
        err_display("inet_pton"); // cout<<"inet_pton error"<<endl;
        return -1;
    }
    // addr�� ����Ǿ� �ִ� IP�ּҿ� port num�� ȭ�鿡 ���
    // IP ���
    char ipaddr[INET_ADDRSTRLEN]; // IPv4�� �ּҸ� ������ �� �ִ� �������� #define 22 
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

