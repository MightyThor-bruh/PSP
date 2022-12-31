#include <iostream>
#include <Windows.h>
#include "ErrorHandling.h"

using namespace std;

int main()
{
	HANDLE hM; // дескриптор почтового ящика
	DWORD wb; // длина записанного сообщения
	char wbuf[] = "Hello from Mailslot-client"; // буфер вывода
	LPCTSTR SlotName = TEXT("\\\\.\\mailslot\\Box");
	try
	{
		if ((hM = CreateFile(SlotName,
			GENERIC_WRITE, // будем писать в ящик
			FILE_SHARE_READ, // разрешаем одновременно читать
			NULL,
			OPEN_EXISTING, // ящик уже есть
			NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("CreateFileError:", GetLastError());
		cout << "Mailslot client launched" << endl;

		clock_t start, stop;
		start = clock();

		for (int i = 0; i < 10000; i++)
			if (!WriteFile(hM,
				wbuf, // буфер
				sizeof(wbuf), // размер буфера
				&wb, // записано
				NULL))
				throw SetPipeError("WriteFileError:", GetLastError());


		stop = clock();
		cout << stop - start << " ticks" << endl;
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
