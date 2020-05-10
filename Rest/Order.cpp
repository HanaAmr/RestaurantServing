#include "Order.h"

//setting the VIP Priority equation assuming that the money has the highest priority as this is a prifitable business,
//and the distance has the least priority
double Order::setVIPpriority()
{
	priority = totalMoney * 4 + ArrTime * 3 + Distance * 1;
	return priority;
}

Order::Order(int at, int id, ORD_TYPE r_Type, REGION r_region, int dist, double money)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	ArrTime = at;
	Region = r_region;
	Distance = dist;
	totalMoney = money;
	if (type == TYPE_NRM || type == TYPE_FROZ)
		priority = 0;
	else
		priority = setVIPpriority();
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}

ORD_TYPE Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{

	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

double Order::getpriority()
{
	return priority;
}

void Order::setFinishTime()
{
	FinishTime = ArrTime + ServTime + WaitingTime;
}

int Order::getFinishTime() const
{
	return FinishTime;
}

void Order::setServTime(int speed)
{
	ServTime = ceil((double)Distance / speed);
}

int Order::getServTime()
{
	return ServTime;
}

void Order::setWaitingTime(int Assigningtimestep)
{
	WaitingTime = Assigningtimestep - ArrTime;
}

int Order::getWaitingTime()
{
	return WaitingTime;
}

bool Order::operator>(Order*& O)const
{
	return (FinishTime > (*O).FinishTime);
}

bool Order::operator<(Order*& O)const
{
	return (FinishTime < (*O).FinishTime);
}

bool Order::operator<=(Order*& O)const
{
	if (FinishTime == (*O).FinishTime)
	{
		return(ServTime <= (*O).ServTime);
	}
	return (FinishTime <= (*O).FinishTime);
}

bool Order::operator>=(Order*& O)const
{
	if (FinishTime == (*O).FinishTime)
	{
		return(ServTime >= (*O).ServTime);
	}
	return (FinishTime >= (*O).FinishTime);
}

int Order::GetArrTime()
{

	return ArrTime;
}

int Order::GetWaitingTime()
{
	return WaitingTime;
}

double Order::getTotalMoney() const
{
	return totalMoney;
}
void Order::setType(ORD_TYPE ord)
{
	type = ord;
}

void Order::setTotalMoney(double money)
{
	totalMoney = money;
}

double Order::getVIPpriority()
{
	return setVIPpriority();
}