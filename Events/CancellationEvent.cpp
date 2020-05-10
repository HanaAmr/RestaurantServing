#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int eTime, int oID):Event(eTime, oID)
{
	TS=eTime;
	Id=oID;
}

Order* CancellationEvent::getOrder(Restaurant *pRes)
{
	Order* Cancelled = NULL;

	for (int i = 0; i < 4; i++)
	{
		if (!pRes->R[i].Normal_List.IsEmpty())
		{
			Order** ArrayNormal;
			ArrayNormal = pRes->R[i].Normal_List.toArray();
			int count = pRes->R[i].Normal_List.getCount();
			for (int j = 0; j < count; j++)
			{
				if (ArrayNormal[j]->GetID() == Id)
				{
					Cancelled = ArrayNormal[j];
					OrdRegion = (REGION)i;
					OrdType = TYPE_NRM;
				}
			}
		}
	}
	return Cancelled;
}

void CancellationEvent::Execute(Restaurant *pRes)
{
	Order*Cancelled = NULL;
	Cancelled=getOrder(pRes);
	if (Cancelled)
	{
		if ( TS >= Cancelled->GetArrTime()  + Cancelled->GetWaitingTime())
		 {
			 Event* e=NULL;
			 pRes->R[(int)OrdRegion].Normal_List.DeleteNodeAt(Cancelled);
			 pRes->ActiveOrders.DeleteNodeAt(Cancelled);
		 }
	}	 
}