using namespace std; 
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Defs.h"

Restaurant::Restaurant() //default constructor
{
	pGUI = NULL;

	for (int i = 0; i < 4; i++)
	{
		AssigningString[i] = "";
	}

	AverageTotalServingTime=0;
	AverageTotalWaitingTime=0;
	
	totalNumOfOrders=0;
	totalNormOrders=0;
	totalVIPOrders=0;
	totalFrozenOrders=0;
	totalNormMotors=0;
	totalFrozMotors=0;
	totalVIPMotors=0;
	totalMotors=0;
}

//The main similation function, it runs the suitable Similation function according to the user's choice at the program start.
void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		SimulationInterractive();
		break;
	case MODE_STEP:
		simulationStep();
		break;
	case MODE_SLNT:
		simulationSilent();
		break;
	};
}

//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
}

void Restaurant::LoadInputFile() //Input Loading Function
{
	pGUI->PrintMessage("Enter the name of the file you want to load");
	string filename = pGUI->GetString();
	ifstream f(filename+".txt");

	if (f.is_open())
	{
		int speed_Normal, speed_Frozen, speed_VIP;
		f >> speed_Normal >> speed_Frozen >> speed_VIP;

		REGION r[4] = { A_REG , B_REG , C_REG , D_REG };
		for (int i = 0; i < 4; i++)
		{
			int NormalCount, FrozenCount, VIPCount;
			f >> NormalCount >> FrozenCount >> VIPCount;
			for (int j = 0; j < NormalCount; j++)
			{
				Motorcycle *n=new Motorcycle(TYPE_NRM, speed_Normal,r[i]);
				R[i].Normal_Motorcycle.InsertBeg(n);
			}
			for (int k = 0; k < FrozenCount; k++)
			{
				Motorcycle *f = new Motorcycle(TYPE_FROZ, speed_Frozen, r[i]);
				R[i].Frozen_Motorcycle.InsertBeg(f);
			}
			for (int l = 0; l < VIPCount; l++)
			{
			Motorcycle *v = new Motorcycle(TYPE_VIP, speed_VIP, r[i]);
				R[i].VIP_Motorcycle.InsertBeg(v);
			}
			R[i].setFrozenMotorcyclesCount(FrozenCount);
			R[i].setNormalMotorcyclesCount(NormalCount);
			R[i].setVIPMotorcyclesCount(VIPCount);
		}

		f >> Promotion_Limit;
		f >> Num_Events;

		for (int i=0; i<Num_Events;i++)
		{
			char type; 
			f>>type;		
			if (type=='R')
				{
					int arrivaltime,id,dist;
					double money;
					char region;
					char typeoforder;
					ORD_TYPE a;
					REGION r;
					f>>arrivaltime;  f>>typeoforder ; f>>id; f>>dist; f>>money; f>>region;
					if (region=='A')
						r=A_REG;
					else if (region=='B')
						r=B_REG;
					else if (region=='C')
						r=C_REG;
					else if (region=='D')
						r=D_REG;

					if (typeoforder=='N')
					{
						 a=TYPE_NRM;
					}
					else if(typeoforder=='V')
					{
						 a=TYPE_VIP;
					}
					else if(typeoforder=='F')
					{
						 a=TYPE_FROZ;
					}
		
			Event *NewEvent= new ArrivalEvent(arrivaltime,id,a,r,dist,money);
			AddEvent(NewEvent);

		}
		else if(type=='X')
		{
			int arrivaltime,id;
			f>> arrivaltime>>id;
			Event *NewEvent= new CancellationEvent(arrivaltime,id);
			AddEvent(NewEvent);
		}
		else if(type=='P')
		{
			//Create a promotion event and add it to the queue of Events
			int arrivaltime,id,extramoney;
			f>> arrivaltime>>id>>extramoney;
			Event*NewEvent=new PromotionEvent( arrivaltime,id,extramoney);
			AddEvent(NewEvent);
		}
	}
  }	
      f.close();
}

//function that gets the statistics of the Restaurant
void Restaurant::setstatistics()
{
	double AddAvgWait=0;
	double AddAvgServe=0;
	for (int i=0;i<4;i++)
	{
		AddAvgWait += R[i].getAddWait();
		AddAvgServe += R[i].getAddServe();
	}
	AverageTotalServingTime=AddAvgServe/totalNumOfOrders;
	AverageTotalWaitingTime=AddAvgWait/totalNumOfOrders;
}

