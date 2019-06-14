#include<iostream>	//input/output stream
#include<fstream>	//file stream
using namespace std;

//#define INTRODUCTION_TO_FILES
//#define EXCHANGE
#define MAC_IP_CHECK

int  my_strlen(char szStr[])
{
	int i = 0;
	for (; szStr[i]; i++);
	return i;
}
bool is_mac(char szStr[]);
bool is_ip(char szStr[]);
void add_file_extention(char szStr[]);

void main()
{
	"Hello World";
	setlocale(LC_ALL, "");
#ifdef INTRODUCTION_TO_FILES
	//cout << "Hello World!" << endl;
//1)Создаем поток вывода в файл:
	ofstream fout("File.txt", ios::app);
	fout << "Hello World" << endl;
	fout.close();
	//system("notepad File.txt");

	ifstream fin("File.txt");
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
#endif // INTRODUCTION_TO_FILES

#ifdef EXCHANGE
	//1) Создаем потоки
	const int SIZE = 256;
	char src_filename[SIZE]{};	//source file name
	char dst_filename[SIZE]{};	//destination file name
	cout << "Введите имя исходного файла: ";
	cin.getline(src_filename, SIZE);
	add_file_extention(src_filename);
	cout << src_filename << endl;
	cout << "Введите имя конечного файла: ";
	cin.getline(dst_filename, SIZE);
	add_file_extention(dst_filename);

	ifstream fin(src_filename);
	ofstream fout(dst_filename);

	//2) Создаем буферы, в которые будет производиться чтение из файла:
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

			if (is_mac(szMACbuffer)) fout << szMACbuffer << "\t";
			if (is_ip(szIPbuffer))   fout << szIPbuffer << "\n";
			std::cout << szMACbuffer << "\t";
			std::cout << szIPbuffer << "\n";
		}
	}
	fout.close();
	fin.close();
	system(dst_filename);
#endif // EXCHANGE

#ifdef MAC_IP_CHECK
	const int n = 20;
	char szStr[n] = "";
	cout << "Input MAC address: ";
	cin >> szStr;
	cout << szStr << endl;
	cout << "MAC address: " << is_mac(szStr) << endl;
	cout << "String length: " << strlen(szStr) << endl;
	cout << "IP address: " << is_ip(szStr) << endl;
#endif // MAC_IP_CHECK

}

bool is_mac(char szStr[])
{
	if (strlen(szStr) != 17)return false;
	for (int i = 0; szStr[i]; i++)
	{
		if (
			!(szStr[i] >= '0' && szStr[i] <= '9') &&
			!(szStr[i] >= 'A' && szStr[i] <= 'F') &&
			!(szStr[i] >= 'a' && szStr[i] <= 'f') &&
			!((szStr[i] == '-' || szStr[i] == ':') && (i + 1) % 3 == 0)
			)
			return false;
	}
	return true;
}

bool is_ip(char szStr[])
{
	if (strlen(szStr) > 15 || strlen(szStr) < 7)return false;
	int number_of_dots = 0;
	int bytes[4] = {};	//числовые значения байтов IP-адреса.
	for (int i = 0, j = 0; szStr[i]; i++)
	{
		if (szStr[i] == '.')number_of_dots++;
		if (szStr[i] == '.' && szStr[i + 1] == 0)return false;
		if (!(szStr[i] >= '0' && szStr[i] <= '9') && szStr[i] != '.')return false;
		if (szStr[i] == '.')
		{
			if (bytes[j] > 255 || number_of_dots > 3)return false;
			j++;
			continue;
		}
		bytes[j] *= 10;
		bytes[j] += (szStr[i] - 48);
	}
	if (number_of_dots != 3 || bytes[3] > 255)return false;
	return true;
}

void add_file_extention(char szStr[])
{
	int size = strlen(szStr);
	if (strcmp(szStr + size - 4, ".txt") == 0)return;
	strcat(szStr, ".txt");	//Конкатенация (слияние) строк.
}
