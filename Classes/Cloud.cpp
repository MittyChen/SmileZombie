#include "Cloud.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Cloud::init()
{
	__super::init();
	initCloudTexture();
	return true;
}

const char* Cloud::getSpiriteName(int index)
{
	CCLOG("Cloud::getSpiriteName  %d",index);
	if(index>=0 && index<=4)
	{
		CCString* resToRet = CCString::createWithFormat( "clouds/cloud%d.png",index);

		return resToRet->getCString();
	}
	return  "clouds/cloud2.png";

}

int Cloud::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%5;
}


void  Cloud::initCloudTexture()
{
	this->setTexture(getSpiriteName(randTexture()));
}

void Cloud::setTexture(const std::string &filename)
{
	__super::setTexture(filename);
}

void Cloud::flowerBreath()
{
	CCAction*  action = CCSequence::createWithTwoActions(	CCScaleTo::create(1, 0.6f), CCScaleTo::create(1, 1.0f));
	this->runAction(action); 
}

void Cloud::setCloudDirection(int dir)
{
	if(dir>1)
	{
		dir =1;
	}
	if(dir<-1)
	{
		dir =-1;
	}
	if(dir==0)
	{
		CCLOG("this cloud will not move");
	}
	cloudDirection = dir;
}

int Cloud::getCloudDirection()
{
	return cloudDirection;
}


