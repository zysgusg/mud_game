#include "Player.h"
#include <sstream>

Player::Player(std::string name) : Attribute(name) {
    // 初始化神剑（开场自带）
    divineSword = new DivineWeapon();
    this->extraActionTurns = 0;
    this->currentRoomId = 1; // 初始位置：迷雾森林
}

Player::~Player() {

    if (divineSword != nullptr) {
        delete divineSword;
        divineSword = nullptr;
    }
    for (auto& pair : setParts) {
        delete pair.second;
    }
    setParts.clear();
    for (auto skill : skills) {
        delete skill;
    }
    skills.clear();
}

// 装备套装部件
void Player::equipSetPart(Equipment* part) {
    if (!part) return;
    EquipmentPart p = part->getPart();
    // 若已有该部位装备，先删除旧装备
    if (setParts.count(p)) {
        delete setParts[p];
    }
    setParts[p] = part;

    // 装备加成生效
    setATK(getATK() + part->getAtkBonus());
    setDEF(getDEF() + part->getDefBonus());
}

// 获取神剑
DivineWeapon* Player::getDivineSword() const { return divineSword; }

// 检查是否集齐套装（6个部件）
bool Player::hasAllSetParts() const {
    return setParts.size() == 6;
}

std::map<EquipmentPart, Equipment*> Player::getAllEquippedItems() const {
    std::map<EquipmentPart, Equipment*> allItems = setParts; // 复制所有套装部件

    if (divineSword != nullptr) {
        allItems[divineSword->getPart()] = divineSword;
    }

    return allItems;
}
// 解锁技能
void Player::unlockSkill(SkillType type) {
    // 根据技能类型创建技能（示例：圣界裂隙斩在1级解锁）
    switch (type) {
    case SkillType::HOLY_RIFT_SLASH:
        skills.push_back(new Skill(type, "圣界裂隙斩", "物理伤害技能", 1,SkillTarget::ENEMY, DamageType::PHYSICAL, 20));
        break;
    case SkillType::GOLDEN_TREE_VOW:
        skills.push_back(new Skill(type, "黄金树之誓", "加血加攻增益", 5,SkillTarget::SELF, DamageType::BUFF, 10));
        break;
    case SkillType::HOLY_PRISON_JUDGMENT:
        skills.push_back(new Skill(type, "圣狱裁决", "魔法伤害技能", 10,SkillTarget::ENEMY, DamageType::MAGICAL, 30));
        break;
    case SkillType::STAR_ARMOR:
        skills.push_back(new Skill(type, "星辰圣铠", "提升防御", 15,SkillTarget::SELF, DamageType::BUFF, 15));
        break;
    case SkillType::HOLY_MARK_SPEED:
        skills.push_back(new Skill(type, "圣痕疾影步", "提升速度", 20,SkillTarget::SELF, DamageType::BUFF, 20));
        break;
    case SkillType::ULTIMATE_SLAY:
        if (hasAllSetParts()) { // 仅在集齐神器时解锁
            skills.push_back(new Skill(type, "星闪流河圣龙飞升·神界湮灭斩·最终式", "终极技能，毁灭一切", 50,SkillTarget::ENEMY, DamageType::MAGICAL, 100));
        }
        break;
    default: break;
    }
}

// 获取技能列表
std::vector<Skill*> Player::getSkills() const { return skills; }

// 获取指定技能
Skill* Player::getSkill(SkillType type) const {
    for (auto skill : skills) {
        if (skill->getType() == type) return skill;
    }
    return nullptr;
}

// 更新任务进度
void Player::updateTaskProgress(std::string taskID, TaskStatus status) {
    auto it = taskProgress.find(taskID);
    if (it != taskProgress.end()) {
        it->second.setStatus(status); // 调用 Task 的 setStatus 方法更新状态
    }
}

// 检查任务是否完成
bool Player::isTaskCompleted(std::string taskID) const {
    auto it = taskProgress.find(taskID);
    if (it != taskProgress.end()) {
        // 调用 Task 的 getStatus 方法，判断是否为“已完成”状态
        return it->second.getStatus() == TaskStatus::COMPLETED;
    }
    return false; // 任务不存在，视为“未完成”
}

void Player::addItem(const Item& item, int quantity) {
    inventory[item.getName()] += quantity;
}

bool Player::useItem(const std::string& itemName) {
    if (inventory.count(itemName) && inventory[itemName] > 0) {
        inventory[itemName]--;
        if (inventory[itemName] == 0) {
            inventory.erase(itemName);
        }
        return true;
    }
    return false;
}