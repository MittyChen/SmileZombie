#include "MainMenuScene.h"
#include "UIButton.h"
#include "GameScene.h"
#include "SZTimeSystem.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::extension;
using namespace ui;
MainMenuScene::MainMenuScene(void)
{
	flowerAn  =  0;
	memitter  = NULL;
	particleTexture = TextureCache::sharedTextureCache()->addImage("flowers/flower_1.png");
	mFlower = NULL;
}
MainMenuScene::~MainMenuScene(void)
{
}
Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*auto mTopLayer = LayerColor::create(ccc4(0,50,50,255));
	mTopLayer->setZOrder(TOP_LAYER_ZORDER);
	this->addChild(mTopLayer);*/

	auto bgSpirit = Sprite::create("gamebg.jpg");
	bgSpirit->setPosition(Vec2(origin.x + visibleSize.width - bgSpirit->getContentSize().width/2 ,
		origin.y + bgSpirit->getContentSize().height/2));

	bgSpirit->setZOrder(TOP_LAYER_ZORDER);

	this->addChild(bgSpirit);

	mclouds = NULL;

	auto event =EventListenerTouchOneByOne::create();
	event->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan,this);
	event->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled,this);
	event->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded,this);
	event->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
	do
	{
		CC_BREAK_IF(! Layer::init());
		this->scheduleUpdate();
	} while (0);
	 
		//mclouds->setBounds(visibleSize.height*0.95,visibleSize.height*0.7,-90.0f,visibleSize.width);
		struct BounsStruct mCloudBouds ={origin.y + visibleSize.height*0.8,origin.y+visibleSize.height*0.7,origin.x -90.0f,origin.x + visibleSize.width};
		CloudSeed::getInstance()->initCloudEngine(this,mCloudBouds,CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_RANDOM,TOP_LAYER_ZORDER);
		CloudSeed::getInstance()->setCloudFixedHeight(600);
		CloudSeed::getInstance()->startCloudEngine();


		this->schedule(schedule_selector(MainMenuScene::updateFlowers) ,2.0f,kRepeatForever, 0.0f);


	////¹Ç÷À¶¯»­
	cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("birdres/bird0.png","birdres/bird0.plist","birdres/bird.ExportJson");
	armature = cocostudio::CCArmature::create("bird");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.6);
	armature->getAnimation()->setSpeedScale(0.5);
	armature->setPosition(ccp(900,600));
	armature->setRotation(-25);
	
	auto mfly = CCMoveTo::create(5,Vec2(100,600));
	armature->runAction(mfly);
	addChild(armature);




	auto label = LabelTTF::create("MainMenu Scene", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);



	// Create the button
	Button* button = Button::create("twitterdefault.png","twitterdown.png");
	button->setPosition(button->getSize());
	button->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
	button->setScale(0.5);
	this->addChild(button);

	SZTimeSystem::getInstance()->init();

    return true;
}


bool MainMenuScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("HelloWorld::onTouchBegan");
	Vec2 currentLocation = touch->getLocation();
	Vec2 previousLocation = touch->getPreviousLocation();
	cleanupParticleSystem(0);
	setParticlesystem(currentLocation,270.0f);

	return true;
}

void MainMenuScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 currentLocation = touch->getLocation();
	Vec2 previousLocation = touch->getPreviousLocation();
	Vec2 moveVector  = previousLocation-currentLocation;

	float mAngle  = ccpAngleSigned(moveVector,Vec2(1.0f,0.0f));

	 float cocosAngle = CC_RADIANS_TO_DEGREES(-1*mAngle);
	if(mFlower)
	{
		mFlower->setPosition(currentLocation);  
	}

	if(memitter)
	{
		memitter->setPosition(currentLocation);  
		memitter->setAngle(cocosAngle);
	}
}

void MainMenuScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	cleanupParticleSystem(0);
	//this->scheduleOnce(schedule_selector(MainMenuScene::cleanupParticleSystem) ,2.0f);
}

void MainMenuScene::onTouchCancelled(Touch *touch, Event *unused_event)
{

}


void MainMenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
 void MainMenuScene::update(float delta)
 {
	 flowerAn += 60;
 }

 void MainMenuScene::updateFlowers(float dt)
 {
	 if(mFlower)
	 {
		 mFlower->setRotation(flowerAn);//flower rotate
		 mFlower->flowerBreath();
	 }
 }

 void MainMenuScene::setParticlesystem(Vec2 mlocation,float amAngle)
 {

	    //CCParticleExplosion±¬Õ¨
		// CCParticleFire »ð
		// CCParticleFireworksÑÌ»ð
		// CCParticleFlower»¨
		// CCParticleGalaxy ÒøºÓ
		// CCParticleMeteor Á÷ÐÇ
		// CCParticleRain ÏÂÓê
		// CCParticleSmoke ÏÂÑ©
		// CCParticleSnow ´¶ÑÌ
		// CCParticleSpiral ÂÝÐý
		// CCParticleSun Ì«ÑôÑæ
	 if(!memitter)
	 {
	 	/* memitter = CCParticleFireworks::create();  
		 memitter->setDuration( kCCParticleDurationInfinity);  
		 memitter->setTotalParticles(50);
		 memitter->retain();  
		 this->addChild(memitter, -10);  
		 memitter->setTexture( particleTexture );  
		 memitter->setPosition(mlocation);  
		 memitter->setStartSize(10);
		 memitter->setStartSizeVar(1);
		 memitter->setRadialAccel(20);  
		 memitter->setRadialAccelVar(1);
		 memitter->setAngle(amAngle);
		 memitter->setVisible(true);*/
		 memitter= ParticleSystemQuad::create();
		 memitter->retain(); 
		 this->addChild(memitter,1);  
		 memitter->setTotalParticles(100);
		 memitter->setTexture(particleTexture);  
		 memitter->setDuration(-1);
		 memitter->setGravity(CCPointZero);
		 memitter->setAngle(0);  
		 memitter->setAngleVar(360);
		 memitter->setSpeed(50);  
		 memitter->setSpeedVar(10);
		 memitter->setRadialAccel(70);  
		 memitter->setRadialAccelVar(10);
		 memitter->setTangentialAccel(0);  
		 memitter->setTangentialAccelVar(0);  
		 memitter->setPosVar(ccp(100,100));
		 memitter->setLife(2);  
		 memitter->setLifeVar(0.3f);
		 memitter->setStartColor(Color4F(0.5,0.5,0.5,1.0));  
		 memitter->setStartColorVar(Color4F(0.5,0.5,0.5,1.0));
		 Color4F cccEnd=Color4F(0.5,0.5,0.5,1.0);  
		 memitter->setStartColor(cccEnd);  
		 memitter->setStartColorVar(cccEnd);
		 memitter->setStartSize(10);  
		 memitter->setStartSizeVar(20);
		 memitter->setStartSize(12);  
		 memitter->setStartSizeVar(12);
		 memitter->setEmissionRate(memitter->getTotalParticles()/memitter->getLife());  
		 memitter->setPosition(mlocation);  
		 memitter->setAngle(amAngle);
		 memitter->setVisible(true);
		 memitter->setZOrder(PARTICLE_ZORDER);
	 }
	 if(!mFlower)
	 {
		 mFlower = (LonelyFlower *)Sprite::create("flowers/flower_1.png");
		 mFlower->setVisible(true);
		 mFlower->setZOrder(FLOWER_ZORDER);
		 mFlower->setPosition(mlocation);
		 this->addChild(mFlower);

	 }else
	 {
			 mFlower->initFlowerTexture();
			 mFlower->setPosition(mlocation);
			 mFlower->setVisible(true);
	 }
 }

 void MainMenuScene::cleanupParticleSystem(float dt)
 {
	 if(memitter)
	 {
		 this->removeChild(memitter);
		 memitter->setVisible(false);
		 memitter->cleanup();
		 memitter->release();
		 memitter = NULL;
	 }
	 if(mFlower)
	 {
		 mFlower->setVisible(false);
	 }
 }


 void MainMenuScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
 {
	 switch (type)
	 {
	 case Widget::TouchEventType::BEGAN:
		 break;

	 case Widget::TouchEventType::MOVED:
		 break;

	 case Widget::TouchEventType::ENDED:
		goGameScene(0);
		 break;

	 case Widget::TouchEventType::CANCELED:
		 break;

	 default:
		 break;
	 }
 }

 void MainMenuScene::goGameScene(float t)
 {
	 auto scene = GameScene::createScene();
	 Director::getInstance()->replaceScene(scene);
 }