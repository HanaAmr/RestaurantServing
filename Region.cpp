#include "Region.h"

Region::Region()
{
	NormalMotorcyclesCount=0;
	FrozenMotorcyclesCount=0;
	VIPMotorcyclesCount=0;

	AverageWaitingTime = 0;
	AverageServingTime = 0;

	AddWait = 0;
	AddServe = 0;
}

void Region::setNormalOrdersCount(int N)
{
	Normal_List.setCount(N);
}

void Region::setFrozenOrdersCount(int F)
{
	Frozen_Queue.count = F;
}

void Region::setVIPOrdersCount(int V)
{
	VIP_Queue.count = V;
}

int Region::getNormalOrdersCount()const
{
	return Normal_List.getCount();
}

int Region::getFrozenOrdersCount()const
{
	return Frozen_Queue.count;
}

int Region::getVIPOrdersCount()const
{
	return VIP_Queue.count;
}

int Region::getNormalMotorcyclesCount()const
{
	return Normal_Motorcycle.getCount();
}

int Region::getFrozenMotorcyclesCount()const
{
	return Frozen_Motorcycle.getCount();
}

int Region::getVIPMotorcyclesCount()const
{
	return VIP_Motorcycle.getCount();
}

void Region::setNormalMotorcyclesCount(int n)
{
	NormalMotorcyclesCount = n;
}

void Region::setFrozenMotorcyclesCount(int f)
{
	FrozenMotorcyclesCount = f;
}

void Region::setVIPMotorcyclesCount(int v)
{
	VIPMotorcyclesCount = v;
}

void Region::setRegionTotalMotors()
{
	regionTotalMotors=FrozenMotorcyclesCount+NormalMotorcyclesCount+VIPMotorcyclesCount;
}

void Region::setRegionTotalOrders()
{	
	regionTotalOrders=Frozen_Delivered.getCount()+Normal_Delivered.getCount()+VIP_Delivered.getCount();
}

int Region::getRegionTotalMotors()const
{
	return regionTotalMotors;
}

int Region::getRegionTotalOrders()const
{
	return regionTotalOrders;
}

Motorcycle * Region::FirstVIPMoto(STATUS S, Order* Ord, int timestep,string& Assigningstring)
{
	Motorcycle** VIPMotoArray = VIP_Motorcycle.toArray();
	

	for (int i = 0; i < VIPMotorcyclesCount; i++)
	{
		if (VIPMotoArray[i]->getstatus() == S)
		{
			VIPMotoArray[i]->switchto_In_Service();

			Ord->setServTime(VIPMotoArray[i]->getspeed());
			Ord->setWaitingTime(timestep);
			Ord->setFinishTime();

			string OrdType;
			if (Ord->GetType() == TYPE_VIP)
				OrdType = "V";
			else if (Ord->GetType() == TYPE_FROZ)
				OrdType = "F";
			else
				OrdType = "N";

			std::string IDOrd = std::to_string(Ord->GetID());
			std::string IDMoto = std::to_string(VIPMotoArray[i]->getID());

			Assigningstring += "V" + IDMoto + "(" + OrdType + IDOrd + ")  ";

			VIPMotoArray[i]->setrestingtime(Ord->getFinishTime() + Ord->getServTime());

			if (S == REST)
				VIPMotoArray[i]->DecrementHealth();
			return VIPMotoArray[i];
		}
	}
	return NULL;
}

Motorcycle * Region::FirstFrozenMoto(STATUS S, Order* Ord, int timestep, string& Assigningstring)
{
	Motorcycle** FrozenMotoArray = Frozen_Motorcycle.toArray();
	

	for (int i = 0; i < FrozenMotorcyclesCount; i++)
	{
		if (FrozenMotoArray[i]->getstatus() == S)
		{
			FrozenMotoArray[i]->switchto_In_Service();
			Ord->setServTime(FrozenMotoArray[i]->getspeed());
			Ord->setWaitingTime(timestep);
			Ord->setFinishTime();

			string OrdType;
			if (Ord->GetType() == TYPE_VIP)
				OrdType = "V";
			else if (Ord->GetType() == TYPE_FROZ)
				OrdType = "F";
			else
				OrdType = "N";

			std::string IDOrd = std::to_string(Ord->GetID());
			std::string IDMoto = std::to_string(FrozenMotoArray[i]->getID());

			Assigningstring += "F" + IDMoto + "(" + OrdType + IDOrd + ")  ";

			FrozenMotoArray[i]->setrestingtime(Ord->getFinishTime() + Ord->getServTime());
			if (S == REST)
				FrozenMotoArray[i]->DecrementHealth();
			return FrozenMotoArray[i];
		}
	}
	return NULL;
}

