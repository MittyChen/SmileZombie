#ifndef __LONELY_FLOWER_H__
#define  __LONELY_FLOWER_H__

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


	int cloudDirection;

};

#endif // _ __LONELY_FLOWER_H__
