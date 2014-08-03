#include "Cloud.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool Cloud::init()
{
	__super::init();
	initCloudTexture();
	return true;
}
const char* Cloud::getSpiriteName(int index)
{
	CCLOG("Cloud::getSpiriteName  %d",index);
	if(index>=0 && index<=4)
	{
		CCString* resToRet = CCString::createWithFormat( "clouds/cloud%d.png",index);

		return resToRet->getCString();
	}

	return  "clouds/cloud2.png";

}

int Cloud::randTexture()
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%5;
}


void  Cloud::initCloudTexture()
{
	this->setTexture(getSpiriteName(randTexture()));
	if(true)
	{
		auto fileUtiles = FileUtils::getInstance();
		auto fragmentFullPath = fileUtiles->fullPathForFilename("SZShaders/greycloud.fsh");
		auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
		auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
		setGLProgramState(GLProgramState::getOrCreateWithGLProgram(glprogram));

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
#endif
	}
else
{//addNormal shader
	this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
}
}

void Cloud::setTexture(const std::string &filename)
{
	__super::setTexture(filename);
}

void Cloud::flowerBreath()
{
	CCAction*  action = Sequence::createWithTwoActions(	ScaleTo::create(1, 0.6f), ScaleTo::create(1, 1.0f));
	this->runAction(action); 
}

void Cloud::setCloudDirection(int dir)
{
	if(dir>1)
	{
		dir =1;
	}
	if(dir<-1)
	{
		dir =-1;
	}
	if(dir==0)
	{
		CCLOG("this cloud will not move");
	}
	cloudDirection = dir;
}

int Cloud::getCloudDirection()
{
	return cloudDirection;
}

 bool Cloud::initWithTexture(Texture2D *texture)
{
	__super::initWithTexture(texture);

	return true;
}