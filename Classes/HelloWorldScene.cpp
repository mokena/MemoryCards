#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CardFactory.h"
#include "Card.h"
#include "GameLevel.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	LevelData data = {};
	data.column = 4;
	data.row = 4;
	auto level = GameLevel::create(data);
	float scale = visibleSize.width / (level->getContentSize().width + 40);
	
	level->setAnchorPoint(Vec2(0.5, 0.5));
	level->ignoreAnchorPointForPosition(false);
	level->setPosition(visibleSize/2);
	level->setScale(scale);
	level->registerCallback([&](CardData* dataA, CardData* dataB) {
		if (dataA->number == dataB->number) {
			CCLOG("paired!");
		}
		else {
			CCLOG("Not a match!");
		}
	}, [&]() {
		CCLOG("Congratulations, you finished!");
	});
	
	addChild(level);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
