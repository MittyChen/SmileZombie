#include "ElementFactory.h"
#include "Element.h"
#include "Element.h"
#include "Cloud.h"
#include "LandItem.h"
#include "Land.h"
using namespace  cocos2d;
//Element config

 bool ElementFactory::init()
 {
	 if(!Node::init())
	 {
		 return false;
	 }

	 Element_SIZE_SCALE = 1.0f;
	 Element_MOVE_STEP =1.5f;
	 Element_SUM=1;
	 Element_SEED_BREAKTIME=1.0f;
	 mZorder = -10;
	 mlayer = NULL;
	 mytype = ELEMENT_FIEXED_SEED_FROM_RIGHT;

	 return true;
 }

void ElementFactory::setBounds(float upBound,float downBound,float leftBound,float rightBound)
{
	ElementBounds.upBounds = upBound;
	ElementBounds.downBounds = downBound;
	ElementBounds.leftBounds = leftBound;
	ElementBounds.rightBounds = rightBound;
}

float ElementFactory::getOriginalPositionX()
{
	return  (ElementBounds.rightBounds)*1.2f;
}

float ElementFactory::getOriginalPositionY()
{
	if(hasFixedHeight)
	{
		return this->ElementsFixedHeight;
	}
	 srand((unsigned) time(NULL));
	float heightToreturn = Random(ElementBounds.downBounds,(int)ElementBounds.downBounds+(int)ElementBounds.upBounds);
	//ElementBounds.downBounds+rand()%((int)ElementBounds.downBounds+(int)ElementBounds.upBounds);
	CCLOG(" ElementFactory::getRandomHeight()  result = %f",heightToreturn);
	return heightToreturn;
}


void ElementFactory::updatePositionHorizen(float dt)
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Element*)mSpriteList.at(i);
		float posiX =mSpir->getPosition().x;
		float posiY =mSpir->getPosition().y;
		mSpir->setPosition(Vec2(posiX+(mSpir->getElementDirection())*Element_MOVE_STEP,posiY));
	}
}


Vector<Element*> ElementFactory::getSpriteList()
{
	return mSpriteList;
}

int ElementFactory::Random(int m, int n)
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

void ElementFactory::startElementEngine()
{
	//�ȳ���Ȼ� ֧Ԯ��û�� ����ȶ���ȥ�ɣ�����
	auto mSpi =getElementObj();
	initSingleElement(mSpi);
	mSpriteList.pushBack(mSpi);
	mlayer->addChild(mSpi,mZorder);


	CCLOG("  ElementFactory::seedElements = new Element");
	//mlayer->schedule(schedule_selector(ElementFactory::seedElements) ,Element_SEED_BREAKTIME,kRepeatForever, 0.0f);
	//mlayer->schedule(schedule_selector(ElementFactory::updatePositionHorizen) ,1/60,kRepeatForever, 0.0f);//Element move
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&ElementFactory::updatePositionHorizen), this, 1/60, false);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&ElementFactory::seedElements), this, Element_SEED_BREAKTIME, false);
	
}

void ElementFactory::initElementEngine(Layer *layer,struct BounsStruct mstrct,ELEMENT_SEED_TYPE seedMode, ELEMENT_CONTENT_TYPE eleType,int Zorder,float scale,float step,int sum,float breaktime)
{
	mlayer = layer;
	mZorder = Zorder;
	ElementBounds = mstrct;
	setSeedType(seedMode);

	Element_SIZE_SCALE = scale;
	Element_MOVE_STEP = step;
	Element_SUM=sum;
	Element_SEED_BREAKTIME=breaktime;
	this->meleType =  eleType;
}
void ElementFactory::seedElements(float dt)
{
	if(ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE == mytype)
	{
		for(int i = 0 ; i < mSpriteList.size() ; i++)
		{
			auto mSpir = (Element*)mSpriteList.at(i);
			CCLOG("   ElementFactory::seedElements index = %d /  pos = %f",i,mSpir->getPosition().x);
		}
	}

	if( mSpriteList.size() < Element_SUM)
	{
		auto mSpi =getElementObj();
		initSingleElement(mSpi);
		mSpriteList.pushBack(mSpi);
		mlayer->addChild(mSpi,mZorder);
		CCLOG("  ElementFactory::seedElements = new Element");
	}else
	{
		for(int i = 0 ; i < mSpriteList.size() ; i++)
		{
			 auto mSpir = (Element*)mSpriteList.at(i);
			 
			 if(checkWidthBounds(mSpir))
			 {
				 mlayer->removeChild(mSpir);
				 auto mSpi = getElementObj();
				 initSingleElement(mSpi);
				 mSpriteList.replace(i,mSpi);
				 mlayer->addChild(mSpi,mZorder);
				 CCLOG("  ElementFactory::seedElements = replace Element");
			 }
		}
	}
}

float ElementFactory::getElementScaleRamdomRate()
{
	if(!useRandomScale)
	{
		return 1.0f;
	}
	return 0.01f*Random(10,90);
}

void ElementFactory::setSeedType(ELEMENT_SEED_TYPE type)
{
	mytype =(ELEMENT_SEED_TYPE)type;
}

void ElementFactory::setElementFixedHeight(float cHeight)
{
	this->hasFixedHeight =true;
	this->ElementsFixedHeight = cHeight;
}

