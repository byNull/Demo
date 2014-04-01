//
//  gameLevelScene.h
//  Demo
//
//  Created by Apple on 3/26/14.
//
//

#ifndef __Demo__gameLevelScene__
#define __Demo__gameLevelScene__

#include <iostream>
#include "common.h"
#include "reader.h"
using namespace rapidjson;


// predeclaration
class GameLevelScene;
class GameLEvelStruct;

// global function
void initGameElementCoord();




////////////////////////////////////////////////////////
//
// definition: GameLevelStruct
// store json file structure
//
///////////////////////////////////////////////////////
class GameLevelJsonStruct : public CCObject{
    
public:
    GameLevelJsonStruct() : rollData(NULL), enemyData(NULL), mapData(NULL), pieceData(NULL){
        
    }
    ~GameLevelJsonStruct();
    GameLevelJsonStruct(const GameLevelJsonStruct &right);
    GameLevelJsonStruct& operator= (const GameLevelJsonStruct &right);
    
    void getLevelConfig(int lev);
    void releaseLevelConfig(int lev);
    
    static GameLevelJsonStruct* create();
    
    
private:
    void copyObj(const GameLevelJsonStruct &obj);
    void destory(const GameLevelJsonStruct &obj);
    
    
    
public:
    int difficulty; // probability of lower difficult
    int dynamiteProbability; // probability of appeared dynamite
    int gameClearType; // 1--turn(by step), 0--time(by time)
    int colorNum; // coin num of certain level
    int horizontalNum;// grid num of horizent
    int verticalNum; // grid num of vertical
    int turnNum;  //step num of finishing game
    int totalSecond; // time of remove piece
    int targetScore; // obtained score of going through level
    int shutterScore; // remove shutter of obtain specified score
    int level; //num of barrier
    
    /*
     background color:
     0    -- yellow
     1000 -- blue
     1010 -- deep blue
     1020 -- reversed blue
     1030 -- reversed yellow
     */
    int *rollData;
    
    /*
     0 -- no enemy
     808 --
     1100 --
     1130 --
     1300 -- lock
     1110 -- deep stone
     1200 -- stell mesh
     14** -- barrier (hexagon : six shape) :
         1400 -- top and bottom can joint line
         1410 -- top
         1420 -- right top
         1430 -- right top, right
         1440 -- top, bottom, right
         1450 -- top, left top, left bottom, right top, right bottom
         1460 -- left top, left bottom, right top, right bottom
    15**
     ...
     ...
     
     */
    int *enemyData;
    
    /*
     if show certain grid
     0 -- show
     1 -- hide
     */
    int *mapData;
    
    /*
     0 -- not coin
     100 -- have coin
     80* -- have bomb, * -- duration: seconds
     */
    int *pieceData; // grid coin of init
};


// struct type
struct CellDataOfGrid{
    CellDataOfGrid(int idx, CCPoint tpt = CCPointZero) : index(idx), pt(tpt) { }
    
    int     index; // index --> [0, m_cellNum)
    CCPoint pt;
};

struct RollDataOfGrid{
    int     index;
    int     type;
    CCPoint pt;
    CCRect  rt;
};

enum RollType{
    ROLL_TYPE_YELLOW = 0,
    ROLL_TYPE_BLUE   = 1000,
    ROLL_TYPE_DARK_BLUE = 1010,
    ROLL_TYPE_REVERSE_BLUE = 1020,
    ROLL_TYPE_REVERSE_YELLOW  = 1030,
    
};

struct PieceDataOfGrid{
    int     valueOfPos;
    int     colorType;
    CCPoint pt;
    CCRect  rt;
    int     index;
};

class GameLevelScene : public CCLayer
{
public:
    
    GameLevelScene(int lev = -1);
    ~GameLevelScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void  initConfigWithGameLevel(int lev);
    
    void  setLevel(int lev){ m_level = lev;}
    int   getLevel() const { return (m_level);}
    
    void  removeLinesObj(); //消除方格时移除线对象
    void  UpdateAllCellsOfGrid();
    void  drawLine(const CCPoint &pt);
    int   getCellIndexByPosition(const CCPoint &pt)const;
    int   getColorTypeByPieceType(int pieceIndex)const;
    float getRotation(CCPoint a, CCPoint b)const;
    bool  isPointInRange(const CCPoint &pt, const CCPoint &mid, const CCRect &rt) const;

    
    
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    //static cocos2d::CCScene* scene();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    
    virtual void registerWithTouchDispatcher();
    
