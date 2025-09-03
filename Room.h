#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>

class Room {
private:
    int roomId;
    std::string roomName;
    std::string description;
    std::string hint;
    std::map<std::string, std::pair<int, std::string>> exits; // 方向到房间ID和名称的映射
    std::vector<std::string> npcs;
    std::vector<std::string> items;

    // 静态成员变量声明（不初始化）
    static const std::map<std::string, std::string> DIR_TO_NUM;
    static const std::map<std::string, std::string> NUM_TO_DIR;

public:
    Room(int id, const std::string& name, const std::string& desc, const std::string& h);

    int getRoomId() const { return roomId; }
    std::string getRoomName() const { return roomName; }
    std::string getDescription() const { return description; }
    std::string getHint() const { return hint; }

    void addExit(const std::string& dir, int targetRoomId, const std::string& targetRoomName);
    void addNPC(const std::string& npcName);
    void addItem(const std::string& itemName);

    const std::map<std::string, std::pair<int, std::string>>& getExits() const { return exits; }

    void showRoomInfo() const;

    // 方向与数字转换
    static std::string numberToDir(const std::string& num) {
        auto it = NUM_TO_DIR.find(num);
        return (it != NUM_TO_DIR.end()) ? it->second : "";
    }

    static std::string dirToNumber(const std::string& dir) {
        auto it = DIR_TO_NUM.find(dir);
        return (it != DIR_TO_NUM.end()) ? it->second : "";
    }
};

#endif // ROOM_H
