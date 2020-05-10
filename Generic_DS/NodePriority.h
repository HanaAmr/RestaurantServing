#pragma once

template < typename T>
class NodePriority
{
	T item; // A data item
	int priority;
	NodePriority<T>* next;
public:
	NodePriority(const T & r_Item, int p);
	void setNext(NodePriority<T>* nextNodePtr);
	void setPriority(int p);
	void setItem(T data);
	NodePriority<T>* getNext() const;
	T getItem() const;
	int getpriority();
};

template < typename T>
NodePriority<T>::NodePriority(const T& r_Item, int p)
{
	item = r_Item;
	priority = p;
	next = nullptr;
}

template<typename T>
int NodePriority<T>::getpriority()
{
	return priority;
}

template<typename T>
void NodePriority<T>::setNext(NodePriority<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
NodePriority<T>* NodePriority<T>::getNext() const
{
	return next;
}

template < typename T>
T NodePriority<T>::getItem() const
{
	return item;
}

template < typename T>
void NodePriority<T>::setItem(T data)
{
	item = data;
}

template < typename T>
void NodePriority<T>::setPriority(int p)
{
	priority = p;
}