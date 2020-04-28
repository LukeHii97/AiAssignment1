#pragma once
#include "Space.h"
#include <iostream>
class NTree
{
private:
	Space* fKey; // 0 for empty 
	NTree* fNodes[4]; // N subtrees of degree N

public:
	//static NTree NIL; // sentinel
	NTree() : fKey((Space*)0)
	{
		// Initialize all nodes to the address of NIL
		for (int i = 0; i < 4; i++)
		{
			fNodes[i] = NULL;
		}
	}
		NTree(Space* aKey) // a simple NTree with key and N subtrees
	{
		fKey = aKey;
		// Initialize all nodes to the address of NIL
		for (int i = 0; i < 4; i++)
		{
			fNodes[i] = NULL;
		}
	}
	//destructor
	~NTree()
	{
		/*
		for (int i = 0; i < 4; i++)
		{
			// Delete nodes that already have value
			if (fNodes[i] != NULL) {
				delete fNodes[i];
			}
		}*/
	}

	bool isEmpty()  // is tree empty
	{
		return this == NULL;
	}

	Space& key()  
	{
		if (isEmpty())
			throw std::domain_error("Empty NTree!");

		return *fKey;
	}

	// indexer (return the selected nodes stored in the array)
	NTree& operator[](int aIndex)
	{
		if (isEmpty())//if the object itself is empty, throw exception
		{
			throw std::domain_error("Empty NTree!");
		}

		if ((aIndex >= 0) && (aIndex < 4))
		{
			return *fNodes[aIndex];
		}
		else//if out of range, throw exception
		{
			throw out_of_range("Illegal subtree index!");
		}
	}

	void attachNTree(int aIndex, NTree* aNTree)
	{
		//NTree t(&aNTree->key());

		if (isEmpty())
			throw std::domain_error("Empty NTree!");
		if ((aIndex >= 0) && (aIndex < 4))
		{
			if (fNodes[aIndex] != NULL)
			{
				throw std::domain_error("Non Empty subtree present!");
			}
			fNodes[aIndex] = aNTree;
		}
		else//if out of range, throw exception
			throw std::out_of_range("Illegal subtree index");

	}
	NTree* detachNTree(int aIndex)
	{
		if (isEmpty())//if the object itself is empty, throw exception
			throw std::domain_error("Empty NTree!");

		if ((aIndex >= 0) && (aIndex < 4))
		{
			NTree* Result = fNodes[aIndex];//create a temporary node and store the fnode
			fNodes[aIndex] = NULL;//fnodes point to NIL
			return Result; // return the value of temporary(fnode previous value)
		}
		else//if out of range, throw exception
			throw std::out_of_range("Illegal subtree index");
	}
};