    void menuReturnCallback(CCObject* pSender);
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLevelScene);
    
protected:
    //void goGameLevel(int level);
    
//    virtual void initMapLyr();
    virtual void initUI();
//    virtual void initEnemyLyr();
//    virtual void initPieceLyr();
    
    void initGameElementCoordinate();
    
    
protected:
    
    std::vector<CellDataOfGrid>  m_lines;
    std::map<int, CCPoint>       m_GridPos;
    std::vector<PieceDataOfGrid> m_piecesData;
    std::vector<RollDataOfGrid>  m_rollsData;
    
    CCPoint m_tBeginPos;
    
    
    CCArray rollData;
    CCArray enemyData;
    CCArray pieceData;
    CCArray mapData; //priority higher rollData: represent if show?
    
    // Sequence: (down-->up) rollLyr->enemey->pieceLyr
    CCLayer *mapLyr;
    CCLayer *rollLyr;
    CCLayer *enemyLyr;
    CCLayer *pieceLyr;
    
    int     m_level;  // locate certain level
    int     m_cellNum;
    int     m_preColor; // 0, 1, 2, 3
    int     m_curPoints;
    
    CCSpriteBatchNode *m_pSptBtNode;
    
    float leftStart;
    float topStart;
    
    
    int MAP_TAG_BASE;     // 0
    int ROLL_TAG_BASE;    // 1
    int ENEMY_TAG_BASE;   // 2
    int PIECE_TAG_BASE;   // 3
    int LINE_BG_TAG_BASE; // 4
    int LINE_TOP_TAG_BASE;// 5
    
public:
    //顶部不可覆盖区域高度
	static int TOP_HEIGHT       ;
    
	//底部不可覆盖区域高度
	static int BOTTOM_HEIGHT    ;
    
	//六边形边长
	static int CELL_LENGTH      ;
    
	//
	static int CELL_WIDTH       ;
	static int CELL_HEIGHT      ;
    
	static int CELL_TOUCH_LENGTH;
    
};


template <typename type1, typename type2>
typename std::multimap<type1, type2>::iterator operator+(typename std::multimap<type1, type2>::iterator &it, int i)
{
    for (int k = 0; k < i; k++) {
        it++;
    }
    
    return (it);
}



#endif /* defined(__Demo__gameLevelScene__) */

/*
 
 var rollDataObj = {
 0: 	cc.rect(1214, 1216, 111, 96),
 1000: 	cc.rect(1101, 1216, 111, 96),
 1010: 	cc.rect(518, 1216, 111, 96),
 1020: 	cc.rect(875, 1196, 111, 96),
 1030: 	cc.rect(988, 1196, 111, 96),
 };
 
 var enemyDataObj = {
 1100: cc.rect(1811, 1174, 111, 96), //stone lv1
 1110: cc.rect(1924, 1174, 111, 96), //stone lv2
 1300: cc.rect(1327, 1236, 111, 96), //锁
 1130: cc.rect(1214, 1216, 111, 96),
 1200: cc.rect(237, 1172, 111, 96),	//铁丝网
 
 1400: cc.rect(640, 1143, 120, 102),
 1410: cc.rect(396, 1160, 120, 102),
 1420: cc.rect(1454, 1163, 120, 102),
 1430: cc.rect(1576, 1163, 120, 102),
 1440: cc.rect(2, 1167, 120, 102),
 1450: cc.rect(1535, 1059, 120, 102),
 1460: cc.rect(1657, 1059, 120, 102),
 
 1500: cc.rect(844, 1092, 120, 102),
 1510: cc.rect(966, 1092, 120, 102),
 1520: cc.rect(1088, 1092, 120, 102),
 1530: cc.rect(518, 1112, 120, 102),
 1540: cc.rect(1210, 1112, 120, 102),
 1550: cc.rect(1332, 1132, 120, 102),
 1560: cc.rect(396, 1056, 120, 102),
 };
 
 var pieceDataObj = {
 100: [
 绿色		cc.rect(525, 1611, 80, 80),
 黄色		cc.rect(607, 1611, 80, 80),
 蓝色		cc.rect(442, 1611, 80, 80),
 蓝色	    cc.rect(266, 1625, 80, 80)
 ],
 800: [
 cc.rect(1960, 301, 78, 103),
 cc.rect(1035, 1314, 78, 103),
 cc.rect(475, 1314, 78, 103),
 cc.rect(1115, 1314, 78, 103)
 ]
 };
 
 */


