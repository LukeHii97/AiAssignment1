#pragma once
#include "NTree.h"
#include "Map.h"
enum class Move {UP,DOWN,LEFT,RIGHT};
class Robot
{
private:
	Map* map;
	vector<NTree> trees;
	vector<Space*> history;
	int level = 0;
	int posX = -1, posY = -1;
	NTree root;
public:
	Robot()
	{}
	Robot(Map& m)
	{
		map = &m;
		for (int i = 0; i < map->getRowSize(); i++)
		{
			for (int j = 0; j < map->getColSize(); j++)
			{
				if (map->getRow(i)->getSpace(j)->getSpaceType() == Type::START)
				{
					posX = i;
					posY = j;
					cout << "posX:" << posX << endl;
					cout << "posY:" << posY << endl;
					break;
				}
			}
		}
		root = NTree(map->getRow(posX)->getSpace(posY));

		//ChkGetNearBy(0, 0);
		autoAttach(&root);
		//cout << "root: x:" << root.key().getX() << " y:" << root.key().getY() << endl;
		//attachRoot();
		//attachRoot(&root);
		//root.attachNTree();
		cout << "hello this is consturtor" << endl;
	}
	~Robot()
	{}

	void show()
	{
		cout << "PosX: " << posX << endl;
		cout << "PosY: " << posY << endl;
	}

	Space* getLocation()
	{
		return map->getSpace(posX, posY);
	}

	void addHistory(Space& sp)
	{
		history.push_back(&sp);
	}

	void moveUp()
	{
		if (map->isUp(posX))
		{
			getLocation()->setSpaceType(Type::WALKED);
			posX -= 1;

		}
	}
	void moveDown()
	{
		if (map->isDown(posX))
		{
			getLocation()->setSpaceType(Type::WALKED);
			posX += 1;
		}
	}

	void moveLeft()
	{
		if (map->isLeft(posY))
		{
			getLocation()->setSpaceType(Type::WALKED);
			posY -= 1;
		}
	}

	void moveRight()
	{
		if (map->isRight(posY))
		{
			getLocation()->setSpaceType(Type::WALKED);
			posY += 1;
		}
	}

	vector<NTree>* getTrees()
	{
		return &trees;
	}

	NTree* getTrees(int z)
	{
		return &trees[z];
	}

