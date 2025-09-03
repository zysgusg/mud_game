#include "Equipment.h"

Equipment::Equipment(int id,std::string name, EquipmentPart part, OathType oath,
    std::string desc, int atk, int def, std::string effect)
    : Item(id,name, ItemType::MISC, desc, -1), part(part), oath(oath),
    atkBonus(atk), defBonus(def), specialEffect(effect) {}

EquipmentPart Equipment::getPart() const { return part; }
OathType Equipment::getOath() const { return oath; }
int Equipment::getAtkBonus() const { return atkBonus; }
int Equipment::getDefBonus() const { return defBonus; }
std::string Equipment::getSpecialEffect() const { return specialEffect; }
Equipment* Equipment::clone() const
{
    return new Equipment(*this);
}
// 装备使用效果描述
std::string Equipment::use() {
    return "穿戴" + name + "，获得" + std::to_string(atkBonus) + "攻击力和" +
        std::to_string(defBonus) + "防御力，特殊效果：" + specialEffect;
}