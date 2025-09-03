#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <string>
#include "Room.h"

class Map {
private:
    std::unordered_map<int, Room> rooms;
    int currentRoomId;

    // 初始化所有房间
    void initRooms();

    // 绘制全局地图
    void drawGlobalMap() const;

    // 绘制定位地图
    void drawLocationMap() const;

public:
    Map();

    // 显示全局地图（只声明，不实现）
    void showGlobalMap();

    // 显示定位地图（只声明，不实现）
    void showLocationMap();

    // 移动房间（只声明，不实现）
    bool switchRoom(const std::string& input);

    // 显示初始房间信息（只声明，不实现）
    void showInitialRoom() const;

    // 快速跳转房间（只声明，不实现）
    void jumpToRoom(int roomId);
};

#endif // MAP_H
