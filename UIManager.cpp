#include "UIManager.h"
#include "Player.h"
#include "Attribute.h"
#include "Equipment.h"
#include <iostream>
#include <iomanip>
#include <windows.h>

void UIManager::displayMessage(const std::string& message, Color color) const {
    // 设置控制台编码为UTF-8以支持中文显示
    SetConsoleOutputCP(CP_UTF8);
    
    // 控制台颜色代码
    const char* colorCodes[] = {
        "\033[30m",  // BLACK
        "\033[31m",  // RED
        "\033[32m",  // GREEN
        "\033[33m",  // YELLOW
        "\033[34m",  // BLUE
        "\033[35m",  // MAGENTA
        "\033[36m",  // CYAN
        "\033[37m",  // WHITE
        "\033[90m",  // GRAY
        "\033[0m"    // RESET
    };
    
    std::cout << colorCodes[static_cast<int>(color)] << message << "\033[0m" << std::endl;
}

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

void UIManager::displayPlayerStatus(const Player& player) const {
    displayMessage("===== 角色状态 =====", Color::CYAN);
    
    // 获取装备信息
    std::map<EquipmentPart, Equipment*> equippedItems = player.getAllEquippedItems();
    
    // 左侧：基础属性，右侧：装备
    std::cout << "\033[37m姓名: " << std::setw(12) << std::left << player.getName() << "\033[0m";
    std::cout << " | \033[33m--- 装备 ---\033[0m" << std::endl;
    
    std::cout << "\033[37m等级: " << std::setw(12) << std::left << player.getLevel() << "\033[0m";
    std::cout << " | \033[37m武器: 六圣裁恶神剑\033[0m" << std::endl;
    
    std::cout << "\033[32m生命值: " << std::setw(8) << std::left << (std::to_string(player.getHP()) + "/" + std::to_string(player.getMaxHP())) << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::HELMET)) {
        std::cout << "\033[35m头盔: " << equippedItems[EquipmentPart::HELMET]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m头盔: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[31m攻击力: " << std::setw(8) << std::left << player.getATK() << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::CHESTPLATE)) {
        std::cout << "\033[35m胸甲: " << equippedItems[EquipmentPart::CHESTPLATE]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m胸甲: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[34m防御力: " << std::setw(8) << std::left << player.getDEF() << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::CAPE)) {
        std::cout << "\033[35m披风: " << equippedItems[EquipmentPart::CAPE]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m披风: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[33m速度: " << std::setw(10) << std::left << player.getSpeed() << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::BOOTS)) {
        std::cout << "\033[35m靴子: " << equippedItems[EquipmentPart::BOOTS]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m靴子: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[36m经验值: " << std::setw(8) << std::left << (std::to_string(player.getExp()) + "/" + std::to_string(player.getExpToNextLevel())) << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::NECKLACE)) {
        std::cout << "\033[35m项链: " << equippedItems[EquipmentPart::NECKLACE]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m项链: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[33m金币: " << std::setw(10) << std::left << player.getGold() << "\033[0m";
    std::cout << " | ";
    if (equippedItems.count(EquipmentPart::RING)) {
        std::cout << "\033[35m戒指: " << equippedItems[EquipmentPart::RING]->getName() << "\033[0m" << std::endl;
    } else {
        std::cout << "\033[90m戒指: [空]\033[0m" << std::endl;
    }
    
    std::cout << "\033[35m暴击率: " << std::setw(8) << std::left << (std::to_string(static_cast<int>(player.getCritRate() * 100)) + "%") << "\033[0m" << std::endl;
    
    displayMessage("==================", Color::CYAN);
    
    // 显示已解锁技能
    displayMessage("--- 已解锁技能 ---", Color::YELLOW);
    const auto& skills = player.getSkills();
    if (skills.empty()) {
        displayMessage("暂无已解锁技能", Color::GRAY);
    } else {
        for (const auto& skill : skills) {
            std::cout << "\033[33m[" << skill->getName() << "]\033[0m ";
            std::cout << "\033[37m" << skill->getDescription() << "\033[0m" << std::endl;
        }
    }
    
    displayMessage("-------------------", Color::YELLOW);
    
    // 显示背包物品
    displayMessage("--- 背包物品 ---", Color::GREEN);
    const auto& inventory = player.getInventory();
    if (inventory.empty()) {
        displayMessage("背包为空", Color::GRAY);
    } else {
        for (const auto& item : inventory) {
            std::cout << "\033[32m" << item.first << "\033[0m: \033[37m" << item.second << "个\033[0m" << std::endl;
        }
    }
    
    displayMessage("------------------", Color::GREEN);
}

void UIManager::displaySimpleCombatStatus(const Attribute& player, const Attribute& enemy) const {
    // 简化的战斗状态显示，只显示核心信息
    std::cout << "\033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m" << std::endl;
    
    // 玩家信息（左侧）
    std::cout << "\033[32m" << std::setw(15) <<std::left<< player.getName() 
              << " Lv." << std::setw(3) << player.getLevel()
              << " HP: " << std::setw(4) << player.getHP() << "/" << std::setw(4) << player.getMaxHP() << "\033[0m";

    std::cout << " VS ";

    // 敌人信息（右侧）
    std::cout << "\033[31m" << std::setw(15)<<std::left << enemy.getName()
              << " Lv." << std::setw(3) << enemy.getLevel()
              << " HP: " << std::setw(4) << enemy.getHP() << "/" << std::setw(4) << enemy.getMaxHP() << "\033[0m" << std::endl;
    
    std::cout << "\033[36m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\033[0m" << std::endl;
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
