#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h> // 윈도우 소켓 버전 2.2
#include <iostream> 
#include <Ws2tcpip.h>


using namespace std;

int main()
{
	// ws2_32.dll 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		cout << "WSASteartup error" << endl;
		return -1;
	}

	// 문지기 소켓 생성
	SOCKET s_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_sock == INVALID_SOCKET)
	{
		cout << "sock error" << endl;
		return -1;
	}

	// 서버가 사용할 IP, Port 예약 및 확인
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8000);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY); // 이렇게 하는걸 원하지 않는다면 inet_pton();

	if (bind(s_sock,(SOCKADDR *)&saddr,sizeof(saddr)))
	{
		cout << "bind error" << endl;
		return -1;
	}

	// 대기 큐를 생성   
	if (listen(s_sock, SOMAXCONN))
	{
		cout << "listen error" << endl;
		return -1;
	}
	// listen 함수만 끝나도 연결은 성공이 된다.
	// 서비스가 accept 함수에서 이루어진다.

	// 서비스를 시작하기 위해 대기 큐에서 하나 꺼내오며 전용 소캣 생성

	SOCKADDR_IN caddr; // 대기 큐에 있는 클라이언트 정보 저장용
	int addrlen = sizeof(caddr);
	SOCKET c_sock = accept(s_sock, (SOCKADDR*)&caddr, &addrlen);
	if (c_sock == INVALID_SOCKET)
	{
		cout << "accept error" << endl;
		return -1;
	}

	char IPaddr[30];
	if (!inet_ntop(AF_INET, &caddr.sin_addr, IPaddr, 30))
	{
		cout << "inet_ntop" << endl;
		return -1;
	}
	cout << "IP : " << IPaddr << "Port : " << ntohs(caddr.sin_port) << "connected" << endl;
	// 전용 소켓으로 데이터 송/수신


	while (1)
	{
		// 수신
		char buf[256]; // 수신 버퍼
		int retval = recv(c_sock, buf, 256 - 1, 0); // retval : 수신이 성공한 바이트 수 
		   // 클라이언트에서 아무것도 하지않으면 여기서 멈춰있음
		if (retval == 0)
		{
			cout << "normal close case" << endl;
			closesocket(c_sock);
			break;
		}
		else if (retval == SOCKET_ERROR)
		{
			cout << "recv close case" << endl;
			closesocket(c_sock);
			break;
		}
		// 클라이언트로 부터 수신된 데이터 화면 출력
		buf[retval] = '\0';
		cout << "From client :	" << buf << endl;

		// 에코서비스를 위해 수신한 데이터를 클라이언트에 전송
		retval = send(c_sock, buf, retval, 0);
	}

	closesocket(s_sock);
	WSACleanup();


	return 0;
}
