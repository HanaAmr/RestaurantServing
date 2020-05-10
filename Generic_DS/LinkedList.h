#pragma once
#ifndef _LINKEDLIST
#define _LINKEDLIST
#include <iostream>
using namespace std;

#include "Node.h"
template<typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	int count;	//Number of nodes in the list
public:
	LinkedList();
	~LinkedList();
	void setCount(int c);
	int getCount()const;
	void InsertEnd(T data);	
	void InsertBeg(T data);	//inserts a new node at list head
	Node<T>* GetNodeAt(T data);
	bool DeleteNodeAt(T value);
	bool IsEmpty();
	T * toArray() const;
	bool DeleteBeg(T& value);
	void InsertSorted(T value);
	T ReturnFirst();
};

template<typename T>
bool LinkedList<T>::IsEmpty()
{
	return (Head == NULL);
}

template<typename T>
LinkedList<T>::LinkedList()
{
	count = 0;
	Head = NULL;
}

template<typename T>
//List is being desturcted ==> delete all items in the list
LinkedList<T>::~LinkedList()
{}

template<typename  T>
void LinkedList<T>::setCount(int c)
{
	count=(c>0)?c:0;
}

template<typename T>
int LinkedList<T>::getCount()const
{
	return count;
}

template<typename T>
void LinkedList<T>::InsertEnd(T data)
{
	Node<T>* n= new Node<T>(data);
	
	if(!Head)
	{	
		Head=n;
		count++;
		return;
	}

	Node<T> * temp= Head;

	while(temp->getNext())
	{
		temp=temp->getNext();
	}
	temp->setNext(n);
	n->setNext(NULL);
	count++;
}

template<typename T>
void LinkedList<T>::InsertBeg(T data)
{
	Node<T> *R = new Node<T>(data);
	R->setNext(Head);
	Head = R;
	count++;

}

template<typename T>
Node<T>* LinkedList<T>:: GetNodeAt(T data)
{
	Node<T>*temp= Head;
	if(temp==NULL) // no elements in the list
	{return NULL;}
	
	if(temp->getNext()==NULL)//One element in the list
	{
		if(temp->getItem()==data)
		{   return temp;	}	
		else 
		{	return NULL;}
	}

	while(temp)
	{
		if(temp->getItem()==data)
		{
			return temp;
		}
		else
			temp=temp->getNext();
	}
	return NULL;
}

template<typename T>
bool LinkedList<T>:: DeleteNodeAt(T value)
{
	Node<T>*temp=Head;
	if(temp)
	{
		Node<T>*del= GetNodeAt(value);
		if(!del)
			return false;

		if(temp==del)//Found at first node
		{
			Head=Head->getNext();
			delete temp;
			temp=NULL;
			count--;
			return true;
		}
		else
		{
			while(temp->getNext()!=del)
			{
				temp=temp->getNext();
			}
			temp->setNext(del->getNext());
			delete del;
			del=NULL;
			count--;
			return true;
		}
	}
	return false;
}

template < typename T>
 T * LinkedList<T>::toArray() const
{
	T * bagContents = new  T [count];
	Node<T>* curPtr = Head;
	int counter = 0;
	while ((curPtr != NULL) && (counter < count))
	{
		bagContents[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} 
	return bagContents;
} 

 template < typename T>
 bool LinkedList<T>::DeleteBeg(T& value)
 {
	 if (IsEmpty())
		 return false;
	 Node<T>* temp = Head;
	 Head = Head->getNext();
	 value = temp->getItem();
	 count--;
	 delete temp;
	 return true;
 }

 template<typename T>
 void LinkedList<T>::InsertSorted(T value)
 {
	 if (Head == NULL)
	 {
		 InsertBeg(value);
		 return;
	 }
	 if (Head->getNext() == NULL)
	 {
		 if (*(Head->getItem()) <= value)
			 InsertBeg(value);
		 if (*(Head->getItem()) > value)
			 InsertEnd(value);
		 return;
	 }
	 if (*(Head->getItem()) <= value)
	 {
		 InsertBeg(value);
		 return;
	 }
	 Node<T>*before = Head;
	 Node<T>*after = Head->getNext();
	 while (after)
	 {
		 if (*(before->getItem()) >= value && *(after->getItem()) <= value)
			 break;
		 before = before->getNext();
		 after = after->getNext();
	 }
	 Node<T>* add = new Node<T>(value);
	 add->setNext(after);
	 before->setNext(add);
	 count++;
 }

 template<typename T>
 T LinkedList<T>::ReturnFirst()
 {
	 return Head->getItem();
 }

#endif	