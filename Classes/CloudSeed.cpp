#include "CloudSeed.h"
#include "Cloud.h"

using namespace  cocos2d;
//cloud config
float CloudSeed::CLOUD_SIZE_SCALE = 1.0f;
float CloudSeed::CLOUD_MOVE_STEP =0.5f;
int CloudSeed::CLOUD_SUM=6;
float CloudSeed::CLOUD_SEED_BREAKTIME=3.0f;
 CloudSeed * CloudSeed::instance = NULL;

 struct  BounsStruct  CloudSeed::cloudBounds = {960,800,-90,1024};
 cocos2d::Vector<Cloud*> CloudSeed::mSpriteList ;
 cocos2d::CCLayer *CloudSeed::mlayer = NULL;
 CLOUD_SEED_TYPE  CloudSeed::mytype = CLOUDE_FIEXED_SEED_FROM_RIGHT;
  int CloudSeed::mZorder = -10;
 bool  CloudSeed::hasFixedHeight =false;
 float  CloudSeed::cloudsFixedHeight = 600.0f;

bool CloudSeed::init()
{
	if(!Node::init())
	{
		return false;
	}
	return true;
}

void CloudSeed::setBounds(float upBound,float downBound,float leftBound,float rightBound)
{
	cloudBounds.upBounds = upBound;
	cloudBounds.downBounds = downBound;
	cloudBounds.leftBounds = leftBound;
	cloudBounds.rightBounds = rightBound;
}

float CloudSeed::getOriginalPositionX()
{
	return  (cloudBounds.rightBounds)*1.2f;
}

float CloudSeed::getOriginalPositionY()
{
	if(hasFixedHeight)
	{
		return cloudsFixedHeight;
	}
	 srand((unsigned) time(NULL));
	float heightToreturn = Random(cloudBounds.downBounds,(int)cloudBounds.downBounds+(int)cloudBounds.upBounds);
	//cloudBounds.downBounds+rand()%((int)cloudBounds.downBounds+(int)cloudBounds.upBounds);
	CCLOG(" CloudSeed::getRandomHeight()  result = %f",heightToreturn);
	return heightToreturn;
}


void CloudSeed::updatePositionHorizen(float dt)
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Cloud*)mSpriteList.at(i);
		float posiX =mSpir->getPosition().x;
		float posiY =mSpir->getPosition().y;
		mSpir->setPosition(Vec2(posiX+(mSpir->getCloudDirection())*CLOUD_MOVE_STEP,posiY));
	}
}


Vector<Cloud*> CloudSeed::getSpriteList()
{
	return mSpriteList;
}

int CloudSeed::Random(int m, int n)
{
	int pos, dis;
	if(m == n)
	{
		return m;
	}
	else if(m > n)
	{
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	}
	else
	{
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}
}

void CloudSeed::startCloudEngine()
{
	mlayer->schedule(schedule_selector(CloudSeed::seedClouds) ,CLOUD_SEED_BREAKTIME,kRepeatForever, 0.0f);
	mlayer->schedule(schedule_selector(CloudSeed::updatePositionHorizen) ,1/60,kRepeatForever, 0.0f);//cloud move
}

void CloudSeed::initCloudEngine(Layer *layer,struct BounsStruct mstrct,CLOUD_SEED_TYPE seedMode,int Zorder)
{
	mlayer = layer;
	mZorder = Zorder;
	cloudBounds = mstrct;
	hasFixedHeight =false;
	setSeedType(seedMode);
}
void CloudSeed::seedClouds(float dt)
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Cloud*)mSpriteList.at(i);
		CCLOG(" CloudSeed::seedClouds  position X === %f",mSpir->getPosition().x);
	}

	if( mSpriteList.size() < CLOUD_SUM)
	{
		auto mSpi =Cloud::create();
		initSingleCloud(mSpi);
		mSpriteList.pushBack(mSpi);
		mlayer->addChild(mSpi,mZorder);
		CCLOG("  CloudSeed::seedClouds = new cloud");
	}else
	{
	    CCLOG("  CloudSeed::seedClouds =   we have %d cloud ",CLOUD_SUM);
		for(int i = 0 ; i < mSpriteList.size() ; i++)
		{
			 auto mSpir = (Cloud*)mSpriteList.at(i);
			 
			 if(checkWidthBounds(mSpir))
			 {
				 mlayer->removeChild(mSpir);
				 auto mSpi =Cloud::create();
				 initSingleCloud(mSpi);
				 mSpriteList.replace(i,mSpi);
				 mlayer->addChild(mSpi,mZorder);
				 CCLOG("  CloudSeed::seedClouds = replace cloud");
			 }
		}
	}
}

float CloudSeed::getCloudScaleRamdomRate()
{
	return 0.01f*Random(10,90);
}

void CloudSeed::setSeedType(CLOUD_SEED_TYPE type)
{
	mytype =(CLOUD_SEED_TYPE)type;
}

void CloudSeed::setCloudFixedHeight(float cHeight)
{
	hasFixedHeight =true;
	cloudsFixedHeight = cHeight;
}

bool CloudSeed::checkWidthBounds( Cloud* mSpir )
{
	bool thisCloudBeyondBonds = false;
	//set position and  direction
	switch (mytype)
	{
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_FROM_LEFT:
		if(mSpir->getPosition().x > (cloudBounds.rightBounds)*1.3f)
		{
			thisCloudBeyondBonds = true;
		}
		break;
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_FROM_RIGHT:

		if(mSpir->getPosition().x < (cloudBounds.rightBounds)*(-0.3f))
		{
			thisCloudBeyondBonds = true;
		}
		break;
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_RANDOM:
		if((mSpir->getCloudDirection() >0&&(mSpir->getPosition().x > (cloudBounds.rightBounds)*1.3f))||
			( mSpir->getCloudDirection() <0&&(mSpir->getPosition().x < (cloudBounds.rightBounds)*(-0.3f))))
		{
			thisCloudBeyondBonds = true;
		}
		CCLOG("this is a random cloud seed mode");
		break;

	default:
		break;
	}

	return thisCloudBeyondBonds;
}

void CloudSeed::initSingleCloud( Cloud* mSpi )
{
	//set position and  direction
	switch (mytype)
	{
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_FROM_LEFT:
		mSpi->setPosition(Vec2((cloudBounds.rightBounds)*(-0.2f),getOriginalPositionY()));
		mSpi->setCloudDirection(1);
		break;
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_FROM_RIGHT:
		mSpi->setPosition(Vec2((cloudBounds.rightBounds)*1.2f,getOriginalPositionY()));
		mSpi->setCloudDirection(-1);
		break;
	case CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_RANDOM:
		{ srand(time(0));

		int randomDir = rand()%3 - 1;
		if(randomDir == 0)
		{
			randomDir = 1;
		}

		if(randomDir >0 )
		{
			mSpi->setPosition(Vec2((cloudBounds.rightBounds)*(-0.2f),getOriginalPositionY()));
			mSpi->setCloudDirection(1);
		}else{
			mSpi->setPosition(Vec2((cloudBounds.rightBounds)*1.2f,getOriginalPositionY()));
			mSpi->setCloudDirection(-1);
		}
		CCLOG("this is a random cloud seed mode");
		break;
		}
	default:
		break;
	}

			mSpi->setScale(getCloudScaleRamdomRate()*CLOUD_SIZE_SCALE);
}

void CloudSeed::clearCloud( float dt )
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Cloud*)mSpriteList.at(i);//×´Ì¬¸Ä±äÔÆ¶ä½¥Òþ 
		mSpir->runAction(CCFadeOut::create(2));
	}

	CCLOG("the day  statu is changed");
}

