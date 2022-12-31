﻿#include <iostream>
#include <Windows.h>
#include "ErrorHandling.h"
#include <tchar.h>

#define BUFSIZE 512

using namespace std;

int main()
{
	//LPCWSTR lpvMessage = TEXT("Darova, eto server");
	DWORD  cbRead, cbToWrite, cbWritten;
	TCHAR  chBuf[BUFSIZE];
	TCHAR checkBuf[BUFSIZE] = TEXT("");
	BOOL   fSuccess = FALSE;

	HANDLE hPipe; // дескриптор канала

	bool multi = true; //////////////////////////////////////

	try
	{
		do
		{
			if ((hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Tube"),
				PIPE_ACCESS_DUPLEX, //дуплексный канал
				PIPE_TYPE_MESSAGE | PIPE_WAIT, // сообщения|синхронный
				1, NULL, NULL, // максимум 1 экземпляр
				INFINITE, NULL)) == INVALID_HANDLE_VALUE)
				throw SetPipeError("create:", GetLastError());

			cout << "Waiting.." << endl;

			if (!ConnectNamedPipe(hPipe, NULL)) // ожидать клиента
				throw SetPipeError("connect:", GetLastError());

			cout << "Connected!" << endl;

			//..................................................................
			do
			{
				do
				{
					fSuccess = ReadFile(
						hPipe, // pipe handle
						chBuf, // buffer to receive reply
						BUFSIZE * sizeof(TCHAR), // size of buffer
						&cbRead, // number of bytes read
						NULL); // not overlapped
				} while (!fSuccess);

				if (!fSuccess)
				{
					throw SetPipeError("readfile:", GetLastError());
				}

				if (!wcscmp(chBuf, checkBuf)) {
					break;
				}

				_tprintf(TEXT("%s\n"), chBuf);

				//..................................................................

				cbToWrite = (lstrlen(chBuf) + 1) * sizeof(TCHAR);

				fSuccess = WriteFile(
					hPipe, // pipe handle
					chBuf, // message
					cbToWrite, // message length
					&cbWritten, // bytes written
					NULL); // not overlapped

				if (!fSuccess)
				{
					throw SetPipeError("writefile:", GetLastError());
				}

			} while (wcscmp(chBuf, checkBuf) && multi);

			cout << "Disconnected" << endl;

			DisconnectNamedPipe(hPipe);
			CloseHandle(hPipe);
		} while (true);
	}
	catch (string ErrorPipeText)
	{
		cout << endl << ErrorPipeText;

		//DisconnectNamedPipe(hPipe);
		//CloseHandle(hPipe);
	}

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
