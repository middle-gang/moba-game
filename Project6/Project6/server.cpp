#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <string>
//using namespace std;

#pragma comment(lib, "ws2_32.lib")

SOCKET _cSock[2] = { INVALID_SOCKET };
char InfOppo[2][100];

void receive1() {
	char buf1[100];
	buf1[0] = 'u';
	buf1[1] = '0';
	buf1[2] = InfOppo[0][1];
	send(_cSock[1], buf1, 100, 0);
	while (true) {
		char intro[100] = {};
		recv(_cSock[1], intro, 100, 0);
		send(_cSock[0], intro, 100, 0);
	}
}

void receive2() {
	char buf[100] = {};
	buf[0] = 'u';
	buf[1] = '1';
	buf[2] = InfOppo[1][1];
	send(_cSock[0], buf, 100, 0);
	while (true) {
		char extro[100] = {};
		recv(_cSock[0], extro, 100, 0);
		send(_cSock[1], extro, 100, 0);
	}
}

int main() {
	// ����Windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//----------------



	// --��Socket API��������TCP������
	// ����һ��socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// �����ڽ��ܿͻ������ӵ�����˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(9527);
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;
	
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin))){
		printf("ERROR,�����ڽ��ܿͻ������ӵ�����˿�ʧ��...\n");
	}	
	else {
		printf("�󶨶˿ڳɹ�...\n");
		char hostname[128];
		hostent* hn;
		gethostname(hostname, 128);
		hn = gethostbyname(hostname);
		char* ip=inet_ntoa(*(struct in_addr *)hn->h_addr_list[0]);
		printf("%s\n", ip);
	}


	// �����˿�
	if (SOCKET_ERROR == listen(_sock, 5)) {
		printf("��������˿�ʧ��...\n");
	}
	else {
		printf("��������˿ڳɹ�...\n");
	}


	// ���տͻ�������
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);

	// ��ͻ��˷���һ������
	for (int i = 0; i < 2; i++) {
		_cSock[i] = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		
		if (INVALID_SOCKET == _cSock[i]){
			printf("���ܵ���Ч�ͻ���SOCKET...\n");
		}

		std::string str = "i";
		str += std::to_string(i);
		str.push_back('*');
		const char* msgBuf = str.c_str();
		printf("�¿ͻ��˼���:IP = %s\n", inet_ntoa(clientAddr.sin_addr));
		recv(_cSock[i], InfOppo[i], 100, 0);
	}

	std::thread sock1 = std::thread(receive1);
	sock1.detach();

	std::thread sock2 = std::thread(receive2);
	sock2.detach();
	
	while (1) {
	}

	closesocket(_sock);
	WSACleanup();

	return 0;
}


