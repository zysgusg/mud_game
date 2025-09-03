#include "Map.h"
#include <iostream>

// 构造函数
Map::Map() {
    initRooms();
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
    obsidian.addNPC("厄休拉（嗜权将军）");
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
    cliff.addNPC("卡莱恩（背信将军）");
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
    platform.addNPC("玛尔索（诳言将军）");
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
    arena.addNPC("克鲁尔萨（残虐将军）");
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
    top.addNPC("灭欲（灭欲将军）");
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
    fortress.addNPC("尼赫尔（亡念将军）");
    rooms.insert({ 18, fortress });

    // 最终区域
    Room chaos(19, "混沌之心", "虚空之地，漂浮着时空碎片，中央是能量核心",
        "万恶枢机就在核心处，准备最终决战吧");
    chaos.addExit("南", 18, "亡念堡垒");
    chaos.addNPC("万恶枢机（最终BOSS）");
    rooms.insert({ 19, chaos });
}

// 分散式全局地图
void Map::drawGlobalMap() const {
    std::cout << "\n\033[35m======================================= 安特大陆全局地图 =======================================\033[0m" << std::endl;

    // 顶层：混沌之隙(19)
    std::cout << "                                         ┌─────┐ " << std::endl;
    std::cout << "                                         │     │ " << std::endl;
    std::cout << "                                         └─────┘ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 19 ? "\033[31m●\033[0m " : "○ ") << "混沌之隙(19) " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;

    // 上层：遗忘堡垒(18) - 星图图书馆(17)
    std::cout << "                 ┌─────────────┐                        ┌─────────────┐ " << std::endl;
    std::cout << "                /               \\                      /               \\ " << std::endl;
    std::cout << "               /                 \\                    /                 \\ " << std::endl;
    std::cout << "              /                   \\                  /                   \\ " << std::endl;
    std::cout << "              \\                   /                  \\                   / " << std::endl;
    std::cout << "               \\                 /                    \\                 / " << std::endl;
    std::cout << "                \\               /                      \\               / " << std::endl;
    std::cout << "                 └─────────────┘                        └─────────────┘ " << std::endl;
    std::cout << "               " << (currentRoomId == 18 ? "\033[31m●\033[0m " : "○ ") << "遗忘堡垒(18)                        " << (currentRoomId == 17 ? "\033[31m●\033[0m " : "○ ") << "星图图书馆(17) " << std::endl;
    std::cout << "                         │                                 │ " << std::endl;
    std::cout << "                         └─────────────────────────────────┘ " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;
    std::cout << "                                         ┌─────────────┐ " << std::endl;
    std::cout << "                                        /               \\ " << std::endl;
    std::cout << "                                       /                 \\ " << std::endl;
    std::cout << "                                      /                   \\ " << std::endl;
    std::cout << "                                      \\                   / " << std::endl;
    std::cout << "                                       \\                 / " << std::endl;
    std::cout << "                                        \\               / " << std::endl;
    std::cout << "                                         └─────────────┘ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 16 ? "\033[31m●\033[0m " : "○ ") << "虚空之城(16) " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;

    // 中层右上：顶端(15) - 漠然尖塔(13) - 迷宫(14) - 冷漠殿(12)
    std::cout << "                                         O " << std::endl;
    std::cout << "                                        /|\\ " << std::endl;
    std::cout << "                                       / | \\ " << std::endl;
    std::cout << "                                      /  |  \\ " << std::endl;
    std::cout << "                                     ┌────┴────┐ " << std::endl;
    std::cout << "                                     │         │ " << std::endl;
    std::cout << "                                     └────┬────┘ " << std::endl;
    std::cout << "                                       " << (currentRoomId == 15 ? "\033[31m●\033[0m " : "○ ") << "顶端(15) " << std::endl;
    std::cout << "                                         │ " << std::endl;
    std::cout << "                                         ▼ " << std::endl;
    std::cout << "                 O                           O " << std::endl;
    std::cout << "                /|\\                         /|\\ " << std::endl;
    std::cout << "               / | \\                       / | \\ " << std::endl;
    std::cout << "              /  |  \\                     /  |  \\ " << std::endl;
    std::cout << "             ┌────┴────┐                 ┌────┴────┐ " << std::endl;
    std::cout << "             │         │                 │         │ " << std::endl;
    std::cout << "             └────┬────┘                 └────┬────┘ " << std::endl;
    std::cout << "             " << (currentRoomId == 13 ? "\033[31m●\033[0m " : "○ ") << "漠然尖塔(13)                 " << (currentRoomId == 14 ? "\033[31m●\033[0m " : "○ ") << "迷宫(14) " << std::endl;
    std::cout << "                 │                             │ " << std::endl;
    std::cout << "                 └─────────────────────────────┘ " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;
    std::cout << "                                         ┌─────────────┐ " << std::endl;
    std::cout << "                                        /               \\ " << std::endl;
    std::cout << "                                       /                 \\ " << std::endl;
    std::cout << "                                      /                   \\ " << std::endl;
    std::cout << "                                      \\                   / " << std::endl;
    std::cout << "                                       \\                 / " << std::endl;
    std::cout << "                                        \\               / " << std::endl;
    std::cout << "                                         └─────────────┘ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 12 ? "\033[31m●\033[0m " : "○ ") << "冷漠殿(12) " << std::endl;

    // 中层左下：竞技场(11) - 怜悯之厅(9) - 山脚(10)
    std::cout << "\n\n";
    std::cout << "                                         ┌─────┐ " << std::endl;
    std::cout << "                                        /       \\ " << std::endl;
    std::cout << "                                       /         \\ " << std::endl;
    std::cout << "                                      /           \\ " << std::endl;
    std::cout << "                                     /             \\ " << std::endl;
    std::cout << "                                    /               \\ " << std::endl;
    std::cout << "                                   /                 \\ " << std::endl;
    std::cout << "                                  └───────────────────┘ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 11 ? "\033[31m●\033[0m " : "○ ") << "竞技场(11) " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;
    std::cout << "                                         ┌─────┐ " << std::endl;
    std::cout << "                                        /       \\ " << std::endl;
    std::cout << "                                       /         \\ " << std::endl;
    std::cout << "                                      /           \\ " << std::endl;
    std::cout << "                                     /             \\ " << std::endl;
    std::cout << "                                      \\           / " << std::endl;
    std::cout << "                                       \\         / " << std::endl;
    std::cout << "                                        \\       / " << std::endl;
    std::cout << "                                         └─────┘ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 9 ? "\033[31m●\033[0m " : "○ ") << "怜悯之厅(9) " << std::endl;
    std::cout << "                                          │ " << std::endl;
    std::cout << "                                          ▼ " << std::endl;
    std::cout << "                                           ┌─────┐ " << std::endl;
    std::cout << "                                          /       \\ " << std::endl;
    std::cout << "                                         /         \\ " << std::endl;
    std::cout << "                                        /           \\ " << std::endl;
    std::cout << "                                       /             \\ " << std::endl;
    std::cout << "                                      /               \\ " << std::endl;
    std::cout << "                                     └────────────────┘ " << std::endl;
    std::cout << "                                       " << (currentRoomId == 10 ? "\033[31m●\033[0m " : "○ ") << "山脚(10) " << std::endl;

    // 中下层：双子平台(8) - 双子石柱(7) - 悬崖之边(6)
    std::cout << "\n\n";
    std::cout << "                                      ┌─────────────┐ " << std::endl;
    std::cout << "                                     /               \\ " << std::endl;
    std::cout << "                                    /                 \\ " << std::endl;
    std::cout << "                                   /                   \\ " << std::endl;
    std::cout << "                                  /                     \\ " << std::endl;
    std::cout << "                                   \\                   / " << std::endl;
    std::cout << "                                    \\                 / " << std::endl;
    std::cout << "                                     \\               / " << std::endl;
    std::cout << "                                      └─────────────┘ " << std::endl;
    std::cout << "                                       " << (currentRoomId == 8 ? "\033[31m●\033[0m " : "○ ") << "双子平台(8) " << std::endl;
    std::cout << "                                              │ " << std::endl;
    std::cout << "                                              ▼ " << std::endl;
    std::cout << "                             ┌─────────────┐ " << std::endl;
    std::cout << "                            /               \\ " << std::endl;
    std::cout << "                           /                 \\ " << std::endl;
    std::cout << "                          /                   \\ " << std::endl;
    std::cout << "                         /                     \\ " << std::endl;
    std::cout << "                          \\                   / " << std::endl;
    std::cout << "                           \\                 / " << std::endl;
    std::cout << "                            \\               / " << std::endl;
    std::cout << "                             └─────────────┘ " << std::endl;
    std::cout << "                               " << (currentRoomId == 7 ? "\033[31m●\033[0m " : "○ ") << "双子石柱(7) " << std::endl;
    std::cout << "                                              │ " << std::endl;
    std::cout << "                                              ▼ " << std::endl;
    std::cout << "                    ┌─────────────┐ " << std::endl;
    std::cout << "                   /               \\ " << std::endl;
    std::cout << "                  /                 \\ " << std::endl;
    std::cout << "                 /                   \\ " << std::endl;
    std::cout << "                /                     \\ " << std::endl;
    std::cout << "                 \\                   / " << std::endl;
    std::cout << "                  \\                 / " << std::endl;
    std::cout << "                   \\               / " << std::endl;
    std::cout << "                    └─────────────┘ " << std::endl;
    std::cout << "                     " << (currentRoomId == 6 ? "\033[31m●\033[0m " : "○ ") << "悬崖之边(6) " << std::endl;

    // 底层：背契之坛(5) - 黑曜石圣殿(4) - 裂隙(3) - 铁匠铺(2) - 迷雾森林(1)
    std::cout << "                                              │ " << std::endl;
    std::cout << "                                              ▼ " << std::endl;
    std::cout << "    ┌─────────────┐                        ┌───────────────┐ " << std::endl;
    std::cout << "   /               \\                       |               | " << std::endl;
    std::cout << "  /                 \\                      |               | " << std::endl;
    std::cout << " /                   \\                     |               | " << std::endl;
    std::cout << "|                     |                    |               | " << std::endl;
    std::cout << " \\                   /                     |               | " << std::endl;
    std::cout << "  \\                 /                      |               | " << std::endl;
    std::cout << "   \\               /                       └───────────────┘ " << std::endl;
    std::cout << "    └─────────────┘                                   /|\\ " << std::endl;
    std::cout << "    " << (currentRoomId == 5 ? "\033[31m●\033[0m " : "○ ") << "背契之坛(5)                          " << (currentRoomId == 4 ? "\033[31m●\033[0m " : "○ ") << "黑曜石圣殿(4)        " << std::endl;
    std::cout << "                                                       /   \\ " << std::endl;
    std::cout << "         ┌───────────────┐             ┌───────────────┐ " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         └───────────────┘             └───────────────┘ " << std::endl;
    std::cout << "             " << (currentRoomId == 3 ? "\033[31m●\033[0m " : "○ ") << "裂隙(3)                       " << (currentRoomId == 2 ? "\033[31m●\033[0m " : "○ ") << "铁匠铺(2) " << std::endl;
    std::cout << "                                              │ " << std::endl;
    std::cout << "                                              ▼ " << std::endl;
    std::cout << "                                     ┌───────────────┐ " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     └───────────────┘ " << std::endl;
    std::cout << "                                      " << (currentRoomId == 1 ? "\033[31m●\033[0m " : "○ ") << "迷雾森林(1) " << std::endl;

    // 地图图例
    std::cout << "\n\033[35m========================================= 地图图例 =========================================\033[0m" << std::endl;
    std::cout << "  \033[31m●\033[0m - 当前位置   ○ - 可到达房间   │ - 垂直路径   ─ - 水平路径   ▼ - 下行指示 " << std::endl;
    std::cout << "  形状说明：" << std::endl;
    std::cout << "  ┌─┐ 方框=初始区域   O/|\\ 人形=中层右上   /\\ 斜角框=上层区域" << std::endl;
    std::cout << "  方向键对应：1=北 2=东北 3=东 4=东南 5=南 6=西南 7=西 8=西北 9=上 0=下 " << std::endl;
    std::cout << "\033[35m============================================================================================\033[0m" << std::endl;
}

// 绘制定位地图（保持相同规范）
void Map::drawLocationMap() const {
    std::cout << "\n\033[35m======================================= 实时定位地图 =======================================\033[0m" << std::endl;

    std::cout << "                                  区域缩略图 " << std::endl;
    std::cout << "                               高亮显示当前位置 " << std::endl;
    std::cout << "  ---------------------------------------------------------------------------------------- " << std::endl;

    if (currentRoomId >= 1 && currentRoomId <= 4) { // 初始区域
        std::cout << "                            ┌───────────────┐ " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            └───────────────┘ " << std::endl;
        std::cout << "                           " << (currentRoomId == 4 ? "\033[31m●\033[0m " : "○ ") << "黑曜石圣殿(4) " << std::endl;
        std::cout << "                           /|              |\\ " << std::endl;
        std::cout << "                          / |              | \\ " << std::endl;
        std::cout << "                         /  |              |  \\ " << std::endl;
        std::cout << "         ┌───────────────+  |              |  +───────────────┐ " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         └───────────────┘  |              |  └───────────────┘ " << std::endl;
        std::cout << "             " << (currentRoomId == 3 ? "\033[31m●\033[0m " : "○ ") << "裂隙(3)                       " << (currentRoomId == 2 ? "\033[31m●\033[0m " : "○ ") << "铁匠铺(2) " << std::endl;
        std::cout << "                                              │ " << std::endl;
        std::cout << "                                              ▼ " << std::endl;
        std::cout << "                                     ┌───────────────┐ " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     └───────────────┘ " << std::endl;
        std::cout << "                                      " << (currentRoomId == 1 ? "\033[31m●\033[0m " : "○ ") << "迷雾森林(1) " << std::endl;
    }
    // 其他区域定位地图按相同规范实现

    std::cout << "  ---------------------------------------------------------------------------------------- " << std::endl;
    std::cout << "  当前位置：" << rooms.at(currentRoomId).getRoomName() << "(ID:" << currentRoomId << ")" << std::endl;
    std::cout << "  可移动方向：";
    const auto& exits = rooms.at(currentRoomId).getExits();
    for (const auto& exit : exits) {
        std::cout << exit.first << "(" << Room::dirToNumber(exit.first) << ") ";
    }
    std::cout << std::endl;
    std::cout << "  区域提示：" << rooms.at(currentRoomId).getHint() << std::endl;
    std::cout << "\033[35m============================================================================================\033[0m" << std::endl;
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
    std::string dir;

    if (input.length() == 1 && isdigit(input[0])) {
        dir = Room::numberToDir(input);
        if (dir.empty()) {
            std::cout << "\033[33m[提示] 无效数字，请使用1-0对应方向\033[0m" << std::endl;
            return false;
        }
    }
    else {
        dir = input;
    }

    auto currIt = rooms.find(currentRoomId);
    if (currIt == rooms.end()) {
        std::cerr << "\033[31m[错误] 当前房间不存在\033[0m" << std::endl;
        return false;
    }

    const auto& exits = currIt->second.getExits();
    auto exitIt = exits.find(dir);
    if (exitIt == exits.end()) {
        std::cout << "\033[33m[提示] 无法向" << dir << "方向移动，没有通路\033[0m" << std::endl;
        return false;
    }

    currentRoomId = exitIt->second.first;
    std::cout << "\n\033[32m[移动成功] 通过" << dir << "方向到达：" << rooms.at(currentRoomId).getRoomName() << "(ID:" << currentRoomId << ")\033[0m" << std::endl;
    rooms.at(currentRoomId).showRoomInfo();
    return true;
}

// 显示初始房间信息
void Map::showInitialRoom() const {
    rooms.at(1).showRoomInfo();
}

// 快速跳转房间
void Map::jumpToRoom(int roomId) {
    if (rooms.find(roomId) != rooms.end()) {
        currentRoomId = roomId;
        std::cout << "\033[32m[跳转成功] 已到达：" << rooms.at(roomId).getRoomName() << "(ID:" << roomId << ")\033[0m" << std::endl;
        rooms.at(roomId).showRoomInfo();
    }
    else {
        std::cerr << "\033[31m[错误] " << roomId << "号房间不存在\033[0m" << std::endl;
    }
}