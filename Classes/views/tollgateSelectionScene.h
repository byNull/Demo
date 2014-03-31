//
//  tollgateSelectionScene.h
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#ifndef __Demo__tollgateSelectionScene__
#define __Demo__tollgateSelectionScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;



class tollgateSelectionScene : public cocos2d::CCLayer, public cocos2d::CCTouchDelegate
{
public:
    tollgateSelectionScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void returnCallback(CCObject *pSender);
    void goGameTollagetCallback(CCObject *pSender);
    
    //virtual void enterMenuCallback(CCObject *pSender);
    
    
//    virtual bool ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
//    
//    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher();
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(tollgateSelectionScene);
    
protected:
    void goGameLevel(int lev);
    
    
private:
    std::vector<CCSprite*> levelSpir;
    //CCMenuItem *m_pItemMenu1;
    CCPoint m_tBeginPos;
    CCMenu *m_pTollgateMenu;
    int     levels;
    int     base;
};


#endif /* defined(__Demo__tollgateSelectionScene__) */
