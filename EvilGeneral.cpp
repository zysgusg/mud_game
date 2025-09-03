#include "EvilGeneral.h"
#include <iostream>
#include <cstdlib>

EvilGeneral::EvilGeneral(std::string name, EvilType type, std::string territory, int level)
    :CommonEnemy (EnemyType::BOSS,level), evilType(type), territory(territory) {
    // 通过基类setter设置属性（原直接访问私有成员错误）
    maxHp = 200 + level * 20; // 增加合理的最大生命值
    setHP(maxHp);
    setHP(getMaxHP());
    setATK(50 + level * 5);
    setDEF(20 + level * 3);
    setSpeed(10 + level * 2);
    setCritRate(0.1f + level * 0.01f);
}

// 战斗AI：随机选择攻击或技能
void EvilGeneral::performAction() {
	int action = rand() % 2; // 随机选择0或1
	if (action == 0) {
		// 普通攻击
		std::cout << getName() << " 使用普通攻击！" << std::endl;
	}
	else {
		// 使用技能（示例技能）
		std::cout << getName() << " 使用了强力技能！" << std::endl;
	}
}