	vector<Space*> getNearBy(int x, int y)
	{
		vector<Space*> s{};
		bool ch = true;

		cout << "ori x: " << x << " y: " << y << endl;

		//Up
		if (map->isUp(x))
		{
			if (map->getRow(x - 1)->getSpace(y)->getSpaceType() != Type::BLOCK)
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x - 1)->getSpace(y) == history[i])
					{
						ch = false;
					}
				}
				if (ch)
				{
					s.push_back(map->getRow(x - 1)->getSpace(y));
					addHistory(*map->getRow(x - 1)->getSpace(y));
				}
				ch = true;
			}
		}

		if (map->isDown(x))
		{
			if (map->getRow(x + 1)->getSpace(y)->getSpaceType() != Type::BLOCK)
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x + 1)->getSpace(y) == history[i])
					{
						ch = false;
					}
				}
				if (ch)
				{
					s.push_back(map->getRow(x + 1)->getSpace(y));
					addHistory(*map->getRow(x + 1)->getSpace(y));
				}
				ch = true;
			}
		}

		if (map->isLeft(y))
		{

			if (map->getRow(x)->getSpace(y - 1)->getSpaceType() != Type::BLOCK)
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x)->getSpace(y - 1) == history[i])
					{
						ch = false;
					}
				}
				if (ch)
				{
					s.push_back(map->getRow(x)->getSpace(y - 1));
					addHistory(*map->getRow(x)->getSpace(y - 1));
				}
				ch = true;
			}
		}
		if (map->isRight(y))
		{
			if (map->getRow(x)->getSpace(y + 1)->getSpaceType() != Type::BLOCK)
			{
				for(int i=0;i<history.size();i++)
				{
					if(map->getRow(x)->getSpace(y + 1)== history[i])
					{
						ch = false;
					}
				}
				if (ch == true)
				{
					s.push_back(map->getRow(x)->getSpace(y + 1));
					addHistory(*map->getRow(x)->getSpace(y + 1));
				}
			}
		}

		cout << "History: " << endl;
		for (int i = 0; i < history.size(); i++)
		{
			cout << " x: " << history[i]->getX() << " y: " << history[i]->getY() << endl;
		}

		return s;
	}



	void autoAttach(NTree *tr)
	{
		vector<Space*> sp = getNearBy(tr->key().getX(), tr->key().getY());
		int no=0;
		cout << "Trees Size" << trees.size() << endl;
		cout << "level:" << level << endl;
		cout << endl << "Tr ";
		cout << "x : " << tr->key().getX() << " y:" << tr->key().getY() << endl;
		cout << "sp size: " << sp.size() << endl;
		cout << "sp : "<< endl;


		for (int i = 0; i < sp.size(); i++)
		{
			NTree t(sp[i]);   //generate TreeNode From sp.
			getTrees()->push_back(t);
			cout << "x: " << sp[i]->getX() << " y:" << sp[i]->getY() << endl;
			for (int z = 0; z < trees.size(); z++)
			{
				if (sp[i]->getX() == getTrees(z)->key().getX() && sp[i]->getY() == getTrees(z)->key().getY())
				{
					no = z;//get the index
					break;
				}
			}
			tr->attachNTree(i, getTrees(no));
		}

		cout << "done" << endl;
		for (int j = 0; j < sp.size(); j++)
		{

			level += 1;
			cout << "in. TR " <<j<<endl;
			autoAttach(&tr[j]);
			level -= 1;
		}
		cout << "out. level:" << level << endl;
	}
};





/*
	void attachRoot()
	{
		cout << "attach Root" << endl;
		vector<Space*> sp = getNearBy(root.key().getX(), root.key().getY());
		cout <<endl<< "SP:" << endl;
		//tree nodes generated
		for (int i = 0; i < sp.size(); i++)
		{
			cout << "X:"<<sp[i]->getX() << " Y:" << sp[i]->getY() << endl;
			NTree t(sp[i]);
			trees.push_back(t);
		}

		for (int j = 0; j < trees.size(); j++)
		{

			for (int i = 0; i < sp.size(); i++)
			{
				if (sp[i]->getX() == getTrees(j)->key().getX() && sp[i]->getY() == getTrees(j)->key().getY())
				{
					root.attachNTree(i, getTrees(j));
				}
			}
		}
		cout << "root:" << endl;
		cout<<"x:" << root.key().getX() << " y:" << root.key().getY() << endl;
		int z = sp.size();
		for (int k = 0; k < z; k++)
		{
			cout << "root[" << k << "]: "<< "x:" << root[k].key().getX() << " y:" << root[k].key().getY() << endl;
			vector<Space*> sp = getNearBy(root[k].key().getX(), root[k].key().getY());
			cout << endl << "SP:" << endl;
			//tree nodes generated
			for (int i = 0; i < sp.size(); i++)
			{
				cout<<i << ".   X:" << sp[i]->getX() << " Y:" << sp[i]->getY() << endl;

				NTree t(sp[i]);
				cout << "NTree t(sp[i]);" << endl;
				trees.push_back(t);
				cout << "trees.push_back(t);" << endl;
			}
			cout << "outside for loop" << endl;
		}


	}


		void checkDirection(int x, int y)
	{
		if (map->isUp(x))
		{
			cout <<"x(Up): "<< x - 1 << "is possible in this map" << endl;
		}
		if (map->isDown(x))
		{
			cout << "x(Down): " << x + 1 << "is possible in this map" << endl;
		}
		if (map->isLeft(y))
		{
			cout << "y(Left): " << y - 1 << "is possible in this map" << endl;
		}
		if (map->isRight(y))
		{
			cout << "y(Right): " << y + 1 << "is possible in this map" << endl;
		}
	}
	*/