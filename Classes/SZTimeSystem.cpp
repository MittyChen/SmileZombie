
#include "SZTimeSystem.h"
#include <time.h>
#include <stdio.h> 
#include "GameScene.h"
using namespace cocos2d;
SZTimeSystem* SZTimeSystem::instance= NULL;
DAY_TIME_BLOCK SZTimeSystem::currentDayBlock = DAY_TIME_BLOCK_NONE; 
DAY_TIME_BLOCK  SZTimeSystem::lastDayBlock = DAY_TIME_BLOCK_NONE; 
DAY_TIME_BLOCK  SZTimeSystem::nextDayBlock = DAY_TIME_BLOCK_NONE; 
bool SZTimeSystem::isNeedChangeStatus = false;
float SZTimeSystem::nightDarkRate = 1.0f;
 cocos2d::GLProgramState * SZTimeSystem::glprogramstate_dark = NULL;
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
	
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&SZTimeSystem::updateStatus), instance, 0.1f, false);
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
	if(!Node::init())
	{
		return false;
	}
	startTime = NULL;

	isNeedChangeStatus = false;

	initGameTimeShader();
 
	
	return true;
}

DAY_TIME_BLOCK SZTimeSystem::getDayStatus()
{
	DAY_TIME_BLOCK res = DAY_DAY_TIME_BLOCK;
	struct tm *newtime;
	time_t long_time;
	time( &long_time ); //Get time as long integer
	newtime = localtime( &long_time ); 
	int h = newtime->tm_sec;
	int m = newtime->tm_min;

	if(h>=0&&h<10)
	{
		res = DAY_TIME_BLOCK::DAY_MORNING_BLOCK;
	}else if(h>=10&&h<30)
	{
		res = DAY_TIME_BLOCK::DAY_DAY_TIME_BLOCK;
	}
	else if(h>=30&&h<=35)
	{
		res = DAY_TIME_BLOCK::DAY_DUSK_BLOCK;
	}
	else
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

 bool SZTimeSystem::needChangeStatus()
 {
	 return isNeedChangeStatus;
 }

 void SZTimeSystem::updateStatus( float delta )
 {
	 if(getDayStatus() != currentDayBlock)
	 {
		 lastDayBlock = currentDayBlock;

		 currentDayBlock = getDayStatus();
		 
		 nextDayBlock = getNextStatus();

		 isNeedChangeStatus = true;
	 }
	 goDark(delta);
 }

 void SZTimeSystem::setNeedChangeStatus( bool val )
 {
	 SZTimeSystem::isNeedChangeStatus = val;
 }

 DAY_TIME_BLOCK SZTimeSystem::getNextStatus()
 {
		//DAY_NIGHT_BLOCK= 1,//黑夜
		// DAY_DUSK_BLOCK = 7,//黄昏
		// DAY_MORNING_BLOCK = 8,//清晨
		// DAY_DAY_TIME_BLOCK = 10,//白天
		// DAY_TIME_BLOCK_NONE = 0//无状态

	 //time state machine
	switch(currentDayBlock)
	{
	case DAY_NIGHT_BLOCK:
		return DAY_MORNING_BLOCK;
		break;


	case DAY_DUSK_BLOCK:
		return DAY_NIGHT_BLOCK;
		break;


	case DAY_MORNING_BLOCK:
		return DAY_DAY_TIME_BLOCK;
		break;


	case DAY_DAY_TIME_BLOCK:
		return DAY_DUSK_BLOCK;
		break;


	case DAY_TIME_BLOCK_NONE:
		return DAY_MORNING_BLOCK;
		break;

	default:
		return DAY_MORNING_BLOCK;
		break;
	};
	
	 return DAY_TIME_BLOCK_NONE;
 }

 void SZTimeSystem::initGameTimeShader()
 {
	 auto fileUtiles = FileUtils::getInstance();
	 auto fragmentFullPath = fileUtiles->fullPathForFilename("SZShaders/night.fsh");
	 auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
	 auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	 nightDarkRate = 0.01f* getDayStatus();
	 glprogramstate_dark = GLProgramState::getOrCreateWithGLProgram(glprogram);
	 glprogramstate_dark->setUniformFloat("nightDegree", nightDarkRate);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 _backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
		 [this](EventCustom*)
	 {
		 glprogram->reset();
		 glprogram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
		 glprogram->link();
		 glprogram->updateUniforms();
	 }
	 );
	 Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif
 }

 void SZTimeSystem::goDark(float dt)
 {
	 if(needChangeStatus() )
	 {
		 if(currentDayBlock < lastDayBlock  )
		 {
			 if( nightDarkRate >(0.1f * currentDayBlock))
			 {
				 glprogramstate_dark->setUniformFloat("nightDegree", nightDarkRate-=0.02f);
				 if(nightDarkRate < (0.1f * currentDayBlock) )
				 {
					 setNeedChangeStatus(false);
				 }
			 }
		 }
		 else
		 {
			 if( nightDarkRate < (0.1f * currentDayBlock))
			 {
				 glprogramstate_dark->setUniformFloat("nightDegree", nightDarkRate+=0.02f);
				 if(nightDarkRate > (0.1f*currentDayBlock))
				 {
					setNeedChangeStatus(false);
				 }			
			 }
		 }
	 }
 }

 cocos2d::GLProgramState* SZTimeSystem::getDayChangeGLState()
 {
	 return this->glprogramstate_dark;
 }

 SZTimeSystem::SZTimeSystem()
 {

 }
 SZTimeSystem::~SZTimeSystem()
 {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
 }