//Function resposible for the output file
void Restaurant::Save()
{
	pGUI->PrintMessage("Enter the name of the file you want to save in");
	string Filename=pGUI->GetString();
	ofstream OutFile(Filename+".txt", ios::out);

	if (OutFile.is_open())
	{
		OutFile << "FT"<<"\t"<<"ID" << "\t" << "AT" << "\t" << "WT"<<"\t"<<"ST"<< endl;

		FillDeliveredOrdersList();
		Order** delivered=TotalDeliveredOrders.toArray();
		setTotalNoOfOrders();
		for(int i=totalNumOfOrders-1;i>=0;i--)
		{
			OutFile<<delivered[i]->getFinishTime()<<"\t"<<delivered[i]->GetID()<<"\t"<<delivered[i]->GetArrTime()<<"\t";
			OutFile<<delivered[i]->GetWaitingTime()<<"\t"<<delivered[i]->getServTime()<<endl;
		}
		OutFile<<"............................................."<<endl;
		OutFile<<"............................................."<<endl;
		string p;

		for (int i = 0; i < 4; i++) //To output region name
		{
			if (i == 0)
				p = "A";
			else if (i == 1)
				p = "B";
			else if (i == 2)
				p = "C";
			else
				p = "D";
			
			OutFile<<"Region "<<p<<":"<<endl;

			R[i].SetAverageWaitingAndServingTime();

			setstatistics();
			
			//Printing the data of each region
			R[i].setRegionTotalOrders();
			R[i].setRegionTotalMotors();

			OutFile<<"Orders: "<<R[i].getRegionTotalOrders()<<" "<<"["<<"Norm: "<<R[i].Normal_Delivered.getCount();
			OutFile<<", Froz: "<<R[i].Frozen_Delivered.getCount()<<", VIP "<<R[i].VIP_Delivered.getCount()<<"]"<<endl;

			OutFile<<"MotorC: "<<R[i].getRegionTotalMotors()<<" "<<"["<<"Norm: "<<R[i].getNormalMotorcyclesCount();
			OutFile<<", Froz: "<<R[i].getFrozenMotorcyclesCount()<<", VIP "<<R[i].getVIPMotorcyclesCount()<<"]"<<endl;

			OutFile<<"Avg Wait= "<<R[i].getAverageWaitingTime()<<"\t"<<", Avg Serv=  "<<R[i].getAverageServingTime()<<endl;

			cout<<endl;
		}

		setTotalNormOrders();
		setTotalVIPOrders();
		setTotalFrozenOrders();
		setTotalNormMotors();
		setTotalFrozMotors();
		setTotalVIPMotors();
		setTotalMotors();

		OutFile<<"Restaurant Data: "<<endl;

		OutFile<<"Orders: "<<totalNumOfOrders<<"\t"<<"["<<"Norm: "<<totalNormOrders;
		OutFile<<", Froz: "<<totalFrozenOrders<<", VIP "<<totalVIPOrders<<"]"<<endl;

		OutFile<<"MotorC: "<<totalMotors<<"\t"<<"["<<"Norm: "<<totalNormMotors;
		OutFile<<", Froz: "<<totalFrozMotors<<", VIP "<<totalVIPMotors<<"]"<<endl;

		OutFile<<"Avg Wait="<<AverageTotalWaitingTime<<"\t"<<"Avg Serv=  "<<AverageTotalServingTime<<endl;
	}
	OutFile.close();
}

//function resposible for drawing the orders onto the screen
void Restaurant::DrawOrders()
{
	for (int i = 0; i < 4; i++)
	{
		PriorityQueue<Order*> AuxillaryQueue;
		Order*temp=NULL;
		while (R[i].VIP_Queue.dequeue(temp))
		{
			pGUI->AddOrderForDrawing(temp);
			pGUI->UpdateInterface();
			AuxillaryQueue.enqueue(temp,temp->getpriority());
		}

		while (AuxillaryQueue.dequeue(temp))
		{
			R[i].VIP_Queue.enqueue(temp,temp->getpriority());
		}
			
		Queue<Order*> Auxillary2;
		while (R[i].Frozen_Queue.dequeue(temp))
		{
			pGUI->AddOrderForDrawing(temp);
			pGUI->UpdateInterface();
			Auxillary2.enqueue(temp);
		}

		while (Auxillary2.dequeue(temp))
		{
			R[i].Frozen_Queue.enqueue(temp);
		}

		Order** ArrayNormalOrder = R[i].Normal_List.toArray();
		int countNormal = R[i].getNormalOrdersCount();

		for (int i = 0; i < countNormal; i++)
		{
			pGUI->AddOrderForDrawing(ArrayNormalOrder[i]);
			pGUI->UpdateInterface();
		}
	}
}

