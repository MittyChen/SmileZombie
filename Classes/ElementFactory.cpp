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
	//救场如救火 支援还没到 你就先顶上去吧！！！
	auto mSpi =getElementObj();
	initSingleElement(mSpi);
	mSpriteList.pushBack(mSpi);
	mlayer->addChild(mSpi,mZorder);
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
	//if(ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE == mytype)
	//{
	//	for(int i = 0 ; i < mSpriteList.size() ; i++)
	//	{
	//		auto mSpir = (Element*)mSpriteList.at(i);
	//	}
	//}

	if( mSpriteList.size() < Element_SUM)
	{
		auto mSpi =getElementObj();
		initSingleElement(mSpi);
		mSpriteList.pushBack(mSpi);
		mlayer->addChild(mSpi,mZorder);
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
		break;

	default:
		break;
	}

	return thisElementBeyondBonds;
}

void ElementFactory::initSingleElement( Element* mSpi )
{
	float targetX  = 0;
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
		{
				if(mSpriteList.size()>0)
				{
					mSpi->setPosition(Vec2((ElementBounds.rightBounds)*1.2f,getOriginalPositionY()));
				}else
				{
					mSpi->setPosition(Vec2((ElementBounds.rightBounds)*0.7f,getOriginalPositionY()));
				}

				mSpi->setElementDirection(-1); 
				
				break;
		}
	

	case ELEMENT_SEED_TYPE::ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE:
		{
			if(mSpriteList.size()>0){
				Element* mEle = getMaxPositionInElements();//最后一个
				mSpi->setPosition(Vec2(mEle->getPosition().x+(mEle->getContentSize().width) , getOriginalPositionY()));
			}else{
				mSpi->setPosition(Vec2((ElementBounds.rightBounds)*0.8f,getOriginalPositionY()));
			} 
			mSpi->setRotation3D(Vec3(-45,0,0));//逆时针翻转
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
		break;
		}
	default:
		break;
	}
	if(mSpi->getElementDirection() > 0)
	{
		targetX = (ElementBounds.leftBounds+ElementBounds.leftBounds*0.2);
	}else{
		targetX = (ElementBounds.leftBounds-ElementBounds.leftBounds*0.2);
	}
	mSpi->setScale(getElementScaleRamdomRate()*Element_SIZE_SCALE);
	mSpi->runAction(MoveTo::create(targetX/Element_MOVE_STEP,Vec2(targetX,mSpi->getPosition().y)));
}

void ElementFactory::clearElement( float dt )
{
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Element*)mSpriteList.at(i);//状态改变云朵渐隐 
		mSpir->runAction(CCFadeOut::create(2));
	}
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
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&ElementFactory::seedElements),this);
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&ElementFactory::updatePositionHorizen),this);
}

Element *  ElementFactory::getMaxPositionInElements()
{
	int indexM = 0;
	float maxVal = 0.0f;
	for(int i = 0 ; i < mSpriteList.size() ; i++)
	{
		auto mSpir = (Element*)mSpriteList.at(i);
		 float posiX = mSpir->getPosition().x+mSpir->getContentSize().width;
		 if(posiX > maxVal )
		 {
			  maxVal = posiX;
			  indexM = i;
		 }
	}
	

	return  mSpriteList.at(indexM);
}
