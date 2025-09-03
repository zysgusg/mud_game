#include "DivineSet.h"

DivineSet::DivineSet() {}

// �����װ����
void DivineSet::addPart(Equipment* part) {
    if (part) {
        parts[part->getPart()] = part;
    }
}

// ����Ƿ��루6��������
bool DivineSet::isComplete() const {
    return parts.size() == 6;
}

// ��װ����Ч���������������ռ��ܣ�
std::string DivineSet::getResonanceEffect() const {
    return isComplete() ? "�������ռ��ܡ���������ʥ���������������ն������ʽ����ȫ����+20%" : "δ������װ���޹���Ч��";
}

// ��������Ч��
std::string DivineSet::getPartEffect(EquipmentPart part) const {
    auto it = parts.find(part);
    if (it != parts.end()) {
        return it->second->getSpecialEffect();
    }
    return "�ò�λδװ����װ����";
}