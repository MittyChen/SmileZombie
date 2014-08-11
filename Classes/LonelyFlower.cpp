#include "LonelyFlower.h"
#include "Consts.h"



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
	if(index>=0 && index<=FLOWER_PICTURE_MAX_INDEX)
	{
				CCString* resToRet = CCString::createWithFormat( "%s%d.%s",FLOWER_PICTURE_PREFIX,index,FLOWER_PICTURE_TYPE);
		return resToRet->getCString();
	}
		return  FLOWER_PICTURE_DEFAULT;
}

int LonelyFlower::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%(FLOWER_PICTURE_MAX_INDEX+1);
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