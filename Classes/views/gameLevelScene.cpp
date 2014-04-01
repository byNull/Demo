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

/////////////////////////////////////
//
//
struct LineData{
    LineData(CCRect t_bg, CCRect t_top) : bg(t_bg), top(t_top){ }
public:
    CCRect top;
    CCRect bg;
};

std::map     <int , CCRect> rollDataMap;
std::map     <int , CCRect> enemyDataMap;
std::multimap<int , CCRect> pieceDataMap;

std::map<int, LineData>     lineDataObj;
std::vector<CCRect>         lineSignBg;

enum {
    up         = 1,
    down       = 4,
    right_up   = 2,
    right_down = 3,
    left_up    = 5,
    left_down  = 6,
};
std::map<int, CCRect>   arrowImg;

typedef struct ButtonArrow{
    ButtonArrow(int tx, int ty, int tlevel) : x(tx), y(ty), level(tlevel){  }
    
    int x;
    int y;
    int level;
}buttonArrow;

std::vector<ButtonArrow> buttonArr;



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
    
    lineDataObj.insert( std::pair<int, LineData>(0, LineData(CCRect(1871, 474,  18, 114), CCRect(1035, 1722, 18, 114))) );
    lineDataObj.insert( std::pair<int, LineData>(1, LineData(CCRect(1216, 854,  18, 114), CCRect(1397, 1724, 18, 114))) );
    lineDataObj.insert( std::pair<int, LineData>(2, LineData(CCRect(1320, 1691, 18, 114), CCRect(1417, 1724, 18, 114))) );
    lineDataObj.insert( std::pair<int, LineData>(3, LineData(CCRect(902 , 1698, 18, 114), CCRect(1437, 1724, 18, 114))) );

    // std::vector<CCRect> lineSignBg;
    lineSignBg.push_back(CCRect(1545, 1267, 94, 94));
    lineSignBg.push_back(CCRect(1641, 1272, 94, 94));
    lineSignBg.push_back(CCRect(1737, 1272, 94, 94));
    lineSignBg.push_back(CCRect(1833, 1272, 94, 94));
/*
//    var lineSignF = [ //4,1,2,3,5,6
//                     {
//                     2: [cc.rect(1583, 1683, 46, 92), cc.rect(191,1301, 97, 83)],
//                     3: [cc.rect(1987, 2, 46, 98), cc.rect(1944,825, 102, 91)],
//                     4: [cc.rect(2,1574, 71, 94), cc.rect(382,1359, 84, 94)]
//                     },
//                     {
//                     
//                     2: [cc.rect(1467, 1654, 46, 98), cc.rect(743,1294, 100, 86)],
//                     3: [cc.rect(1631, 1683, 46, 90), cc.rect(368,1264, 105, 93)],
//                     4: [cc.rect(946,1294, 87, 95), cc.rect(1929,1272, 92, 95)]
//                     },
//                     {
//                     2: [cc.rect(1679, 1683, 46, 90), cc.rect(845,1294, 99, 85)],
//                     3: [cc.rect(2, 1670, 46, 98), cc.rect(1439,1267, 104, 93)],
//                     4: [cc.rect(1195,1314, 86, 93), cc.rect(2,1301, 87, 95)]
//                     },
//                     {
//                     2: [cc.rect(1141, 1680, 45, 97), cc.rect(91,1301, 98, 83)],
//                     3: [cc.rect(349, 1172, 45, 88), cc.rect(1944,732, 102, 91)],
//                     4: [cc.rect(1000,1629, 70, 91), cc.rect(1283,1334, 88, 90)]
//                     },
//                     ];
*/
    // rowArr: up-->1, down-->4, right_up-->2, right_down-->3, left_up-->5, left_down-->6
    // std::map<int, CCRect> arrowImg;
    arrowImg.insert(std::pair<int, CCRect>(1, CCRect(262,  1037, 23, 14)));
    arrowImg.insert(std::pair<int, CCRect>(4, CCRect(1871, 658,  23, 14)));
    arrowImg.insert(std::pair<int, CCRect>(2, CCRect(2028, 406,  18, 23)));
    arrowImg.insert(std::pair<int, CCRect>(3, CCRect(1606, 642,  19, 23)));
    arrowImg.insert(std::pair<int, CCRect>(5, CCRect(2028, 431,  18, 23)));
    arrowImg.insert(std::pair<int, CCRect>(6, CCRect(1350, 982,  19, 22)));
    
    // std::vector<ButtonArrow> buttonArr;
    buttonArr.push_back(buttonArrow(514, 844, 0));
    buttonArr.push_back(buttonArrow(429, 790, 1));
    buttonArr.push_back(buttonArrow(384, 706, 2));
    buttonArr.push_back(buttonArrow(324, 606, 3));
    buttonArr.push_back(buttonArrow(264, 511, 50));
    
    
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
//
// Class: GameLevelScene
//
/////////////////////////////////////////////

