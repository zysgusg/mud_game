#include "EvilGeneral.h"
#include <cstdlib>

EvilGeneral::EvilGeneral(std::string name, EvilType type, std::string territory, int level)
    :Attribute(name, level), evilType(type), territory(territory) {
    // 通过基类setter设置属性（原直接访问私有成员错误）
    maxHp = 200 + level * 20; // 增加合理的最大生命值
    setHP(maxHp);
    setHP(getMaxHP());
    setATK(50 + level * 5);
    setDEF(20 + level * 3);
    setSpeed(10 + level * 2);
    setCritRate(0.1f + level * 0.01f);
}
    // 添加掉落物品（示例：嗜权将军掉落黑曜晶尘）


// 战斗AI：随机选择攻击或技能