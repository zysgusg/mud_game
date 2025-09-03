#include "DivineWeapon.h"
#include "Skills.h"

DivineWeapon::DivineWeapon()
    : Equipment("��ʥ�ö���", EquipmentPart::RING, OathType::TRUTH,  // ��ʱ��λ��ʵ��Ϊ��������
        "�ɳɳ����񽣣��Կ�����ĺ�������", 10, 0, "��ȼ���������") {
    growthLevel = 1;
}

// �񽣳ɳ�������ҵȼ������������� �����
void DivineWeapon::grow(int playerLevel) {
    // ������ҵȼ����������ɳ��ȼ�
    if (playerLevel % 5 == 0) {
        growthLevel++;
    }
}

// �������ܣ���5������ʥ���þ���
bool DivineWeapon::unlockSkill(int playerLevel, SkillType& skillType) {
    if (playerLevel >= 5 && growthLevel >= 2) {
        skillType = SkillType::HOLY_PRISON_JUDGMENT;
        return true;
    }
    // �������ܽ�������...
    return false;
}