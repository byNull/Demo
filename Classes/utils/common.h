//
//  common.h
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#ifndef Demo_common_h
#define Demo_common_h


#include "cocos2d.h"
#include "cocos-ext.h"
#include <cstdlib>
#include <cmath>

#include <map>
#include <string>

using std::map;
using std::string;


USING_NS_CC;
USING_NS_CC_EXT;

////作为一般服务端请求调用的返回结果，第一个表示error信息，第二个表示返回结果的json信息
//#define server_response_selector(_SELECTOR) (SEL_ServerResponseNotifier)(&_SELECTOR)
//#define file_download_response_selector(_SELECTOR) (SEL_FileDownloadedNotifier)(&_SELECTOR)
//
////请求的回调函数为 ( error, data )，由于这个是一对一映射的，不需要进行标记
//typedef void (CCObject::*SEL_ServerResponseNotifier)(int, std::string);
//
////文件下载的回调函数（ error, downloadUrl, localpath )
//typedef void (CCObject::*SEL_FileDownloadedNotifier)(int, std::string);
//
//#define     SCREEN_DESIGNED_WIDTH       640         //The designed width
//#define     SCREEN_DESIGNED_HEIGHT      960         //The designed height
//
//#define MOBAGE_SDK 0



// import namespace
//using namespace cocos2d;
//using namespace cocos2d::extension;
//using namespace rapidjson;


enum{
    BACKGROUND_SET = 0,
    CLOSENORMAL    = 1,
    CLOSESELECTED  = 2,
    GAME_PARTS     = 3,
    HELLOWORLD     = 4,
    LEVLE_BG       = 5,
    DYNAMITEFONT   = 6,
    LINE_BG_1      = 7,
    MAP_LVL_BASE_LOCKED = 8,
    MAP_LVL_BASE_UNLOCKED = 9,
    MAP_LVL_STAR          = 10,
    MAP_TW                = 11,
    JSON_ALL_STAGE        = 12,
    
    
};
extern const char *picNames[];



#endif