//function resposible for serving the orders in all regions
void Restaurant::ServeAllRegions(int timestep)
{
	for (int i = 0; i < 4; i++)
	{
		AssigningString[i] = "";
		R[i].ServeALL(timestep,AssigningString[i]);
	}
}

//function resposible for promoting the orders according to the user's choice
void Restaurant::PromoteOrder(Order*O) 
{
	if (O != NULL)
	{
		R[(int)O->GetRegion()].Promotion(O);
	}
}

//function responsible for the auto-promotion of orders if they'd been waiting for too long
void Restaurant::autoPromote(int timestep)
{
	for (int i = 0; i < 4; i++)
	{
		Order** A = R[i].Normal_List.toArray();
		int count = R[i].Normal_List.getCount();
		for (int j = 0; j < count; j++)
		{
			if (timestep - A[j]->GetArrTime() >= Promotion_Limit)
			{
				PromoteOrder(A[j]);
			}
		}
	}
}

//function responsible for finding the delivered orders, and filling it in the list of delivered orders 
void  Restaurant::FillDeliveredOrdersList()
{
	for (int i=0 ; i<4 ; i++)
	{
		Order** FDel=R[i].Frozen_Delivered.toArray();
		for(int j=0 ; j<R[i].Frozen_Delivered.getCount();j++)
		{
			TotalDeliveredOrders.InsertSorted(FDel[j]);
		}

		Order** NDel=R[i].Normal_Delivered.toArray();
		for(int j=0 ; j<R[i].Normal_Delivered.getCount();j++)
		{
			TotalDeliveredOrders.InsertSorted(NDel[j]);
		}
		
		Order** VDel=R[i].VIP_Delivered.toArray();
		for(int j=0 ; j<R[i].VIP_Delivered.getCount();j++)
		{
			TotalDeliveredOrders.InsertSorted(VDel[j]);
		}

	}
}

//function resposible for getting the order at the current timestep
Order* Restaurant::getOrder(int ID)
{
	Order* O = NULL;

	for (int i = 0; i < 4; i++)
	{
		if (!(R[i].Normal_List.IsEmpty()))
		{
			Order** ArrayNormal= R[i].Normal_List.toArray();
			int count = R[i].Normal_List.getCount();
			for (int j = 0; j < count; j++)
			{
				if (ArrayNormal[j]->GetID() == ID)
				{
					O = ArrayNormal[j];
				}
			}
		}
	}
	return O;
}

//function resposible for checking whether all the orders are already served or not
bool Restaurant::AllServed()
{
	bool a = true;
	for (int i=0 ; i<4 ; i++)
	{
		a = R[i].IsEmpty();
		if (!a)
			return false;
	}
	return true;
}

//function responsible for prinitng the imformation required in the status bar
void Restaurant::PrintStatus(int CurrentTimeStep)
{
	string r;
	string Reg[4];

	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
			r = "A";
		else if (i == 1)
			r = "B";
		else if (i == 2)
			r = "C";
		else
			r = "D";

		std::string v = std::to_string(R[i].getVIPOrdersCount());
		std::string n = std::to_string(R[i].getNormalOrdersCount());
		std::string f = std::to_string(R[i].getFrozenOrdersCount());
		std::string mv = std::to_string(R[i].getVIPMotorcyclesCount());
		std::string mn = std::to_string(R[i].getNormalMotorcyclesCount());
		std::string mf = std::to_string(R[i].getFrozenMotorcyclesCount());
		std::string dv = std::to_string(R[i].VIP_Delivered.getCount());
		std::string df = std::to_string(R[i].Frozen_Delivered.getCount());
		std::string dn = std::to_string(R[i].Normal_Delivered.getCount());


		Reg[i] = "   Region " + r + ":  VIP: " + v + "   Frozen: " + f + "   Normal:" + n + "     NMotos:" + mn + "    FMotos:" + mf + "    VIPMotos: " + mv + "    DelivVIP: " + dv + "     DelivFrozen: " + df + "     DelivNormal: " + dn + AssigningString[i];
	}

	std::string x = std::to_string(CurrentTimeStep);
	pGUI->PrintMessage(" TimeStep: " + x);
	pGUI->PrintMessage(10, 650 - (int)(150 / 1.5), Reg[0]);
	pGUI->PrintMessage(10, 650 - (int)(120 / 1.5), Reg[1]);
	pGUI->PrintMessage(10, 650 - (int)(90 / 1.5), Reg[2]);
	pGUI->PrintMessage(10, 650 - (int)(60 / 1.5), Reg[3]);
}

