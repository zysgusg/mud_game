#include "Map.h"
#include "BossWanEshuji.h"
#include <iostream>
#include <random>

// 构造函数
Map::Map() {
    initRooms();
    initNPCs();
    initBosses();
    initEnemies();
    currentRoomId = 1; // 初始位置：迷雾森林
}

// 初始化所有房间
void Map::initRooms() {
    // 初始区域
    Room forest(1, "迷雾森林", "古老的森林，参天大树遮天蔽日，藤蔓掩盖着路径",
        "东北部似乎有火光，或许是可以落脚的地方");
    forest.addExit("东北", 2, "铁匠铺");
    rooms.insert({ 1, forest });

    Room blacksmith(2, "铁砧铁匠铺", "炉火熊熊的铁匠铺，墙上挂着王室徽记",
        "东边有通往裂隙废墟的小径，北边是黑曜权枢殿");
    blacksmith.addExit("西南", 1, "迷雾森林");
    blacksmith.addExit("东", 3, "裂隙废墟");
    blacksmith.addExit("北", 4, "黑曜权枢殿");
    blacksmith.addNPC("杨思睿（白发铁匠）");
    blacksmith.addItem("破枷之冠蓝图");
    rooms.insert({ 2, blacksmith });

    Room rift(3, "裂隙废墟", "泛着幽蓝微光的古代废墟，地面散落着黑曜晶尘",
        "收集3份黑曜晶尘可修复装备");
    rift.addExit("西", 2, "铁砧铁匠铺");
    rift.addExit("东北", 4, "黑曜权枢殿");
    rift.addItem("黑曜晶尘（1/3）");
    rooms.insert({ 3, rift });

    Room obsidian(4, "黑曜权枢殿", "黑曜石建造的宏伟殿堂，中央有巨大王座",
        "击败厄休拉后可向东进入背契之坛");
    obsidian.addExit("南", 2, "铁砧铁匠铺");
    obsidian.addExit("西南", 3, "裂隙废墟");
    obsidian.addExit("东", 5, "背契之坛");
    rooms.insert({ 4, obsidian });

    // 背契区域
    Room betrayal(5, "背契之坛", "刻有红色咒文的圆形石坛，中央矗立着断柱",
        "晋津津守在这里，他或许知道卡莱恩的弱点");
    betrayal.addExit("西", 4, "黑曜权枢殿");
    betrayal.addExit("东北", 6, "凋誓之崖");
    betrayal.addNPC("晋津津（祭祀）");
    betrayal.addItem("铁誓胸甲");
    rooms.insert({ 5, betrayal });

    Room cliff(6, "凋誓之崖", "临海悬崖，海风呼啸，崖边有破碎的船骸",
        "东边断柱后隐藏着通往布道台的路径");
    cliff.addExit("西南", 5, "背契之坛");
    cliff.addExit("东", 7, "残垣断柱");
    rooms.insert({ 6, cliff });

    Room pillar(7, "残垣断柱", "刻有古老经文的巨大断柱，部分掩埋在沙土中",
        "张焜杰守在这里，他会指引你找到明识之戒");
    pillar.addExit("西", 6, "凋誓之崖");
    pillar.addExit("东南", 8, "残垣布道台");
    pillar.addNPC("张焜杰（守誓者）");
    pillar.addItem("明识之戒");
    rooms.insert({ 7, pillar });

    Room platform(8, "残垣布道台", "笼罩在粉色迷雾中的布道台，有虚假告示牌",
        "玛尔索的幻象在这里作祟，用明识之戒可破除");
    platform.addExit("西北", 7, "残垣断柱");
    platform.addExit("南", 9, "怜悯之城");
    rooms.insert({ 8, platform });

    // 怜悯区域
    Room mercy(9, "怜悯之城", "曾经繁华的城市，如今改为残酷的斗技场",
        "钟志炜城主知道怜悯之链的藏匿处");
    mercy.addExit("北", 8, "残垣布道台");
    mercy.addExit("东南", 10, "山脚下");
    mercy.addExit("东", 11, "棘刑斗技场");
    mercy.addNPC("钟志炜（城主）");
    rooms.insert({ 9, mercy });

    Room foot(10, "城外山脚下", "布满岩石的山坡，有隐蔽洞穴",
        "洞穴深处藏着怜悯之链");
    foot.addExit("西北", 9, "怜悯之城");
    foot.addItem("怜悯之链");
    rooms.insert({ 10, foot });

    Room arena(11, "棘刑斗技场", "环形斗技场，四周是带刺的铁丝网",
        "克鲁尔萨在这里进行残酷的角斗表演");
    arena.addExit("西", 9, "怜悯之城");
    arena.addExit("北", 12, "漠心城");
    rooms.insert({ 11, arena });

    // 漠心区域
    Room apathy(12, "漠心城", "灰白色调的城市，行人面无表情，目光空洞",
        "北边的静默尖塔是这座城市的地标");
    apathy.addExit("南", 11, "棘刑斗技场");
    apathy.addExit("北", 13, "静默尖塔");
    rooms.insert({ 12, apathy });

    Room spire(13, "静默尖塔", "无窗石塔，刻有'禁止喧哗'的符文",
        "塔内有上下两条路径，通往迷宫和塔顶");
    spire.addExit("南", 12, "漠心城");
    spire.addExit("下", 14, "塔底迷宫");
    spire.addExit("上", 15, "塔顶");
    rooms.insert({ 13, spire });

    Room maze(14, "塔底迷宫", "多岔路的石制迷宫，墙壁会轻微移动",
        "王浠珃被困在这里，她持有晨曦披风");
    maze.addExit("上", 13, "静默尖塔");
    maze.addNPC("王浠珃（三军将领）");
    maze.addItem("晨曦披风");
    rooms.insert({ 14, maze });

    Room top(15, "塔顶", "开阔平台，中央有黑色晶石，天空呈现灰白色",
        "灭欲将军在这里吸收着人们的情感");
    top.addExit("下", 13, "静默尖塔");
    top.addExit("东", 16, "虚无之城");
    rooms.insert({ 15, top });

    // 虚无区域
    Room voidCity(16, "虚无之城", "半坍塌的城市，街道覆盖着厚厚的灰尘",
        "东边的旧图书馆或许还保留着一些知识");
    voidCity.addExit("西", 15, "塔顶");
    voidCity.addExit("东", 17, "旧图书馆废墟");
    rooms.insert({ 16, voidCity });

    Room library(17, "旧图书馆废墟", "烧毁的图书馆，少数书页仍可辨认",
        "周洋迅在这里研究古代文献，他知道创世战靴的位置");
    library.addExit("西", 16, "虚无之城");
    library.addExit("北", 18, "亡念堡垒");
    library.addNPC("周洋迅（拾荒者）");
    library.addItem("创世战靴");
    rooms.insert({ 17, library });

    Room fortress(18, "亡念堡垒", "黑色石块砌成的堡垒，弥漫死亡气息",
        "尼赫尔将军的黑暗力量笼罩着这里");
    fortress.addExit("南", 17, "旧图书馆废墟");
    fortress.addExit("北", 19, "混沌之心");
    rooms.insert({ 18, fortress });

    // 最终区域
    Room chaos(19, "混沌之心", "虚空之地，漂浮着时空碎片，中央是能量核心",
        "万恶枢机就在核心处，准备最终决战吧");
    chaos.addExit("南", 18, "亡念堡垒");
    rooms.insert({ 19, chaos });
}

