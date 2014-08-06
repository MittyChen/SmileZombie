
#include "SZTimeSystem.h"
#include <time.h>
#include <stdio.h> 

SZTimeSystem* SZTimeSystem::instance= NULL;

void SZTimeSystem::startSystem()
{
	//time_t t = time(0);
	//char tmp[64];
	//strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z",localtime(&t) );
	//puts( tmp ); 
	 
	time_t long_time;
	time( &long_time ); //Get time as long integer
	startTime = localtime( &long_time ); 
	int month = startTime->tm_mon;
	int day = startTime->tm_mday;
	int hour = startTime->tm_hour;
	int minite = startTime->tm_min;
	int second = startTime->tm_sec;

	gameStartTime[0] = month;//月
	gameStartTime[1] = day;//日
	gameStartTime[2] = hour;//时
	gameStartTime[3] = minite;//分
	gameStartTime[4] = second;//秒
	

}

void SZTimeSystem::setTimeStep(float timest)
{
	this->timeStep = timest;
}

SZTimeSystem* SZTimeSystem::getInstance()
{
	if(!instance)
	{
		instance = SZTimeSystem::create();
		instance->startSystem();
	}
	return instance;
}

bool SZTimeSystem::init()
{
	__super::init();
	startTime = NULL;
	return true;
}

DAY_TIME_BLOCK SZTimeSystem::getDayStatus()
{
	DAY_TIME_BLOCK res;
	struct tm *newtime;
	time_t long_time;
	time( &long_time ); //Get time as long integer
	newtime = localtime( &long_time ); 
	int h = newtime->tm_hour;
	int m = newtime->tm_min;

	if(h>5&&h<7)
	{
		res = DAY_TIME_BLOCK::DAY_MORNING_BLOCK;
	}else if(h>7&&h<17)
	{
		res = DAY_TIME_BLOCK::DAY_DAY_TIME_BLOCK;
	}
	else if(h>17&&h<19)
	{
		res = DAY_TIME_BLOCK::DAY_DUSK_BLOCK;
	}
	else
	{
		res = DAY_TIME_BLOCK::DAY_NIGHT_BLOCK;
	} 

	if(m>17)
	{
		res = DAY_TIME_BLOCK::DAY_NIGHT_BLOCK;
	}
	return res;
}

struct tm * SZTimeSystem::getGameStartTime()
{
	return startTime;
}

 int * SZTimeSystem::getGameStartTimeArray()
{
	return gameStartTime;
}





