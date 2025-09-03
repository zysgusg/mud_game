#include "Item.h"

Item::Item(int id,std::string name, ItemType type, std::string desc, int price)
    :id(id), name(name), type(type), description(desc), price(price) {}

std::string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
std::string Item::getDescription() const { return description; }
int Item::getPrice() const { return price; }
// ������Ʒ����ʵ��
HealthPotion::HealthPotion() :Item(1,"����ҩˮ", ItemType::HEALTH_POTION, "�ظ�50������ֵ", 50) {}
std::string HealthPotion::use() { return "�ظ�50������ֵ"; }

EnergyPotion::EnergyPotion() : Item(2,"����ҩˮ", ItemType::ENERGY_POTION, "�¸��غ��ж�����+1", 100) {}
std::string EnergyPotion::use() { return "�¸��غ��ж�����+1"; }

HealthPotion* HealthPotion::clone() const {
    return new HealthPotion(*this);
}
EnergyPotion* EnergyPotion::clone() const {
    return new EnergyPotion(*this);
}