#pragma once
#include "list.h"

void Search_Unique_Cities(List<string>* Cities, ifstream& read);
void Search_Matrix(List<string>* Cities, ifstream& read, int** Adjacency_Matrix);
void Bellman_Ford(int** Adjacency_Matrix, int** Shortest_Distances, int unique_cities, int index_from_city);
void Process(ifstream& read, int& result);