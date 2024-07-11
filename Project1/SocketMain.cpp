
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
	listen(hListen, SOMAXCONN); // hListen�� ���Ӵ�� ���·�

	SOCKADDR_IN tCIntAddr = {};
	int iCIntSize = sizeof(tCIntAddr);

	//Ŭ���̾�Ʈ�� �ּ����� ����ü�� �ּ� :  (SOCKADDR*)&tCIntAddr
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tCIntAddr, &iCIntSize); //���� ��û �� ����
	//accept �Լ��� �̿��Ͽ� ���� ��û�� ����


	char cBuffer[PACKET_SIZE] = {}; //���� ����

	recv(hClient, cBuffer, PACKET_SIZE, 0); // �������� ���� ����
	printf("Ŭ���̾�Ʈ�κ��� ���� �޽��� : %s\n", cBuffer);
	
	char cMsg[] = "�����κ��� ������ ���� �޽����� �����Ͽ����ϴ�.";

	send(hClient, cMsg, strlen(cMsg), 0);


	closesocket(hClient);
	closesocket(hListen);


	WSACleanup();
	return 0;
}