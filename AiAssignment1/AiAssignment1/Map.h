#pragma once
#include "Row.h"
//#include "NTree.h"
#include<iostream>
class Map

{
private:
	vector<Row> fMap;
	//vector<Space> history;
	int rSize, cSize;
public:
	Map()
	{
		rSize = 0;
		cSize = 0;
	}
	Map(int x, int y, vector<vector<int>> s, vector<vector<int>> b)
	{
		rSize = x;
		cSize = y;
		for (int i = 0; i < rSize; i++)
		{
			Row r = Row();
			for (int j = 0; j < cSize; j++)
			{
				Space sp = Space(i, j, Type::EMPTY);
				r.AddSpace(sp);
			}
			fMap.push_back(r);
		}
		for (int i = 1; i < s.size(); i++)
		{
			if (i == 1)
			{
				fMap[s[i][1]].setSpace(s[i][0], Space(s[i][1], s[i][0], Type::START));

			}
			else
			{
				fMap[s[i][1]].setSpace(s[i][0], Space(s[i][1], s[i][0], Type::END));
			}
		}

		for (int h = 0; h < b.size(); h++)
		{
			for (int i = 0; i < b[h][2]; i++)
			{
				for (int j = 0; j < b[h][3]; j++)
				{
					fMap[b[h][1] + j].setSpace(b[h][0] + i, Space(b[h][1] + j, b[h][0] + i, Type::BLOCK));
				}
			}
		}

		for (int i = 0; i < rSize; i++)
		{
			for (int j = 0; j < cSize; j++)
			{
				if (fMap[i].getSpace(j)->getSpaceType() == Type::END)
				{
					fMap[i].getSpace(j)->setDist(0);
				}
			}
		}

		for (int i = rSize - 1; i > 0; i--)
		{
			for (int j = cSize - 1; j >= 0; j--)
			{
				//cout << " i: " << i << ", j:" << j << endl;
				if (fMap[i].getSpace(j)->getDist() != -1)
				{
					//Up
					if (i > 0)
					{
						if (fMap[i - 1].getSpace(j)->getDist() == -1)
							fMap[i - 1].getSpace(j)->setDist(fMap[i].getSpace(j)->getDist() + 1);
						else
							if (fMap[i].getSpace(j)->getDist() + 1 < fMap[i - 1].getSpace(j)->getDist())
								fMap[i - 1].getSpace(j)->setDist(fMap[i].getSpace(j)->getDist() + 1);
					}
					//down
					if (i < rSize - 1)
					{
						if (fMap[i + 1].getSpace(j)->getDist() == -1)
							fMap[i + 1].getSpace(j)->setDist(fMap[i].getSpace(j)->getDist() + 1);
						else
							if (fMap[i].getSpace(j)->getDist() + 1 < fMap[i - 1].getSpace(j)->getDist())
								fMap[i + 1].getSpace(j)->setDist(fMap[i].getSpace(j)->getDist() + 1);
					}
					//left
					if (j > 0)
					{
						if (fMap[i].getSpace(j - 1)->getDist() == -1)
							fMap[i].getSpace(j - 1)->setDist(fMap[i].getSpace(j)->getDist() + 1);
						else
							if (fMap[i].getSpace(j)->getDist() + 1 < fMap[i].getSpace(j - 1)->getDist())
								fMap[i].getSpace(j - 1)->setDist(fMap[i].getSpace(j)->getDist() + 1);
					}
					//right
					if (j < cSize - 1)
					{
						if (fMap[i].getSpace(j + 1)->getDist() == -1)
							fMap[i].getSpace(j + 1)->setDist(fMap[i].getSpace(j)->getDist() + 1);
						else
							if (fMap[i].getSpace(j)->getDist() + 1 < fMap[i].getSpace(j + 1)->getDist())
								fMap[i].getSpace(j + 1)->setDist(fMap[i].getSpace(j)->getDist() + 1);
					}
				}
			}
		}
		//NTree root(fMap[posX].getSpace(posY));
	}
	~Map()
	{}

	void setSpace(int x, int y, Space s)
	{
		fMap[x].setSpace(y, s);
	}

	Space* getSpace(int x, int y)
	{
		return fMap[x].getSpace(y);
	}

	void AddRow(Row r)
	{
		fMap.push_back(r);
	}
	
	Row* getRow(int x)
	{
		return &fMap[x];
	}

	Row getCopyOfRow(int x)
	{
		return fMap[x];
	}

	int getRowSize()
	{
		return rSize;
	}

	int getColSize()
	{
		return cSize;
	}

	vector<Row>* GetMap()
	{
		return &fMap;
	}

	void DisplayMap()
	{
		for (int i = 0; i < rSize; i++)
		{
			cout << i << " | ";
			for (int j = 0; j < cSize; j++)
			{
				//show type
				cout << fMap[i].getSpace(j)->disType();

				//show indexs
				//cout << fMap[i].getSpace(j)->getX() << ", " << fMap[i].getSpace(j)->getY();

				//show distance
				cout << fMap[i].getSpace(j)->getDist();
				cout << " | ";
			}
			cout << endl;
		}
	}

	bool isUp(int x)
	{
		if (x - 1 >= 0)
			return true;
		else
			return false;
	}

	bool isDown(int x)
	{
		if (x + 1 <= fMap.size())
			return true;
		else
			return false;
	}
	bool isLeft(int y)
	{
		return fMap[0].left(y);
	}

	bool isRight(int y)
	{
		return fMap[0].right(y);
	}

	vector<Space> getNearby(int x, int y)
	{
		vector<Space> nb{};
		if (isUp(x))
		{
			nb.push_back(fMap[x - 1].getCopySpace(y));
		}
		if (isDown(x))
		{
			nb.push_back(fMap[x - 1].getCopySpace(y));
		}
		if (isLeft(y))
		{
			nb.push_back(fMap[x].getCopySpace(y - 1));
		}
		if (isRight(y))
		{
			nb.push_back(fMap[x].getCopySpace(y + 1));
		}
		return nb;
	}
};

