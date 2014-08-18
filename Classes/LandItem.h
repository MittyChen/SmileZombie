#ifndef __LAND_ITEM_H__
#define  __LAND_ITEM_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"
#include "Element.h"

class LandItem : public Element
{
public:
	virtual bool init();  
	CREATE_FUNC(LandItem);
	virtual const char* getSpiriteName(int index);
	virtual int randTexture();
	void initLandItemTexture();
	//shaders
protected:
	LandItem()
	{
	}
	~LandItem()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif // _ _LandItem_H__