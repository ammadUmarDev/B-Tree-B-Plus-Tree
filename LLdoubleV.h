#pragma once

#include <cstring>
#include "string.h"
#include <string>
#include <cmath>
#include <sstream>
#include <stdio.h> 
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;



template <class T>
struct VectorNodeVV
{

public:
	T data;
	VectorNodeVV<T> *next;
};

template <class T>
class VECTORVV
{

private:

	VectorNodeVV<T> *head;
	VectorNodeVV<T> *tail;

	int size;










public:
	VECTORVV()
	{
		head = NULL;
		size = 0;
		//	cout << endl << "Vector initialized!" << endl;


	}

	/*
	VECTOR(VECTOR<T> &NodePtr)
	{
	this->head->data = NodePtr->head->data;
	this->head->next = NodePtr->head->next;

	this->tail->data = NodePtr->tail->data;
	this->tail->next = NodePtr->tail->next;


	size = 0;
	//	cout << endl << "Vector initialized!" << endl;


	}*/

	void createnode(T value)
	{
		VectorNodeVV<T> *temp = new VectorNodeVV<T>;
		temp->data = value;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		// cout << endl << "Node Created!" << endl;
		size++;
	}



	void createnode_with_node(VectorNodeVV<T> *insObj)
	{

		if (head == NULL)
		{
			head = insObj;
			tail = insObj;
			insObj = NULL;
		}
		else
		{
			tail->next = insObj;
			tail = insObj;
		}
		// cout << endl << "Node Created!" << endl;
		size++;
	}


	void display()
	{
		VectorNodeVV<T> *temp = new VectorNodeVV<T>;
		temp = head;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl << "vector object displayed" << endl;

	}


	void displayD()
	{
		VectorNodeVV<VECTOR<int>> *temp = new VectorNodeVV<VECTOR<int>>;
		temp = head;
		while (temp != NULL)
		{
			temp->data.display();
				cout << endl;
			temp = temp->next;
		}
		cout << endl << "vector object displayed" << endl;

	}


	void insert_start(T value)
	{
		VectorNodeVV<T> *temp = new VectorNodeVV<T>;
		temp->data = value;
		temp->next = head;
		head = temp;
		cout << endl << "Node Created!" << endl;
		size++;


	}



	void insert_position(int pos, T value)
	{
		VectorNodeVV<T> *pre = new VectorNodeVV<T>;
		VectorNodeVV<T> *cur = new VectorNodeVV<T>;
		VectorNodeVV<T> *temp = new VectorNodeVV<T>;
		cur = head;
		for (int i = 1; i<pos; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		temp->data = value;
		pre->next = temp;
		temp->next = cur;
		cout << endl << "Node Created!" << endl;
		size++;


	}



	void delete_first()
	{
		VectorNodeVV<T> *temp = new VectorNodeVV<T>;
		temp = head;
		head = head->next;
		delete temp;
		cout << endl << "Node Deleted!" << endl;
		size--;


	}




	void delete_last()
	{
		VectorNodeVV<T> *current = new VectorNodeVV<T>;
		VectorNodeVV<T> *previous = new VectorNodeVV<T>;
		current = head;
		while (current->next != NULL)
		{
			previous = current;
			current = current->next;
		}
		tail = previous;
		previous->next = NULL;
		delete current;
		cout << endl << "Node Deleted!" << endl;
		size--;


	}




	void delete_position(int pos)
	{
		VectorNodeVV<T> *current = new VectorNodeVV<T>;
		VectorNodeVV<T> *previous = new VectorNodeVV<T>;
		current = head;
		for (int i = 1; i<pos; i++)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
		cout << endl << "Node Deleted!" << endl;
		size--;


	}







	/*	VectorNode<T>* NthNode(VectorNode<T> *nodePtr, int n)
	{
	int count = 1;

	//if count equal too n return node->data
	if (count == n)
	return nodePtr;

	//recursively decrease n and increase
	// head to next pointer


	return NthNode(nodePtr->next, n - 1);
	}
	*/
	VectorNodeVV<T>* GetNthNode(VectorNodeVV<T> *nodePtr, int num_child)
	{
		cout << endl << "Node returned!" << endl;
		return NthNode(head, num_child);
	}
	/*

	T GetNthValue(int n)
	{
	VectorNode<T> *temp= NthNode(head, n);
	return temp->data;
	}

	*/


	int getCount()
	{
		int count = 0;  // Initialize count 
		VectorNodeVV<T>* current = head;  // Initialize current 
		while (current != NULL)
		{
			count++;
			current = current->next;
		}
		//cout << endl << "Node count!" << endl;
		return count;
	}


	T GetNth(int index)
	{
		VECTOR<int> lol;
		if (index <= size)
		{
			VectorNodeVV<T>* current = head;
			int count = 0; /* the index of the node we're currently
						looking at */
			while (current != NULL)
			{
				if (count == index)
					return(current->data);
				count++;
				current = current->next;
			}
		}
		else
			return lol;

	}





	T operator[](int i)
	{
		return this->GetNth(i);
	}

	VECTORVV<T> operator=(VECTORVV<T>& rhs)
	{


		for (int i = 0; i < rhs.getCount(); i++)
		{
			this->createnode(rhs.GetNth(i));
		}
		return *this;
	}



};


#pragma once
