#include "Motorcycle.h"

int Motorcycle::count = 0; //initializing the static data member "count"

Motorcycle::Motorcycle() //default constructor
{
	status = IDLE;
	count++;
	ID = count;
	Health=100;
	damagetime = -100;
}

Motorcycle::Motorcycle(ORD_TYPE o, int s, REGION r) //non-default constructor
{
	type = o;
	setRegion(r);
	setSpeed(s);
	status = IDLE;
	count++;
	ID = count;
	Health = 100;
	damagetime = -100;
}

//decreasing the health of the motocycle as an indication to its damage, we assumed it will decrease by 10
void Motorcycle:: DecrementHealth() 
{
	Health-=10;
}

//setting the speed of the motorcycle
void Motorcycle::setSpeed(int s)
{
	speed = s;
}

//setting the region at which the motocycle is present in.
void Motorcycle::setRegion(REGION r)
{
	region = r;
}

//getting the motorcycle speed
int Motorcycle::getspeed()
{
	return speed;
}

//getting the motorcycle health
int Motorcycle::getHealth()
{
	return Health;
}

Motorcycle::~Motorcycle()
{}

//getting the motorcycle status: idle or in-service?
STATUS Motorcycle::getstatus()
{
	return status;
}

//setting the time in which the motorcycle will take to heal from damages
void Motorcycle::setrestingtime(int r)
{
	restingtime = r;
}

void Motorcycle::setdamagetime(int d)
{
	damagetime = d;
}

int Motorcycle::getID()
{
	return ID;
}

void Motorcycle::switchto_In_Service()
{
	status = SERV;
}

void Motorcycle::UpdateStatus(int timestep)
{
	if (Health == 0)
	{
		status = DAMAGED;
		if(damagetime==-100)
			damagetime = timestep;
	}

	if (status == SERV)
	{
		if (timestep == restingtime)
			status = REST;
	}
	else if (status == REST)
	{
		if (timestep == restingtime + 2)
			status = IDLE;
	}
	else if (status == DAMAGED)
	{
		if (timestep == damagetime +10)
		{
			status = IDLE;
			Health = 100;
		}
	}
}