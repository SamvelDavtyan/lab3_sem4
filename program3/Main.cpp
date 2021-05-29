#include <fstream>
#include "Bellman-Ford.h"

using namespace std;

#define inf INT_MAX/2-1

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream read;
	int result = 0;
	read.open("air_flights.txt", ios::in);
	if (read.bad())
	{
		cout << "Ошибка! Файл не открылся.";
		return 0;
	}
	Process(read,result);	
	return 0;
}