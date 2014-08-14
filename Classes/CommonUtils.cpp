#include "CommonUtils.h"
#include "cocos2d.h"
#include "Consts.h"
 
using namespace CocosDenshion;
using namespace cocos2d;

 bool CommonUtils::effectMusicShouldPlay = false;


CommonUtils::CommonUtils(void)
{
}


CommonUtils::~CommonUtils(void)
{
}

void CommonUtils::preloadAudioResources()
{
	effectMusicShouldPlay = UserDefault::getInstance()->getBoolForKey("AUDIO_EFFECT_ON");
 
	//资源加载
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_BACKGROUND_MUSIC)).c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathForFilename(GAME_TOUCH_BUTTON_MUSIC)).c_str());

	//音量
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);  
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);  
}

void CommonUtils::playBackgrondMusic()
{
		if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::sharedFileUtils()->fullPathForFilename(GAME_BACKGROUND_MUSIC).c_str(),true); 
		}
}

void CommonUtils::playButtonTouchMusic()
{ 
	if(effectMusicShouldPlay)
	{
		SimpleAudioEngine::getInstance()->playEffect(std::string(FileUtils::sharedFileUtils()->fullPathForFilename(GAME_TOUCH_BUTTON_MUSIC)).c_str());
	}
}

void CommonUtils::setEffectMusicShouldPlay(bool val)
{
	effectMusicShouldPlay = val;
}



