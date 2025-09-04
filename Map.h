#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "Room.h"
#include "NPC.h"
#include "EvilGeneral.h"
#include "CommonEnemy.h"

// 前向声明
class UIManager;

class Map {
private:
    std::unordered_map<int, Room> rooms;
    std::unordered_map<int, std::unique_ptr<NPC>> roomNPCs;        // 房间ID -> NPC
    std::unordered_map<int, std::unique_ptr<EvilGeneral>> roomBosses; // 房间ID -> BOSS
    std::unordered_map<int, std::vector<std::unique_ptr<CommonEnemy>>> roomEnemies; // 房间ID -> 普通敌人列表
    int currentRoomId;

    // 初始化所有房间
    void initRooms();
    
    // 初始化NPC
    void initNPCs();
    
    // 初始化BOSS
    void initBosses();
    
    // 初始化普通敌人
    void initEnemies();

    // 绘制全局地图
    void drawGlobalMap() const;

    // 绘制定位地图
    void drawLocationMap() const;

public:
    Map();

    // 显示全局地图
    void showGlobalMap();

    // 显示定位地图
    void showLocationMap();

    // 移动房间
    bool switchRoom(const std::string& input);

    // 显示当前房间信息
    void showCurrentRoom() const;
    
    // 显示初始房间信息
    void showInitialRoom() const;

    // 快速跳转房间
    void jumpToRoom(int roomId);
    
    // 获取当前房间ID
    int getCurrentRoomId() const;
    
    // 设置当前房间ID
    void setCurrentRoomId(int roomId);
    
    // 获取当前房间的NPC
    NPC* getCurrentRoomNPC() const;
    
    // 获取当前房间的BOSS
    EvilGeneral* getCurrentRoomBoss() const;
    
    // 获取当前房间的随机敌人
    CommonEnemy* getRandomEnemy() const;
    
    // 移除已击败的敌人
    void removeDefeatedEnemy(CommonEnemy* enemy);
    
    // 移除已击败的BOSS
    void removeDefeatedBoss();
};

#endif // MAP_H
