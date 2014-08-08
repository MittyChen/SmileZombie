
#include "LonelyFlower.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LonelyFlower::init()
{
	if(!Sprite::init())
	{
		return false;
	}

	return true;
}

const char* LonelyFlower::getSpiriteName(int index)
{
	CCLOG("LonelyFlower::getSpiriteName  %d",index);
	if(index>=0 && index<=3)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
				CCString* resToRet = CCString::createWithFormat( "flowers/flower_%d.png",index);
#else
				CCString* resToRet = CCString::createWithFormat( "flower_%d.png",index);
#endif
		return resToRet->getCString();
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		return  "flowers/flower_2.png";
#else
		return  "flower_2.png";
#endif
}

int LonelyFlower::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%4;
}


void  LonelyFlower::initFlowerTexture()
{
	this->setTexture(getSpiriteName(randTexture()));
}

void LonelyFlower::flowerBreath()
{
	CCAction*  action = Sequence::createWithTwoActions(	ScaleTo::create(1, 0.6f), ScaleTo::create(1, 1.0f));
	this->runAction(action); 
}