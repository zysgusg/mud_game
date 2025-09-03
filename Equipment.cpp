#include "Equipment.h"

Equipment::Equipment(std::string name, EquipmentPart part, std::string desc, int atk, int def, std::string effect) : Item(0, name, ItemType::MISC, desc, -1), part(part), atkBonus(atk), defBonus(def), specialEffect(effect) {}

EquipmentPart Equipment::getPart() const { return part; }
int Equipment::getAtkBonus() const { return atkBonus; }
int Equipment::getDefBonus() const { return defBonus; }
std::string Equipment::getSpecialEffect() const { return specialEffect; }

// 装备使用效果描述
std::string Equipment::use()
{
    return "穿戴" + name + "，获得" + std::to_string(atkBonus) + "攻击力和" + std::to_string(defBonus) + "防御力，特殊效果：" + specialEffect;
}