// 初始化NPC
void Map::initNPCs() {
    // 铁匠铺的NPC - 杨思睿
    roomNPCs[2] = std::make_unique<NPC>(
        "杨思睿", NPCType::BLACKSMITH,
        std::vector<std::string>{"欢迎来到铁砧铁匠铺！", "我可以为你修复装备。", "需要什么服务吗？"},
        "1"  // 发布任务ID为1的任务
    );

    // 背契之坛的NPC - 晋津津
    roomNPCs[5] = std::make_unique<NPC>(
        "晋津津", NPCType::PRIEST,
        std::vector<std::string>{"神明保佑你，勇者。", "背契之坛见证着古老的誓言。", "愿圣光指引你前行。"},
        "2"
    );

    // 残垣断柱的NPC - 张焜杰
    roomNPCs[7] = std::make_unique<NPC>(
        "张焜杰", NPCType::GUARDIAN,
        std::vector<std::string>{"我是这里的守护者。", "明识之戒就在这里。", "愿你能看清真相。"},
        ""
    );

    // 怜悯之城的NPC - 钟志炜
    roomNPCs[9] = std::make_unique<NPC>(
        "钟志炜", NPCType::MAYOR,
        std::vector<std::string>{"欢迎来到怜悯之城。", "这里曾经是繁华之地。", "怜悯之链藏在山脚下。"},
        ""
    );

    // 塔底迷宫的NPC - 王浠珃
    roomNPCs[14] = std::make_unique<NPC>(
        "王浠珃", NPCType::GENERAL,
        std::vector<std::string>{"我被困在这迷宫中。", "晨曦披风是我的珍藏。", "帮助我脱困吧。"},
        ""
    );

    // 图书馆的NPC - 周洋迅
    roomNPCs[17] = std::make_unique<NPC>(
        "周洋迅", NPCType::SCAVENGER,
        std::vector<std::string>{"我在这里研究古代文献。", "创世战靴的线索就在这些书中。", "知识就是力量。"},
        ""
    );
}

