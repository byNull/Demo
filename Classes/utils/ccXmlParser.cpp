//
//  ccXmlParser.cpp
//  Demo
//
//  Created by Apple on 3/23/14.
//
//

#include "ccXmlParser.h"
#include "cocos-ext.h"


XmlParse *pXmlParser = NULL;

XmlParse *sharedXmlParse()
{
    if (!pXmlParser) {
        pXmlParser = new XmlParse();
    }
    
    return (pXmlParser);
}

XmlParse* XmlParse::create(const char *tmxFile)
{
    return (parserWithFile(tmxFile));
}

XmlParse* XmlParse::parserWithFile(const char *tmxFile)
{
    XmlParse *pRet=new XmlParse();
    if(pRet && pRet->initXmlParse(tmxFile))
    {
        pRet->autorelease();
        return (pRet);
    }
    CC_SAFE_DELETE(pRet);
    return (NULL);
}

bool XmlParse::initXmlParse(const char *xmlName)

{
    
    //m_xmlMap = new std::multimap<std::string,std::string>();
    m_xmlMap.clear();
    
    CCSAXParser _par;
    
    if(false==_par.init("UTF-8"))
    {
        CCLog("-----请使用utf-8格式!");
        return (false);
    }
    _par.setDelegator(this);
    
    const char *_path=CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlName).c_str();
    
    return (_par.parse(_path));
    
}

//回调函数

void XmlParse::startElement(void *ctx,const char *name,const char **atts)

{
    
    CC_UNUSED_PARAM(ctx);
    
    startXmlElement = (char*)name;
    if(!isJumpHeadData){//跳过数据头
        CCLog("------跳过rootname");
        isJumpHeadData = true;
        root_name = startXmlElement;
        return;
    }
    
    //CCLog("-startElement----%s",startXmlElement.c_str());
    
}

void XmlParse::endElement(void *ctx,const char *name)

{
    CC_UNUSED_PARAM(ctx);
    
    endXmlElement = (char*)name;
    if(endXmlElement == root_name){//数据尾
        CCLog("读取xml结束");
        isJumpHeadData = false;
        root_name = "";
        return;
    }
    
    //CCLog("-endElement----%s",endXmlElement.c_str());
}
//键值对的结束字段
void XmlParse::textHandler(void *ctx,const char *ch,int len)
{
    
    CC_UNUSED_PARAM(ctx);
    currString = string((char*)ch, 0, len);
   
    if(root_name != "" || root_name != " "){
        m_xmlMap[startXmlElement] = currString;
        //std::pair<std::string, std::string> tmp(startXmlElement, currString);
        //m_xmlMap.insert(tmp);
        //mDic->setObject(ccStr,startXmlElement);
        CCLog("-----key:%s,value:%s",startXmlElement.c_str(),m_xmlMap.find(startXmlElement)->second.c_str());
    }
    
    CCLog("-textHandler----%s",currString.c_str());
    
}

