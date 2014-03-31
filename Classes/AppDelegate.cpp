#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "sptFileNames.h"

USING_NS_CC;

/////////////////////////////////////////
//define global variable
extern std::map<int, SubTexture*> gSubTexture;
///////////////////////////////////////

AppDelegate::AppDelegate() {
    
    ////////////////////////
    getXmlConfig("game_parts.xml");


}

AppDelegate::~AppDelegate() 
{
    releaseXmlConfigData();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // add Resource search directory
    std::vector<std::string> searchpath;
    searchpath.push_back("images");
    searchpath.push_back("datas");
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchpath);
    
    
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pHwScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pHwScene);
      
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