// static variable init
//顶部不可覆盖区域高度
int GameLevelScene::TOP_HEIGHT        = 80;

//底部不可覆盖区域高度
int GameLevelScene::BOTTOM_HEIGHT     = 165;

//六边形边长
int GameLevelScene::CELL_LENGTH       = 55.5;

//
int GameLevelScene::CELL_WIDTH        = 111;
int GameLevelScene::CELL_HEIGHT       = 96;

int GameLevelScene::CELL_TOUCH_LENGTH = 45;


GameLevelScene::GameLevelScene(int lev) : m_level(lev), m_cellNum(0), m_preColor(-1), m_curPoints(0)
{
    // set tag base
    MAP_TAG_BASE   = 0;
    ROLL_TAG_BASE  = 1;
    ENEMY_TAG_BASE = 2;
    PIECE_TAG_BASE = 3;
    LINE_BG_TAG_BASE  = 4;
    LINE_TOP_TAG_BASE = 5;
    
    m_GridPos.clear();
    m_lines.clear();
    m_piecesData.clear();
    m_rollsData.clear();
    
    m_pSptBtNode = NULL;
    
    if(!init()){
        //CCLog("GameLevelScene: function -- %s failured\n", );
        this->~GameLevelScene();
        
    }
}

GameLevelScene::~GameLevelScene()
{
    m_preColor  = -1;
    m_curPoints = 0;
    
    m_GridPos.clear();
    m_lines.clear();
    m_piecesData.clear();
    m_rollsData.clear();
}

void GameLevelScene::initConfigWithGameLevel(int lev)
{
    
    s_pGls = GameLevelJsonStruct::create();
    s_pGls->autorelease();
    s_pGls->getLevelConfig(lev);
    
}

void GameLevelScene::initGameElementCoordinate()
{
    initGameElementCoord();
}

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
bool GameLevelScene::init()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCLog("winsize = (%d, %d)", (int)winSize.width, (int)winSize.height);
    CCLog("visSize = (%d, %d)", (int)visSize.width, (int)visSize.height);
    
    
    // 1. init data from config file "allStage.json"
    initConfigWithGameLevel(m_level);
    m_cellNum = s_pGls->verticalNum * s_pGls->horizontalNum;
    
    // 2. init game element position
    initGameElementCoordinate();
    
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
    this->addChild(pMenu, 100); // 按钮放在最上面
    
    CCSprite *pBg = CCSprite::create("background_set.png");
    pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    pBg->setScaleX(winSize.width/pBg->getContentSize().width);
    pBg->setScaleY(winSize.height/pBg->getContentSize().height);
    this->addChild(pBg, -1); // 背景放在最里面
    
    
    // 4. init scene by data
    initUI();
    
    
    //CCDirector::
    
    
    return (true);
    
}

