#include "LonelyFlower.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LonelyFlower::init()
{
	__super::init();

	return true;
}

const char* LonelyFlower::getSpiriteName(int index)
{
	CCLOG("LonelyFlower::getSpiriteName  %d",index);
	if(index>=0 && index<=3)
	{
		CCString* resToRet = CCString::createWithFormat( "flowers/flower_%d.png",index);
		
		return resToRet->getCString();
	}
	return  "flowers/flower_2.png";
		
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

void LonelyFlower::setTexture(const std::string &filename)
{
	__super::setTexture(filename);
}

void LonelyFlower::flowerBreath()
{
	CCAction*  action = CCSequence::createWithTwoActions(	CCScaleTo::create(1, 0.6f), CCScaleTo::create(1, 1.0f));
	this->runAction(action); 
}