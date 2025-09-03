#include "UIManager.h"
#include "Player.h"
#include"Skills.h"
#include <iostream>

void UIManager::setColor(Color color) const {
    switch (color) {
    case Color::BLACK:   std::cout << "\033[30m"; break;
    case Color::RED:     std::cout << "\033[31m"; break;
    case Color::GREEN:   std::cout << "\033[32m"; break;
    case Color::YELLOW:  std::cout << "\033[33m"; break;
    case Color::BLUE:    std::cout << "\033[34m"; break;
    case Color::MAGENTA: std::cout << "\033[35m"; break;
    case Color::CYAN:    std::cout << "\033[36m"; break;
    case Color::WHITE:   std::cout << "\033[37m"; break;
    case Color::GRAY:    std::cout << "\033[90m"; break;
    case Color::RESET:   std::cout << "\033[0m";  break;
    }
}

std::string equipmentPartToString(EquipmentPart part) {
    switch (part) {
    case EquipmentPart::HELMET: return "头盔";
    case EquipmentPart::CHESTPLATE: return "胸甲";
    case EquipmentPart::CAPE: return "披风";
    case EquipmentPart::BOOTS: return "靴子";
    case EquipmentPart::NECKLACE: return "项链";
    case EquipmentPart::RING: return "戒指";
    default: return "未知部位";
    }
}
void UIManager::displayMessage(const std::string& message, Color color) const {
    setColor(color);
    std::cout << message << std::endl;
    setColor(Color::RESET);
}

void UIManager::displayPlayerEquipment(const Player& player) const{
    displayMessage("--- 装备 ---", Color::YELLOW);
    std::cout << "武器:六圣裁恶神剑" << std::endl;
    std::vector<EquipmentPart> slotOrder = {
        EquipmentPart::HELMET,
        EquipmentPart::CHESTPLATE,
        EquipmentPart::CAPE,
        EquipmentPart::BOOTS,
        EquipmentPart::NECKLACE,
        EquipmentPart::RING
    };

    std::map<EquipmentPart, Equipment*> equippedItems = player.getAllEquippedItems();

    for (EquipmentPart part : slotOrder) {
        std::cout << equipmentPartToString(part) << ": ";
        // 检查玩家是否在该槽位装备了物品
        if (equippedItems.count(part)) {
            std::cout << equippedItems[part]->getName() << std::endl;
        }
        else {
            std::cout << "[空]" << std::endl;
        }
    }
}
void UIManager::displayPlayerStatus(const Player& Player) const {
    displayMessage("--- 角色状态 ---", Color::YELLOW);
    std::cout << "姓名: " << Player.getName() << " | 等级: " << Player.getLevel() << std::endl;
    std::cout << "生命: " << Player.getHP() << "/" << Player.getMaxHP() << std::endl;
    std::cout << "攻击: " << Player.getATK() << " | 防御: " << Player.getDEF() << " | 速度: " << Player.getSpeed() << std::endl;
    std::cout << "经验: " << Player.getExp() << " | 金币: " << Player.getGold() << std::endl;

    displayMessage("--- 技能 ---", Color::CYAN);
    if (Player.getSkills().empty()) {
        std::cout << "无" << std::endl;
    }
    else {
        std::string skill_line;
        for (const auto& skill : Player.getSkills()) {
            skill_line += "[" + skill->getName() + "] ";
        }
        std::cout << skill_line << std::endl;
    }

    displayPlayerEquipment(Player);
    displayMessage("--- 道具 ---", Color::CYAN);
    if (Player.inventory.empty()) {
        std::cout << "背包是空的" << std::endl;
    }
    else {
        std::string item_line;
        for (const auto& pair : Player.inventory) {
            // pair.first 是物品名称, pair.second 是数量
            item_line += pair.first + " x" + std::to_string(pair.second) + " | ";
        }
        // 移除末尾多余的 " | "
        if (!item_line.empty()) {
            item_line.pop_back();
            item_line.pop_back();
            item_line.pop_back();
        }
        std::cout << item_line << std::endl;
    }

    displayMessage("------------------", Color::YELLOW);
}
void UIManager::displayScene(const std::string& description) const {
    displayMessage("--- 当前场景 ---", Color::GREEN);
    displayMessage(description, Color::WHITE);
    displayMessage("------------------", Color::GREEN);
}

void UIManager::pause() const {
    displayMessage("按 Enter 键继续...", Color::GRAY);
    std::string dummy;
    std::getline(std::cin, dummy);
}