Motorcycle * Region::FirstNormalMoto(STATUS S, Order* Ord, int timestep, string& Assigningstring)
{
	Motorcycle** NormalMotoArray = Normal_Motorcycle.toArray();
	

	for (int i = 0; i < NormalMotorcyclesCount; i++)
	{
		if (NormalMotoArray[i]->getstatus() == S)
		{
			NormalMotoArray[i]->switchto_In_Service();
			Ord->setServTime(NormalMotoArray[i]->getspeed());
			Ord->setWaitingTime(timestep);
			Ord->setFinishTime();

			string OrdType;
			if (Ord->GetType() == TYPE_VIP)
				OrdType = "V";
			else if (Ord->GetType() == TYPE_FROZ)
				OrdType = "F";
			else
				OrdType = "N";

			std::string IDOrd = std::to_string(Ord->GetID());
			std::string IDMoto = std::to_string(NormalMotoArray[i]->getID());

			Assigningstring += "N" + IDMoto + "(" + OrdType + IDOrd + ")  ";

			NormalMotoArray[i]->setrestingtime(Ord->getFinishTime()+Ord->getServTime());
			if (S == REST)
				NormalMotoArray[i]->DecrementHealth();
			return NormalMotoArray[i];
		}
	}
	return NULL;
}

void Region::UpdateMotorcycles(int timestep)
{
	Motorcycle** NormalMotoArray = Normal_Motorcycle.toArray();
	

	for (int i = 0; i < NormalMotorcyclesCount; i++)
	{
		NormalMotoArray[i]->UpdateStatus(timestep);
	}

	Motorcycle** FrozenMotoArray = Frozen_Motorcycle.toArray();
	
	for (int i = 0; i < FrozenMotorcyclesCount; i++)
	{
		FrozenMotoArray[i]->UpdateStatus(timestep);
	}

	Motorcycle** VIPMotoArray = VIP_Motorcycle.toArray();

	for (int i = 0; i < VIPMotorcyclesCount; i++)
	{
		VIPMotoArray[i]->UpdateStatus(timestep);
	}
}

bool Region::ServeVIP(int timestep, string& Assigningstring)
{
	
	bool a = true;
	Motorcycle* ServingMoto;
	Order* ToServe=NULL;
	while (!VIP_Queue.isEmpty())
	{
		VIP_Queue.peekFront(ToServe);
		ServingMoto = FirstVIPMoto(IDLE,ToServe, timestep, Assigningstring);
		if (!ServingMoto)
		{
			ServingMoto = FirstNormalMoto(IDLE, ToServe, timestep, Assigningstring);
			if (!ServingMoto)
			{
				ServingMoto = FirstFrozenMoto(IDLE, ToServe, timestep, Assigningstring);
				if (!ServingMoto)
				{
					ServingMoto = FirstVIPMoto(REST, ToServe, timestep, Assigningstring);
					if (!ServingMoto)
					{
						ServingMoto = FirstNormalMoto(REST, ToServe, timestep, Assigningstring);
						if (!ServingMoto)
						{
							ServingMoto = FirstFrozenMoto(REST, ToServe, timestep, Assigningstring);
							if (!ServingMoto)
							{
								a = false;
								break;
							}
						}
					}
				}
			}
		}
		if (a == true)
		{
			VIP_Queue.dequeue(ToServe);
			VIP_Delivered.InsertSorted(ToServe);
		}
	}
	return a;
}

