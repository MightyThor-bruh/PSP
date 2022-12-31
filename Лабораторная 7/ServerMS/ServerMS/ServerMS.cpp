#include <iostream>
#include <Windows.h>
#include "ErrorHandling.h"

using namespace std;

int main()
{
	HANDLE hM; // дескриптор почтового ящика
	DWORD rb; // длина почитанного сообщения
	char rbuf[100]; // буфер ввода
	LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\Box");
	try
	{
		if ((hM = CreateMailslot(SlotName,
			300,
			//MAILSLOT_WAIT_FOREVER, // ждать вечно
			180000, // 180000 milliseconds (180 sec = 3 min)
			NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("CreateMailslotError:", GetLastError());
		cout << "Mailslot server launched" << endl;
		cout << "Waiting for reading 3 minutes.." << endl;
		while (true)
		{
			if (!ReadFile(hM,
				rbuf, // буфер
				sizeof(rbuf), // размер буфера
				&rb, // прочитано
				NULL))
				throw SetPipeError("ReadFileError:", GetLastError());
			cout << rbuf << endl;
		}
		//..................................................................
		CloseHandle(hM);
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
