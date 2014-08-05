#ifndef  _SZ_TIME_SYSTEM_H_
#define  _SZ_TIME_SYSTEM_H_
#include "cocos2d.h"

enum DAY_TIME_BLOCK
{
	DAY_MORNING_BLOCK,//Çå³¿
	DAY_DAY_TIME_BLOCK,//°×Ìì
	DAY_DUSK_BLOCK,//»Æ»è
	DAY_NIGHT_BLOCK,//ºÚÒ¹
	DAY_TIME_BLOCK_NONE//ÎÞ×´Ì¬
};
class SZTimeSystem:public cocos2d::Node
{
public:
	virtual bool init();  
	void updateStatus(float delta);
	CREATE_FUNC(SZTimeSystem);
	static SZTimeSystem* getInstance();
	void startSystem();
	void setTimeStep(float timest);
	DAY_TIME_BLOCK getDayStatus();
	struct tm * getGameStartTime();
	int* getGameStartTimeArray();
	bool shouldGoDark();
	void setShouldGoDark(bool val);
protected:
private:
	float timeStep;
	float timeNow;
	static SZTimeSystem* instance;
	int gameStartTime[5];
	struct tm *startTime;
	static DAY_TIME_BLOCK currentDayBlock;
	bool isShouldGoDark;
};

#endif