bool Region::ServeFrozen(int timestep, string& Assigningstring)
{
	bool a = true;
	Motorcycle* ServingMoto;
	Order* ToServe = NULL;
	while (!Frozen_Queue.isEmpty())
	{
		Frozen_Queue.peekFront(ToServe);
		ServingMoto = FirstFrozenMoto(IDLE, ToServe, timestep, Assigningstring);
		if (!ServingMoto)
		{
			ServingMoto = FirstFrozenMoto(REST, ToServe, timestep, Assigningstring);
			if (!ServingMoto)
			{
				a = false;
				break;
			}
		}
		if (a == true)
		{
			Frozen_Queue.dequeue(ToServe);
			Frozen_Delivered.InsertSorted(ToServe);
		}
	}
	return a;
}

bool Region::ServeNormal(int timestep, string& Assigningstring)
{
	bool a = true;
	Motorcycle* ServingMoto;
	Order* ToServe = NULL;
	while (!Normal_List.IsEmpty())
	{
		Order* ToServe = Normal_List.ReturnFirst();
		ServingMoto = FirstNormalMoto(IDLE, ToServe, timestep, Assigningstring);
		if (!ServingMoto)
		{
			ServingMoto = FirstVIPMoto(IDLE, ToServe, timestep, Assigningstring);
			if (!ServingMoto)
			{
				ServingMoto = FirstNormalMoto(REST, ToServe, timestep, Assigningstring);
				if (!ServingMoto)
				{
					ServingMoto = FirstVIPMoto(REST, ToServe, timestep, Assigningstring);
					if (!ServingMoto)
					{
						a = false;
						break;
					}
				}
			}
		}
		if (a == true)
		{
			Normal_List.DeleteBeg(ToServe);
			Normal_Delivered.InsertSorted(ToServe);
		}

	}
	return a;
}

void Region::ServeALL(int timestep, string& Assigningstring)
{
	string VIP="";
	string F="";
	string N="";
	UpdateMotorcycles(timestep);
	bool a = ServeVIP(timestep, VIP);
	if (a)
	{
		ServeFrozen(timestep, F);
		ServeNormal(timestep, N);
	}
	Assigningstring = " " + VIP + " " + F + " " + N;
}

bool Region::IsEmpty()
{
	return (Normal_List.getCount()+Frozen_Queue.count+VIP_Queue.count==0);
}

//function responsible for the promotion of a single region
//it's then called for all regions in Restaurant
void Region::Promotion(Order* O)
{				
	Normal_List.DeleteNodeAt(O);
	O->setVIPpriority();
	double priority = O->getVIPpriority();
	VIP_Queue.enqueue(O, priority);
	O->setType(TYPE_VIP);
}

//function resposible for getting the average waiting and serving time
void Region::SetAverageWaitingAndServingTime()
{
	int countOrders=Normal_Delivered.getCount()+Frozen_Delivered.getCount()+VIP_Delivered.getCount();

	Order** NormalOrderArray = Normal_Delivered.toArray();
	for (int i = 0; i < Normal_Delivered.getCount(); i++)
	{
		AddWait += NormalOrderArray[i]->getWaitingTime();
		AddServe += NormalOrderArray[i]->getServTime();
	}

	Order** FrozenOrderArray = Frozen_Delivered.toArray();
	for (int i = 0; i < Frozen_Delivered.getCount(); i++)
	{
		AddWait += FrozenOrderArray[i]->getWaitingTime();
		AddServe += FrozenOrderArray[i]->getServTime();
	}

	Order** VIPOrderArray = VIP_Delivered.toArray();
	for (int i = 0; i < VIP_Delivered.getCount(); i++)
	{
		AddWait += VIPOrderArray[i]->getWaitingTime();
		AddServe += VIPOrderArray[i]->getServTime();
	}

	if (countOrders==0)
	{
		AverageServingTime=AverageWaitingTime=0;
	}
	else
	{
	AverageServingTime=AddServe/countOrders;
	AverageWaitingTime=AddWait/countOrders;
	}
}

double Region::getAverageWaitingTime() const
{
	return AverageWaitingTime;
}

double Region::getAverageServingTime() const
{
	return AverageServingTime;
}

double Region::getAddWait()
{
	return AddWait;
}

double Region::getAddServe()
{
	return AddServe;
}

Region::~Region()
{
}