////////////////////////////////////////////////
// initRollLyr --> initUI
////////////////////////////////////////////////
void GameLevelScene::initUI()
{
    CCSize winSize  = CCDirector::sharedDirector()->getWinSize();
    
    int vet = s_pGls->verticalNum, hoz = s_pGls->horizontalNum;
    int row = vet, column = hoz;
    int elemNum = row * column;
    int initTag = 0;
    float xPos, yPos;
    
    CCSpriteBatchNode *pSptBatch = CCSpriteBatchNode::create("game_parts.png", elemNum * 3);
    pSptBatch->setContentSize(winSize);
    pSptBatch->setPosition(CCPointZero);
    pSptBatch->setTag(1); //rollBatchNode tag -- 1
    this->addChild(pSptBatch);
    
    auto totalWidth = (3 * column + 1) / 2 * this->CELL_LENGTH;
    auto totalHeight = (2 * row + 1) * std::sqrt(3) / 2 * this->CELL_LENGTH;
    
    this->leftStart = (winSize.width - totalWidth) / 2 + this->CELL_LENGTH;
    this->topStart =  (winSize.height + totalHeight  - this->TOP_HEIGHT) / 2;
    
    CCRect rtRoll, rtEnemy, rtPiece;
    
    // 叠放层次：roll(岩石:z--1)--->enemy(障碍:z--2)--->piece(钱币:z--3)
    for (int i = 0; i < row; i++) {
        
        for (int j = 0; j < column; j++) {
            
            int pos = i * column + j;
            int valueOfRollPos  = s_pGls->rollData[pos];
            int valueOfEnemyPos = s_pGls->enemyData[pos];
            int valueOfPiecePos = s_pGls->pieceData[pos];
            
            std::pair <std::multimap<int,CCRect>::iterator,std::multimap<int,CCRect>::iterator> ret;
            ret = pieceDataMap.equal_range(valueOfPiecePos);
            std::multimap<int, CCRect>::iterator it = ret.first;
            
            int rdVal = (int)std::rand()%4; //[0, 3] -- 表示钱币的类型
            CCLog("random value = %d", rdVal);
            
            for (int k = 0; k < rdVal && it != ret.second; k++, it++) {
                
            }
            
            rtRoll  = (CCRect)(rollDataMap.find(valueOfRollPos)->second);
            rtEnemy = (CCRect)(enemyDataMap.find(valueOfEnemyPos)->second);
            rtPiece = (CCRect)(it->second);
            
            
            xPos = this->leftStart + (this->CELL_WIDTH - 14) * j * std::sqrt(3) / 2;
            if(j % 2 == 1){
                yPos = this->topStart - this->CELL_HEIGHT * i + this->CELL_HEIGHT * 0.5;
            }else{
                yPos = this->topStart - this->CELL_HEIGHT * i;
            }
            
            // 创建石头精灵
            CCSprite *pRollSpt = CCSprite::createWithTexture(pSptBatch->getTexture(), rtRoll);
            //            CCSprite *pRollSpt = CCSprite::create("game_parts.png", rtRoll);
            pRollSpt->setTag(pos + elemNum * ROLL_TAG_BASE);
            pRollSpt->setPosition(ccp(xPos, yPos));
            
            // 创建障碍精灵
            CCSprite *pEnemySpt;
            if (valueOfEnemyPos != 0){
                pEnemySpt= CCSprite::createWithTexture(pSptBatch->getTexture(), rtEnemy);
                //                pEnemySpt = CCSprite::create("game_parts.png", rtEnemy);
                pEnemySpt->setTag(pos + elemNum * ENEMY_TAG_BASE);
                pEnemySpt->setPosition(ccp(xPos, yPos));
            }
            
            // 创建钱币精灵
            CCSprite *pPieceSpt = CCSprite::createWithTexture(pSptBatch->getTexture(), rtPiece);
            //            CCSprite *pPieceSpt = CCSprite::create("game_parts.png", rtPiece);
            pPieceSpt->setTag(pos + elemNum * PIECE_TAG_BASE);
            pPieceSpt->setPosition(ccp(xPos, yPos));
            
            // 将精灵添加到游戏场景中
            // 添加石头
            pSptBatch->addChild (pRollSpt, 1);
            if (valueOfEnemyPos != 0){
                // 添加障碍
                pSptBatch->addChild(pEnemySpt, 2);
            }
            // 添加钱币
            pSptBatch->addChild(pPieceSpt, 3);
            
            // 根据mapData数据判断是否显示精灵
            if (s_pGls->mapData[pos] == 0) {
                pRollSpt->setVisible(false);
                if (valueOfEnemyPos != 0){
                    pEnemySpt->setVisible(false);
                }
                pPieceSpt->setVisible(false);
            }
            
            /*
            // 调试
            //this->addChild(pRollSpt, 200);
            //            CCLog("valueOfRollPos  = %d", valueOfRollPos );
            //            CCLog("valueOfEnemyPos = %d", valueOfEnemyPos);
            //            CCLog("valueOfPiecePos = %d", valueOfPiecePos);
            //            CCLog("position        = (%f, %f)", xPos, yPos);
            //            CCLog("sprite position = (%f, %f)",   xPos, yPos);
            //            CCLog("valueOfRollPos  = (%f, %f, %f, %f)",   rtRoll.origin.x, rtRoll.origin.y, rtRoll.size.width, rtRoll.size.height);
            //            CCLog("valueOfEnemyPos = (%f, %f, %f, %f)",   rtEnemy.origin.x, rtEnemy.origin.y, rtEnemy.size.width, rtEnemy.size.height);
            //            CCLog("valueOfPiecePos = (%f, %f, %f, %f)\n", rtPiece.origin.x, rtPiece.origin.y, rtPiece.size.width, rtPiece.size.height);
            */
            
            initTag++; // initTag = pos
            
            // put <posIndex, PointPos> into m_GridPos
            m_GridPos.insert(std::pair<int, CCPoint>(pos, CCPoint(xPos, yPos)));
            
            PieceDataOfGrid coinObj;
            coinObj.index      = pos;
            coinObj.colorType  = rdVal;
            coinObj.valueOfPos = valueOfPiecePos;
            coinObj.pt         = CCPoint(xPos, yPos);
            coinObj.rt         = rtPiece;
            m_piecesData.push_back(coinObj);
            
            
            RollDataOfGrid rollCellObj;
            rollCellObj.index = pos;
            rollCellObj.type  = (enum RollType)valueOfRollPos;
            rollCellObj.pt    = CCPoint(xPos, yPos);
            rollCellObj.rt    = rtRoll;
            m_rollsData.push_back(rollCellObj);
        }
    }
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
    m_lines.clear();
    m_curPoints = 0;
    
    CCTouch *pTouch = (CCTouch *)(*pTouches->begin());
    CCPoint pos = pTouch->getLocation();
    CCLog("touch position = (%f, %f)\n", pos.x, pos.y);

    drawLine(pos);
}
void GameLevelScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
    CCTouch *pTouch = (CCTouch *)(*pTouches->begin());
    CCPoint pos = pTouch->getLocation();
    CCLog("touch position = (%f, %f)\n", pos.x, pos.y);

    drawLine(pos);

}

void GameLevelScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
    CCTouch *pTouch = (CCTouch *)(*pTouches->begin());
    CCPoint pos = pTouch->getLocation();
    CCLog("touch position = (%f, %f)\n", pos.x, pos.y);

    drawLine(pos);
    
    removeLinesObj();
    UpdateAllCellsOfGrid(); //eliminate cell of line, and update cell by using m_lines and m_curPoints
    
    m_lines.clear();
    m_preColor  = -1;
    m_curPoints = 0;
    
}
void GameLevelScene::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
    
    CCTouch *pTouch = (CCTouch *)(*pTouches->begin());
    CCPoint pos = pTouch->getLocation();
    CCLog("touch position = (%f, %f)\n", pos.x, pos.y);
    
    //drawLine(pos);

    
}

//eliminate cell of line, and update cell by using m_lines and m_curPoints
void GameLevelScene::UpdateAllCellsOfGrid()
{
    int row = s_pGls->verticalNum;
    int col = s_pGls->horizontalNum;
    int step = 0;
    
    // 1. update roll and remove piece
    // 2. update piece
    
    for (std::vector<CellDataOfGrid>::size_type i = 0; i < m_lines.size(); i++) {
        
        int tag = m_lines[i].index;
        
        // update roll
        int type = m_rollsData[tag].type;
        CCRect rtRoll;
        
        if (type == ROLL_TYPE_BLUE) {
            // ROLL_TYPE_BLUE --> ROLL_TYPE_YELLOW
            
            rtRoll  = (CCRect)(rollDataMap.find(ROLL_TYPE_YELLOW)->second);

            m_pSptBtNode->removeChild(m_pSptBtNode->getChildByTag(tag + ROLL_TAG_BASE * m_cellNum), true);
            
            CCSprite *pSptRoll = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), rtRoll);
            pSptRoll->setPosition(m_piecesData[tag].pt);
            m_pSptBtNode->addChild(pSptRoll, 1, tag + ROLL_TAG_BASE * m_cellNum);
            
            m_rollsData[tag].type = ROLL_TYPE_YELLOW;

            
        } else if(type == ROLL_TYPE_DARK_BLUE) {
            // ROLL_TYPE_DARK_BLUE --> ROLL_TYPE_BLUE
            
            rtRoll  = (CCRect)(rollDataMap.find(ROLL_TYPE_BLUE)->second);
            
            m_pSptBtNode->removeChild(m_pSptBtNode->getChildByTag(tag + ROLL_TAG_BASE * m_cellNum), true);
            
            CCSprite *pSptRoll = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), rtRoll);
            pSptRoll->setPosition(m_piecesData[tag].pt);
            m_pSptBtNode->addChild(pSptRoll, 1, tag + ROLL_TAG_BASE * m_cellNum);
            
            m_rollsData[tag].type = ROLL_TYPE_BLUE;
            
        } else if(type == ROLL_TYPE_REVERSE_BLUE) {
            // ROLL_TYPE_REVERSE_BLUE --> ROLL_TYPE_REVERSE_YELLOW
            
            rtRoll  = (CCRect)(rollDataMap.find(ROLL_TYPE_REVERSE_YELLOW)->second);
            
            m_pSptBtNode->removeChild(m_pSptBtNode->getChildByTag(tag + ROLL_TAG_BASE * m_cellNum), true);
            
            CCSprite *pSptRoll = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), rtRoll);
            pSptRoll->setPosition(m_piecesData[tag].pt);
            m_pSptBtNode->addChild(pSptRoll, 1, tag + ROLL_TAG_BASE * m_cellNum);
            
            m_rollsData[tag].type = ROLL_TYPE_REVERSE_YELLOW;
            
        }else if(type == ROLL_TYPE_REVERSE_YELLOW) {
            // ROLL_TYPE_REVERSE_YELLOW --> ROLL_TYPE_REVERSE_BLUE
            
            rtRoll  = (CCRect)(rollDataMap.find(ROLL_TYPE_REVERSE_BLUE)->second);
            
            m_pSptBtNode->removeChild(m_pSptBtNode->getChildByTag(tag + ROLL_TAG_BASE * m_cellNum), true);
            
            CCSprite *pSptRoll = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), rtRoll);
            pSptRoll->setPosition(m_piecesData[tag].pt);
            m_pSptBtNode->addChild(pSptRoll, 1, tag + ROLL_TAG_BASE * m_cellNum);
            
            m_rollsData[tag].type = ROLL_TYPE_REVERSE_BLUE;
            
        }

        // remove piece
        m_pSptBtNode->removeChild(m_pSptBtNode->getChildByTag(tag + PIECE_TAG_BASE * m_cellNum), true);
        
    }
    
    //
    // ... deal with dropping roll
    
    
    
}

