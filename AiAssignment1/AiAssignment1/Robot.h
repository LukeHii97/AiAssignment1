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
	int posX=-1, posY = -1;
	NTree root;
public:
	Robot()
	{}
	Robot(Map &m)
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
					
					break;
				}
			}
		}
		root= NTree(map->getRow(posX)->getSpace(posY));
		autoAttach(&root);
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

	void addHistory(Space &sp)
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

	vector<Space*> getNearBy(int x,int y)
	{
		vector<Space*> s{};
		bool ch = true;
		cout << "ori x: " << x << " y: " << y << endl;
			if (map->isUp(x))
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x - 1)->getSpace(y) == history[i] || map->getRow(x - 1)->getSpace(y)->getSpaceType() == Type::BLOCK)
					{
						ch = false;
						break;
					}
				}
				if (ch==true)
				{
					cout << "Up" << endl;
					cout << " x: " << map->getRow(x - 1)->getSpace(y)->getX() << " y: " << map->getRow(x - 1)->getSpace(y)->getY() << endl;
					s.push_back(map->getRow(x - 1)->getSpace(y));
					addHistory(*map->getRow(x - 1)->getSpace(y));
				}
				else
					ch = true;
			}
			if (map->isDown(x))
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x + 1)->getSpace(y) == history[i] || map->getRow(x + 1)->getSpace(y)->getSpaceType() == Type::BLOCK)
					{
						ch = false;
						break;
					}
				}
				if (ch == true) 
				{
					cout << "Down" << endl;
					cout << " x: " << map->getRow(x + 1)->getSpace(y)->getX() << " y: " << map->getRow(x + 1)->getSpace(y)->getY() << endl;
					s.push_back(map->getRow(x + 1)->getSpace(y));
					addHistory(*map->getRow(x + 1)->getSpace(y));
				}
				else
					ch = true;
			}
			if (map->isLeft(y))
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x)->getSpace(y - 1) == history[i] || map->getRow(x)->getSpace(y - 1)->getSpaceType() == Type::BLOCK)
					{
						ch = false;
						break;
					}
				}
				if (ch == true)
				{
					cout << "Left" << endl;
					cout << " x: " << map->getRow(x)->getSpace(y-1)->getX() << " y: " << map->getRow(x)->getSpace(y-1)->getY() << endl;
					s.push_back(map->getRow(x)->getSpace(y - 1));
					addHistory(*map->getRow(x)->getSpace(y - 1));
				}
				else
					ch = true;
			}
			if (map->isRight(y))
			{
				for (int i = 0; i < history.size(); i++)
				{
					if (map->getRow(x)->getSpace(y + 1) == history[i] || map->getRow(x)->getSpace(y + 1)->getSpaceType() == Type::BLOCK)
					{
						ch = false;
						break;
					}
				}
				if (ch == true)
				{
					cout << "Right" << endl;
					cout << " x: " << map->getRow(x)->getSpace(y+1)->getX() << " y: " << map->getRow(x)->getSpace(y+1)->getY() << endl;
					s.push_back(map->getRow(x)->getSpace(y + 1));
					addHistory(*map->getRow(x)->getSpace(y + 1));
				}
				else
					ch = true;
			}
			cout << "History: " << endl;
			for (int i = 0; i < history.size(); i++)
			{
				cout << " x: " << history[i]->getX()<< " y: " << history[i]->getY() << endl;

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
			NTree t(sp[i]);
			getTrees()->push_back(t);
			cout << "x: " << sp[i]->getX() << " y:" << sp[i]->getY() << endl;
			for (int z = 0; z < trees.size(); z++)
			{
				if (sp[i]->getX() == getTrees(z)->key().getX() && sp[i]->getY() == getTrees(z)->key().getY())
				{
					no = z;//get the index
					z = trees.size();//break z for loop
				}
			}
			//bug
			cout << "Trees" << endl;
			for (int z = 0; z < getTrees()->size(); z++)
			{
				cout << "x: " << getTrees(z)->key().getX() << " y: " << getTrees(z)->key().getY() << endl;
				cout << "add: "<< &getTrees(z)->key()<< endl;
				cout << "next" << endl;
			}
			//cout << getTrees(0)->key().getX();
			//if not attach tree to tr then everything is fine.
			tr->attachNTree(0, &getTrees()->at(0));
			//tr->attachNTree(1, getTrees(1));
			//tr->attachNTree(2, getTrees(2));
			//need attach trees[z] to tr.
		}
		/*

		cout << "Trees" << endl;
		for (int z = 0; z < 3; z++)
		{
			cout << "here" << endl;
			cout << "x: " << tr[z].key().getX() << endl;
			cout<<" y: " << tr[z].key().getY() << endl;
		}
		
		
		for (int i = 0; i < sp.size(); i++)
		{
			tr.attachNTree(i, &trees[z]);
			cout << "x : " << tr[i].key().getX() << " y:" << tr[i].key().getY() << endl;

		}
		for (int j = 0; j < sp.size(); j++)
		{

			level += 1;
			cout << "in"<< endl;
			autoAttach(tr[j]);
			level -= 1;
		}
		cout << "out. level:" << level << endl;
		*/
	}
};

