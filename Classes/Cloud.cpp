#include "Cloud.h"
#include "Consts.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Cloud::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	initCloudTexture();
	return true;
}
const char* Cloud::getSpiriteName(int index)
{
	if(index>=0 && index<=CLOUD_PICTURE_MAX_INDEX)
	{
		CCString* resToRet = CCString::createWithFormat( "%s%d.%s",CLOUD_PICTURE_PREFIX,index,CLOUD_PICTURE_TYPE);
		return resToRet->getCString();
	}
	return  CLOUD_PICTURE_DEFAULT;
}

int Cloud::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%(CLOUD_PICTURE_MAX_INDEX+1);
}


void  Cloud::initCloudTexture()
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