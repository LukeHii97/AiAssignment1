#pragma once
using namespace std;

enum class Type { EMPTY, BLOCK, START, END, WALKED };
class Space
{
private:
	int x;
	int y;
	int dist;
	Type spaceType;

public:
	Space()
	{
		x = 0;
		y = 0;
		dist = 0;
		spaceType = Type::EMPTY;
	}

	Space(int xloc, int yloc, Type sp)
	{
		x = xloc;
		y = yloc;
		spaceType = sp;
		dist = -1;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	int getDist()
	{
		return dist;
	}

	Type getSpaceType()
	{
		return spaceType;
	}

	void setX(int xloc)
	{
		x = xloc;
	}

	void setY(int yloc)
	{
		y = yloc;
	}

	void setSpaceType(Type sp)
	{
		spaceType = sp;
	}

	void setDist(int d)
	{
		dist = d;
	}

	void setSpace(Space s)
	{
		x = s.getX();
		y = s.getY();
		spaceType = s.getSpaceType();
		dist = s.getDist();
	}

	char disType()
	{
		if (spaceType == Type::START)
		{
			return 'S';
		}
		if (spaceType == Type::EMPTY)
		{
			return '_';
		}
		if (spaceType == Type::END)
		{
			return 'E';
		}
		if (spaceType == Type::WALKED)
		{
			return '-';
		}
		if (spaceType == Type::BLOCK)
		{
			return 'X';
		}
	}
};

