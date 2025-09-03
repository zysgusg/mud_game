#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include "Player.h"
#include "UIManager.h"
#include "TaskSystem.h" // 需要包含TaskSystem
#include <string>
#include <vector>
#include <ctime>
#include <filesystem> // 需要 C++17 支持

// 存档槽元数据结构
struct SaveSlot {
    int id;
    std::string filename;
    time_t timestamp;
    std::string playerName;
    int playerLevel;
};

class SaveLoadSystem {
public:
    SaveLoadSystem(UIManager& uiManager);

    void saveGame(const Player& player, const TaskSystem& tasks);
    bool loadGame(Player& player, TaskSystem& tasks);

private:
    UIManager& ui;
    const int MAX_SAVES = 10;
    const std::string SAVE_DIR = "save"; // 定义存档目录

    std::vector<SaveSlot> listSaveSlots();
};

#endif // SAVELOADSYSTEM_H