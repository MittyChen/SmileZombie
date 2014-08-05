#ifndef __SUROUNDINGS_SPRITE_H__
#define  __SUROUNDINGS_SPRITE_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"

class SurroundingsSprite : public cocos2d::Sprite
{
public:
	SurroundingsSprite(){}
	~SurroundingsSprite()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		Director::getInstance()->getEventDispatcher()->removeEventListener(_backgroundListener);
#endif
	}
	virtual bool init();
	virtual void update(float delta);
	CREATE_FUNC(SurroundingsSprite);
	void setTextureByindex(int index );
	const char* getSpiriteName(int index);//picture name from 0 to maxindex
	int randTexture(int maxVa);
	void initBaseTexture(	const char* filePrefix,const char* filetype,int max_index);
	void goDark(float dt);
protected:
	const char* filePrefix;
	const char* fileType;
	int max_index;
	float nightDarkRate;
	 cocos2d::GLProgramState* _glprogramstate;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::EventListenerCustom* _backgroundListener;
#endif
};

#endif //  __SUROUNDINGS_SPRITE_H__
