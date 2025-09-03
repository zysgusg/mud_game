#pragma once
#ifndef DIVINESET_H
#define DIVINESET_H
#include "Equipment.h"
#include <map>

class DivineSet {
private:
    std::map<EquipmentPart, Equipment*> parts;  // ��װ��������λ->װ����

public:
    DivineSet();

    // �����װ����
    void addPart(Equipment* part);

    // ����Ƿ������в���
    bool isComplete() const;

    // ��ȡ��װ����Ч��������󴥷���
    std::string getResonanceEffect() const;

    // ��ȡ��������������Ч��
    std::string getPartEffect(EquipmentPart part) const;
};

#endif // DIVINESET_H