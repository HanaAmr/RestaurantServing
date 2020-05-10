#pragma once
#include "Generic_DS\LinkedList.h"
#include "Rest\Motorcycle.h"
#include "Rest\Order.h"
#include "Generic_DS\PriorityQueue.h"
#include "Generic_DS\Queue.h"
#include <iostream>
using namespace std;
#include <string>

class Region
{
private:
	int NormalMotorcyclesCount;
	int FrozenMotorcyclesCount;
	int VIPMotorcyclesCount;

	double AverageWaitingTime;
	double AverageServingTime;

	double AddWait;
	double AddServe;

	int regionTotalOrders;
	int regionTotalMotors;
public:
	Region();

	PriorityQueue<Order*> VIP_Queue;
	LinkedList<Order*> Normal_List;
	Queue<Order*> Frozen_Queue;

	LinkedList<Motorcycle*> VIP_Motorcycle;
	LinkedList<Motorcycle*> Normal_Motorcycle;
	LinkedList<Motorcycle*> Frozen_Motorcycle;

	LinkedList<Order*> VIP_Delivered;
	LinkedList<Order*> Frozen_Delivered;
	LinkedList<Order*> Normal_Delivered;

	Motorcycle* FirstVIPMoto(STATUS S,Order* Ord, int timestep, string& Assigningstring);
	Motorcycle* FirstFrozenMoto(STATUS S, Order* Ord, int timestep, string& Assigningstring);
	Motorcycle* FirstNormalMoto(STATUS S, Order* Ord, int timestep, string& Assigningstring);

	void setNormalOrdersCount(int);
	void setFrozenOrdersCount(int);
	void setVIPOrdersCount(int);

	void setNormalMotorcyclesCount(int n);
	void setFrozenMotorcyclesCount(int f);
	void setVIPMotorcyclesCount(int v);

	void setRegionTotalOrders();
	void setRegionTotalMotors();
	
	void SetAverageWaitingAndServingTime();
	
	int getNormalOrdersCount()const;
	int getFrozenOrdersCount()const;
	int getVIPOrdersCount()const;

	int getNormalMotorcyclesCount()const;
	int getFrozenMotorcyclesCount()const;
	int getVIPMotorcyclesCount()const;

	int getRegionTotalOrders()const;
	int getRegionTotalMotors()const;

	double getAverageWaitingTime() const;
	double getAverageServingTime() const;

	double getAddWait();
	double getAddServe();

	void UpdateMotorcycles(int timestep);
	
	bool ServeVIP(int timestep, string& Assigningstring);
	bool ServeFrozen(int timestep, string& Assigningstring);
	bool ServeNormal(int timestep, string& Assigningstring);

	void ServeALL(int timestep,string& Assigningstring);

	bool IsEmpty();
	void Promotion(Order* O);

	~Region();
};