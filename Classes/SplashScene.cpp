#include "SplashScene.h"
#include "MainMenuScene.h"
#include "cocostudio/CCArmature.h"
#include "Consts.h"
#include "CommonUtils.h"


USING_NS_CC;
using namespace cocostudio;
using namespace  CocosDenshion;
Scene* SplashScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	//auto sprite = Sprite::create("baby.png");
	//// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	//// add the sprite as a child to this layer
	//this->addChild(sprite, 0);
	//FadeOut* mFade =  FadeOut::create(3.0f);
	//sprite->runAction(mFade);
	//scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);

	cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("giftest/giftest0.png","giftest/giftest0.plist","giftest/giftest.ExportJson");
	CCArmature *armature = CCArmature::create("giftest");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	addChild(armature);
	FadeOut* mFade =  FadeOut::create(3.0f);
	armature->runAction(mFade);
	scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);

	CommonUtils::preloadAudioResources();

	//Time Block
	{
		SZTimeSystem::getInstance();
	}

	return true;
}


 void SplashScene::goGameScene(float t)
 {
		auto scene = MainMenuScene::createScene();
		 Director::getInstance()->replaceScene(scene);
 }