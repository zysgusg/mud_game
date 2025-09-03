#include "CombatSystem.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <limits>

CombatSystem::CombatSystem(UIManager &uiManager) : ui(uiManager) {}
bool is_digits(const std::string &str)
{
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
// calculateDamage 和 attemptEscape 函数无需改动
int CombatSystem::calculateDamage(const Attribute &attacker, const Attribute &defender, int power)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    int baseAttack = (power > 0) ? power : attacker.getATK();
    bool isCrit = dis(gen) < attacker.getCritRate();
    if (isCrit)
    {
        ui.displayMessage(attacker.getName() + " 打出了致命一击!", UIManager::Color::YELLOW);
        baseAttack *= 2;
    }
    int damage = baseAttack - defender.getDEF();
    return std::max(1, damage);
}

bool CombatSystem::attemptEscape(const Player &player, const CommonEnemy &enemy)
{
    double escapeChance = 0.5 + (player.getSpeed() - enemy.getSpeed()) * 0.02;
    escapeChance = std::max(0.05, std::min(0.95, escapeChance));
    ui.displayMessage("你的逃跑成功率为 " + std::to_string(static_cast<int>(escapeChance * 100)) + "%...", UIManager::Color::GRAY);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen) < escapeChance;
}

// playerTurn 函数现在代表玩家的“单次行动”
void CombatSystem::playerTurn(Player &player, CommonEnemy &enemy, const std::map<int, std::unique_ptr<Item>> &itemDb)
{
    // 函数前半部分的菜单和输入逻辑保持不变
    ui.displayMessage("选择行动: [1]攻击 [2]技能 [3]道具 [4]逃跑", UIManager::Color::WHITE);
    int choice = 0;
    while (!(std::cin >> choice) || choice < 1 || choice > 4)
    {
        std::cout << "无效输入, 请输入 1-4 之间的数字: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice)
    {
    case 1: // 攻击
    case 2: // 技能
        if (choice == 1)
        {
            int damage = calculateDamage(player, enemy);
            enemy.takeDamage(damage);
            ui.displayMessage("你对 " + enemy.getName() + " 造成了 " + std::to_string(damage) + " 点伤害!", UIManager::Color::RED);
        }
        else
        {
            if (player.getSkills().empty())
            {
                ui.displayMessage("你没有可用的技能!", UIManager::Color::YELLOW);
                playerTurn(player, enemy, itemDb); // 让玩家重新选择
                return;
            }
            ui.displayMessage("选择技能:", UIManager::Color::WHITE);
            for (size_t i = 0; i < player.getSkills().size(); ++i)
            {
                ui.displayMessage("[" + std::to_string(i + 1) + "] " + player.getSkills()[i]->getName(), UIManager::Color::WHITE);
            }
            int skillChoice = 0;
            std::cin >> skillChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (skillChoice > 0 && skillChoice <= player.getSkills().size())
            {
                Skill& skill = *(player.getSkills()[skillChoice - 1]);
                switch (skill.getDamageType())
                {
                case DamageType::PHYSICAL:
                {
                    int damage = calculateDamage(player, enemy, skill.getPower());
                    enemy.takeDamage(damage);
                    ui.displayMessage("你使用 [" + skill.getName() + "] 对 " + enemy.getName() + " 造成了 " + std::to_string(damage) + " 点物理伤害!", UIManager::Color::MAGENTA);
                    break;
                }                
                case DamageType::MAGICAL:
                {
                    int damage = calculateDamage(player, enemy, skill.getPower());
                    enemy.takeDamage(damage);
                    ui.displayMessage("你使用 [" + skill.getName() + "] 对 " + enemy.getName() + " 造成了 " + std::to_string(damage) + " 点魔法伤害!", UIManager::Color::MAGENTA);
                    break;
                }
                case DamageType::BUFF:
                {
                    player.heal(skill.getPower());
                    ui.displayMessage("你使用 [" + skill.getName() + "] 恢复了 " + std::to_string(skill.getPower()) + " 点生命!", UIManager::Color::GREEN);
                    break;
                }
                }
            }
            else
            {
                ui.displayMessage("无效选择。", UIManager::Color::RED);
                playerTurn(player, enemy, itemDb);
            }
        }
        break;
    case 3:
    { // 道具
        if (player.inventory.empty())
        {
            ui.displayMessage("你的背包是空的!", UIManager::Color::YELLOW);
            playerTurn(player, enemy, itemDb); // 重新选择
            return;
        }
        ui.displayMessage("选择道具:", UIManager::Color::WHITE);
        std::vector<std::string> itemNames;
        int itemIdx = 1;
        for (const auto& pair : player.inventory)
        {
            ui.displayMessage("[" + std::to_string(itemIdx) + "] " + pair.first + " x" + std::to_string(pair.second), UIManager::Color::WHITE);
            itemNames.push_back(pair.first);
            itemIdx++;
        }
        int itemChoice = 0;
        std::cin >> itemChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (itemChoice > 0 && itemChoice <= itemNames.size())
        {
            std::string chosenItemName = itemNames[itemChoice - 1];

            if (chosenItemName == "能量药水")
            {
                if (player.useItem(chosenItemName))
                {
                    player.extraActionTurns++;
                    ui.displayMessage("你使用了[能量药水]，感觉充满了力量！效果将在你的下一回合生效。", UIManager::Color::CYAN);
                }
            }
            else
            {
                if (chosenItemName == "生命药水");
                {
                    if (player.useItem(chosenItemName))
                    {
                        int hpToRestore = 50;
                        player.heal(hpToRestore);
                        ui.displayMessage("你使用了 [" + chosenItemName + "]，恢复了 " + std::to_string(hpToRestore) + " 点生命!", UIManager::Color::GREEN);
                    }
                }
                playerTurn(player, enemy, itemDb);
                
            }
        }
        else
        {
            ui.displayMessage("无效选择。", UIManager::Color::RED);
            playerTurn(player, enemy, itemDb);
        }
        break;
    }
    case 4:
    { // 逃跑
        if (attemptEscape(player, enemy))
        {
            ui.displayMessage("你成功逃离了战斗!", UIManager::Color::GREEN);
        }
        else
        {
            ui.displayMessage("逃跑失败了!", UIManager::Color::RED);
            // 逃跑失败会消耗一次行动
        }
        break;
    }
    }
}

void CombatSystem::enemyTurn(CommonEnemy &enemy, Player &player)
{
    ui.displayMessage("--- " + enemy.getName() + " 的回合 ---", UIManager::Color::MAGENTA);
    int damage = calculateDamage(enemy, player);
    player.takeDamage(damage);
    ui.displayMessage(enemy.getName() + " 对你造成了 " + std::to_string(damage) + " 点伤害!", UIManager::Color::RED);
}

CombatResult CombatSystem::startCombat(Player &player, CommonEnemy &enemy, const std::map<int, std::unique_ptr<Item>> &itemDb)
{
    ui.displayMessage("战斗开始! " + player.getName() + " vs " + enemy.getName(), UIManager::Color::MAGENTA);
    player.extraActionTurns = 0;

    Attribute *first = &player;
    Attribute *second = &enemy;

    if (enemy.getSpeed() > player.getSpeed())
    {
        first = &enemy;
        second = &player;
        ui.displayMessage(enemy.getName() + " 速度更快，获得先手!", UIManager::Color::YELLOW);
    }
    else
    {
        ui.displayMessage(player.getName() + " 速度更快，获得先手!", UIManager::Color::GREEN);
    }

    while (player.isAlive() && enemy.isAlive())
    {
        ui.displayPlayerStatus(player);

        // 定义一个lambda函数来处理玩家的完整回合，包括额外行动
        auto execute_player_turn_phase = [&]()
        {
            if (!player.isAlive())
                return;

            int actions_this_turn = 1; // 基础行动次数
            if (player.extraActionTurns > 0)
            {
                actions_this_turn++;       // 增加一次行动
                player.extraActionTurns--; // 在回合开始时消耗效果
                ui.displayMessage("能量药水的效果触发了！本回合你可以多行动一次。", UIManager::Color::YELLOW);
            }

            // 循环执行本回合的所有行动
            for (int i = 0; i < actions_this_turn; ++i)
            {
                if (!enemy.isAlive())
                    break; // 如果敌人在上一次行动中死亡，则中断

                if (actions_this_turn > 1)
                {
                    ui.displayMessage("--- 你的行动 (" + std::to_string(i + 1) + "/" + std::to_string(actions_this_turn) + ") ---", UIManager::Color::CYAN);
                }
                playerTurn(player, enemy, itemDb); // 执行单次行动
            }
        };

        // 根据先手顺序执行回合
        if (first->getName() == player.getName())
        {
            // 玩家先手
            execute_player_turn_phase();
            if (enemy.isAlive())
            {
                enemyTurn(enemy, player);
            }
        }
        else
        {
            // 敌人先手
            enemyTurn(enemy, player);
            execute_player_turn_phase();
        }
    }

    if (player.isAlive())
    {
        ui.displayMessage(enemy.getName() + " 被击败了!", UIManager::Color::GREEN);
        player.addExp(enemy.getExpReward());
        player.addGold(enemy.getGoldReward());
        ui.displayMessage("你获得了 " + std::to_string(enemy.getExpReward()) + " 点经验和 " + std::to_string(enemy.getGoldReward()) + " 枚金币。", UIManager::Color::YELLOW);
        player.levelUp();
        return CombatResult::Victory;
    }
    else
    {
        ui.displayMessage("你被 " + enemy.getName() + " 击败了...", UIManager::Color::RED);
        ui.displayMessage("--- 你要怎么做？ ---", UIManager::Color::YELLOW);
        ui.displayMessage("[1] 重新开始本次战斗", UIManager::Color::WHITE);
        ui.displayMessage("[2] 读取存档", UIManager::Color::WHITE);
        ui.displayMessage("[3] 退出游戏", UIManager::Color::WHITE);

        while (true)
        {
            std::cout << "> ";
            std::string input;
            std::cin >> input;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (is_digits(input))
            {
                int choice = std::stoi(input);
                switch (choice)
                {
                case 1:
                    return CombatResult::Defeat_Restart;
                case 2:
                    return CombatResult::Defeat_Load;
                case 3:
                    return CombatResult::Defeat_Exit;
                }
            }
            std::cout << "无效输入, 请输入 1-3 之间的数字。" << std::endl;
        }
    }
}

// 在CombatSystem.cpp中，当需要访问itemDb中的Item时，需要使用.get()或->
// 例如：
// auto itemIt = itemDb.find(itemId);
// if (itemIt != itemDb.end() && itemIt->second) {
//     Item* item = itemIt->second.get(); // 获取裸指针
//     // 或者直接使用 itemIt->second->someMethod()
// }