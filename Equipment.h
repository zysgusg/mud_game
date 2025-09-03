#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "Item.h"
#include "GameData.h"

// ��Լ���ԣ���Ӧ����������Լ��
enum class OathType {
    FREEDOM,    // ������Լ���Ƽ�֮�ڣ�
    LOYALTY,    // �ҳ���Լ�������ؼף�
    TRUTH,      // ������Լ����ʶ֮�䣩
    MERCY,      // ������Լ������֮����
    HOPE,       // ϣ����Լ���������磩
    ORDER       // ������Լ������սѥ��
};

class Equipment : public Item {
private:
    EquipmentPart part;    // װ����λ
    OathType oath;         // ��Լ����
    int atkBonus;          // �������ӳ�
    int defBonus;          // �������ӳ�
    std::string specialEffect;  // ����Ч������ֿ�������ƣ�

public:
    Equipment(int id,std::string name, EquipmentPart part, OathType oath,
        std::string desc, int atk = 0, int def = 0, std::string effect = "");

    EquipmentPart getPart() const;
    OathType getOath() const;
    int getAtkBonus() const;
    int getDefBonus() const;
    std::string getSpecialEffect() const;

    // װ��ʹ�ã�����ʱ����Ч��������
    std::string use() override;
    Equipment* clone() const override;
};

#endif // EQUIPMENT_H