// 初始化BOSS
void Map::initBosses() {
    // 黑曜权枢殿 - 厄休拉
    roomBosses[4] = std::make_unique<EvilGeneral>("厄休拉", EvilType::POWER_HUNGRY, "黑曜权枢殿", 10);
    
    // 凋誓之崖 - 卡莱恩  
    roomBosses[6] = std::make_unique<EvilGeneral>("卡莱恩", EvilType::BETRAYAL, "凋誓之崖", 12);
    
    // 残垣布道台 - 玛尔索
    roomBosses[8] = std::make_unique<EvilGeneral>("玛尔索", EvilType::LIE, "残垣布道台", 14);
    
    // 棘刑斗技场 - 克鲁尔萨
    roomBosses[11] = std::make_unique<EvilGeneral>("克鲁尔萨", EvilType::CRUELTY, "棘刑斗技场", 16);
    
    // 塔顶 - 灭欲
    roomBosses[15] = std::make_unique<EvilGeneral>("灭欲", EvilType::DESIRELESS, "塔顶", 18);
    
    // 亡念堡垒 - 尼赫尔
    roomBosses[18] = std::make_unique<EvilGeneral>("尼赫尔", EvilType::DESTRUCTION, "亡念堡垒", 20);
    
    // 混沌之心 - 万恶枢机 (最终BOSS)
    roomBosses[19] = std::make_unique<BossWanEshuji>();
}

// 初始化普通敌人
void Map::initEnemies() {
    // 迷雾森林
    roomEnemies[1].push_back(std::make_unique<CommonEnemy>(EnemyType::GOBLIN, 1));
    roomEnemies[1].push_back(std::make_unique<CommonEnemy>(EnemyType::SLIME, 1));
    
    // 裂隙废墟 - 蚀骨恶狼守卫
    roomEnemies[3].push_back(std::make_unique<CommonEnemy>(EnemyType::CORRUPT_WOLF, 2));
    roomEnemies[3].push_back(std::make_unique<CommonEnemy>(EnemyType::CORRUPT_WOLF, 2));
    
    // 漠心城
    roomEnemies[12].push_back(std::make_unique<CommonEnemy>(EnemyType::ZOMBIE, 8));
    roomEnemies[12].push_back(std::make_unique<CommonEnemy>(EnemyType::SKELETON, 8));
    
    // 虚无之城
    roomEnemies[16].push_back(std::make_unique<CommonEnemy>(EnemyType::MINOTAUR, 10));
    roomEnemies[16].push_back(std::make_unique<CommonEnemy>(EnemyType::ZOMBIE, 10));
}

// 绘制全局地图
void Map::drawGlobalMap() const {
    std::cout << "\033[32m==== 恶念之界地图 ====\033[0m" << std::endl;
    std::cout << std::endl;
    std::cout << "     混沌之心[19]" << std::endl;
    std::cout << "         |" << std::endl;
    std::cout << "   亡念堡垒[18]" << std::endl;
    std::cout << "         |" << std::endl;
    std::cout << "   旧图书馆[17]──虚无之城[16]──塔顶[15]" << std::endl;
    std::cout << "                         |" << std::endl;
    std::cout << "                    静默尖塔[13]" << std::endl;
    std::cout << "                     |      |" << std::endl;
    std::cout << "                 迷宫[14]  漠心城[12]" << std::endl;
    std::cout << "                           |" << std::endl;
    std::cout << "                   棘刑斗技场[11]──怜悯之城[9]" << std::endl;
    std::cout << "                              |  \\     " << std::endl;
    std::cout << "                          山脚[10] 布道台[8]" << std::endl;
    std::cout << "                                     |" << std::endl;
    std::cout << "                              断柱[7]──凋誓崖[6]" << std::endl;
    std::cout << "                                     |" << std::endl;
    std::cout << "                          黑曜权枢殿[4]──背契坛[5]" << std::endl;
    std::cout << "                            |     |" << std::endl;
    std::cout << "                      铁匠铺[2]──裂隙废墟[3]" << std::endl;
    std::cout << "                         |" << std::endl;
    std::cout << "                      迷雾森林[1]" << std::endl;
    std::cout << std::endl;
}

// 绘制定位地图
void Map::drawLocationMap() const {
    std::cout << "\033[36m当前区域地图:\033[0m" << std::endl;
    auto it = rooms.find(currentRoomId);
    if (it != rooms.end()) {
        const Room& currentRoom = it->second;
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
        std::cout << "当前位置: " << currentRoom.getRoomName() << " [" << currentRoomId << "]" << std::endl;
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
        
        // 显示相邻房间
        const auto& exits = currentRoom.getExits();
        if (!exits.empty()) {
            std::cout << "可前往区域:" << std::endl;
            for (const auto& exit : exits) {
                std::cout << "  " << exit.first << "(" << Room::dirToNumber(exit.first) 
                         << ") -> " << exit.second.second << " [" << exit.second.first << "]" << std::endl;
            }
        }
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    }
}

