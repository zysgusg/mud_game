#include "Game.h"
#include <iostream>
#include <algorithm>
bool is_digits_game(const std::string &str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
// Game类的构造函数
Game::Game() : 
    player("安特王子"), 
    combat(ui), 
    tasks(ui), 
    shop(ui), 
    saveLoad(ui),
    isRunning(true),
    currentState(GameState::Exploring)
{
    // 初始化物品数据库
    itemDb[1] = {1, "生命药水", "恢复50点生命", 20, "POTION", 50};
    itemDb[2] = {2, "能量药水", "下一回合行动两次", 50, "POTION", 0};
    itemDb[3] = {3, "教训", "1金币买个教训。", 1, "MISC", 0};

    tasks.initializeTasks();
    shop.initializeShop();
    registerCommands();
    setupCommandAliases();
}

// 游戏主循环
void Game::run() {
    ui.displayMessage("欢迎来到MUD世界, " + player.name + "!", UIManager::Color::CYAN);
    ui.displayScene("你站在一片被恶兽侵扰的树林前，远处隐约可见一间破落的铁匠铺。");
    ui.displayMessage("输入 'help' 或 '帮助' 查看可用命令。", UIManager::Color::YELLOW);

    while (isRunning) {
        Command cmd = parser.getCommand();
        if (cmd.command.empty()) continue;
        
        std::string canonicalCmd = getCanonicalCommand(cmd.command);

        if (commandHandlers.count(canonicalCmd)) {
            commandHandlers[canonicalCmd](cmd.args);
        } else {
            ui.displayMessage("未知命令: " + cmd.command, UIManager::Color::RED);
        }
    }
}

// 设置命令别名
void Game::setupCommandAliases() {
    commandAliases["h"] = "help"; commandAliases["帮助"] = "help";
    commandAliases["st"] = "status"; commandAliases["状态"] = "status";
    commandAliases["l"] = "look"; commandAliases["观察"] = "look";
    commandAliases["f"] = "fight"; commandAliases["战斗"] = "fight";
    commandAliases["t"] = "task"; commandAliases["任务"] = "task";
    commandAliases["sh"] = "shop"; commandAliases["商店"] = "shop";
    commandAliases["b"] = "buy"; commandAliases["购买"] = "buy";
    commandAliases["sa"] = "save"; commandAliases["存档"] = "save";
    commandAliases["lo"] = "load"; commandAliases["读档"] = "load";
    commandAliases["q"] = "quit"; commandAliases["退出"] = "quit";
    commandAliases["le"] = "leave"; commandAliases["离开"] = "leave";
}

// 将别名或大小写命令转换为标准命令
std::string Game::getCanonicalCommand(std::string cmd) {
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    if (commandAliases.count(cmd)) {
        return commandAliases[cmd];
    }
    return cmd;
}

// 注册所有命令及其处理逻辑
void Game::registerCommands() {
    commandHandlers["help"] = [this](const auto& args) {
        ui.displayMessage("可用命令: help(h,帮助), status(st,状态), look(l,观察), fight(f,战斗), shop(sh,商店), save(sa,存档), load(lo,读档), quit(q,退出)", UIManager::Color::WHITE);
        if (currentState == GameState::InShop) {
            ui.displayMessage("商店命令: buy(b,购买), leave(le,离开)", UIManager::Color::YELLOW);
        }
    };

    commandHandlers["status"] = [this](const auto& args) { ui.displayPlayerStatus(player); };

    commandHandlers["look"] = [this](const auto& args) { ui.displayScene("你站在一片被恶兽侵扰的树林前，远处隐约可见一间破落的铁匠铺。"); };

    commandHandlers["fight"] = [this](const auto& args) {
         if (currentState != GameState::Exploring) { ui.displayMessage("你现在不能战斗。", UIManager::Color::RED); return; }
         ui.displayMessage("一只'蚀骨恶狼'跳了出来!", UIManager::Color::MAGENTA);
         // 1. 在战斗开始前，备份玩家和敌人的初始状态
         Player player_backup = player;
         Enemy original_enemy("蚀骨恶狼", 1, 30, 10, 3, 12, 0.1, 50, 20);
         Enemy current_enemy = original_enemy;

         // 2. 使用一个循环来处理“重新挑战”
         while (true) {
             CombatResult result = combat.startCombat(player, current_enemy, itemDb);

             switch (result) {
                 case CombatResult::Victory:
                    // 战胜后，任务进度更新等逻辑在这里处理
                    tasks.updateTaskProgress(player, "击败蚀骨恶狼");
                    return; // 战斗彻底结束，退出函数

                 case CombatResult::Escaped:
                    player = player_backup; // 逃跑成功，状态恢复到战前
                    ui.displayMessage("你回到了战前的位置。", UIManager::Color::GRAY);
                    return; // 战斗彻底结束，退出函数

                 case CombatResult::Defeat_Restart:
                    ui.displayMessage("准备重新挑战...", UIManager::Color::YELLOW);
                    player = player_backup;       // 恢复玩家状态
                    current_enemy = original_enemy; // 恢复敌人状态
                    // 循环将自动开始下一次战斗
                    break; 

                 case CombatResult::Defeat_Load:
                    if (saveLoad.loadGame(player, tasks)) {
                        ui.displayMessage("数据已加载。", UIManager::Color::GREEN);
                        ui.displayPlayerStatus(player);
                    }
                    return; // 无论加载成功与否，战斗都结束了

                 case CombatResult::Defeat_Exit:
                    isRunning = false; // 设置游戏主循环退出标志
                    return; // 战斗彻底结束，退出函数
             }
         }
    };

    commandHandlers["task"] = [this](const auto& args) { tasks.showPlayerTasks(player); };

    commandHandlers["shop"] = [this](const auto& args) {
        if (currentState == GameState::Exploring) {
            ui.displayMessage("你进入了商店。", UIManager::Color::GREEN);
            shop.displayShopItems();
            currentState = GameState::InShop;
        } else {
            ui.displayMessage("你已经在商店里了。", UIManager::Color::YELLOW);
            shop.displayShopItems();
        }
    };

    commandHandlers["buy"] = [this](const auto& args) {
        if (currentState != GameState::InShop) {
            ui.displayMessage("你必须先进入商店才能购买物品。请输入 'shop' 进入商店。", UIManager::Color::RED);
            return;
        }
        if (args.empty()) {
            ui.displayMessage("用法: buy <序号> 或 buy <序号>*<数量>", UIManager::Color::YELLOW);
            return;
        }
        
        std::string input = args[0];
        size_t starPos = input.find('*');
        int id = 0;
        int quantity = 1;

        try {
            std::string id_str;
            std::string quantity_str = "1";

            if (starPos == std::string::npos) {
                id_str = input;
            } else {
                id_str = input.substr(0, starPos);
                quantity_str = input.substr(starPos + 1);
            }
            
            // 验证ID和数量是否都是纯数字
            if (!is_digits_game(id_str) || !is_digits_game(quantity_str)) {
                 throw std::invalid_argument("Invalid number format");
            }

            id = std::stoi(id_str);
            quantity = std::stoi(quantity_str);

        } catch (const std::exception&) {
            ui.displayMessage("输入格式错误。请输入如 'buy 1' 或 'buy 1*5'。", UIManager::Color::RED);
            return;
        }

        if (quantity <= 0) {
            ui.displayMessage("购买数量必须大于0。", UIManager::Color::RED);
            return;
        }

        auto itemOpt = shop.getItemById(id);
        if (itemOpt) {
            shop.buyItem(player, *itemOpt, quantity);
        } else {
            ui.displayMessage("商店里没有序号为 " + std::to_string(id) + " 的商品。", UIManager::Color::RED);
        }
    };

    commandHandlers["leave"] = [this](const auto& args) {
        if (currentState == GameState::InShop) {
            currentState = GameState::Exploring;
            ui.displayMessage("你离开了商店。", UIManager::Color::GREEN);
            ui.displayScene("你站在一片被恶兽侵扰的树林前，远处隐约可见一间破落的铁匠铺。");
        } else {
            ui.displayMessage("你不在商店里。", UIManager::Color::YELLOW);
        }
    };
    
    commandHandlers["save"] = [this](const auto& args) { 
        // --- 修正：传递 tasks 对象 ---
        saveLoad.saveGame(player, tasks); 
    };

    commandHandlers["load"] = [this](const auto& args) { 
        // --- 修正：传递 tasks 对象 ---
        if (saveLoad.loadGame(player, tasks)) {
            ui.displayMessage("数据已加载。", UIManager::Color::GREEN);
            ui.displayPlayerStatus(player);
        }
    };

    commandHandlers["quit"] = [this](const auto& args) { 
        isRunning = false; 
        ui.displayMessage("感谢游玩，再见!", UIManager::Color::CYAN);
    };
}