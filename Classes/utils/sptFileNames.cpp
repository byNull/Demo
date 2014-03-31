//
//  sptFileNames.cpp
//  Demo
//
//  Created by Apple on 3/23/14.
//
//

#include "sptFileNames.h"



/////////////////////////////////////////
//define global variable
std::map<int, SubTexture*> gSubTexture;
///////////////////////////////////////


std::map<int, SubTexture*> getXmlConfig(const char *str)
{
    int i = 0;
    rapidxml::file<> fdoc(CCFileUtils::sharedFileUtils()->fullPathForFilename(str).c_str());//读取数据
    
    rapidxml::xml_document<> myRapidXMLDoc;
    myRapidXMLDoc.parse<0>(fdoc.data()); // 将数据写入xml_document
    
    rapidxml::xml_node<>* root = myRapidXMLDoc.first_node();//获取根节点
    
    rapidxml::xml_node<>* node1 = root->first_node(); //获取node1节点
    
   //FILE *fp = fopen("/Users/apple/cocos2d-x/cocos2d-x-2.2.2/projects/Demo/Resources/pos.txt", "w+");
//    if (fp == NULL){
//        CCLog("file create failure\n");
//    }
    //freopen("pos.txt", "w+", stdout);
    
    
    do{
        SubTexture *elem = new SubTexture();
        char str[1024] = {0};
        //int  len = 0;
        
        rapidxml::xml_attribute<>* info_attr = node1->first_attribute(); //获取node1属性
        
        do{
            //CCLog("%s: %s\n", info_attr->name(), info_attr->value());
            sprintf(str + strlen(str), "%s", info_attr->value());
            strcat(str, "  ");
        }while ((info_attr  = info_attr->next_attribute()) != NULL);
        
        char fileName[100] = { 0 };
        sscanf(str, "%s %d %d %d %d %d %d",
               fileName, &elem->x, &elem->y, &elem->width, &elem->height, &elem->pivotX, &elem->pivotY);
        

        elem->name = std::string(fileName).substr(0, std::string(fileName).find_last_of('.'));
        
        //fprintf(fp, "%3d, (%4d, %4d, %4d, %4d), %s,\n",i, elem->x, elem->y, elem->width,
        //        elem->height,  elem->name.c_str());

        gSubTexture.insert(std::pair<int, SubTexture*>(i++, elem));
        
    }while ((node1 = node1->next_sibling()) != NULL) ;
    
//    CCLog("%d\n", (int)gSubTexture.size());
//    
//    for (i = 0; i < gSubTexture.size(); i++) {
//        SubTexture *elem = gSubTexture.find(i)->second;
//        CCLog("%s: %d, %d, %d, %d, %d, %d\n", elem->name.c_str(), elem->x, elem->y,
//    elem->width, elem->height, elem->pivotX, elem->pivotY);
//    }

//    fclose(fp);
    return (gSubTexture);
    
}

void releaseXmlConfigData()
{
    for (int i = 0; i < gSubTexture.size(); i++) {
        
        SubTexture *tmp = gSubTexture.find(i)->second;
        delete tmp;
        tmp = NULL;
    }
}

