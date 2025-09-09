#include "SaveLoadSystem.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <regex>
#include <sstream>

bool SaveLoadSystem::is_digits_save(const std::string& str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

std::string SaveLoadSystem::timeToString(time_t time)
{
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &time);
#else
    localtime_r(&time, &tm_buf);
#endif
    std::stringstream ss;
    ss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

SaveLoadSystem::SaveLoadSystem(UIManager& uiManager) : ui(uiManager)
{
    if (!std::filesystem::exists(SAVE_DIR))
    {
        std::filesystem::create_directory(SAVE_DIR);
    }
}

std::vector<SaveSlot> SaveLoadSystem::listSaveSlots()
{
    std::vector<SaveSlot> slots;
    const std::regex file_regex("save_slot_(\\d+)_(\\d{14})\\.sav");

    for (const auto& entry : std::filesystem::directory_iterator(SAVE_DIR))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            std::smatch match;
            if (std::regex_match(filename, match, file_regex))
            {
                SaveSlot slot;
                slot.id = std::stoi(match[1].str());
                slot.filename = filename;

                std::tm tm = {};
                std::stringstream ss(match[2].str());
                ss >> std::get_time(&tm, "%Y%m%d%H%M%S");
                slot.timestamp = mktime(&tm);

                std::ifstream file(entry.path().string());
                if (file.is_open())
                {
                    std::string line, key;
                    if (std::getline(file, line))
                    {
                        std::stringstream meta_ss(line);
                        std::string meta_key;
                        meta_ss >> meta_key >> slot.playerName >> slot.playerLevel;
                        if (meta_key == "META") {
                            slots.push_back(slot);
                        }
                    }
                    file.close();
                }
            }
        }
    }
    return slots;
}

void SaveLoadSystem::saveGame(const Player& player, const TaskSystem& taskProgress)
{
    auto slots = listSaveSlots();
    int slotToUse = -1;

    if (slots.size() < MAX_SAVES)
    {
        for (int i = 0; i < MAX_SAVES; ++i)
        {
            bool is_used = false;
            for (const auto& s : slots)
            {
                if (s.id == i)
                {
                    is_used = true;
                    break;
                }
            }
            if (!is_used)
            {
                slotToUse = i;
                break;
            }
        }
    }
    else
    {
        ui.displayMessage("存档已满！请选择一个要覆盖的存档，或输入 'c' 取消。", UIManager::Color::YELLOW);
        for (const auto& slot : slots)
        {
            std::string text = "[" + std::to_string(slot.id) + "] " + slot.playerName +
                " - 等级 " + std::to_string(slot.playerLevel) +
                " (存档时间: " + timeToString(slot.timestamp) + ")";
            ui.displayMessage(text, UIManager::Color::WHITE);
        }

        while (true)
        {
            std::cout << "请输入要覆盖的存档槽位ID (0-9) 或 'c' 取消: ";
            std::string choice_str;
            std::cin >> choice_str;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (choice_str == "c" || choice_str == "C")
            {
                ui.displayMessage("保存已取消。", UIManager::Color::GRAY);
                return;
            }
            if (is_digits_save(choice_str))
            {
                int choice_id = std::stoi(choice_str);
                if (choice_id >= 0 && choice_id < MAX_SAVES)
                {
                    slotToUse = choice_id;
                    break;
                }
            }
            std::cout << "无效输入，请重试。" << std::endl;
        }
    }

    for (const auto& slot : slots)
    {
        if (slot.id == slotToUse)
        {
            std::filesystem::remove(std::filesystem::path(SAVE_DIR) / slot.filename);
            break;
        }
    }

    time_t now = time(nullptr);
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &now);
#else
    localtime_r(&now, &tm_buf);
