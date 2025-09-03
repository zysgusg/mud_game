#include "DivineWeapon.h"
#include "Skills.h"

DivineWeapon::DivineWeapon()
    : Equipment("六圣裁恶神剑", EquipmentPart::RING, OathType::TRUTH,  // 临时部位，实际为特殊武器
        "可成长的神剑，对抗恶念的核心武器", 10, 0, "随等级提升威力") {
    growthLevel = 1;
}

// 神剑成长（随玩家等级提升攻击力） 待添加
void DivineWeapon::grow(int playerLevel) {
    // 根据玩家等级提升武器成长等级
    if (playerLevel % 5 == 0) {
        growthLevel++;
    }
}

// 解锁技能（如5级解锁圣狱裁决）
bool DivineWeapon::unlockSkill(int playerLevel, SkillType& skillType) {
    if (playerLevel >= 5 && growthLevel >= 2) {
        skillType = SkillType::HOLY_PRISON_JUDGMENT;
        return true;
    }
    // 其他技能解锁条件...
    return false;
}