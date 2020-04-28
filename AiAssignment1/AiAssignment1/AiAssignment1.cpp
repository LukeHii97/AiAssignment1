// AiA1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Robot.h"
#include "Map.h"
#include "Row.h"
#include<vector>
using namespace std;

int merge(int int1, int int2)
{
	int int2_copy = int2;
	do
	{
		int1 *= 10;
		int2_copy /= 10;
	} while (int2_copy);

	return int1 + int2;
}
void getInputs(string sInput[], int size, vector<vector<int>>& s2d, vector<vector<int>>& b2d)
{
	int rowcount = 0;

	char char_array[99];
	cout << "size: " << size << endl;

	for (int x = 0; x < size; x++)
	{
		strcpy_s(char_array, sInput[x].c_str());
		int n = sInput[x].length();
		int j = 0;
		int integers[10];
		int intstr, intstr2;
		bool row = false;

		int count = 0;
		bool same = false;
		for (int i = 0; char_array[i] != '\0'; i++)
		{
			if (char_array[i] >= '0' && char_array[i] <= '9') {
				row = true;
				count += 1;
				if (same == true)
				{
					intstr = integers[j - 1];
					intstr2 = (int)char_array[i] - 48;
					integers[j - 1] = merge(intstr, intstr2);
					j -= 1;
					count = count - 1;
				}
				else {
					same = true;
					integers[j] = (int)char_array[i] - 48;
				}
				j++;
			}
			else
			{
				same = false;
			}

		}
		if (row == true)
		{
			rowcount += 1;
		}
		vector<int> s;
		vector<int> b;
		for (int z = 0; z < count; z++)
		{
			if (count <= 2)
			{
				s.push_back(integers[z]);
			}
			else
			{
				b.push_back(integers[z]);
			}
		}
		if (count <= 2 && count != 0)
		{
			s2d.push_back(s);
		}
		else if (count != 0)
		{
			b2d.push_back(b);
		}

	}


	cout << "rowcount: " << rowcount << endl;

}

int main()
{
	ifstream lInput;
	string sInput[99]; //12
	int size = 0;
	string inputFileName = "RobotNav-test.txt";
	lInput.open(inputFileName, ifstream::in);
	int xSize, ySize;
	vector<vector<int>> s2d;
	vector<vector<int>> b2d;

	if (!lInput.good())
	{
		cerr << "Cannot open input file: " << inputFileName << endl;
		return 2;
	}

	//input to sInput
	while (lInput >> sInput[size])
	{
		//print sInput
		cout << sInput[size] << endl;
		size += 1;
	}

	getInputs(sInput, size, s2d, b2d);
	xSize = s2d[0][0];
	ySize = s2d[0][1];
	
	Map m = Map(xSize, ySize, s2d, b2d);

	/*
	for (int i = 0; i < 5; i++)
	{
		Map m = Map();
		for (int j = 0; j < 11; j++)
		{
			Space s = Space(i, j, Type::EMPTY);
			m.AddSpace(s);
		}
		r.AddMap(m);
	}
	*/
	Space sp = Space(1, 2, Type::EMPTY);
	//NTree root(&sp);
	//root.key();
	m.DisplayMap();
	Robot r = Robot(m);
	//r.show();
	//r.moveDown();
	//r.moveRight();
	//r.moveRight();
	//r.show();
	
	m.DisplayMap();
	cout << "Hello World!\n";
}

