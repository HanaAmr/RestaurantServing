#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, int dist, double money):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance = dist;
	OrdMoney = money;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
		Order* pOrd = new Order(EventTime,OrderID,OrdType,OrdRegion,OrdDistance,OrdMoney);
		if (OrdType==TYPE_NRM)
		{
			pRest->R[(int)OrdRegion].Normal_List.InsertEnd(pOrd);
		}
		else if (OrdType==TYPE_FROZ)
		{
			pRest->R[(int)OrdRegion].Frozen_Queue.enqueue(pOrd);
		}
		else
		{
			pRest->R[(int)OrdRegion].VIP_Queue.enqueue(pOrd,pOrd->getpriority());
		}
		pRest->ActiveOrders.InsertEnd(pOrd);
}