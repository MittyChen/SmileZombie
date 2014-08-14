#include "SurroundingsSprite.h"
#include "SZTimeSystem.h"
#include "GameScene.h"


USING_NS_CC;

// on "init" you need to initialize your instance
bool SurroundingsSprite::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	nightDarkRate = 1.0f;

	initShaders();

	return true;
}

const char* SurroundingsSprite::getSpiriteName(int index)
{
	
	if(index>=0 && index<=max_index)
	{
		CCString* resToRet = CCString::createWithFormat( "%s%d.%s",filePrefix,index,fileType);
		//mapbg/dungeon_battle_
		CCLOG("SurroundingsSprite::getSpiriteName  %s",resToRet->getCString());
		return resToRet->getCString();
	}
	return  getSpiriteName(0);
}

int SurroundingsSprite::randTexture(int maxVa)
{
	srand( (unsigned)time( NULL ) ); 
	return rand()%(maxVa+1);
}


void  SurroundingsSprite::initBaseTexture(	const char* filePrefix,const char* filetype,int max_index)
{
	this->max_index =max_index;
	this->filePrefix = filePrefix;
	this->fileType=filetype;

	//Ëæ»úÉú³É
	this->setTexture(getSpiriteName(randTexture(max_index)));

	 schedule(schedule_selector( SurroundingsSprite::goDark) ,0.1f,kRepeatForever, 0.0f);
}

void SurroundingsSprite::setTextureByindex(int index)
{

	this->setTexture(getSpiriteName(index));
}

void SurroundingsSprite::goDark(float dt)
{
	if(SZTimeSystem::getInstance()->needChangeStatus() )
	{
		if(SZTimeSystem::currentDayBlock < SZTimeSystem::lastDayBlock  )
		{
			if( nightDarkRate >(0.1f * SZTimeSystem::currentDayBlock))
			{
				_glprogramstate->setUniformFloat("nightDegree", nightDarkRate-=0.02f);
				if(nightDarkRate < (0.1f * SZTimeSystem::currentDayBlock) )
				{
					SZTimeSystem::getInstance()->setNeedChangeStatus(false);
				}
			}
		}
		else
		{
			if( nightDarkRate < (0.1f * SZTimeSystem::currentDayBlock))
			{
				_glprogramstate->setUniformFloat("nightDegree", nightDarkRate+=0.02f);
				if(nightDarkRate > (0.1f*SZTimeSystem::currentDayBlock))
				{
					SZTimeSystem::getInstance()->setNeedChangeStatus(false);
				}			
			}
		}
	}
}

void SurroundingsSprite::initShaders()
{
	
	
	auto fileUtiles = FileUtils::getInstance();
	auto fragmentFullPath = fileUtiles->fullPathForFilename("SZShaders/night.fsh");
	auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
	auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
	_glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);

	nightDarkRate =  0.1f* SZTimeSystem::getInstance()->getDayStatus();
	_glprogramstate->setUniformFloat("nightDegree",nightDarkRate);

	this->setGLProgramState(_glprogramstate);

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
