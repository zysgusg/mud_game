#pragma once
#ifndef SKILLS_H
#define SKILLS_H
#include "GameData.h"
#include <string>

// ����Ŀ������
enum class SkillTarget {
    ENEMY,  // Ŀ��Ϊ����
    SELF    // Ŀ��Ϊ�Լ�
};

// �����˺�����
enum class DamageType {
    PHYSICAL,  // �����˺�
    MAGICAL,   // ħ���˺�
    BUFF       // ����Ч�������˺���
};

class Skill {
private:
    SkillType type;
    std::string name;
    std::string description;
    int unlockLevel;  // �����ȼ�
    SkillTarget target;
    DamageType damageType;
    int power;        // �����������˺�/�ӳ�ֵ��

public:
    Skill(SkillType type, std::string name, std::string desc, int unlockLv,
        SkillTarget target, DamageType dmgType, int power);

    SkillType getType() const;
    std::string getName() const;
    std::string getDescription() const;
    int getUnlockLevel() const;
    SkillTarget getTarget() const;
    DamageType getDamageType() const;
    int getPower() const;
};

#endif // SKILLS_H