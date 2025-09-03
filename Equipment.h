#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Item.h"
#include "GameData.h"

class Equipment : public Item {
private:
    EquipmentPart part;    // 装备部位
    int atkBonus;          // 攻击力加成
    int defBonus;          // 防御力加成
    std::string specialEffect;  // 特殊效果（如抵抗精神控制）

public:
    Equipment(std::string name, EquipmentPart part, std::string desc, int atk = 0, int def = 0, std::string effect = "");

    EquipmentPart getPart() const;
    int getAtkBonus() const;
    int getDefBonus() const;
    std::string getSpecialEffect() const;

    // 装备使用（穿戴时触发效果描述）
    std::string use() override;
};

#endif // EQUIPMENT_H