bool ElementFactory::checkWidthBounds( Element* mSpir )
{
	bool thisElementBeyondBonds = false;
	//set position and  direction
	switch (mytype)
	{
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_LEFT:
		if(mSpir->getPosition().x > (ElementBounds.rightBounds)*1.3f)
		{
			thisElementBeyondBonds = true;
		}
		break;
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_RIGHT:

		if(mSpir->getPosition().x < (ElementBounds.rightBounds)*(-0.3f))
		{
			thisElementBeyondBonds = true;
		}
		break;
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE:

		if(mSpir->getPosition().x + mSpir->getContentSize().width < (ElementBounds.leftBounds))
		{
			thisElementBeyondBonds = true;
		}
		break;
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_RANDOM:
		if((mSpir->getElementDirection() >0&&(mSpir->getPosition().x > (ElementBounds.rightBounds)*1.3f))||
			( mSpir->getElementDirection() <0&&(mSpir->getPosition().x < (ElementBounds.rightBounds)*(-0.3f))))
		{
			thisElementBeyondBonds = true;
		}
		CCLOG("this is a random Element seed mode");
		break;

	default:
		break;
	}

	return thisElementBeyondBonds;
}

void ElementFactory::initSingleElement( Element* mSpi )
{
	//set position and  direction
	switch (mytype)
	{
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_LEFT:
		
		if(mSpriteList.size()>0)
		{
			mSpi->setPosition(Vec2((ElementBounds.rightBounds)*(-0.2f),getOriginalPositionY()));
		}else
		{
			mSpi->setPosition(Vec2((ElementBounds.rightBounds)*(0.2f),getOriginalPositionY()));
		}

		mSpi->setElementDirection(1);
		break;
	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_RIGHT:
		if(mSpriteList.size()>0)
		{
			mSpi->setPosition(Vec2((ElementBounds.rightBounds)*1.2f,getOriginalPositionY()));
		}else
		{
			mSpi->setPosition(Vec2((ElementBounds.rightBounds)*0.7f,getOriginalPositionY()));
		}
	
		mSpi->setElementDirection(-1);
		break;

	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE:
		{
			if(mSpriteList.size()>0){
				Element* mEle = getMaxPositionInElements();//���һ��
				mSpi->setPosition(Vec2(mEle->getPosition().x+(mEle->getContentSize().width) , getOriginalPositionY()));
			}else{
				mSpi->setPosition(Vec2((ElementBounds.rightBounds)*0.8f,getOriginalPositionY()));
			} 
			mSpi->setRotation3D(Vec3(-45,0,0));//��ʱ�뷭ת
			mSpi->setElementDirection(-1);
		break;
		}

	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_RANDOM:
		{ srand(time(0));

		int randomDir = rand()%3 - 1;
		if(randomDir == 0)
		{
			randomDir = 1;
		}

		if(randomDir >0 )
		{
			if(mSpriteList.size()>0)
			{
					mSpi->setPosition(Vec2((ElementBounds.rightBounds)*(-0.2f),getOriginalPositionY()));
			}else
			{
					mSpi->setPosition(Vec2((ElementBounds.rightBounds)*(0.2f),getOriginalPositionY()));
			}  
			mSpi->setElementDirection(1);
		}else{

			if(mSpriteList.size()>0)
			{
				mSpi->setPosition(Vec2((ElementBounds.rightBounds)*1.2f,getOriginalPositionY()));
			}else
			{
				mSpi->setPosition(Vec2((ElementBounds.rightBounds)*0.8f,getOriginalPositionY()));
			} 

			
			mSpi->setElementDirection(-1);
		}
		CCLOG("this is a random Element seed mode");
		break;
		}
	default:
		break;
	}

			mSpi->setScale(getElementScaleRamdomRate()*Element_SIZE_SCALE);
}

void ElementFactory::clearElement( float dt )
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Element*)mSpriteList.at(i);//״̬�ı��ƶ佥�� 
		mSpir->runAction(CCFadeOut::create(2));
	}

	CCLOG("the day  statu is changed");
}

void ElementFactory::setUseRandomScale(bool val)
{
	this->useRandomScale = val;
}

ElementFactory::ElementFactory()
{
	init();
}

ElementFactory::~ElementFactory()
{
	stopElementEngine();
}

Element * ElementFactory::getElementObj()
{
	switch (meleType)
	{
	case ELEMENT_CONTENT_TYPE::ELEMENT_CLOUDS:
		return Cloud::create();
		break;
	case ELEMENT_CONTENT_TYPE::ELEMENT_LAND_ITEMS:
		return   LandItem::create();
		break;
	case ELEMENT_CONTENT_TYPE::ELEMENT_LAND:
		return   Land::create();
		break;
	default:
		return  LandItem::create();
		break;
	}
}

void ElementFactory::stopElementEngine()
{
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&ElementFactory::updatePositionHorizen),this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&ElementFactory::seedElements),this);
}

Element *  ElementFactory::getMaxPositionInElements()
{
	int i,j;
	Element * mtemp  = NULL;
	int n = mSpriteList.size();
	for(i=0;i<n-1;i++){
		float temp1sp = mSpriteList.at(i)->getPosition().x;
		for(j=n-1; j>i; j--){
			float temp2sp = mSpriteList.at(j)->getPosition().x;
			if(temp1sp>temp2sp)
			{
				mtemp = mSpriteList.at(j);
				mSpriteList.replace(j,mSpriteList.at(i));
				mSpriteList.replace(i,mtemp);
			}
		}
	}
	if(mtemp)
	{
		mtemp->release();
		mtemp =NULL;
	}


	return  mSpriteList.at(mSpriteList.size()-1);
}
