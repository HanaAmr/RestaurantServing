#pragma once
#include"Event.h"
#include "..\Rest\Restaurant.h"
#include "..\Generic_DS\Node.h"
#include "..\Generic_DS\LinkedList.h"

class PromotionEvent :public Event
{
private:
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	 
	int ExtraMoney;
	int TS;
	int Id;
	int N; //the number of timesteps that the order can wait before being automatically promoted
public:
	PromotionEvent(int arrivaltime, int id, double extramoney);
	virtual void Execute(Restaurant *pRes);
	~PromotionEvent();
};