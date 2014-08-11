#include "GameScene.h"
#include "SurroundingsSprite.h"
#include "UIButton.h"

#include "MainMenuScene.h"
#include "Consts.h"
USING_NS_CC;

using namespace cocostudio;
using namespace cocos2d::extension;

GameScene * GameScene::instance = NULL;
cocos2d::LabelTTF* GameScene::dayStatusLabel = NULL;
GameScene::GameScene(void)
{
	flowerAn  =  0;
	memitter  = NULL;
	mFlower = NULL;
}
GameScene::~GameScene(void)
{
}
Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		particleTexture = TextureCache::sharedTextureCache()->addImage("flowers/flower_1.png");
#else
		particleTexture = TextureCache::sharedTextureCache()->addImage("flower_1.png");
#endif



	gameBG = SurroundingsSprite::create();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	gameBG->initBaseTexture(GAME_SCENE_BACKGROUND_PICTURE_PREFIX,GAME_SCENE_BACKGROUND_PICTURE_TYPE,GAME_SCENE_BACKGROUND_PICTURE_£ÍAXINDEX);
#else
		gameBG->initBaseTexture("dungeon_battle_","jpg",13);
#endif


	/*auto mTopLayer = LayerColor::create(ccc4(0,50,50,255));
	mTopLayer->setZOrder(TOP_LAYER_ZORDER);
	this->addChild(mTopLayer);*/

	//gameBG->setTextureByindex(2);//set bg handly
	gameBG->setTexture("bgtest.png");
	gameBG->setPosition(Vec2(origin.x + visibleSize.width - gameBG->getContentSize().width/2 ,
		origin.y + gameBG->getContentSize().height/2));

	gameBG->setZOrder(TOP_LAYER_ZORDER);

	this->addChild(gameBG);

	mclouds = NULL;

	auto event =EventListenerTouchOneByOne::create();
	event->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	event->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled,this);
	event->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	event->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);


	do
	{
		CC_BREAK_IF(! Layer::init());
		this->scheduleUpdate();
	} while (0);
	 
	if(!mclouds)
	{
		mclouds = CloudSeed::create();
		mclouds->setUseRandomScale(false);
		//mclouds->setBounds(visibleSize.height*0.95,visibleSize.height*0.7,-90.0f,visibleSize.width);
		struct BounsStruct mCloudBouds ={origin.y + visibleSize.height*0.8,origin.y+visibleSize.height*0.7,origin.x -90.0f,origin.x + visibleSize.width};
		mclouds->initCloudEngine(this,mCloudBouds,CLOUD_SEED_TYPE::CLOUDE_FIEXED_SEED_FROM_RIGHT,TOP_LAYER_ZORDER);
		mclouds->setCloudFixedHeight(100);
		mclouds->startCloudEngine();
	}
	this->schedule(schedule_selector(GameScene::updateFlowers) ,2.0f,kRepeatForever, 0.0f);


	////¹Ç÷À¶¯»­
	//cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("birdres/bird0.png","birdres/bird0.plist","birdres/bird.ExportJson");
	//armature = cocostudio::CCArmature::create("bird");
	//armature->getAnimation()->playByIndex(0);
	//armature->setScale(0.6);
	//armature->getAnimation()->setSpeedScale(0.5);
	//armature->setPosition(ccp(900,600));
	//armature->setRotation(-25);
	//
	//auto mfly = CCMoveTo::create(5,Vec2(100,600));
	//armature->runAction(mfly);
	//addChild(armature);


	// Create the button
	Button* button = Button::create(HOME_PICTURE_NORMAL,HOME_PICTURE_DOWN);
	button->setPosition(Vec2(origin.x+button->getContentSize().width/2,origin.y+visibleSize.height-button->getContentSize().height/2));
	button->addTouchEventListener(CC_CALLBACK_2(GameScene::touchEvent, this));
	this->addChild(button);

	auto label = LabelTTF::create("Game Scene", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	dayStatusLabel=LabelTTF::create("day", "Arial", 24);

	dayStatusLabel->setPosition(Vec2(origin.x + visibleSize.width/6,origin.y + visibleSize.height*5/6));
	cocos2d::String* mstr = cocos2d::String::createWithFormat("%d",SZTimeSystem::currentDayBlock);
	GameScene::dayStatusLabel->setString(mstr->getCString());
	this->addChild(dayStatusLabel);

	auto details=LabelTTF::create("day", "Arial", 12);
	details->setPosition(Vec2(origin.x + visibleSize.width/3,origin.y + visibleSize.height*2/6));
	details->setString("1=NIGHT 7 = DUSK 8 = MORNING 10=DAY 0=NONE");
	this->addChild(details);


    return true;
}


bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	CCLOG("HelloWorld::onTouchBegan");
	Vec2 currentLocation = touch->getLocation();
	Vec2 previousLocation = touch->getPreviousLocation();
	cleanupParticleSystem(0);
	setParticlesystem(currentLocation,270.0f);

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
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

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	cleanupParticleSystem(0);
	//this->scheduleOnce(schedule_selector(GameScene::cleanupParticleSystem) ,2.0f);
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
{

}


void GameScene::menuCloseCallback(Ref* pSender)
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
 void GameScene::update(float delta)
 {
	 flowerAn += 60;
 }

 void GameScene::updateFlowers(float dt)
 {
	 if(mFlower)
	 {
		 mFlower->setRotation(flowerAn);//flower rotate
		 mFlower->flowerBreath();
	 }

	 cocos2d::String* mstr = cocos2d::String::createWithFormat("%d",SZTimeSystem::currentDayBlock);
	 GameScene::dayStatusLabel->setString(mstr->getCString());
 }

 void GameScene::setParticlesystem(Vec2 mlocation,float amAngle)
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

 void GameScene::cleanupParticleSystem(float dt)
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
 GameScene* GameScene::getInstance()
 {
	 if(!instance)
	 {
		 instance = GameScene::create();
	 }
	 return  instance;
 }

 void GameScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
 {
	 switch (type)
	 {
	 case Widget::TouchEventType::BEGAN:
		 break;

	 case Widget::TouchEventType::MOVED:
		 break;

	 case Widget::TouchEventType::ENDED:
		 {
		 auto scene = MainMenuScene::createScene();
		 Director::getInstance()->replaceScene(scene);		 
		 }

		 break;

	 case Widget::TouchEventType::CANCELED:
		 break;

	 default:
		 break;
	 }
 }