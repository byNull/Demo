//
//  GlobalDataManager.h
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#ifndef __Demo__GlobalDataManager__
#define __Demo__GlobalDataManager__

#include <iostream>
#include "cocos2d.h"
#include "common.h"

class GlobalDataManager : public CCObject
{
public:
    
    typedef enum
    {
        GLOBAL_DATA_TYPE_CONFIG_FOLDER_PATH,
        GLOBAL_DATA_TYPE_DYNAMIC_CONTENT_MANIFEST_PATH,
        GLOBAL_DATA_TYPE_PLATFORM,
        GLOBAL_DATA_TYPE_GAMEER,
        GLOBAL_DATA_TYPE_FRAMESIZE,
        GLOBAL_DATA_TYPE_SERVER_URL,
        GLOBAL_DATA_TYPE_END,
    }GENERIC_GLOBAL_DATA_TYPE;
    
    static GlobalDataManager* getInstance();
    
private:
    GlobalDataManager();
    virtual ~GlobalDataManager();
    
    std::string     m_userName;     //用户的登录用户名
    std::string     m_mobageID;     //mobageID
    int             m_serverID;     //用户选择的服务器ID
    std::string     m_sid;          //服务端给添加的Cookie里的connect.sid，保存了连接服务端获取session的信息，将其带在每次request里
    
    std::map<int, std::string> m_genericDataMap;        //可以预见未来可能会有蛮多数据从C++传递到javascript，希望在这里构造一个相对一致的数据结构来进行存储
    
public:
    void        setUserName( std::string userName ) { m_userName = userName; };
    std::string getUserName() { return m_userName; };
    
    void        setMobageID( std::string mobageID ){ m_mobageID = mobageID; };
    std::string getMobageID() { return m_mobageID; };
    
    void        setServerID( int serverID ) { m_serverID = serverID; };
    int         getServerID() { return m_serverID; };
    
    void        setConnectSID( std::string sid ) { m_sid = sid; };
    std::string getConnectSID() { return m_sid; };
    
    void        setGenericData( int type, std::string data );
    std::string getGenericData( int type );
};


#endif /* defined(__Demo__GlobalDataManager__) */