/////////////////////////////////////////
// touch end, remove all lineobj: include bg and top
/////////////////////////////////////////
void  GameLevelScene::removeLinesObj()
{
    for (std::vector<CellDataOfGrid>::size_type i = 0; i < m_lines.size(); i++) {
        this->removeChild(this->getChildByTag(i + 1 + LINE_BG_TAG_BASE  * m_cellNum));
        this->removeChild(this->getChildByTag(i + 1 + LINE_TOP_TAG_BASE * m_cellNum));

    }
}

/////////////////////////////////////////
// procedure:
//
// 1. cell positon illegal and if show
// 2. if color is same
//  2.1 color isnot same, return
//  2.2 color is same, draw line
// 3. judge point number
// 4. if current point is the same as previous point
//
/////////////////////////////////////////
void GameLevelScene::drawLine(const CCPoint &pt)
{
    // -1 : illegal;  cellIndex --> [0, m_cellNum-1]
    int cellIndex = getCellIndexByPosition(pt);
    
    // 1. the pos illegal or can't show
    if (cellIndex == -1 || s_pGls->mapData[cellIndex] == 0) {
        return ;
    }
    
    int curColor = this->getColorTypeByPieceType(cellIndex);
    
    // current color is different from previous color, return
    // 2.1 color is not same
    if (m_preColor != -1 && m_preColor != curColor) {
        return;
    }
    
    CCPoint curPt   = m_piecesData[cellIndex].pt;
    int     elemNum = m_lines.size();
    
    // 2.2 The same color or first point of drawing line
    // 3. 判断是否为第一个点, 只有一个点不画线, only update data
    if (elemNum > 0){
        
        CCPoint prePt  = m_lines[elemNum-1].pt;
        
        // 回退一格
        if (elemNum >= 2) {
            CCPoint pprePt = m_lines[elemNum - 2].pt;
            if ((curPt.x == pprePt.x) && (curPt.y == pprePt.y)){
                
                this->removeChild(this->getChildByTag(elemNum - 1 + LINE_BG_TAG_BASE * m_cellNum));
                this->removeChild(this->getChildByTag(elemNum - 1 + LINE_TOP_TAG_BASE * m_cellNum));
                m_lines.pop_back();
                m_curPoints--;
                
                return;
            }
        }
        
        // 4. if current point is the same as previous point
        // 4.1 the same
        if ((curPt.x == prePt.x) && (curPt.y == prePt.y)){
            // 判断是否和前一个点相同
            // same, return
            return;
        }else {
            // 4.2 not same, draw lines
            
            LineData lineObj  = lineDataObj.find(m_preColor)->second;
            
            float rotation = this->getRotation(prePt, curPt);
            
            // bg sprite img
            CCSprite *pBgSpt  = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), lineObj.bg);
            pBgSpt->setPosition((curPt + prePt)/2);
            pBgSpt->setRotation(rotation);
            this->addChild(pBgSpt, 5, elemNum + LINE_BG_TAG_BASE * m_cellNum);
            
            // top sprite img
            CCSprite *pTopSpt = CCSprite::createWithTexture(m_pSptBtNode->getTexture(), lineObj.top);
            pBgSpt->setPosition((curPt + prePt)/2);
            pBgSpt->setRotation(rotation);
            this->addChild(pTopSpt, 5, elemNum + LINE_TOP_TAG_BASE * m_cellNum);
            
        }
        
    }
    
    m_preColor = curColor;
    m_lines.push_back(CellDataOfGrid(cellIndex, curPt));
    m_curPoints++;
    
}

