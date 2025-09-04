#include "Game.h"
#include <memory>
#include <iostream>
#include <algorithm>
bool is_digits_game(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
// Game类的构造函数
Game::Game() :
    player("安特王子"),
    gameMap(),              // 初始化地图
    combat(ui),
    tasks(ui),
    shop(ui),
    saveLoad(ui),
    isRunning(true),
    currentState(GameState::Exploring)
{
    // 同步玩家和地图的位置
    player.setCurrentRoomId(gameMap.getCurrentRoomId());
    
    // 初始化物品数据库
    itemDb[1] = std::make_unique<HealthPotion>();
    itemDb[2] = std::make_unique<EnergyPotion>();

    tasks.initializeTasks();
    shop.initializeShop();
    registerCommands();
    setupCommandAliases();
}

// 游戏主循环
void Game::run() {
    ui.displayMessage("欢迎来到MUD世界, " + player.getName() + "!", UIManager::Color::CYAN);
    ui.displayMessage("输入 'help' 或 '帮助' 查看可用命令。", UIManager::Color::YELLOW);
    
    // 显示初始房间信息
    gameMap.showInitialRoom();

    while (isRunning) {
        Command cmd = parser.getCommand();
        if (cmd.command.empty()) continue;

        std::string canonicalCmd = getCanonicalCommand(cmd.command);

        if (commandHandlers.count(canonicalCmd)) {
            commandHandlers[canonicalCmd](cmd.args);
        }
        else {
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
    commandAliases["m"] = "map"; commandAliases["地图"] = "map";
    commandAliases["g"] = "go"; commandAliases["前往"] = "go";
    commandAliases["n"] = "npc"; commandAliases["对话"] = "npc";
    commandAliases["北"] = "go"; commandAliases["南"] = "go"; commandAliases["东"] = "go"; commandAliases["西"] = "go";
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
        ui.displayMessage("基础命令: help(h,帮助), status(st,状态), look(l,观察), quit(q,退出)", UIManager::Color::WHITE);
        ui.displayMessage("地图命令: map(m,地图) [all] - 查看当前区域或全局地图", UIManager::Color::CYAN);
        ui.displayMessage("移动命令: go <方向>(g,前往) - 如: go 北, go 1", UIManager::Color::CYAN);
        ui.displayMessage("交互命令: npc(n,对话) - 与当前区域NPC对话", UIManager::Color::CYAN);
        ui.displayMessage("战斗命令: fight(f,战斗) - 挑战当前区域的敌人", UIManager::Color::RED);
        ui.displayMessage("任务命令: task(t,任务) [list/accept <ID>/submit <ID>]", UIManager::Color::YELLOW);
        ui.displayMessage("商店命令: shop(sh,商店), buy(b,购买) <ID>[*数量], leave(le,离开)", UIManager::Color::GREEN);
        ui.displayMessage("存档命令: save(sa,存档), load(lo,读档)", UIManager::Color::MAGENTA);
        if (currentState == GameState::InShop) {
            ui.displayMessage("当前在商店中，可使用: buy, leave", UIManager::Color::YELLOW);
        }
    };    commandHandlers["status"] = [this](const auto& args) { ui.displayPlayerStatus(player); };

    commandHandlers["look"] = [this](const auto& args) { 
        gameMap.showCurrentRoom(); 
    };

    commandHandlers["map"] = [this](const auto& args) {
        if (args.empty()) {
            gameMap.showLocationMap();
        } else if (args[0] == "all" || args[0] == "全部") {
            gameMap.showGlobalMap();
        } else {
            ui.displayMessage("用法: map 或 map all", UIManager::Color::YELLOW);
        }
    };

    commandHandlers["go"] = [this](const auto& args) {
        if (args.empty()) {
            ui.displayMessage("用法: go <方向> (如：go 北 或 go 1)", UIManager::Color::YELLOW);
            return;
        }
        
        if (gameMap.switchRoom(args[0])) {
            // 同步玩家位置
            player.setCurrentRoomId(gameMap.getCurrentRoomId());
            ui.displayMessage("你移动到了新的区域。", UIManager::Color::GREEN);
        }
    };

    commandHandlers["npc"] = [this](const auto& args) {
        NPC* npc = gameMap.getCurrentRoomNPC();
        if (npc) {
            ui.displayMessage("与 " + npc->getName() + " 对话:", UIManager::Color::CYAN);
            npc->showDialogue();
            
            // 检查是否有任务
            std::string taskId = npc->getTaskID();
            if (!taskId.empty()) {
                ui.displayMessage("输入 'task accept " + taskId + "' 接受任务", UIManager::Color::YELLOW);
            }
        } else {
            ui.displayMessage("这里没有可以对话的NPC。", UIManager::Color::RED);
        }
    };

    commandHandlers["fight"] = [this](const auto& args) {
        if (currentState != GameState::Exploring) { 
            ui.displayMessage("你现在不能战斗。", UIManager::Color::RED); 
            return; 
        }

        // 确保战斗状态
        currentState = GameState::InCombat;

        // 检查是否有BOSS
        EvilGeneral* boss = gameMap.getCurrentRoomBoss();
        if (boss) {
            ui.displayMessage("你挑战了强敌 " + boss->getName() + "！", UIManager::Color::MAGENTA);
            
            // 备份玩家关键状态而不是整个对象
            int backup_hp = player.getHP();
            int backup_exp = player.getExp();
            int backup_gold = player.getGold();
            std::map<std::string, int> backup_inventory = player.inventory;
            
            EvilGeneral original_boss = *boss;
            EvilGeneral current_boss = original_boss;

            while (true) {
                CombatResult result = combat.startCombat(player, current_boss, itemDb);
                
                switch (result) {
                case CombatResult::Victory:
                    tasks.updateTaskProgress(&player, "击败" + boss->getName());
                    gameMap.removeDefeatedBoss();
                    ui.displayMessage("战斗胜利！继续你的冒险吧。", UIManager::Color::GREEN);
                    currentState = GameState::Exploring;  // 恢复探索状态
                    return; // 结束当前命令处理
                    
                case CombatResult::Escaped:
                    // 恢复玩家状态
                    player.setHP(backup_hp);
                    player.setExp(backup_exp);
                    player.setGold(backup_gold);
                    player.inventory = backup_inventory;
                    ui.displayMessage("你回到了战前的位置。", UIManager::Color::GRAY);
                    currentState = GameState::Exploring;  // 恢复探索状态
                    return; // 结束当前命令处理
                    
                case CombatResult::Defeat_Restart:
                    ui.displayMessage("准备重新挑战...", UIManager::Color::YELLOW);
                    // 恢复玩家状态
                    player.setHP(backup_hp);
                    player.setExp(backup_exp);
                    player.setGold(backup_gold);
                    player.inventory = backup_inventory;
                    current_boss = original_boss;
                    continue; // 继续循环，重新开始战斗
                    
                case CombatResult::Defeat_Load:
                    if (saveLoad.loadGame(player, tasks)) {
                        gameMap.setCurrentRoomId(player.getCurrentRoomId());
                    }
                    currentState = GameState::Exploring;  // 恢复探索状态
                    return;
                    
                case CombatResult::Defeat_Exit:
                    isRunning = false;
                    return;
                    
                default:
                    // 处理其他情况，包括Continue
                    continue;
                }
            }
            return; // 结束当前命令处理，避免继续检查普通敌人
        }

        // 检查是否有普通敌人
        CommonEnemy* enemy = gameMap.getRandomEnemy();
        if (enemy) {
            ui.displayMessage("一只 " + enemy->getName() + " 跳了出来!", UIManager::Color::MAGENTA);
            
            // 备份玩家关键状态而不是整个对象
            int backup_hp = player.getHP();
            int backup_exp = player.getExp();
            int backup_gold = player.getGold();
            std::map<std::string, int> backup_inventory = player.inventory;
            
            CommonEnemy original_enemy = *enemy;
            CommonEnemy current_enemy = original_enemy;

            while (true) {
                CombatResult result = combat.startCombat(player, current_enemy, itemDb);

                switch (result) {
                case CombatResult::Victory:
                    tasks.updateTaskProgress(&player, "击败" + enemy->getName());
                    gameMap.removeDefeatedEnemy(enemy);
                    
                    ui.displayMessage("战斗胜利！", UIManager::Color::GREEN);
                    currentState = GameState::Exploring;  // 恢复探索状态
                    break; // 改为break而不是return

                case CombatResult::Escaped:
                    // 恢复玩家状态
                    player.setHP(backup_hp);
                    player.setExp(backup_exp);
                    player.setGold(backup_gold);
                    player.inventory = backup_inventory;
                    ui.displayMessage("你回到了战前的位置。", UIManager::Color::GRAY);
                    currentState = GameState::Exploring;  // 恢复探索状态
                    break; // 改为break而不是return

                case CombatResult::Defeat_Restart:
                    ui.displayMessage("准备重新挑战...", UIManager::Color::YELLOW);
                    // 恢复玩家状态
                    player.setHP(backup_hp);
                    player.setExp(backup_exp);
                    player.setGold(backup_gold);
                    player.inventory = backup_inventory;
                    current_enemy = original_enemy;
                    break;

                case CombatResult::Defeat_Load:
                    if (saveLoad.loadGame(player, tasks)) {
                        gameMap.setCurrentRoomId(player.getCurrentRoomId());
                    }
                    currentState = GameState::Exploring;  // 恢复探索状态
                    return;

                case CombatResult::Defeat_Exit:
                    isRunning = false;
                    return;
                }
                
                // 如果是胜利或逃跑，跳出循环
                if (result == CombatResult::Victory || result == CombatResult::Escaped) {
                    break;
                }
            }
        } else {
            ui.displayMessage("这个区域暂时没有敌人。", UIManager::Color::GRAY);
            currentState = GameState::Exploring;  // 确保状态正确
        }
    };

    // 任务系统命令
    commandHandlers["task"] = [this](const auto& args) {
        if (args.empty()) {
            tasks.showPlayerTasks(player);
            return;
        }
        
        if (args[0] == "accept" && args.size() > 1) {
            tasks.acceptTask(&player, args[1]);
        } else if (args[0] == "submit" && args.size() > 1) {
            tasks.submitTask(&player, args[1]);
        } else if (args[0] == "list") {
            tasks.showTaskList(&player);
        } else {
            ui.displayMessage("任务命令: task (查看已接任务), task list (可接任务), task accept <ID> (接任务), task submit <ID> (提交任务)", UIManager::Color::YELLOW);
        }
    };

    commandHandlers["shop"] = [this](const auto& args) {
        if (currentState == GameState::Exploring) {
            currentState = GameState::InShop;
            shop.displayShopItems();
        }
        else {
            ui.displayMessage("你已经在商店中。", UIManager::Color::YELLOW);
        }
    };

    commandHandlers["buy"] = [this](const auto& args) {
        if (currentState != GameState::InShop) {
            ui.displayMessage("你需要先进入商店。", UIManager::Color::RED);
            return;
        }
        if (args.empty()) {
            ui.displayMessage("用法: buy <物品ID> 或 buy <物品ID>*<数量>", UIManager::Color::YELLOW);
            return;
        }

        std::string input = args[0];
        size_t starPos = input.find('*');
        int id = 0;
        int quantity = 1;

        try {
            if (starPos != std::string::npos) {
                id = std::stoi(input.substr(0, starPos));
                quantity = std::stoi(input.substr(starPos + 1));
            } else {
                id = std::stoi(input);
            }
        }
        catch (const std::exception&) {
            ui.displayMessage("无效的输入格式。", UIManager::Color::RED);
            return;
        }

        if (quantity <= 0) {
            ui.displayMessage("数量必须大于0。", UIManager::Color::RED);
            return;
        }

        const Item* itemToBuy = shop.getItemById(id);
        if (itemToBuy) {
            shop.buyItem(player, *itemToBuy, quantity);
        }
        else {
            ui.displayMessage("商店中没有ID为 " + std::to_string(id) + " 的物品。", UIManager::Color::RED);
        }
    };

    commandHandlers["leave"] = [this](const auto& args) {
        if (currentState == GameState::InShop) {
            currentState = GameState::Exploring;
            ui.displayMessage("你离开了商店。", UIManager::Color::GREEN);
        }
        else {
            ui.displayMessage("你不在商店中。", UIManager::Color::YELLOW);
        }
    };

    commandHandlers["save"] = [this](const auto& args) {
        saveLoad.saveGame(player, tasks);
    };

    commandHandlers["load"] = [this](const auto& args) {
        if (saveLoad.loadGame(player, tasks)) {
            // 同步地图位置
            gameMap.setCurrentRoomId(player.getCurrentRoomId());
            ui.displayMessage("游戏加载成功！当前位置已更新。", UIManager::Color::GREEN);
            ui.displayPlayerStatus(player);
        } else {
            ui.displayMessage("加载游戏失败。", UIManager::Color::RED);
        }
    };

    commandHandlers["quit"] = [this](const auto& args) {
        isRunning = false;
        ui.displayMessage("感谢游玩，再见!", UIManager::Color::CYAN);
    };
}