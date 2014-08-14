#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include "cocos2d.h"
class CommonUtils
{
public:
	CommonUtils(void);
	~CommonUtils(void);
	static void preloadAudioResources();
	static void playBackgrondMusic();
	static void playButtonTouchMusic();
	static void setEffectMusicShouldPlay(bool val);

private:
	static bool effectMusicShouldPlay;

};

#endif