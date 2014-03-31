//
//  MainScreenScene.h
//  Demo
//
//  Created by Apple on 3/23/14.
//
//

#ifndef __Demo__MainScreenScene__
#define __Demo__MainScreenScene__

#include <iostream>
#include "common.h"

class MainSceneLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback, return last scene
    virtual void menuReturnCallback(CCObject* pSender);

    virtual void onEnterTransitionDidFinish();
    
    virtual void ccTouchesBegin(CCSet *pTouches, CCEvent *pEvent);
    
    
    // click start button, enter game selection screen
    virtual void gameStartCallback(CCObject *pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainSceneLayer);
};


#endif /* defined(__Demo__MainScreenScene__) */