float GameLevelScene::getRotation(CCPoint a, CCPoint b)const
{
    if(std::abs(a.x - b.x) < 10){
        return 0;
    }else if(a.x > b.x){
        if(a.y < b.y){
            return 120;
        }else{
            return 60;
        }
    }else{
        if(a.y < b.y){
            return 60;
        }else{
            return 120;
        }
    }
    return 0;
}

int GameLevelScene::getColorTypeByPieceType(int pieceIndex)const
{
    
    return (m_piecesData[pieceIndex].colorType);
}

int GameLevelScene::getCellIndexByPosition(const CCPoint &pt)const
{
    // return value: [0, m_cellNum]
    int loc = -1;
    //首先遍历列 找出x 的格子
	//loc = cc.Director.getInstance().convertToGL(loc);
	for (std::vector<PieceDataOfGrid>::size_type i = 0; i < m_piecesData.size(); i++) {
        if (isPointInRange(pt, m_piecesData[i].pt, m_piecesData[i].rt)){
            loc = i;
            break;
        }
    }
    
    return (loc);
    
}

bool GameLevelScene::isPointInRange(const CCPoint &pt, const CCPoint &mid, const CCRect &rt) const
{
    CCPoint begPt = CCPoint(mid.x - rt.size.width/2, mid.y - rt.size.height/2);
    CCPoint endPt = CCPoint(mid.x + rt.size.width/2, mid.y + rt.size.height/2);
    
    if ((pt.x >= begPt.x && pt.x <= endPt.x) &&
        (pt.y >= begPt.y && pt.y <= endPt.y)) {
        return (true);
    }
    return (false);
}

void GameLevelScene::registerWithTouchDispatcher()
{
     CCLog("File: %s, class: GameLevelScene, function: %s, line: %d\n", __FILE__,  __FUNCTION__, __LINE__);
}