#endif
    std::stringstream filename_ss;
    filename_ss << "save_slot_" << slotToUse << "_" << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << ".sav";
    std::string filename = filename_ss.str();

    std::ofstream saveFile((std::filesystem::path(SAVE_DIR) / filename).string());
    if (!saveFile)
    {
        ui.displayMessage("错误: 无法创建存档文件 " + filename, UIManager::Color::RED);
        return;
    }

    saveFile << "META " << player.getName() << " " << player.getLevel() << std::endl;
    saveFile << "Level " << player.getLevel() << std::endl;
    saveFile << "Hp " << player.getHP() << std::endl;
    saveFile << "MaxHp " << player.getMaxHP() << std::endl;
    saveFile << "Attack " << player.getATK() << std::endl;
    saveFile << "Defense " << player.getDEF() << std::endl;
    saveFile << "Speed " << player.getSpeed() << std::endl;
    saveFile << "Experience " << player.getExp() << std::endl;
    saveFile << "Gold " << player.getGold() << std::endl;
    saveFile << "CritRate " << player.getCritRate() << std::endl;
    saveFile << "CurrentRoom " << player.getCurrentRoomId() << std::endl;

    // 保存背包道具
    const auto& inventory = player.getInventory();
    for (const auto& item : inventory)
    {
        saveFile << "Item " << item.first << " " << item.second << std::endl;
    }

    for (const auto& pair : player.taskProgress)
    {
        const Task& task = pair.second;
        saveFile << "Task " << task.getId() << " " << static_cast<int>(task.getStatus()) << std::endl;
    }

    saveFile.close();
    ui.displayMessage("游戏已成功保存到槽位 " + std::to_string(slotToUse), UIManager::Color::GREEN);
}

void SaveLoadSystem::autoSaveGame(const Player& player, const TaskSystem& taskProgress)
{
    // 删除旧的自动存档
    for (const auto& entry : std::filesystem::directory_iterator(SAVE_DIR))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            if (filename.find("auto_save_") == 0)
            {
                std::filesystem::remove(entry.path());
            }
        }
    }

    // 创建新的自动存档
    time_t now = time(nullptr);
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &now);
#else
    localtime_r(&now, &tm_buf);
#endif
    std::stringstream filename_ss;
    filename_ss << "auto_save_" << std::put_time(&tm_buf, "%Y%m%d%H%M%S") << ".sav";
    std::string filename = filename_ss.str();

    std::ofstream saveFile((std::filesystem::path(SAVE_DIR) / filename).string());
    if (!saveFile)
    {
        ui.displayMessage("错误: 无法创建自动存档文件 " + filename, UIManager::Color::RED);
        return;
    }

    saveFile << "META " << player.getName() << " " << player.getLevel() << std::endl;
    saveFile << "Level " << player.getLevel() << std::endl;
    saveFile << "Hp " << player.getHP() << std::endl;
    saveFile << "MaxHp " << player.getMaxHP() << std::endl;
    saveFile << "Attack " << player.getATK() << std::endl;
    saveFile << "Defense " << player.getDEF() << std::endl;
    saveFile << "Speed " << player.getSpeed() << std::endl;
    saveFile << "Experience " << player.getExp() << std::endl;
    saveFile << "Gold " << player.getGold() << std::endl;
    saveFile << "CritRate " << player.getCritRate() << std::endl;
    saveFile << "CurrentRoom " << player.getCurrentRoomId() << std::endl;

    // 保存背包道具
    const auto& inventory = player.getInventory();
    for (const auto& item : inventory)
    {
        saveFile << "Item " << item.first << " " << item.second << std::endl;
    }

    for (const auto& pair : player.taskProgress)
    {
        const Task& task = pair.second;
        saveFile << "Task " << task.getId() << " " << static_cast<int>(task.getStatus()) << std::endl;
    }

    saveFile.close();
    ui.displayMessage("游戏已自动保存", UIManager::Color::BLUE);
}

