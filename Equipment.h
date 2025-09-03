#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Item.h"
#include "GameData.h"

// 誓约属性（对应六大正向誓约）
enum class OathType {
    FREEDOM,    // 自由誓约（破枷之冠）
    LOYALTY,    // 忠诚誓约（铁誓胸甲）
    TRUTH,      // 真理誓约（明识之戒）
    MERCY,      // 怜悯誓约（抚伤之链）
    HOPE,       // 希望誓约（晨曦披风）
    ORDER       // 秩序誓约（创世战靴）
};

class Equipment : public Item {
private:
    EquipmentPart part;    // 装备部位
    OathType oath;         // 誓约属性
    int atkBonus;          // 攻击力加成
    int defBonus;          // 防御力加成
    std::string specialEffect;  // 特殊效果（如抵抗精神控制）

public:
    Equipment(int id,std::string name, EquipmentPart part, OathType oath,
        std::string desc, int atk = 0, int def = 0, std::string effect = "");

    EquipmentPart getPart() const;
    OathType getOath() const;
    int getAtkBonus() const;
    int getDefBonus() const;
    std::string getSpecialEffect() const;

    // 装备使用（穿戴时触发效果描述）
    std::string use() override;
    Equipment* clone() const override;
};

#endif // EQUIPMENT_H