#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"
#include <cmath>

class Order
{
protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant              
	double totalMoney;	//Total order money
	int ArrTime, ServTime, FinishTime,WaitingTime;	//arrival, service start, and finish times
	double priority;       // indication to priority the higher the number the faster you should serve
public:
	Order(int at,int ID, ORD_TYPE r_Type, REGION r_region,int dist, double money);
	int GetID();
	int GetArrTime();
	int GetWaitingTime();
	ORD_TYPE GetType() const;
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;
	double getpriority();

	void setServTime(int speed);
	int getServTime();

	void setWaitingTime(int Assigningtimestep);
	int getWaitingTime();

	void setFinishTime();
	int getFinishTime()const;

	bool operator>(Order*& O)const;
	bool operator<(Order*&O)const;
	bool operator<=(Order*&O)const;
	bool operator>=(Order*&O)const;

	double setVIPpriority();    // function that calculates the priority of the VIP order according to its arrival time, money  and distance
	void setTotalMoney(double);
	double getTotalMoney() const;
	void setType(ORD_TYPE ord);
	double getVIPpriority();

	virtual ~Order();
};

#endif