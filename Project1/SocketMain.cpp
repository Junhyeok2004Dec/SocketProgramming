
#include <stdio.h>
#include <WinSock2.h>


#pragma comment(lib, "ws2_32")


#define _WINSOCK_DEPRECATED_NO_WARNINGS


#define PORT 4501
#define PACKET_SIZE 1024

int Cmain()
{
	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);


	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);


	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN); // hListen을 접속대기 상태로

	SOCKADDR_IN tCIntAddr = {};
	int iCIntSize = sizeof(tCIntAddr);

	//클라이언트측 주소정보 구조체의 주소 :  (SOCKADDR*)&tCIntAddr
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tCIntAddr, &iCIntSize); //접속 요청 시 승인
	//accept 함수를 이용하여 접속 요청을 수락


	char cBuffer[PACKET_SIZE] = {}; //버퍼 생성

	recv(hClient, cBuffer, PACKET_SIZE, 0); // 소켓으로 받은 정보
	printf("클라이언트로부터 받은 메시지 : %s\n", cBuffer);
	
	char cMsg[] = "서버로부터 다음과 같은 메시지를 수신하였습니다.";

	send(hClient, cMsg, strlen(cMsg), 0);


	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
	return 0;
}