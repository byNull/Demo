//
//  ToolChain.h
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#ifndef __Demo__ToolChain__
#define __Demo__ToolChain__


#include "cocos2d.h"

#include "common.h"


class ToolChain : public cocos2d::CCNode
{
public:
    static ToolChain* getInstance();
    
private:
    ToolChain();
    virtual ~ToolChain();
    
public:
    //MBG_SDK
//#if MOBAGE_SDK == 1
//    void createTransaction(jsval input, jsval onSuccess, jsval onError, jsval object);
//    void closeTransaction(jsval input, jsval onSuccess, jsval onError, jsval object);
//    void openTransaction(jsval input, jsval onSuccess, jsval onError, jsval object);
//    
//    void getCurrentUser(/* jsval input, */ jsval onSuccess, jsval onError, jsval object);
//#endif
    
private:
    
    static ToolChain * instance_;
};


#endif /* defined(__Demo__ToolChain__) */
