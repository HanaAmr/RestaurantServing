#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\LinkedList.h"
#include "Motorcycle.h"
#include "..\Events\Event.h"
#include "..\Region.h"
#include "..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include "Order.h"
#include <fstream>
// it is the maestro of the project

class Restaurant  
{	
private:
	GUI *pGUI;
	int Num_Events;
	int Promotion_Limit;
	string AssigningString[4];

	double AverageTotalWaitingTime;
	double AverageTotalServingTime;
	LinkedList<Order*> TotalDeliveredOrders;
	
	int totalMotors;
	int totalNumOfOrders;
	int totalNormOrders;
	int totalVIPOrders;
	int totalFrozenOrders;
	int totalNormMotors;
	int totalFrozMotors;
	int totalVIPMotors;
public:
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	LinkedList<Order*> ActiveOrders;

	Region R[4];
	
	Restaurant();
	~Restaurant();

	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void DrawOrders();
	void ServeAllRegions(int timestep);

	void LoadInputFile();
	void Save();
	void PromoteOrder(Order* O);
	void autoPromote(int timestep);
	
	void FillDeliveredOrdersList();
	void setTotalNoOfOrders();

	void setTotalNormOrders();
	void setTotalVIPOrders();
	void setTotalFrozenOrders();
	void setTotalNormMotors();
	void setTotalFrozMotors();
	void setTotalVIPMotors();
	void setTotalMotors();

	void SimulationInterractive();
	void simulationStep();
	void simulationSilent();

	Order* getOrder(int ID);
	bool AllServed();
	void PrintStatus(int CurrentTimeStep);
	void setstatistics();
};

#endif