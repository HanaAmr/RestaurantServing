#include "..\Events\PromotionEvent.h"

PromotionEvent::PromotionEvent(int arrivaltime, int id, double extramoney):Event(arrivaltime,id)
{
	TS = arrivaltime;
	Id = id;
	ExtraMoney = extramoney;
}

//Function resposibile for the execution of the promotion event.
void PromotionEvent::Execute(Restaurant *pRest) 
{
	Order* promoted = pRest->getOrder(Id);
	//getting the order at a specific timestep.

	if (promoted) //checking if the order is Found
	{
	OrdRegion = promoted->GetRegion(); //getting the order region: A, B, C or D
	OrdType = TYPE_NRM; //setting the data member OrdType to "Normal"
	pRest->PromoteOrder(promoted); //calling the function PromoteOrder in Restaurant
	promoted->setTotalMoney(promoted->getTotalMoney() + ExtraMoney); //adding the extra money to be paid by the customer to the total
	//money of the order
	}
}

PromotionEvent::~PromotionEvent()
{}