void Restaurant::setTotalMotors()
{
	totalMotors =totalFrozMotors+totalNormMotors+totalVIPMotors;
}

void Restaurant::setTotalNoOfOrders()
{
	for(int i=0;i<4;i++)
		totalNumOfOrders+=R[i].Normal_Delivered.getCount()+R[i].Frozen_Delivered.getCount()+R[i].VIP_Delivered.getCount();
}

void Restaurant::setTotalNormOrders()
{
		for(int i=0;i<4;i++)
			totalNormOrders+=R[i].Normal_Delivered.getCount();
}

void Restaurant::setTotalFrozenOrders()
{
	for(int i=0;i<4;i++)
	{
		totalFrozenOrders+=R[i].Frozen_Delivered.getCount();
	}
}

void Restaurant::setTotalVIPOrders()
{
	for(int i=0;i<4;i++)
		totalVIPOrders+=R[i].VIP_Delivered.getCount();
}

void Restaurant::setTotalFrozMotors()
{		
	for(int i=0;i<4;i++)
		totalFrozMotors+=R[i].getFrozenMotorcyclesCount();
}

void Restaurant::setTotalNormMotors()
{
	for(int i=0;i<4;i++)
		totalNormMotors+=R[i].getNormalMotorcyclesCount();
}

void Restaurant::setTotalVIPMotors()
{
	for(int i=0;i<4;i++)
		totalVIPMotors+=R[i].getVIPMotorcyclesCount();
}

void Restaurant::SimulationInterractive()
{
	Order* pOrd=NULL;
	int CurrentTimeStep = 1;
	
	LoadInputFile();

	while(!EventsQueue.isEmpty() || !AllServed())
	{

		autoPromote(CurrentTimeStep);

		ExecuteEvents(CurrentTimeStep);

		pGUI->ResetDrawingList();
		DrawOrders();

		PrintStatus(CurrentTimeStep);

		ServeAllRegions(CurrentTimeStep);
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
	}
	PrintStatus(CurrentTimeStep);
	pGUI->ResetDrawingList();
	DrawOrders();
	pGUI->UpdateInterface();
	Sleep(2000);
	Save();
	pGUI->PrintMessage("click to END program");
	pGUI->waitForClick();
}

void Restaurant::simulationStep()
{
	Order* pOrd=NULL;
	int CurrentTimeStep = 1;
	
	LoadInputFile();

	while(!EventsQueue.isEmpty() || !AllServed())// || !ActiveOrders.IsEmpty())
	{
		autoPromote(CurrentTimeStep);
		ExecuteEvents(CurrentTimeStep);

		pGUI->ResetDrawingList();
		DrawOrders();

		PrintStatus(CurrentTimeStep);

		ServeAllRegions(CurrentTimeStep);

		pGUI->UpdateInterface();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}

	PrintStatus(CurrentTimeStep);	
	pGUI->ResetDrawingList();
	DrawOrders();

	pGUI->UpdateInterface();
	Sleep(2000);

	Save();
	
	pGUI->PrintMessage("click to END program");
	pGUI->waitForClick();
}

void Restaurant::simulationSilent()
{
	Order* pOrd=NULL;
	int CurrentTimeStep = 1;
	
	LoadInputFile();

	while(!EventsQueue.isEmpty() || !AllServed())// || !ActiveOrders.IsEmpty())
	{
		
		autoPromote(CurrentTimeStep);
		ExecuteEvents(CurrentTimeStep);
		
		ServeAllRegions(CurrentTimeStep);
		
		CurrentTimeStep++;	//advance timestep	
	}

	Sleep(1000);

	Save();
	
	pGUI->PrintMessage("click to END program");
	pGUI->waitForClick();
}

Restaurant::~Restaurant()
{
		delete pGUI;
}