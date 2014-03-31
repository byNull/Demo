//
//  tollgateSelectionScene.cpp
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#include "tollgateSelectionScene.h"
#include "HelloWorldScene.h"
#include "MainScreenScene.h"
#include "common.h"
#include "gameLevelScene.h"

using namespace cocos2d::extension;

USING_NS_CC;

static CCPoint s_tCurPos = CCPointZero;

tollgateSelectionScene::tollgateSelectionScene() : levels(100), base(150)
{
    
}

CCScene* tollgateSelectionScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    tollgateSelectionScene *layer = tollgateSelectionScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool tollgateSelectionScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    ///////////////////////////////////////////////////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    CCMenu *pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //CCMenuItemImage *pRtItemMenu = CCMenuItemImage::create("return.png", this, menu_selector(tollgateSelectionScene::returnCallback));
    CCSprite *pRtSpt = CCSprite::create("return.png");
    CCMenuItemSprite *pSptRtItemMenu = CCMenuItemSprite::create(pRtSpt, pRtSpt, pRtSpt, this,
                                                              menu_selector(tollgateSelectionScene::returnCallback));
    pSptRtItemMenu->setScale(0.5);
    pSptRtItemMenu->setAnchorPoint(CCPointZero);
    pSptRtItemMenu->setPosition(CCPointZero);
    
    pMenu->addChild(pSptRtItemMenu, 2);
    

    
//    CCCallFunc *pRtSptCallback = CCCallFunc::create(this, callfunc_selector(tollgateSelectionScene::returnCallback));
//    this->runAction(pRtSptCallback);
//    this->addChild(pRtSpt, 1);
    
    
    //CCSpriteBatchNode *pSptBatch = CCSpriteBatchNode::create(picNames[MAP_LVL_BASE_UNLOCKED], 1000);
    //this->addChild(pSptBatch, 2);
    //pSptBatch->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    
    // 生成关卡选择菜单
    m_pTollgateMenu = CCMenu::create();
    m_pTollgateMenu->setContentSize(CCSizeMake(visibleSize.width, base * (levels)));
    CCLog("visiable.width = %f, visible.height = %f\n", visibleSize.width, visibleSize.height);
    //m_pTollgateMenu->setAnchorPoint(ccp(0, m_pTollgateMenu->getContentSize().height/visibleSize.height));
    //s_tCurPos = ccp(0, m_pTollgateMenu->getContentSize().height - visibleSize.height);
    m_pTollgateMenu->setPosition(s_tCurPos);
    this->addChild(m_pTollgateMenu);

    for (int i = 0; i < levels; i++){
        
        CCMenuItemImage *pSptMenuItem = CCMenuItemImage::create(picNames[MAP_LVL_BASE_UNLOCKED],
                                                                 picNames[MAP_LVL_BASE_UNLOCKED],
                                                                 picNames[MAP_LVL_BASE_UNLOCKED], this,
                                                                 menu_selector(tollgateSelectionScene::goGameTollagetCallback));
        float sptX = visibleSize.width/2;
        float sptY = pSptMenuItem->getContentSize().height/2 + base * i;
        CCLog("sptx = %f, spty = %f\n", sptX, sptY);
        
        pSptMenuItem->setPosition(ccp(sptX, sptY));
        m_pTollgateMenu->addChild(pSptMenuItem, 3, (i+1));
        
        char dstr[1024] = {0};
        sprintf(dstr, "%d", i+1);
        
        CCLabelTTF* pDgtLbl = CCLabelTTF::create(dstr, "Arial", 25);
        // position the label on the center of the sprite image
        float xDgtLbl = pSptMenuItem->getContentSize().width/2;
        float yDgtLbl = pSptMenuItem->getContentSize().height/2;
        
        pDgtLbl->setPosition(ccp(xDgtLbl, yDgtLbl));
        pSptMenuItem->addChild(pDgtLbl);
        
    }
    
    // enabled support touch event
    this->setTouchEnabled(true);
    
    return true;
}

void tollgateSelectionScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("tollgateSelectionScene::ccTouchBegan");
    
    CCSetIterator it = pTouches->begin();
    
    m_tBeginPos = ((CCTouch*)(*it))->getLocation();

}

void tollgateSelectionScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog(" tollgateSelectionScene::ccTouchEnded");
    
    CCSetIterator it = pTouches->begin();
    CCTouch *pTouch = (CCTouch *)(*it);
    
    CCPoint endPos = pTouch->getLocation();
    
    float nMoveY = endPos.y - m_tBeginPos.y;
    float nMoveX = 0;
    
    //得到当前精灵菜单的位置和下个位置
    CCPoint curPos  = m_pTollgateMenu->getPosition();
    CCLog("curPos(x, y) = (%f, %f)", curPos.x, curPos.y);
    CCPoint nextPos = ccp(curPos.x + nMoveX, curPos.y + nMoveY);
    CCLog("nextPos(x, y) = (%f, %f)", nextPos.x, nextPos.y);
    
    if (nextPos.y < 0.0f)
    {
        m_pTollgateMenu->setPosition(CCPointZero);
        return;
    }
   // float height = CCDirector::sharedDirector()->getVisibleSize().height;
    if (nextPos.y > ((levels)* base))
    {
        m_pTollgateMenu->setPosition(ccp(0, ((levels)* base)));
        return;
    }
    
    m_pTollgateMenu->setPosition(nextPos);
    m_tBeginPos = endPos;
    s_tCurPos   = nextPos;
}



void tollgateSelectionScene::registerWithTouchDispatcher()
{
    //CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -120, true);
}

void tollgateSelectionScene::goGameLevel(int lev)
{
    CCLOG("Enter level %d\n", lev);
    
    CCLayer *pGlsLayer = new GameLevelScene(lev);
    CCScene *pScene = CCScene::create();
    
    pGlsLayer->autorelease();
    
    pScene->addChild(pGlsLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    
    
}

void tollgateSelectionScene::goGameTollagetCallback(CCObject *pSender){
    
    CCLOG("tollgateSelectionScene::goGameTollagetCallback\n");
    CCMenuItem *pMenuItem = (CCMenuItem*)pSender;
    int level = pMenuItem->getTag();
    CCLOG("tag = %d\n", level);
    
    goGameLevel(level);
}



void tollgateSelectionScene::returnCallback(CCObject* pSender)
{
    CCLog("tollgateSelectionScene::returnCallback");
    
    CCScene *pHwScene = MainSceneLayer::scene();
    
    // run
    CCDirector::sharedDirector()->replaceScene(pHwScene);
    
}

