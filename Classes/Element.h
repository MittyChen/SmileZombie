#ifndef __ELEMENT_H__
#define  __ELEMENT_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"

class Element : public cocos2d::Sprite
{
public:
	virtual bool init();  
	CREATE_FUNC(Element);
	virtual const char* getSpiriteName(int index);
	virtual int randTexture();
	void flowerBreath();
	void initElementTexture();
	void setElementDirection(int dir);
	int getElementDirection();
	int ElementDirection;
	//shaders
protected:
	Element()
	{
	}
	~Element()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif // __ELEMENT_H__