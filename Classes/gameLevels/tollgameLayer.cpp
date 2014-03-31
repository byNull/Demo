//
//  tollgateLayer .cpp
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#include "tollgameLayer.h"
#include "common.h"


USING_NS_CC;

// static memeber initialization

int TollgameLayer::sGameLevel = 0;

CCScene* TollgameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TollgameLayer *layer = TollgameLayer::create();
    
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TollgameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    
    // add "关卡背景图片" splash screen"
    CCSprite* pSprite = CCSprite::create("levelbg.png");
    assert(pSprite != NULL);
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
  
    
    this->setTouchEnabled(true);
    
    return true;
}

bool TollgameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return (true);
}

void TollgameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}



void TollgameLayer::registerWithTouchDispatcher()
{
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -120, true);
}



void TollgameLayer::returnCallback(CCObject* pSender)
{
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
//    
//    pDirector->setOpenGLView(pEGLView);
//    
//    // turn on display FPS
//    pDirector->setDisplayStats(true);
//    
//    // set FPS. the default value is 1.0/60 if you don't call this
//    pDirector->setAnimationInterval(1.0 / 60);
//    
//    // create a scene. it's an autorelease object
//    CCScene *pHwScene = HelloWorld::scene();
//    
//    
//    // run
//    pDirector->replaceScene(pHwScene);
    
}

void TollgameLayer::setGameLevel(const int lvl)
{
    sGameLevel = lvl;
}




