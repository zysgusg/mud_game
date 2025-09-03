#pragma once
#ifndef DIVINEWEAPON_H
#define DIVINEWEAPON_H
#include "Equipment.h"

class DivineWeapon : public Equipment {
private:
    int growthLevel;  // �񽣳ɳ��ȼ�������ҵȼ�������

public:
    DivineWeapon();  // ��ʼ�񽣣������Դ���
    DivineWeapon* clone() const override;
    // �񽣳ɳ�������ҵȼ�������������
    void grow(int playerLevel);

    // �������ܣ����ݳɳ��ȼ�������Ӧ���ܣ�
    bool unlockSkill(int playerLevel, SkillType& skillType);
};

#endif // DIVINEWEAPON_H