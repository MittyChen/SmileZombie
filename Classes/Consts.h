
//we may make a function to change the theme of our game


	//Game BASIC
	static const char * GAME_BACKGROUND_PICTURE = "gamebg.jpg";
	static const char * GAME_BACKGROUND_MUSIC = "background_M_Menu.wav";
	static const char* GAME_TOUCH_BUTTON_MUSIC = "touchbutton.wav";
	static const char * GAME_START_BUTTON_NORMAL = "playnormal.png";
	static const char * GAME_START_BUTTON_DOWN = "playdown.png";
	static const char * BACKGROUND_MUSIC_BUTTON_ON = "bgon.png";
	static const char * BACKGROUND_MUSIC_BUTTON_OFF = "bgoff.png";
	static const char * GAME_EFFECT_BUTTON_ON = "effecton.png";
	static const char * GAME_EFFECT_BUTTON_OFF = "effectoff.png";
	static const char * GAME_TITTLE_PICTURE = "gametitle.png";
	


	//Cloud System
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * CLOUD_PICTURE_PREFIX = "clouds/cloud_";
	static const char * CLOUD_PICTURE_DEFAULT = "clouds/cloud_2.png";

#else
	static const char * CLOUD_PICTURE_PREFIX = "cloud";
	static const char * CLOUD_PICTURE_DEFAULT = "cloud2.png";
#endif
	static const char * CLOUD_PICTURE_TYPE = "png";
	static const  int  CLOUD_PICTURE_MAX_INDEX = 4;


	//Cloud System
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * LAND_ITEMS_PICTURE_PREFIX = "items/item_";
	static const char * LAND_ITEMS_PICTURE_DEFAULT = "items/item_2.png";

#else
	static const char * LAND_ITEMS_PICTURE_PREFIX = "item_";
	static const char * LAND_ITEMS_PICTURE_DEFAULT = "item_2.png";
#endif
	static const char * LAND_ITEMS_PICTURE_TYPE = "png";
	static const  int  LAND_ITEMS_PICTURE_MAX_INDEX = 14;


	//Cloud System
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * LAND_PICTURE_PREFIX = "land_";
	static const char * LAND_PICTURE_DEFAULT = "land_0.png";

#else
	static const char * LAND_PICTURE_PREFIX = "land_";
	static const char * LAND_PICTURE_DEFAULT = "land_0.png";
#endif
	static const char * LAND_PICTURE_TYPE = "png";
	static const  int  LAND_PICTURE_MAX_INDEX = 0;



//Game Scene

	//背景图
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * GAME_SCENE_BACKGROUND_PICTURE_PREFIX = "mapbg/dungeon_battle_";
	static const char * GAME_SCENE_BACKGROUND_PICTURE_DEFAULT = "mapbg/dungeon_battle_2.png";
#else
	static const char * GAME_SCENE_BACKGROUND_PICTURE_PREFIX = "dungeon_battle_";
	static const char * GAME_SCENE_BACKGROUND_PICTURE_DEFAULT = "dungeon_battle_2.jpg";
#endif
	static const char * GAME_SCENE_BACKGROUND_PICTURE_TYPE =  "jpg";//文件后缀无.
	static const  int  GAME_SCENE_BACKGROUND_PICTURE_ＭAXINDEX= 13;


//touch特效
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * FLOWER_PICTURE_PREFIX = "flowers/flower_";
	static const char * FLOWER_PICTURE_DEFAULT = "flowers/flower_";
#else
	static const char * FLOWER_PICTURE_PREFIX = "flower_";
	static const char * FLOWER_PICTURE_DEFAULT = "flower_2.png";
#endif
	static const char * FLOWER_PICTURE_TYPE =  "png";
	static const  int  FLOWER_PICTURE_MAX_INDEX = 3;


//Buttons
	//返回按钮
	static const char * BACK_PICTURE_NORMAL = "backbutton.png";
	static const char * BACK_PICTURE_DOWN =  "backbuttondown.png";


	//land 
	static const char * LAND_PICTURE_NORMAL = "land.png";
