#ifndef __ELEMENT_FACTORY_H__
#define  __ELEMENT_FACTORY_H__

#include "cocos2d.h"
#include "SZTimeSystem.h"

class Element;
struct BounsStruct
{
	float upBounds;
	float downBounds;
	float leftBounds;
	float rightBounds;
};
typedef enum 
{
	ELEMENT_FIEXED_SEED_FROM_RIGHT,
	ELEMENT_FIEXED_SEED_FROM_LEFT,
	ELEMENT_FIEXED_SEED_RANDOM,
	ELEMENT_FIEXED_SEED_FROM_RIGHT_CONTINUE
}ELEMENT_SEED_TYPE;//生产位置与方向

typedef enum 
{
	ELEMENT_CLOUDS,
	ELEMENT_LAND_ITEMS,
	ELEMENT_LAND
}ELEMENT_CONTENT_TYPE;//生产类型

class ElementFactory : public cocos2d::Node
{
public:

	virtual bool init();

	ElementFactory();
	~ElementFactory();

	/*CREATE_FUNC(ElementFactory);*/
	void setBounds(float upBounds,float downBounds,float leftBounds,float rightBounds);
	float getOriginalPositionX();
	float getOriginalPositionY();
	bool checkWidthBounds(Element* mSpir);
	void updatePositionHorizen(float dt);
	void seedElements(float dt);
	//void seedElements( cocos2d::CCLayer *layer,int Zorder);
	cocos2d::Vector<Element*> getSpriteList();
	int Random(int m, int n);
	void initElementEngine(cocos2d::Layer *layer,struct BounsStruct mstrct,ELEMENT_SEED_TYPE seedMode,
										ELEMENT_CONTENT_TYPE eleType,int Zorder,float scale,float step,int sum,float breaktime);
	void startElementEngine();
	float getElementScaleRamdomRate();
	const char* getSpiriteName(int index);
	int randTexture();
	void setSeedType(ELEMENT_SEED_TYPE type);
	void setElementFixedHeight(float cHeight);
	void initSingleElement( Element* mSpir );
	void clearElement(float dt);
	void setUseRandomScale(bool val);
	void stopElementEngine();
	Element * getElementObj();
	Element * getMaxPositionInElements();
private:
	 cocos2d::Vector<Element*> mSpriteList;
	 cocos2d::CCLayer *mlayer;
	 int mZorder;
	 struct  BounsStruct  ElementBounds ;
	 ELEMENT_SEED_TYPE mytype;
	 ELEMENT_CONTENT_TYPE meleType;
	 float ElementsFixedHeight;
	 bool hasFixedHeight;
	 float Element_MOVE_STEP;
	 float Element_SIZE_SCALE;
	 int Element_SUM;
	 float Element_SEED_BREAKTIME;
	 int useRandomScale;

	 

};

#endif // __ELEMENT_FACTORY_H__
