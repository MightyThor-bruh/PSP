#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "ErrorHandling.h"
#include <iostream>
#include <ctime>
#include "Winsock2.h"  
#pragma comment(lib, "WS2_32.lib")   

using namespace std;

bool GetServerByHostName(char* name, char* hostName, sockaddr* from, int* flen);

void main()
{
	WSADATA wsaData;

	SOCKADDR_IN from;
	memset(&from, 0, sizeof(from));
	char name[] = "Hello";
	int lfrom = sizeof(from);
	char hostName[] = "DESKTOP-PKU4T2M";
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		if (GetServerByHostName(name, hostName, (sockaddr*)&from, &lfrom))
		{
			cout << "Connection successful" << endl << endl;

			cout << "Connected server: " << endl;
			cout << "Hostname: " << hostName << endl;
			cout << "IP: " << inet_ntoa(from.sin_addr) << endl;
			cout << "Port: " << htons(from.sin_port) << endl;

		}
		else
		{
			cout << "Wrong call name" << endl;
		}

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << "WSAGetLastError: " << errorMsgText << endl;
	}
}

bool GetServerByHostName(char* name, char* hostName, sockaddr* from, int* flen)
{
	SOCKET sock;

	hostent* servInfo;
	memset(&servInfo, 0, sizeof(servInfo));
	servInfo = gethostbyname(hostName);
	in_addr* addr_list;
	addr_list = (in_addr*)*(servInfo->h_addr_list);

	((SOCKADDR_IN*)from)->sin_family = AF_INET;
	((SOCKADDR_IN*)from)->sin_port = htons(2000);
	((SOCKADDR_IN*)from)->sin_addr = *addr_list;
	int lbuf;
	char ibuf[50];
	int optval = 1;

	if ((sock = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw SetErrorMsgText("socket: ", WSAGetLastError());

	if (lbuf = sendto(sock, name, strlen(name) + 1, NULL, from, *flen) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());

	if (lbuf = recvfrom(sock, ibuf, sizeof(ibuf), NULL, from, flen) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			return false;
		else
			throw SetErrorMsgText("recvfrom: ", WSAGetLastError());
	}

	if (strcmp(ibuf, name) == 0)
		return true;
	else
		return false;

	if (closesocket(sock) == SOCKET_ERROR)
		throw SetErrorMsgText("closesocket: ", WSAGetLastError());
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
