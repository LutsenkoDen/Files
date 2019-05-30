#include<iostream> //input/output stream
#include<fstream> //file stream
using namespace std;

//#define INTRODUCTION_TO_FILES
void main()
{
	setlocale(LC_ALL, "");
#if defined INTRODUCTION_TO_FILES
	//cout << "Hello Word" << endl;
	// Создаем поток вывода в файл
	ofstream fout("file.txt", ios::app);
	fout << "Hello Word" << endl;
	fout.close();
	//system("notepad file.txt");
	ifstream fin("file.txt");
	if (fin.is_open())
	{
		const int n = 256;
		char sz_buffer[n]{};
		while (!fin.eof())
		{
			//fin >> sz_buffer;
			fin.getline(sz_buffer, n);
			cout << sz_buffer << endl;
		}
	}
	fin.close();
#endif

	//1)Создаем потоки
	const int SIZE = 256;
	char src_filename[SIZE]{};
	char dst_filename[SIZE]{};
	cout << "Введите имя исходного файла: ";
	cin.getline(src_filename, SIZE);
	cout << "Введите имя конечного файла: ";
	cin.getline(dst_filename, SIZE);
	ifstream fin(src_filename);
	ofstream fout(dst_filename);

	//2)Создаем буферы, в которые будет производиться чтение из файла
	const int IP_MAX_SIZE = 16;
	const int MAC_MAX_SIZE = 18;
	char szIPbuffer[IP_MAX_SIZE]{};
	char szMACbuffer[MAC_MAX_SIZE]{};
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> szIPbuffer;
			fin >> szMACbuffer;
			fout << szMACbuffer << "\t";
			fout << szIPbuffer << "\n";
		}
	}
	fin.close();
	fout.close();
	system(dst_filename);
}
