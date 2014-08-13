#ifndef __CLOUD_H__
#define  __CLOUD_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"
#include "Element.h"

class Cloud : public Element
{
public:
	virtual bool init();  
	CREATE_FUNC(Cloud);
	virtual const char* getSpiriteName(int index);
	virtual int randTexture();
	void flowerBreath();
	void initCloudTexture();
	void setCloudDirection(int dir);
	int getCloudDirection();
	int cloudDirection;
	//shaders
protected:
	Cloud()
	{
	}
	~Cloud()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif // _ _CLOUD_H__