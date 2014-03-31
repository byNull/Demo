#include "HelloWorldScene.h"
#include "cocos-ext.h"
#include "MainScreenScene.h"
#include "sptFileNames.h"

using namespace cocos2d::extension;

extern std::map<int, SubTexture*> gSubTexture;

USING_NS_CC;

bool HelloWorld::m_bEnabledEnter = false;



CCScene* HelloWorld::scene()
{
   
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // add Resource search directory
//    std::vector<std::string> searchpath;
//    searchpath.push_back("images");
//    searchpath.push_back("datas");
//    
//    CCFileUtils::sharedFileUtils()->setSearchPaths(searchpath);
    
    
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

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2,                                origin.y + pCloseItem->getContentSize().height/2));
    
    // add Enter button
    CCLabelTTF *pEnLbl = CCLabelTTF::create("START", "Arial", 30);
    CCMenuItemLabel* myEnterItemLbl = CCMenuItemLabel::create(pEnLbl, this,
                                                              menu_selector(HelloWorld::gameEnterCallback));
    myEnterItemLbl->setPosition(ccp(visibleSize.width/2 + origin.x, origin.y  + 40.0));
    

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(myEnterItemLbl, NULL);
    
    pMenu->addChild(pCloseItem);
    
    pMenu->setPosition(CCPointZero);
    
    this->addChild(pMenu, 1);
    
    //CCControlButton *pbEnter = CCControlButton::create("Enter","Arial", 30.0);
    //pbEnter->setPosition(ccp(origin.x + visibleSize.width/2 , origin.y + 40.0));
    //this->addChild(pbEnter, 0);
    
    
    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Welcome, DemoGame", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    // init variable
    
    (m_bEnabledEnter == true) ? (NULL) : (m_bEnabledEnter = false);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCLog("HelloWorld::menuCloseCallback");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
    
}


void HelloWorld::onEnterTransitionDidFinish()
{
    //当游戏闪屏画面进入后，进入初始化界面
    CCLog("HelloWorld::onEnterTransitonDidFinish");
//    CCScene *pIntroScene = IntroScene::scene();
//    
//    CCDirector::sharedDirector()->replaceScene(pIntroScene);
    if (!m_bEnabledEnter){
        
        CCDirector* pDirector = CCDirector::sharedDirector();
        
        CCScene *pMsScene = MainSceneLayer::scene();
        
        // run
        pDirector->replaceScene(pMsScene);
        //  pDirector->pushScene(pScene);
        
        m_bEnabledEnter = true;
    }
    
}

void HelloWorld::gameEnterCallback(cocos2d::CCObject *pSender)
{

    
    CCDirector* pDirector = CCDirector::sharedDirector();
    
    CCScene *pMsScene = MainSceneLayer::scene();
    
    // run
    pDirector->replaceScene(pMsScene);
    //  pDirector->pushScene(pScene);
    
}


