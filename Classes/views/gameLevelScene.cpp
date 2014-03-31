//
//  gameLevelScene.cpp
//  Demo
//
//  Created by Apple on 3/26/14.
//
//

//#include "common.h"
#include "gameLevelScene.h"
#include "cocos-ext.h"
#include "sptFileNames.h"
#include "json.h"
#include "tollgateSelectionScene.h"

extern const char *picNames[];
extern std::map<int, SubTexture*> gSubTexture;

static GameLevelJsonStruct *s_pGls = NULL;

std::map     <int , CCRect> rollDataMap;
std::map     <int , CCRect> enemyDataMap;
std::multimap<int , CCRect> pieceDataMap;



void initGameElementCoord()
{
    // init roll pos
    rollDataMap.insert(std::pair<int, CCRect>(0, CCRect(1214, 1216, 111, 96)));
    rollDataMap.insert(std::pair<int, CCRect>(1000, CCRect(1101, 1216, 111, 96)));
    rollDataMap.insert(std::pair<int, CCRect>(1010, CCRect(518, 1216, 111, 96)));
    rollDataMap.insert(std::pair<int, CCRect>(1020, CCRect(875, 1196, 111, 96)));
    rollDataMap.insert(std::pair<int, CCRect>(1030, CCRect(988, 1196, 111, 96)));
    
    // init enemy pos
    enemyDataMap.insert(std::pair<int, CCRect>(1100, CCRect(1811, 1174, 111, 96 )));
    enemyDataMap.insert(std::pair<int, CCRect>(1110, CCRect(1924, 1174, 111, 96 )));
    enemyDataMap.insert(std::pair<int, CCRect>(1300, CCRect(1327, 1236, 111, 96 )));
    enemyDataMap.insert(std::pair<int, CCRect>(1130, CCRect(1214, 1216, 111, 96 )));
    enemyDataMap.insert(std::pair<int, CCRect>(1200, CCRect(237,  1172, 111, 96 )));
    enemyDataMap.insert(std::pair<int, CCRect>(1400, CCRect(640,  1143, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1410, CCRect(396,  1160, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1420, CCRect(1454, 1163, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1430, CCRect(1576, 1163, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1440, CCRect(2,    1167, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1450, CCRect(1535, 1059, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1460, CCRect(1657, 1059, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1500, CCRect(844,  1092, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1510, CCRect(966,  1092, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1520, CCRect(1088, 1092, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1530, CCRect(518,  1112, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1540, CCRect(1210, 1112, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1550, CCRect(1332, 1132, 120, 102)));
    enemyDataMap.insert(std::pair<int, CCRect>(1560, CCRect(396,  1056, 120, 102)));

    
    // init piece data pos
    pieceDataMap.insert(std::pair<int, CCRect>(100, CCRect(525, 1611, 80, 80)));//绿色
    pieceDataMap.insert(std::pair<int, CCRect>(100, CCRect(607, 1611, 80, 80)));//黄色
    pieceDataMap.insert(std::pair<int, CCRect>(100, CCRect(442, 1611, 80, 80)));//蓝色
    pieceDataMap.insert(std::pair<int, CCRect>(100, CCRect(266, 1625, 80, 80)));//蓝色
    
    pieceDataMap.insert(std::pair<int, CCRect>(800, CCRect(1960, 301,  78, 103)));
    pieceDataMap.insert(std::pair<int, CCRect>(800, CCRect(1035, 1314, 78, 103)));
    pieceDataMap.insert(std::pair<int, CCRect>(800, CCRect(475,  1314, 78, 103)));
    pieceDataMap.insert(std::pair<int, CCRect>(800, CCRect(1115, 1314, 78, 103)));
    
    
}

//using namespace cocos2d;

GameLevelJsonStruct* GameLevelJsonStruct::create()
{
    GameLevelJsonStruct *pGLS = new GameLevelJsonStruct();
    
    return (pGLS);
}

GameLevelJsonStruct::~GameLevelJsonStruct()
{
    
    destory(*this);
    
}

void GameLevelJsonStruct::copyObj(const GameLevelJsonStruct &obj)
{
    this->difficulty          = obj.difficulty;
    this->dynamiteProbability = obj.dynamiteProbability;
    this->gameClearType       = obj.gameClearType;
    this->colorNum            = obj.colorNum;
    this->horizontalNum       = obj.horizontalNum;
    this->verticalNum         = obj.verticalNum;
    this->turnNum             = obj.turnNum;
    this->totalSecond         = obj.totalSecond;
    this->targetScore         = obj.targetScore;
    this->shutterScore        = obj.shutterScore;
    this->level               = obj.level;
    
    int nodeNum = this->horizontalNum * this->verticalNum;
    
    this->rollData = new int[nodeNum];
    memcpy(this->rollData, obj.rollData, nodeNum * sizeof(int));
    
    this->enemyData = new int[nodeNum];
    memcpy(this->enemyData, obj.enemyData, nodeNum * sizeof(int));
    
    this->mapData = new int[nodeNum];
    memcpy(this->mapData, obj.mapData, nodeNum * sizeof(int));
    
    this->pieceData = new int[nodeNum];
    memcpy(this->pieceData, obj.pieceData, nodeNum * sizeof(int));

}

void GameLevelJsonStruct::destory(const GameLevelJsonStruct &obj)
{
    if (!rollData){
        delete[] (rollData);
    }
    
    if (!enemyData){
        delete[] (enemyData);
    }
    
    if (!mapData) {
        delete[] (mapData);
    }
    if (!obj.pieceData) {
        delete[] (pieceData);
    }

    
}

GameLevelJsonStruct::GameLevelJsonStruct(const GameLevelJsonStruct &right)
{
    this->copyObj(right);
}

GameLevelJsonStruct& GameLevelJsonStruct::operator= (const GameLevelJsonStruct &right)
{
    
    if  (this != &right){
        
        destory (*this);
        
        copyObj (right);
        
    }
    
    return (*this);
    
}

void GameLevelJsonStruct::getLevelConfig(int lev)
{
    CCLog("game level = %d\n", lev);
    
    // 1. get allStage file data
    CCFileUtils *pFileUitl = CCFileUtils::sharedFileUtils();
    
    unsigned long fileLen;
    char *str = (char *)pFileUitl->getFileData(picNames[JSON_ALL_STAGE], "r", &fileLen);
    //CCLog("str = %s\n, fileLen = %ld\n", str, fileLen);
    
    // 2. using Reader.parse
    Json::Reader reader;
    Json::Value root;
    reader.parse (str, root, false);
    assert(!root.isNull());
    
    Json::Value tollgates;
    tollgates = root.get ("allStageData", NULL);
    assert(!tollgates.isNull());
    
    if (lev > 0 || lev <= tollgates.size()){
        CCLog("tollgates = %d\n", tollgates.size());
        Json::Value tog = tollgates[lev - 1];
        
        this->difficulty          = tog.get("difficulty", NULL).asInt();
        this->dynamiteProbability = tog.get("dynamiteProbability", NULL).asInt();
        this->gameClearType       = (tog.get("gameClearType", NULL).asString() == "turn") ? (1) : (0);
        this->colorNum            = tog.get("colorNum", NULL).asInt();
        this->horizontalNum       = tog.get("horizontalNum", NULL).asInt();
        this->verticalNum         = tog.get("verticalNum", NULL).asInt();
        this->turnNum             = tog.get("turnNum", NULL).asInt();
        this->totalSecond         = tog.get("totalSecond", NULL).asInt();
        this->targetScore         = tog.get("targetScore", NULL).asInt();
        this->shutterScore        = tog.get("shutterScore", NULL).asInt();
        this->level               = tog.get("level", NULL).asInt();
        
        CCLog("difficulty = %d\n", difficulty);
        CCLog("dynamiteProbability = %d\n", dynamiteProbability);
        CCLog("gameClearType = %d\n", gameClearType);
        CCLog("colorNum = %d\n", colorNum);
        CCLog("horizontalNum = %d\n", horizontalNum);
        CCLog("verticalNum = %d\n", verticalNum);
        CCLog("turnNum = %d\n", turnNum);
        CCLog("totalSecond = %d\n", totalSecond);
        CCLog("targetScore = %d\n", targetScore);
        CCLog("shutterScore = %d\n", shutterScore);
        CCLog("level = %d\n", level);
        
        
        Json::Value data;
        int elemNum = (this->horizontalNum) * (this->verticalNum);
        
        this->rollData = new int[elemNum];
        if ((data = tog.get("rollData", NULL)).isArray()){
            for (int i = 0; i < elemNum; i++) {
                this->rollData[i] = data[i].asInt();
                CCLog("rollData[%d] = %d\n", i, rollData[i]);
            }
        }
        
        this->enemyData = new int[elemNum];
        if ((data = tog.get("enemyData", NULL)).isArray()){
            for (int i = 0; i < elemNum; i++) {
                this->enemyData[i] = data[i].asInt();
                CCLog("enemyData[%d] = %d\n", i, enemyData[i]);
            }

        }
        

        this->mapData = new int[elemNum];
        if ((data = tog.get("mapData", NULL)).isArray()){
            for (int i = 0; i < elemNum; i++) {
                this->mapData[i] = data[i].asInt();
                CCLog("mapData[%d] = %d\n", i, mapData[i]);
            }

        }
        

        this->pieceData = new int[elemNum];
        if ((data = tog.get("pieceData", NULL)).isArray()){
            for (int i = 0; i < elemNum; i++) {
                this->pieceData[i] = data[i].asInt();
                CCLog("pieceData[%d] = %d\n", i, pieceData[i]);
            }

        }
        
    }
    
    
}

void GameLevelJsonStruct::releaseLevelConfig(int lev)
{
    destory(*this);
}



/////////////////////////////////////////////
// Class: GameLevelScene
/////////////////////////////////////////////

GameLevelScene::GameLevelScene(int lev)
{
    m_level = lev;
    
    if(!init()){
        //CCLog("GameLevelScene: function -- %s failured\n", );
        this->~GameLevelScene();
        
    }
    
}

GameLevelScene::~GameLevelScene(){
    
}

void GameLevelScene::initConfigWithGameLevel(int lev)
{
    
    s_pGls = GameLevelJsonStruct::create();
    s_pGls->autorelease();
    s_pGls->getLevelConfig(lev);
    
}

void GameLevelScene::initGameElementPositon()
{
    initGameElementCoord();
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool GameLevelScene::init()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // 1. init data from config file "allStage.json"
    initConfigWithGameLevel(m_level);
    
    // 2. init game element position
    initGameElementPositon();
    
    // 3. init return button
    //  add a "Return" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pReturnItem = CCMenuItemImage::create(
                                                           "return.png",
                                                           "return.png",
                                                           this,
                                                           menu_selector(GameLevelScene::menuReturnCallback));
    pReturnItem->setAnchorPoint(ccp(0, 0));
	pReturnItem->setPosition(CCPointZero);
    pReturnItem->setScale(0.5);
    
    CCMenu* pMenu = CCMenu::create(pReturnItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 100);
    
    CCSprite *pBg = CCSprite::create("background_set.png");
    pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    pBg->setScaleX(winSize.width/pBg->getContentSize().width);
    pBg->setScaleY(winSize.height/pBg->getContentSize().height);
    
    this->addChild(pBg, -1);
    
    

    
    // 4. init scene by data
    
    //m_pSptBtNode = CCSpriteBatchNode::create("game_parts.png", 100);
    
    initMapLyr();
    //this->addChild(mapLyr, 0, 0);
    
    initRollLyr();
    //this->addChild(rollLyr, 1, 1);
    
    initEnemyLyr();
    //this->addChild(enemyLyr, 2, 2);
    
    initPieceLyr();
    //this->addChild(pieceLyr, 2, 3);
    
    //CCTextureCache *pImgGame = CCTextureCache::sharedTextureCache()->addImage(picNames[GAME_PARTS]);
    
//    char fileName[100] = {0};
//    for (int i = 0; i < gSubTexture.size(); i++) {
//        SubTexture *pTmp = gSubTexture.find(i)->second;
//        
//        CCSprite *pSptTmp = CCSprite::create(picNames[GAME_PARTS],
//                                             CCRect(pTmp->x, pTmp->y, pTmp->width, pTmp->height));
//        pSptTmp->setPosition(ccp(winSize.width/2, winSize.height/2));
//        if (i == 6) {
//            this->addChild(pSptTmp);
//        }
//        sprintf(fileName, "%d.png", i);
//        //this->addChild(pSptTmp);
//    }
//    //CCSprite *pSpt = CCSprite::create("game_parts.png");
    
    
   
    //CCDirector::
    
    
    return (true);
    
}


void GameLevelScene::initMapLyr()
{
    mapLyr = CCLayer::create();
    
//    int elemNum = s_pGls->horizontalNum * s_pGls->verticalNum;
//    int initTag = elemNum * 0;
//    int rollX =
//    
//    for (int i = 0; i < s_pGls->) {
//        <#statements#>
//    }
    
}

void GameLevelScene::initRollLyr()
{
    rollLyr = CCLayer::create();
    rollLyr->setTag(1);
    rollLyr->setPosition(CCPointZero);
    
    CCSize winSize  = CCDirector::sharedDirector()->getWinSize();
    CCPoint mid     = ccp(winSize.width/2, winSize.height/2);
   
    
    int vet = s_pGls->verticalNum, hoz = s_pGls->horizontalNum;
    int elemNum = vet * hoz;
    int initTag = elemNum * 1;
    

    
    //CCTexture2D *pRollPng = CCTextureCache::sharedTextureCache()->addImage("game_parts.png");
   // CCSize rollSize = pRollPng->getContentSize();
    //float scale = std::min(winSize.height/((vet + 4)*rollSize.height), winSize.width/((hoz + 4)*rollSize.width));

    
    CCSpriteBatchNode *pRollBatch = CCSpriteBatchNode::create("game_parts.png", elemNum);
    pRollBatch->setContentSize(winSize);
    pRollBatch->setPosition(CCPointZero);
    pRollBatch->setTag(1); //rollBatchNode tag
    this->addChild(pRollBatch, 200);
    
    CCSize rollSize = CCSize(111, 96);
    //float scale = std::min(winSize.height/((vet + 4)*rollSize.height), winSize.width/((hoz + 4)*rollSize.width));
     //CCLog("scale = %f\n", scale);
    
    // left top sprite position
    CCPoint begin;
    
//    begin.x = mid.x - (hoz * rollSize.width/2);
//    begin.y = mid.y + (vet * rollSize.height/2);
    begin.x = 0.0;
    begin.y = winSize.height;
    
    int xBase = rollSize.width/2;
    int yBase = rollSize.height/2;
    
    CCLog("screen size = (%d, %d)\n", (int)winSize.width, (int)winSize.height);
    CCLog("hoz = %d, vet = %d\n", hoz, vet);
    CCLog("Begin pos = (%d, %d)\n", (int)begin.x, (int)begin.y);
    CCLog("sprite (width, height) = (%d, %d)\n", (int)rollSize.width, (int)rollSize.height);
    CCLog("sprite total (width, height) = (%d, %d)\n", (int)rollSize.height * vet, (int)rollSize.width * hoz);
   
    int row = vet, col = hoz;
    for (int i = 0; i < row; i++) {
        begin.y = begin.y - i*rollSize.height;
        for (int j = 0; j < col; j++) {
            
            int pos = i * col + j;
            int rollValue = s_pGls->rollData[pos];
            CCRect rt = (CCRect)(rollDataMap.find(rollValue)->second);
            CCPoint ptPos = ccp(begin.x + (j * xBase), begin.y + yBase);
            yBase = -yBase;
            
            CCSprite *pRollSpt = CCSprite::createWithTexture(pRollBatch->getTexture(), rt);
            pRollSpt->setTag(initTag);
            pRollSpt->setPosition(ptPos);
            //pRollSpt->setScale(scale);
//            if (s_pGls->mapData[pos] == 0)
//                pRollSpt->setVisible(true);
            
            this->addChild(pRollSpt, 200);
            CCLog("position     = (%f, %f)\n", ptPos.x, ptPos.y);
            
            
            initTag++;
//            
//            CCLog("rollPos      = %d\n", pos);
//            CCLog("rollPosValue = %d\n", rollValue);
//            CCLog("rollPosition = (%f, %f, %f, %f)\n", rt.origin.x, rt.origin.y, rt.size.width, rt.size.height);
//            CCLog("position     = (%f, %f)\n", ptPos.x, ptPos.y);
//            CCLog("initTag      = %d\n", initTag-1);
        }
    }
   // this->addChild(pRollBatch, 1);
    //rollLyr->addChild(pRollBatch);
}

void GameLevelScene::initEnemyLyr()
{
    enemyLyr = CCLayer::create();

    int elemNum = s_pGls->horizontalNum * s_pGls->verticalNum;
    int initTag = elemNum * 2;
    
}

void GameLevelScene::initPieceLyr()
{
    pieceLyr = CCLayer::create();

    int elemNum = s_pGls->horizontalNum * s_pGls->verticalNum;
    int initTag = elemNum * 3;
    
}



void GameLevelScene::menuReturnCallback(CCObject* pSender)
{
    CCLog("MainSceneLayer::menuReturnCallback");
    CCScene *pScene = tollgateSelectionScene::scene();
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}

void GameLevelScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
}
void GameLevelScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
     CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
}

void GameLevelScene::registerWithTouchDispatcher()
{
     CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
    
}



