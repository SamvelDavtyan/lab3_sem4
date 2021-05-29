#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../program3/List.h"
#include "../program3/Bellman-Ford.h"
#include "../program3/Bellman-Ford.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab3
{
	TEST_CLASS(BellmanFordTest)
	{
	public:
		
		TEST_METHOD(Search_Unique_Cities_Test)
		{
			ifstream read;
			read.open("D:\\Программирование\\4 сем\\lab3\\program3\\test_1.txt", ios::in);
			List<string>* Cities = new List<string>;
			Search_Unique_Cities(Cities, read);
			Assert::IsTrue("Yerevan" == Cities->at(0));
			Assert::IsTrue("Ufa" == Cities->at(1));
			Assert::IsTrue("Moscow" == Cities->at(2));
		}
		TEST_METHOD(Search_Matrix_Test)
		{
			ifstream read;
			read.open("D:\\Программирование\\4 сем\\lab3\\program3\\test_1.txt", ios::in);
			List<string>* Cities = new List<string>;
			Search_Unique_Cities(Cities, read);
			read.clear();
			read.seekg(0);
			int unique_cities = Cities->GetSize();
			int** Adjacency_Matrix = new int* [unique_cities];
			for (int i = 0; i < unique_cities; i++) 
			{
				Adjacency_Matrix[i] = new int[unique_cities];
			}
			for (int i = 0; i < unique_cities; i++) 
			{
				for (int j = 0; j < unique_cities; j++) {
					Adjacency_Matrix[i][j] = 0;
				}
			}
			Search_Matrix(Cities, read, Adjacency_Matrix);
			Assert::IsTrue(Adjacency_Matrix[0][0] == 0);
			Assert::IsTrue(Adjacency_Matrix[0][1] == 2);
			Assert::IsTrue(Adjacency_Matrix[0][2] == 5);
			Assert::IsTrue(Adjacency_Matrix[1][0] == 10);
			Assert::IsTrue(Adjacency_Matrix[1][1] == 0);
			Assert::IsTrue(Adjacency_Matrix[1][2] == 2);
			Assert::IsTrue(Adjacency_Matrix[2][0] == 9);
			Assert::IsTrue(Adjacency_Matrix[2][1] == 4);
			Assert::IsTrue(Adjacency_Matrix[2][2] == 0);
			for (unsigned j = 0; j < unique_cities; ++j)
				delete[] Adjacency_Matrix[j];
			delete[] Adjacency_Matrix;
		}
		TEST_METHOD(Belman_Ford_Test1)
		{
			ifstream read;
			int result = 0;
			read.open("D:\\Программирование\\4 сем\\lab3\\program3\\test_1.txt", ios::in);
			List<string>* Cities = new List<string>;
			Search_Unique_Cities(Cities, read);
			read.clear();
			read.seekg(0);
			int unique_cities = Cities->GetSize();
			int** Adjacency_Matrix = new int* [unique_cities];
			for (int i = 0; i < unique_cities; i++)
			{
				Adjacency_Matrix[i] = new int[unique_cities];
			}
			for (int i = 0; i < unique_cities; i++)
			{
				for (int j = 0; j < unique_cities; j++)
				{
					Adjacency_Matrix[i][j] = 0;
				}
			}
			Search_Matrix(Cities, read, Adjacency_Matrix);
			int** Shortest_Distances = new int* [unique_cities];
			for (int i = 0; i < unique_cities; i++)
			{
				Shortest_Distances[i] = new int[unique_cities];
			}
			for (int i = 0; i < unique_cities; i++)
			{
				for (int j = 0; j < unique_cities; j++) {
					Shortest_Distances[i][j] = inf;
				}
			}

			string from_choice = "Yerevan";
			int from = Cities->search(from_choice);

			Bellman_Ford(Adjacency_Matrix, Shortest_Distances, unique_cities, from);

			string to_choice = "Moscow";
			int to = Cities->search(to_choice);

			result = Shortest_Distances[unique_cities - 1][to];

			// check: from Yerevan to Moscow
			Assert::IsTrue(result == 4);

			for (unsigned j = 0; j < unique_cities; ++j)
				delete[] Adjacency_Matrix[j];
			delete[] Adjacency_Matrix;

			for (unsigned j = 0; j < unique_cities; ++j)
				delete[] Shortest_Distances[j];
			delete[] Shortest_Distances;
			
		}
		TEST_METHOD(Belman_Ford_Test2)
		{
			ifstream read;
			int result = 0;
			read.open("D:\\Программирование\\4 сем\\lab3\\program3\\test_2.txt", ios::in);
			List<string>* Cities = new List<string>;
			Search_Unique_Cities(Cities, read);
			read.clear();
			read.seekg(0);
			int unique_cities = Cities->GetSize();
			int** Adjacency_Matrix = new int* [unique_cities];
			for (int i = 0; i < unique_cities; i++) 
			{
				Adjacency_Matrix[i] = new int[unique_cities];
			}
			for (int i = 0; i < unique_cities; i++) 
			{
				for (int j = 0; j < unique_cities; j++) 
				{
					Adjacency_Matrix[i][j] = 0;
				}
			}
			Search_Matrix(Cities, read, Adjacency_Matrix);
			int** Shortest_Distances = new int* [unique_cities];
			for (int i = 0; i < unique_cities; i++) 
			{
				Shortest_Distances[i] = new int[unique_cities];
			}
			for (int i = 0; i < unique_cities; i++) 
			{
				for (int j = 0; j < unique_cities; j++) {
					Shortest_Distances[i][j] = inf;
				}
			}
			
			string from_choice = "Yerevan";
			int from = Cities->search(from_choice);

			Bellman_Ford(Adjacency_Matrix, Shortest_Distances, unique_cities, from);

			string to_choice = "Ufa";
			int to = Cities->search(to_choice);
		
			result = Shortest_Distances[unique_cities - 1][to];
		
			// check: from Yerevan to Ufa
			Assert::IsTrue(result == inf);

			for (unsigned j = 0; j < unique_cities; ++j)
				delete[] Adjacency_Matrix[j];
			delete[] Adjacency_Matrix;

			for (unsigned j = 0; j < unique_cities; ++j)
				delete[] Shortest_Distances[j];
			delete[] Shortest_Distances;
		}
	};
	TEST_CLASS(LinkedListTest)
	{
	public:

		TEST_METHOD(ConstructorTest)
		{
			List<int> lst;
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(IsEmptyTest1)
		{
			List<int> lst;
			Assert::IsTrue(lst.isEmpty());
		}
		TEST_METHOD(IsEmptyTest2)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.isEmpty() == false);
		}
		TEST_METHOD(AtTest1)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.at(0) == 3);
		}
		TEST_METHOD(AtTest2)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			Assert::IsTrue(lst.at(0) == 2, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 3, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 2, L"Assert 3");
		}
		TEST_METHOD(AtTest3)
		{
			List<int> lst;
			lst.push_back(3);
			try
			{
				lst.at(-5);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(GetSizeTest1)
		{
			List<int> lst;
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(GetSizeTest2)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			Assert::IsTrue(lst.GetSize() == 2);
		}
		TEST_METHOD(GetSizeTest3)
		{
			List<int> lst;
			lst.push_back(3);
			lst.push_front(2);
			lst.pop_back();
			lst.pop_front();
			Assert::IsTrue(lst.GetSize() == 0);
		}

		TEST_METHOD(PushBackTest1)
		{
			List<int> lst;
			lst.push_back(3);
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 1");
			Assert::IsTrue(lst.at(0) == 3, L"Assert 2");
		}
		TEST_METHOD(PushBackTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 3, L"Assert 2");
		}
		TEST_METHOD(PushFrontTest1)
		{
			List<int> lst;
			lst.push_front(3);
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 1");
			Assert::IsTrue(lst.at(0) == 3, L"Assert 2");
		}
		TEST_METHOD(PushFrontTest2)
		{
			List<int> lst;
			lst.push_front(0);
			lst.push_front(1);
			lst.push_front(2);
			lst.push_front(3);
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 0, L"Assert 2");
		}
		TEST_METHOD(PopBackTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.pop_back();
			Assert::IsTrue(lst.GetSize() == 3);
		}
		TEST_METHOD(PopBackTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.pop_back();
			Assert::IsTrue(lst.GetSize() == 0);
		}
		TEST_METHOD(PopBackTest3)
		{
			List<int> lst;
			try
			{
				lst.pop_back();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Linked list is Empty.");
			}
		}
		TEST_METHOD(PopFrontTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.pop_front();
			Assert::IsTrue(lst.at(0) == 1, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 3, L"Assert 3");
		}
		TEST_METHOD(PopFrontTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.pop_front();
			Assert::IsTrue(lst.isEmpty(), L"Assert 1");
		}
		TEST_METHOD(PopFrontTest3)
		{
			List<int> lst;
			try
			{
				lst.pop_front();
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Linked list is Empty.");
			}
		}
		TEST_METHOD(InsertTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.insert(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 0, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 3");
		}
		TEST_METHOD(InsertTest2)
		{
			List<int> lst;
			lst.insert(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 2");
		}
		TEST_METHOD(InsertTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.insert(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 4, L"Assert 3");
		}
		TEST_METHOD(InsertTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.insert(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 2, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 6, L"Assert 3");
		}
		TEST_METHOD(InsertTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			try
			{
				lst.insert(-3, 21);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(SetTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.set(0, 21);
			Assert::IsTrue(lst.at(0) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(1) == 1, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 3, L"Assert 3");
		}
		TEST_METHOD(SetTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(2, 21);
			Assert::IsTrue(lst.at(2) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(3) == 3, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(7, 21);
			Assert::IsTrue(lst.at(7) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(8) == 8, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.set(8, 21);
			Assert::IsTrue(lst.at(8) == 21, L"Assert 1");
			Assert::IsTrue(lst.at(7) == 7, L"Assert 2");
			Assert::IsTrue(lst.GetSize() == 9, L"Assert 3");
		}
		TEST_METHOD(SetTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			try
			{
				lst.set(-3, 21);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
		TEST_METHOD(RemoveTest1)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.remove(0);
			Assert::IsTrue(lst.at(0) == 1, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 1, L"Assert 2");
		}
		TEST_METHOD(RemoveTest2)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.remove(2);
			Assert::IsTrue(lst.at(2) == 3, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 8, L"Assert 2");
		}
		TEST_METHOD(RemoveTest3)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.push_back(6);
			lst.push_back(7);
			lst.push_back(8);
			lst.remove(6);
			Assert::IsTrue(lst.at(6) == 7, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 8, L"Assert 2");
		}
		TEST_METHOD(RemoveTest4)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			lst.push_back(3);
			lst.push_back(4);
			lst.push_back(5);
			lst.remove(5);
			Assert::IsTrue(lst.at(4) == 4, L"Assert 1");
			Assert::IsTrue(lst.GetSize() == 5, L"Assert 2");
		}
		TEST_METHOD(RemoveTest5)
		{
			List<int> lst;
			lst.push_back(0);
			lst.push_back(1);
			lst.push_back(2);
			try
			{
				lst.remove(-2);
			}
			catch (const char* error)
			{
				Assert::AreEqual(error, "Error! Incorrect input.");
			}
		}
	};
}
