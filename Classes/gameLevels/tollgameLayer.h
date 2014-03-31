//
//  tollgateLayer .h
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#ifndef __Demo__tollgateLayer___
#define __Demo__tollgateLayer___

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class TollgameLayer : public cocos2d::CCLayer, public cocos2d::CCTouchDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void returnCallback(CCObject* pSender);
    
    //virtual void enterMenuCallback(CCObject *pSender);
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(TollgameLayer);
    
public:
    static void setGameLevel(const int lvl);
    
    
    
private:
    static int sGameLevel; //关卡数：表示第几关
};


#endif /* defined(__Demo__tollgateLayer___) */
