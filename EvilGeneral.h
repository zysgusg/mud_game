#pragma once
#ifndef EVILGENERAL_H
#define EVILGENERAL_H
#include "CommonEnemy.h"
#include "GameData.h"
#include "Item.h"
#include <vector>

class EvilGeneral : public CommonEnemy {
private:
    EvilType evilType;         // 恶念类型
    std::string territory;     // 领地（如黑曜权枢殿）
    std::vector<Item*> drops;  // 掉落物品

public:
    // 声明构造函数，参数列表与实现匹配
    EvilGeneral(std::string name, EvilType type, std::string territory, int level);
	void addDropItem(const Item& item);
	EvilType getEvilType() const { return evilType; }
	std::string getTerritory() const { return territory; }
	const std::vector<Item*>& getDropItems() const { return drops; }
	// 战斗AI：随机选择攻击或技能
	void performAction();
};



#endif // EVILGENERAL_H