#include "SplashScene.h"

USING_NS_CC;

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

	/////////////////////////////
	// 3. add your codes below...

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("giraffe.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	CCFadeOut* mFade =  CCFadeOut::create(3.0f);
	sprite->runAction(mFade);
	scheduleOnce(schedule_selector(SplashScene::goGameScene) , 3.0f);

	this->scheduleUpdate();  

	return true;
}


 void SplashScene::goGameScene(float t)
 {
		auto scene = GameScene::createScene();
		 Director::getInstance()->replaceScene(scene);
 }