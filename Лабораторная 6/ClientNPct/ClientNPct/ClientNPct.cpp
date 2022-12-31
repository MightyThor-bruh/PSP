#define _CRT_SECURE_NO_WARNING
#include <iostream>
#include <Windows.h>
#include "ErrorHandling.h"
#include <tchar.h>

#define BUFSIZE 512

using namespace std;

int main()
{
	DWORD  cbRead, cbToWrite, cbWritten;
	TCHAR  chBuf[BUFSIZE] = TEXT("Hello from Client");
	TCHAR  zeroBuf[BUFSIZE] = TEXT("");
	LPTSTR lpvMessage = chBuf;
	BOOL   fSuccess = FALSE;

	HANDLE hPipe; // дескриптор канала
	try
	{
		cout << "Connected!" << endl;

		clock_t start, stop;
		start = clock();

		cbToWrite = (lstrlen(lpvMessage) + 1) * sizeof(TCHAR);

		fSuccess = CallNamedPipe(
			TEXT("\\\\DESKTOP-PKU4T2M\\pipe\\Tube"),        // pipe name 
			lpvMessage,           // message to server 
			(lstrlen(lpvMessage) + 1) * sizeof(TCHAR), // message length 
			chBuf,              // buffer to receive reply 
			BUFSIZE * sizeof(TCHAR),  // size of read buffer 
			&cbRead,                // number of bytes read 
			20000);                 // waits for 20 seconds

		_tprintf(TEXT("%s\n"), chBuf);

		if (!fSuccess)
		{
			throw SetPipeError("transact:", GetLastError());
		}

		stop = clock();
		cout << (stop - start) << " ticks passed" << endl;

		cout << "Disconnected" << endl;
	}
	catch (string ErrorPipeText)
	{
		cout << endl << ErrorPipeText;
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
