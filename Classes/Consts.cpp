
//we may make a function to change the theme of our game


	//Game BASIC
	static const char * GAME_BACKGROUND_PICTURE = "gamebg.jpg";
	static const char * GAME_BACKGROUND_MUSIC = "music/background_M_Menu.mid";


	static const char * GAME_START_BUTTON_NORMAL = "gamestart.png";
	static const char * GAME_START_BUTTON_DOWN = "gamestartdown.png";

	static const char * BACKGROUND_MUSIC_ON = "audioopen.png";
	static const char * BACKGROUND_MUSIC_OFF = "audioclose.png";




	//Cloud System
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const char * CLOUD_PICTURE_PREFIX = "Items/Item_";
	static const char * CLOUD_PICTURE_DEFAULT = "Items/Item_2.png";

#else
	static const char * CLOUD_PICTURE_PREFIX = "cloud";
	static const char * CLOUD_PICTURE_DEFAULT = "cloud2.png";
#endif
	static const char * CLOUD_PICTURE_TYPE = "png";
	static const  int  CLOUD_PICTURE_MAX_INDEX = 14;



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
	static const char * HOME_PICTURE_NORMAL = "twitterdefault.png";
	static const char * HOME_PICTURE_DOWN =  "twitterdown.png";

	class Consts
	{
	public:
		Consts();
		~Consts();

	private:

	};

	Consts::Consts()
	{
	}

	Consts::~Consts()
	{
	}