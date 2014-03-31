#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;


class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);
    
    virtual void onEnterTransitionDidFinish();
    
    
    virtual void gameEnterCallback(CCObject *pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    // only init enter for "false"
    static bool m_bEnabledEnter;
};

#endif // __HELLOWORLD_SCENE_H__