bool SaveLoadSystem::loadGame(Player& player, TaskSystem& taskProgress)
{
    auto slots = listSaveSlots();
    
    // 检查是否有自动存档
    std::vector<std::string> autoSaves;
    for (const auto& entry : std::filesystem::directory_iterator(SAVE_DIR))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            if (filename.find("auto_save_") == 0)
            {
                autoSaves.push_back(filename);
            }
        }
    }
    
    if (slots.empty() && autoSaves.empty())
    {
        ui.displayMessage("没有可用的存档。", UIManager::Color::YELLOW);
        return false;
    }

    ui.displayMessage("请选择要加载的存档:", UIManager::Color::CYAN);
    
    // 显示自动存档选项
    if (!autoSaves.empty())
    {
        ui.displayMessage("[auto] 自动存档", UIManager::Color::BLUE);
    }
    
    // 显示手动存档
    for (const auto& slot : slots)
    {
        std::string text = "[" + std::to_string(slot.id) + "] " + slot.playerName +
            " - 等级 " + std::to_string(slot.playerLevel) +
            " (存档时间: " + timeToString(slot.timestamp) + ")";
        ui.displayMessage(text, UIManager::Color::WHITE);
    }

    int choice_id = -1;
    std::string filename_to_load;

    while (true)
    {
        std::cout << "请输入存档槽位ID、'auto'(自动存档) 或 'c'(取消): ";
        std::string choice_str;
        std::cin >> choice_str;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice_str == "c" || choice_str == "C")
        {
            ui.displayMessage("读档已取消。", UIManager::Color::GRAY);
            return false;
        }
        
        if (choice_str == "auto" && !autoSaves.empty())
        {
            // 选择最新的自动存档
            filename_to_load = autoSaves[0]; // 假设第一个是最新的
            break;
        }

        if (is_digits_save(choice_str))
        {
            choice_id = std::stoi(choice_str);
            bool valid = false;
            for (const auto& slot : slots)
            {
                if (slot.id == choice_id)
                {
                    filename_to_load = slot.filename;
                    valid = true;
                    break;
                }
            }
            if (valid)
                break;
        }
        std::cout << "无效输入, 请重新输入。" << std::endl;
    }

    std::ifstream loadFile((std::filesystem::path(SAVE_DIR) / filename_to_load).string());
    if (!loadFile.is_open())
    {
        ui.displayMessage("错误：无法打开存档文件。", UIManager::Color::RED);
        return false;
    }

    // 清空玩家数据避免重复
    player.taskProgress.clear();
    player.clearInventory();  // 使用clearInventory方法清空背包避免物品翻倍

    std::string dummy;
    std::getline(loadFile, dummy);
    std::stringstream meta_ss(dummy);
    std::string meta_key;
    std::string player_name;
    meta_ss >> meta_key >> player_name;
    if (meta_key == "META") {
        player.setName(player_name);
    }
    std::string key;
    while (loadFile >> key)
    {
        if (key == "Level") {
            int level;
            loadFile >> level;
            player.setLevel(level);
        }
        else if (key == "Hp") {
            int hp;
            loadFile >> hp;
            player.setHP(hp);
        }
        else if (key == "MaxHp") {
            int maxHp;
            loadFile >> maxHp;
            player.setMaxHP(maxHp);
        }
        else if (key == "Attack") {
            int atk;
            loadFile >> atk;
            player.setATK(atk);
        }
        else if (key == "Defense") {
            int def;
            loadFile >> def;
            player.setDEF(def);
        }
        else if (key == "Speed") {
            int speed;
            loadFile >> speed;
            player.setSpeed(speed);
        }
        else if (key == "Experience") {
            int exp;
            loadFile >> exp;
            player.setExp(exp);
        }
        else if (key == "Gold") {
            int gold;
            loadFile >> gold;
            player.setGold(gold);
        }
        else if (key == "CritRate") {
            float critRate;
            loadFile >> critRate;
            player.setCritRate(critRate);
        }
        else if (key == "CurrentRoom") {
            int roomId;
            loadFile >> roomId;
            player.setCurrentRoomId(roomId);
        }
        else if (key == "Item") {
            std::string itemName;
            int quantity;
            loadFile >> itemName >> quantity;
            player.addItemByName(itemName, quantity);
        }
        else if (key == "Task") {
            std::string taskId;
            int statusInt;
            loadFile >> taskId >> statusInt;
            TaskStatus status = static_cast<TaskStatus>(statusInt);
            
            // 查找对应的任务并添加到玩家任务进度中
            Task* task = taskProgress.findTask(taskId);
            if (task) {
                Task taskCopy = *task;
                taskCopy.setStatus(status);
                player.taskProgress[taskId] = taskCopy;
            }
        }
    }

    loadFile.close();
    if (choice_id != -1) {
        ui.displayMessage("游戏已从槽位 " + std::to_string(choice_id) + " 成功加载!", UIManager::Color::GREEN);
    } else {
        ui.displayMessage("游戏已从自动存档成功加载!", UIManager::Color::GREEN);
    }
    return true;
}