#include "Item.h"

Item::Item(int id,std::string name, ItemType type, std::string desc, int price)
    :id(id), name(name), type(type), description(desc), price(price) {}

std::string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
std::string Item::getDescription() const { return description; }
int Item::getPrice() const { return price; }
// 具体物品子类实现
HealthPotion::HealthPotion() :Item(1,"生命药水", ItemType::HEALTH_POTION, "回复50点生命值", 50) {}
std::string HealthPotion::use() { return "回复50点生命值"; }

EnergyPotion::EnergyPotion() : Item(2,"能量药水", ItemType::ENERGY_POTION, "下个回合行动次数+1", 100) {}
std::string EnergyPotion::use() { return "下个回合行动次数+1"; }

HealthPotion* HealthPotion::clone() const {
    return new HealthPotion(*this);
}
EnergyPotion* EnergyPotion::clone() const {
    return new EnergyPotion(*this);
}