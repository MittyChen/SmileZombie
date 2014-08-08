#ifndef __CLOUD_SEED_H__
#define  __CLOUD_SEED_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"

class Cloud;
struct BounsStruct
{
	float upBounds;
	float downBounds;
	float leftBounds;
	float rightBounds;
};
typedef enum 
{
	CLOUDE_FIEXED_SEED_FROM_RIGHT,
	CLOUDE_FIEXED_SEED_FROM_LEFT,
	CLOUDE_FIEXED_SEED_RANDOM
}CLOUD_SEED_TYPE;



class CloudSeed : public cocos2d::Node
{
public:

	virtual bool init();

	CREATE_FUNC(CloudSeed);
	void setBounds(float upBounds,float downBounds,float leftBounds,float rightBounds);
	float getOriginalPositionX();
	float getOriginalPositionY();
	bool checkWidthBounds(Cloud* mSpir);
	void updatePositionHorizen(float dt);
	void seedClouds(float dt);
	//void seedClouds( cocos2d::CCLayer *layer,int Zorder);
	cocos2d::Vector<Cloud*> getSpriteList();
	int Random(int m, int n);
	void initCloudEngine(cocos2d::Layer *layer,struct BounsStruct mstrct,CLOUD_SEED_TYPE seedMode,int Zorder);
	void startCloudEngine();
	float getCloudScaleRamdomRate();
	const char* getSpiriteName(int index);
	int randTexture();
	void setSeedType(CLOUD_SEED_TYPE type);
	void setCloudFixedHeight(float cHeight);
	void initSingleCloud( Cloud* mSpir );
	void clearCloud(float dt);
private:
	static CloudSeed * instance;
	static cocos2d::Vector<Cloud*> mSpriteList;
	static cocos2d::CCLayer *mlayer;
	static int mZorder;
	static struct  BounsStruct  cloudBounds ;
	static CLOUD_SEED_TYPE mytype;
	int cloudDirection;
	static float cloudsFixedHeight;
	static bool hasFixedHeight;
	static float CLOUD_MOVE_STEP;
	static float CLOUD_SIZE_SCALE;
	static int CLOUD_SUM;
	static float CLOUD_SEED_BREAKTIME;
};

#endif // __CLOUD_SEED_H__
