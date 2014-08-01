#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "LonelyFlower.h"
#include "CloudSeed.h"
#include "cocos-ext.h"
#include "cocostudio/CCArmature.h"
#include "ui/UIWidget.h"

USING_NS_CC; 

using namespace ui;
class MainMenuScene : public cocos2d::Layer
{
public:
	MainMenuScene(void);
	~MainMenuScene(void);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

	virtual void update(float delta);

	 virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	 virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	 virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	 virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	 void updateFlowers(float dt);
	 void setParticlesystem(cocos2d::Vec2 mlocation,float amAngle);
	 void cleanupParticleSystem(float dt);
	 void goGameScene(float t);
	 void touchEvent(Ref *pSender, Widget::TouchEventType type);

private:
	LonelyFlower * mFlower;
	cocos2d::CCParticleSystem *memitter;
	float flowerAn;
	cocos2d::Texture2D* particleTexture;
	CloudSeed* mclouds;
	cocostudio::CCArmature* armature;
public:
	enum NodeZorder
	{
		FLOWER_ZORDER = 10,
		PARTICLE_ZORDER = -10,
		TOP_LAYER_ZORDER = -20
	};

};

#endif // __MAIN_MENU_SCENE_H__