#ifndef __CLOUD_H__
#define  _CLOUD_H__

#include "cocos2d.h"
class Cloud : public cocos2d::Sprite
{
public:
	virtual bool init();  
	CREATE_FUNC(Cloud);
	virtual void setTexture(const std::string &filename );
	const char* getSpiriteName(int index);
	int randTexture();
	void flowerBreath();
	void initCloudTexture();
	void setCloudDirection(int dir);
	int getCloudDirection();
	virtual bool initWithTexture(cocos2d::Texture2D *texture);
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