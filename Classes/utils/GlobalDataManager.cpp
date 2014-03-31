//
//  GlobalDataManager.cpp
//  Demo
//
//  Created by zuopeng.liu on 14-3-20.
//
//

#include "GlobalDataManager.h"



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
static GlobalDataManager *s_pGlobalDataManager = NULL; // pointer to singleton

// HttpClient implementation
GlobalDataManager* GlobalDataManager::getInstance()
{
    if (s_pGlobalDataManager == NULL)
    {
        s_pGlobalDataManager = new GlobalDataManager();
    }
    
    return s_pGlobalDataManager;
}

////////////////////////////////////////////////////////////////////////////////////////
GlobalDataManager::GlobalDataManager()
{
    m_userName = "";
    m_mobageID = "";
    m_serverID = -1;
    m_sid = "";
}

////////////////////////////////////////////////////////////////////////////////////////
GlobalDataManager::~GlobalDataManager()
{
    
}

////////////////////////////////////////////////////////////////////////////////////////
void GlobalDataManager::setGenericData( int type, std::string data )
{
    if ( type >= GLOBAL_DATA_TYPE_END )
    {
        return;
    }
    
    m_genericDataMap[type] = data;
    
    return;
}

////////////////////////////////////////////////////////////////////////////////////////
std::string GlobalDataManager::getGenericData( int type )
{
    if ( type >= GLOBAL_DATA_TYPE_END )
    {
        return "";
    }
    
    return m_genericDataMap[type];
}


