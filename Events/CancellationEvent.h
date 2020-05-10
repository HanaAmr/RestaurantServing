#ifndef __CANCELLATION_EVENT_H_
#define __CANCELLATION_EVENT_H_

#include "Event.h"
#include "..\Rest\Restaurant.h"

#include "..\Generic_DS\Node.h"
#include "..\Generic_DS\LinkedList.h"

class CancellationEvent: public Event
{
	//info about the order ralted to arrival event
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	 
	int TS;
	int Id;
public:
	CancellationEvent(int eTime, int oID); 
	virtual void Execute(Restaurant *pRes);
	Order* getOrder(Restaurant *pRes);
};

#endif