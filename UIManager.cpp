#include "UIManager.h"
#include "Player.h"
#include "Attribute.h"
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
void UIManager::displayPlayerStatus(const Player& player) const {
    displayMessage("===== 角色状态 =====", Color::CYAN);
    displayMessage("姓名: " + player.getName(), Color::WHITE);
    displayMessage("等级: " + std::to_string(player.getLevel()), Color::WHITE);
    displayMessage("生命值: " + std::to_string(player.getHP()) + "/" + std::to_string(player.getMaxHP()), Color::GREEN);
    displayMessage("攻击力: " + std::to_string(player.getATK()), Color::RED);
    displayMessage("防御力: " + std::to_string(player.getDEF()), Color::BLUE);
    displayMessage("速度: " + std::to_string(player.getSpeed()), Color::YELLOW);
    displayMessage("经验值: " + std::to_string(player.getExp()) + "/" + std::to_string(player.getExpToNextLevel()), Color::CYAN);
    displayMessage("金币: " + std::to_string(player.getGold()), Color::YELLOW);
    displayMessage("暴击率: " + std::to_string(static_cast<int>(player.getCritRate() * 100)) + "%", Color::MAGENTA);
    displayMessage("==================", Color::CYAN);
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
