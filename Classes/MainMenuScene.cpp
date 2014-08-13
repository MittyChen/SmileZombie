#include "MainMenuScene.h"
#include "UIButton.h"
#include "GameScene.h"
#include "SZTimeSystem.h"
#include "Consts.h"
#include "UICheckBox.h"
MainMenuScene * MainMenuScene::instance = NULL;

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::extension;
using namespace ui;
using namespace  CocosDenshion;

MainMenuScene::MainMenuScene(void)
{
	flowerAn  =  0;
	memitter  = NULL;
	particleTexture = TextureCache::sharedTextureCache()->addImage("flowers/flower_1.png");
	mFlower = NULL;
}
MainMenuScene::~MainMenuScene(void)
{
	this->unschedule(schedule_selector(MainMenuScene::updateFlowers));
	this->unscheduleUpdate();
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
	
	//Data get
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bool audioIsOn = CCUserDefault::sharedUserDefault()->getBoolForKey("AUDIO_ON");

		//UI Block
	{
		
		/*auto mTopLayer = LayerColor::create(ccc4(0,50,50,255));
		mTopLayer->setZOrder(TOP_LAYER_ZORDER);
		this->addChild(mTopLayer);*/

		auto bgSpirit = Sprite::create(GAME_BACKGROUND_PICTURE);
		bgSpirit->setPosition(Vec2(origin.x + visibleSize.width - bgSpirit->getContentSize().width/2 ,
			origin.y + bgSpirit->getContentSize().height/2));
		bgSpirit->setZOrder(TOP_LAYER_ZORDER);
		this->addChild(bgSpirit);


		auto label = LabelTTF::create("MainMenu Scene", "Arial", 24);
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width/2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);

		

		// Create the checkbox
		CheckBox* checkBox_audio = CheckBox::create(BACKGROUND_MUSIC_OFF,
			BACKGROUND_MUSIC_ON,
			BACKGROUND_MUSIC_ON,
			BACKGROUND_MUSIC_ON,
			BACKGROUND_MUSIC_ON);
		checkBox_audio->setPosition(Vec2(origin.x+checkBox_audio->getContentSize().width/2,origin.y+visibleSize.height/2-checkBox_audio->getContentSize().height/2));
		checkBox_audio->setSelectedState(audioIsOn);
		checkBox_audio->setTag(AUDIO_BUTTON);
		checkBox_audio->addEventListener(CC_CALLBACK_2(MainMenuScene::touchAudioButton, this));
		this->addChild(checkBox_audio);

		//game statrt button
		Button* button = Button::create(GAME_START_BUTTON_NORMAL,GAME_START_BUTTON_DOWN);
		button->setPosition(Vec2(origin.x + visibleSize.width/2 ,
												origin.y + visibleSize.height/2 - button->getContentSize().height/2));
		button->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::touchEvent, this));
		button->setScale(0.5);
		this->addChild(button);
	}

	//Sound Block
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		if(audioIsOn)
		{
			if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			{
					SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_BACKGROUND_MUSIC_WIN32,1); 
			}
		}
#else
		if(audioIsOn)
		{
			if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			{
				SimpleAudioEngine::getInstance()->playBackgroundMusic(GAME_BACKGROUND_MUSIC,1); 
			}
		}
#endif

 
	}


	//Touch Block
	{
		auto event =EventListenerTouchOneByOne::create();
		event->onTouchBegan = CC_CALLBACK_2(MainMenuScene::onTouchBegan,this);
		event->onTouchCancelled = CC_CALLBACK_2(MainMenuScene::onTouchCancelled,this);
		event->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded,this);
		event->onTouchMoved = CC_CALLBACK_2(MainMenuScene::onTouchMoved,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(event,this);

	}




	//Elements Block
	{

		this->schedule(schedule_selector(MainMenuScene::updateFlowers) ,2.0f,kRepeatForever, 0.0f);
//		{
//			////¹Ç÷À¶¯»­
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//			cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("birdres/bird0.png","birdres/bird0.plist","birdres/bird.ExportJson");
//
//#else
//			cocostudio::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("bird0.png","bird0.plist","bird.ExportJson");
//#endif
//			armature = cocostudio::CCArmature::create("bird");
//			armature->getAnimation()->playByIndex(0);
//			armature->setScale(0.6);
//			armature->getAnimation()->setSpeedScale(0.5);
//			armature->setPosition(ccp(900,600));
//			armature->setRotation(-25);
//
//			auto mfly = CCMoveTo::create(5,Vec2(100,600));
//			armature->runAction(mfly);
//			addChild(armature);
//		}

	}


	//Schedule Block
	{
		this->scheduleUpdate();
	} 

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

 MainMenuScene* MainMenuScene::getInstance()
 {
	 if(!instance)
	 {
		 instance = MainMenuScene::create();
	 }
	 return  instance;
 }
  MainMenuScene* MainMenuScene::create() 
 { 
	 MainMenuScene *pRet = new MainMenuScene(); 
	 if (pRet && pRet->init()) 
	 { 
		 pRet->autorelease(); 
		 return pRet; 
	 } 
	 else 
	 { 
		 delete pRet; 
		 pRet = NULL; 
		 return NULL; 
	 } 
 }

  void MainMenuScene::touchAudioButton( Ref *pSender, CheckBox::EventType type )
  {

	  bool audioIsOn = CCUserDefault::sharedUserDefault()->getBoolForKey("AUDIO_ON");
	  switch (type)
	  {
	  case CheckBox::EventType::SELECTED:
		  //audio button
		  CCUserDefault::sharedUserDefault()->setBoolForKey("AUDIO_ON", true);
		  if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		  {
			  CCLOG("isBackgroundMusicPlaying");
		  }
			  SimpleAudioEngine::getInstance()->resumeBackgroundMusic(); 
		  break;

	  case CheckBox::EventType::UNSELECTED:
		  if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		  {
			  CCLOG("isBackgroundMusicPlaying");
		  }
			CCUserDefault::sharedUserDefault()->setBoolForKey("AUDIO_ON", false);
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); 
		  break;

	  default:
		  //audio button
		  CCUserDefault::sharedUserDefault()->setBoolForKey("AUDIO_ON", false);
		  break;
	  }

	  CCUserDefault::sharedUserDefault()->flush();

  }
