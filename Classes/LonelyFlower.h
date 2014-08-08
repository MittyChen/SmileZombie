#ifndef __LONELY_FLOWER_H__
#define  __LONELY_FLOWER_H__

#include "cocos2d.h"

class LonelyFlower : public cocos2d::Sprite
{
public:
	
	virtual bool init();  

	CREATE_FUNC(LonelyFlower);

	const char* getSpiriteName(int index);

	int randTexture();

	void initFlowerTexture();

	void flowerBreath();
};

#endif // _ __LONELY_FLOWER_H__
