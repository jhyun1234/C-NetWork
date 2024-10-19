#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h> // ������ ���� ���� 2.2
#include <iostream> // c++ cout, cin , endl;
#include <Ws2tcpip.h>


using namespace std;

int main()
{

	// ws2_32.dll�� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		cout << "WSAStartup error" << endl;
		return -1;
	}

	// getaddrinfo�Լ��� �̿��Ͽ� ���������κ��� IP�ּҸ� ����
	ADDRINFO addr;
	ZeroMemory(&addr, sizeof(addr));

	addr.ai_family = AF_INET;
	addr.ai_socktype = SOCK_STREAM;  // for tcp , SOCK_DGRAM for udp
	addr.ai_protocol = IPPROTO_TCP;  //

	ADDRINFO* result = nullptr;

	if (getaddrinfo("www.daum.net", "80", &addr, &result) != 0)
	{
		cout << "getaddrinfo error" << endl;
		return -1;
	}


	for (ADDRINFO* ptr = result; ptr != NULL; ptr = ptr->ai_next)   // for(;ptr;)
	{
		// ip �ּҴ� addr->sin_addr�� ����Ǿ� ����
		SOCKADDR_IN* addr = (SOCKADDR_IN*)ptr->ai_addr;

		char ipaddr[INET6_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &addr->sin_addr, ipaddr, INET_ADDRSTRLEN) == nullptr)
		{
			cout << "inet_ntop error" << endl;
			return -1;
		}
		cout << "IP : " << ipaddr << " Port : " << ntohs(addr->sin_port) << endl;
	}

	freeaddrinfo(result);
	WSACleanup();


	return 0;
}
#pragma once
