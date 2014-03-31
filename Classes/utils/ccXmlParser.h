//
//  ccXmlParser.h
//  Demo
//
//  Created by Apple on 3/23/14.
//
//

#ifndef __Demo__ccXmlParser__
#define __Demo__ccXmlParser__

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "cocos2d.h"

using namespace cocos2d;

using std::set;
using std::string;
using std::map;


class CC_DLL XmlParse : public CCObject, public CCSAXDelegator
{
    
public:
    static XmlParse *sharedXmlParse();
    static XmlParse *create(const char *tmxFile);
    static XmlParse * parserWithFile(const char *tmxFile);
    
    bool initXmlParse(const char* xmlName);
    
    //  使用 CCSAXDelegator 重写3个回调函数
    
    void startElement(void *ctx, const char *name, const char **atts);
    
    void endElement(void *ctx, const char *name);
    
    void textHandler(void *ctx, const char *ch, int len);
    
    std::string root_name;
    
    bool isJumpHeadData;
    
    std::map<std::string, std::string> m_xmlMap;
    
private:
    
    //static HXmlParse *pXmlParser;
    
    std::string startXmlElement;//用来记录每个key前字段
    
    std::string endXmlElement;//用来记录每个key后字段
    
    std::string currString;//记录每个value的值
    
};





#endif /* defined(__Demo__ccXmlParser__) */
