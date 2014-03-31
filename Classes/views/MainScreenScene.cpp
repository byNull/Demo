//
//  MainScreenScene.cpp
//  Demo
//
//  Created by Apple on 3/23/14.
//
//

#include "MainScreenScene.h"
#include "HelloWorldScene.h"
#include "tollgateSelectionScene.h"
#include "cocos-ext.h"
#include "ccXmlParser.h"
#include "support/tinyxml2/tinyxml2.h"


using namespace tinyxml2;



using namespace cocos2d::extension;

USING_NS_CC;

CCScene* MainSceneLayer::scene()
{
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainSceneLayer *layer = MainSceneLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainSceneLayer::init()
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
    
    // add a "Return" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pReturnItem = CCMenuItemImage::create(
                                                          "return.png",
                                                          "return.png",
                                                          this,
                                                          menu_selector(MainSceneLayer::menuReturnCallback));
    pReturnItem->setAnchorPoint(ccp(0, 0));
	pReturnItem->setPosition(CCPointZero);
    //pReturnItem->setAnchorPoint(ccp(0.5, 0.5));
    
    
    // add Enter button
    CCLabelTTF *pStLbl = CCLabelTTF::create("START", "Arial", 30);
    CCMenuItemLabel* myStartItemLbl = CCMenuItemLabel::create(pStLbl, this,
                                                              menu_selector(MainSceneLayer::gameStartCallback));
    myStartItemLbl->setAnchorPoint(ccp(1.0, 0.0));
    myStartItemLbl->setPosition(ccp(origin.x + visibleSize.width, origin.y));
    
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(myStartItemLbl, pReturnItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Welcome, Enter DemoGame", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    
    this->setTouchEnabled(true);
    
    return true;
}


void MainSceneLayer::menuReturnCallback(CCObject* pSender)
{
    CCLog("MainSceneLayer::menuReturnCallback");
    CCScene *pScene = HelloWorld::scene();
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}


void MainSceneLayer::onEnterTransitionDidFinish()
{
    //当游戏闪屏画面进入后，进入初始化界面
    CCLog("MainSceneLayer::onEnterTransitionDidFinish\n");
    
}

void MainSceneLayer::gameStartCallback(cocos2d::CCObject *pSender)
{
    CCLog("MainSceneLayer::gameStartCallback");
    
    CCScene *pScene = tollgateSelectionScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}

void MainSceneLayer::ccTouchesBegin(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("MainSceneLayer::ccTouchesBegin\n");
}



