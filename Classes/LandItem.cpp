#include "LandItem.h"
#include "Consts.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LandItem::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	initLandItemTexture();
	return true;
}
const char* LandItem::getSpiriteName(int index)
{
	CCLOG("LandItem::getSpiriteName  %d",index);
	if(index>=0 && index<=LAND_ITEMS_PICTURE_MAX_INDEX)
	{
		CCString* resToRet = CCString::createWithFormat( "%s%d.%s",LAND_ITEMS_PICTURE_PREFIX,index,LAND_ITEMS_PICTURE_TYPE);
		return resToRet->getCString();
	}
	return LAND_ITEMS_PICTURE_DEFAULT;
}

int LandItem::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%(LAND_ITEMS_PICTURE_MAX_INDEX+1);
}


void  LandItem::initLandItemTexture()
{
	setTexture(getSpiriteName(randTexture()));

	if(SZTimeSystem::getInstance()->getDayChangeGLState() != NULL)
	{
		//setGLProgramState(SZTimeSystem::getInstance()->getDayChangeGLState() );	
	}

	/*auto fileUtiles = FileUtils::getInstance();
	auto fragmentFullPath = fileUtiles->fullPathForFilename("SZShaders/night.fsh");
	auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
	auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	GLProgramState *_glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	_glprogramstate->setUniformFloat("nightDegree", 0.1f* SZTimeSystem::getInstance()->getDayStatus());
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		_backgroundListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED,
			[this](EventCustom*)
		{
			glprogram->reset();
			glprogram->initWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
			glprogram->link();
			glprogram->updateUniforms();
		}
		);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backgroundListener, -1);
#endif*/
}