// 显示全局地图
void Map::showGlobalMap() {
    drawGlobalMap();
}

// 显示定位地图
void Map::showLocationMap() {
    drawLocationMap();
}

// 移动房间（支持方向文字或数字）
bool Map::switchRoom(const std::string& input) {
    auto it = rooms.find(currentRoomId);
    if (it == rooms.end()) return false;
    
    const Room& currentRoom = it->second;
    const auto& exits = currentRoom.getExits();
    
    // 检查当前房间是否有未击败的BOSS
    if (roomBosses.find(currentRoomId) != roomBosses.end()) {
        std::cout << "你必须先击败这里的BOSS才能离开！" << std::endl;
        return false;
    }
    
    // 检查输入是数字还是方向
    std::string direction = input;
    if (input.length() == 1 && std::isdigit(input[0])) {
        direction = Room::numberToDir(input);
    }
    
    // 查找对应出口
    auto exitIt = exits.find(direction);
    if (exitIt != exits.end()) {
        int targetRoomId = exitIt->second.first;
        if (rooms.find(targetRoomId) != rooms.end()) {
            currentRoomId = targetRoomId;
            showCurrentRoom();
            return true;
        }
    }
    
    std::cout << "无法前往 \"" << input << "\" 方向！" << std::endl;
    return false;
}

// 显示当前房间信息
void Map::showCurrentRoom() const {
    auto it = rooms.find(currentRoomId);
    if (it != rooms.end()) {
        it->second.showRoomInfo();
        
        // 显示NPC
        if (roomNPCs.find(currentRoomId) != roomNPCs.end()) {
            std::cout << "这里有NPC: " << roomNPCs.at(currentRoomId)->getName() << std::endl;
        }
        
        // 显示BOSS
        if (roomBosses.find(currentRoomId) != roomBosses.end()) {
            std::cout << "警告！这里有强敌: " << roomBosses.at(currentRoomId)->getName() << std::endl;
        }
        
        // 显示普通敌人
        if (roomEnemies.find(currentRoomId) != roomEnemies.end() && 
            !roomEnemies.at(currentRoomId).empty()) {
            std::cout << "附近有" << roomEnemies.at(currentRoomId).size() << "只敌人在游荡..." << std::endl;
        }
    }
}

// 显示初始房间信息
void Map::showInitialRoom() const {
    showCurrentRoom();
}

// 快速跳转房间
void Map::jumpToRoom(int roomId) {
    if (rooms.find(roomId) != rooms.end()) {
        currentRoomId = roomId;
        showCurrentRoom();
    } else {
        std::cout << "房间 " << roomId << " 不存在！" << std::endl;
    }
}

// 获取当前房间ID
int Map::getCurrentRoomId() const {
    return currentRoomId;
}

// 设置当前房间ID
void Map::setCurrentRoomId(int roomId) {
    if (rooms.find(roomId) != rooms.end()) {
        currentRoomId = roomId;
    }
}

// 获取当前房间的NPC
NPC* Map::getCurrentRoomNPC() const {
    auto it = roomNPCs.find(currentRoomId);
    return (it != roomNPCs.end()) ? it->second.get() : nullptr;
}

// 获取当前房间的BOSS
EvilGeneral* Map::getCurrentRoomBoss() const {
    auto it = roomBosses.find(currentRoomId);
    if (it != roomBosses.end()) {
        // 检查是否是万恶枢机（BossWanEshuji）
        if (currentRoomId == 19) {
            return nullptr; // 万恶枢机用专门的函数获取
        }
        return it->second.get();
    }
    return nullptr;
}

// 获取当前房间的万恶枢机
BossWanEshuji* Map::getCurrentRoomFinalBoss() const {
    if (currentRoomId == 19) {
        auto it = roomBosses.find(currentRoomId);
        if (it != roomBosses.end()) {
            return dynamic_cast<BossWanEshuji*>(it->second.get());
        }
    }
    return nullptr;
}

// 获取当前房间的随机敌人
CommonEnemy* Map::getRandomEnemy() const {
    auto it = roomEnemies.find(currentRoomId);
    if (it != roomEnemies.end() && !it->second.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, it->second.size() - 1);
        return it->second[dis(gen)].get();
    }
    return nullptr;
}

// 移除已击败的敌人
void Map::removeDefeatedEnemy(CommonEnemy* enemy) {
    auto it = roomEnemies.find(currentRoomId);
    if (it != roomEnemies.end()) {
        auto& enemies = it->second;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ++enemyIt) {
            if (enemyIt->get() == enemy) {
                enemies.erase(enemyIt);
                break;
            }
        }
    }
}

// 移除已击败的BOSS
void Map::removeDefeatedBoss() {
    roomBosses.erase(currentRoomId);
}