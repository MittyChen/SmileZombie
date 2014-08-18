#ifndef __LAND_H__
#define  __LAND_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"
#include "Element.h"

class Land : public Element
{
public:
	virtual bool init();  
	CREATE_FUNC(Land);
	virtual const char* getSpiriteName(int index);
	virtual int randTexture();
	void initLandTexture();
	//shaders
protected:
	Land()
	{
	}
	~Land()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif // _ _Land_H__