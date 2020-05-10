#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include "..\Defs.h"
#pragma once

class Motorcycle	
{
	static int count;
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int Health;    // to indicate the damage that occured to the motorcycle when over-used (bonus part)
	int restingtime;
	int damagetime;
public:
	Motorcycle();
	Motorcycle(ORD_TYPE o, int s ,REGION r);
	void setSpeed(int s);
	void setRegion(REGION r);
	int getspeed();
	int getHealth();
	void DecrementHealth();
	virtual ~Motorcycle();
	STATUS getstatus();
	void setrestingtime(int r);
	void setdamagetime(int d);
	int getID();
	void switchto_In_Service();
	void UpdateStatus(int timestep);
};

#endif