#pragma once
#include <vector>
#include "Space.h"
using namespace std;
class Row
{
	vector<Space> fRow;
	int size;
public:
	Row() 
	{}
	~Row() 
	{}
	void AddSpace(Space s)
	{
		fRow.push_back(s);
	}

	Space* getSpace(int x)
	{
		return &fRow[x];
	}

	Space getCopySpace(int x)
	{
		return fRow[x];
	}

	void setSpace(int x, Space s)
	{
		fRow[x].setSpace(s);
	}

	bool left(int y)
	{
		if (y > 0)
			return true;
		else
			return false;
	}
	bool right(int y)
	{
		if (y < fRow.size())
			return true;
		else
			return false;
	}
};

