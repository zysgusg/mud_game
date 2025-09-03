#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <string>

// ��Ʒ����
enum class ItemType {
    HEALTH_POTION,  // ����ҩˮ
    ENERGY_POTION,  // ����ҩˮ
    QUEST_ITEM,     // ������Ʒ������׾�����
    MISC            // ���������ѵ��
};

class Item {
protected:
    int id;
    std::string name;
    ItemType type;
    std::string description;
    int price;       // �۸�-1��ʾ���ɽ��ף�

public:
    Item(int id,std::string name, ItemType type, std::string desc, int price = -1);
    virtual ~Item() = default;
    int getId()const { return id; }
    std::string getName() const;
    ItemType getType() const;
    std::string getDescription() const;
    int getPrice() const;

    // ��Ʒʹ��Ч�������麯��������ʵ�֣�
    virtual std::string use() = 0;
    virtual Item* clone() const = 0;
};

class HealthPotion : public Item {
public:
    HealthPotion();
    std::string use() override;
    HealthPotion* clone() const override;
};

class EnergyPotion : public Item {
public:
    EnergyPotion();
    std::string use() override;
    EnergyPotion* clone() const override;
};

#endif // ITEM_H