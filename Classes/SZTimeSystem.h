#ifndef  _SZ_TIME_SYSTEM_H_
#define  _SZ_TIME_SYSTEM_H_
#include "cocos2d.h"

enum DAY_TIME_BLOCK
{
	DAY_NIGHT_BLOCK= 1,//ºÚÒ¹
	DAY_DUSK_BLOCK = 7,//»Æ»è
	DAY_MORNING_BLOCK = 8,//Çå³¿
	DAY_DAY_TIME_BLOCK = 10,//°×Ìì
	DAY_TIME_BLOCK_NONE = 0//ÎÞ×´Ì¬
};
class SZTimeSystem:public cocos2d::Node
{
public:
	virtual bool init();  
	void updateStatus(float delta);
	CREATE_FUNC(SZTimeSystem);

	SZTimeSystem();
	~SZTimeSystem();
	
	static SZTimeSystem* getInstance();
	void startSystem();
	void setTimeStep(float timest);
	DAY_TIME_BLOCK getDayStatus();
	struct tm * getGameStartTime();
	int* getGameStartTimeArray();
	bool needChangeStatus();
	void setNeedChangeStatus(bool val);
	DAY_TIME_BLOCK getNextStatus();
	void initGameTimeShader();
	void goDark(float dt);
	cocos2d::GLProgramState* getDayChangeGLState();
	static DAY_TIME_BLOCK currentDayBlock; 
	static DAY_TIME_BLOCK lastDayBlock; 
	static DAY_TIME_BLOCK nextDayBlock;


protected:
private:
	float timeStep;
	float timeNow;
	static SZTimeSystem* instance;
	int gameStartTime[5];
	struct tm *startTime;
	static bool isNeedChangeStatus;
	static cocos2d::GLProgramState *glprogramstate_dark;
	static float nightDarkRate;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif