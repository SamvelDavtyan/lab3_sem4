#include <iostream>
#include <fstream>
#include <string>
#include "list.h"
#include "Bellman-Ford.h"

using namespace std;

#define inf INT_MAX/2-1

// search for unique(non - recurring) cities from the list
void Search_Unique_Cities(List<string>* Cities, ifstream& read) 
{
	string str, temp;
	int counter, index;
	while (!read.eof()) 
	{
		getline(read, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) 
		{
			temp = "";
			while (str[i] != ';' && i != str.size()) 
				temp += str[i++];
			index = Cities->search(temp);
			if (index == -1) 
				Cities->push_back(temp);
			counter++;
			if (counter == 2) 
				break;
		}
	}
}

// finding the adjacency matrix
void Search_Matrix(List<string>* Cities, ifstream& read, int** Adjacency_Matrix)
{
	string str, temp;
	int indexI, indexJ, counter;
	while (!read.eof()) 
	{
		getline(read, str);
		counter = 0;
		for (size_t i = 0; i < str.size(); i++) 
		{
			temp = "";
			while (str[i] != ';' && i != str.size()) 
				temp += str[i++];
			if (counter == 0) 
				indexI = Cities->search(temp);
			if (counter == 1) 
				indexJ = Cities->search(temp);
			if (counter == 2 && temp != "N/A") 
				Adjacency_Matrix[indexI][indexJ] = atoi(temp.c_str());
			if (counter == 3 && temp != "N/A") 
				Adjacency_Matrix[indexJ][indexI] = atoi(temp.c_str());
			counter++;
		}
	}

}

// Bellman–Ford algorithm
void Bellman_Ford(int** Adjacency_Matrix, int** Shortest_Distances, int unique_cities, int index_from_city)
{
	for (int i = 0; i < unique_cities; i++) {
		Shortest_Distances[i][index_from_city] = 0;
	}
	for (int k = 1; k < unique_cities; k++) {
		for (int i = 0; i < unique_cities; i++) {
			for (int j = 0; j < unique_cities; j++) {
				if (Shortest_Distances[k - 1][j] + Adjacency_Matrix[j][i] < Shortest_Distances[k][i] && Adjacency_Matrix[j][i] != 0) {
					Shortest_Distances[k][i] = Shortest_Distances[k - 1][j] + Adjacency_Matrix[j][i];
				}
			}
		}
	}
}

// performs the work of the program
void Process(ifstream& read, int& result)
{
	List<string>* Cities = new List<string>;
	Search_Unique_Cities(Cities, read);
	read.clear();
	read.seekg(0);
	int unique_cities = Cities->GetSize();
	int** Adjacency_Matrix = new int* [unique_cities];
	for (int i = 0; i < unique_cities; i++) 
		Adjacency_Matrix[i] = new int[unique_cities];
	for (int i = 0; i < unique_cities; i++)
		for (int j = 0; j < unique_cities; j++) 
			Adjacency_Matrix[i][j] = 0;
	Search_Matrix(Cities, read, Adjacency_Matrix);
	int** Shortest_Distances = new int* [unique_cities];
	for (int i = 0; i < unique_cities; i++) 
		Shortest_Distances[i] = new int[unique_cities];
	for (int i = 0; i < unique_cities; i++) 
		for (int j = 0; j < unique_cities; j++) 
			Shortest_Distances[i][j] = inf;
	cout << "Здравствуйте, перед Вами список городов. С помощью программы Вы можете найти самый эффективный по стоимости перелет из одного города в другой." << endl;
	Cities->print_to_console();
	int from, control = 0;
	string choice;
	do
	{
		if (control == 0)
			cout << "Выберите город, из которого Вы ищете наиболее эффективный по стоимости перелет: " << endl;
		else
		{
			cout << "\nОшибка! Вы некорректно ввели название города, попробуйте еще раз." << endl;
			cout << "Выберите город, из которого Вы ищете наиболее эффективный по стоимости перелет: " << endl;
		}	
		cin >> choice;
		from = Cities->search(choice);
		control++;
	} while (from == -1 && control < 3);
	if (from == -1)
	{
		cout << "\nВы так и не смогли правильно ввести название нужного города, попробуйте в другой раз." << endl;
		return;
	}

	Bellman_Ford(Adjacency_Matrix, Shortest_Distances, unique_cities, from);

	int to;
	control = 0;
	choice = "";
	do
	{
		if (control == 0)
			cout << "Выберите город, в который Вы ищете наиболее эффективный по стоимости перелет: " << endl;
		else
		{
			cout << "\nОшибка! Вы некорректно ввели название города, попробуйте еще раз." << endl;
			cout << "Выберите город, в который Вы ищете наиболее эффективный по стоимости перелет: " << endl;
		}
		cin >> choice;
		to = Cities->search(choice);
		control++;
	} while (to == -1 && control < 3);
	if (to == -1)
	{
		cout << "\nВы так и не смогли правильно ввести название нужного города, попробуйте в другой раз." << endl;
		return;
	}

	result = Shortest_Distances[unique_cities - 1][to];
	if (result == inf)
		cout << "Пути из города " << Cities->at(from) << " в город " << Cities->at(to) << " не существует" << endl;
	else
		cout << "Наиболее эффективный по стоимости перелет из города " << Cities->at(from) << " в город " << Cities->at(to) << " составляет " << result << endl;

	for (unsigned j = 0; j < unique_cities; ++j)
		delete[] Adjacency_Matrix[j];
	delete[] Adjacency_Matrix;

	for (unsigned j = 0; j < unique_cities; ++j)
		delete[] Shortest_Distances[j];
	delete[] Shortest_Distances;
}
