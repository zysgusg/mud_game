#include "Player.h"
#include <sstream>
#include <iostream>

Player::Player(std::string name) : Attribute(name) {
    // 初始化神剑（开场自带）
    divineSword = new DivineWeapon();
    this->extraActionTurns = 0;
    this->currentRoomId = 1; // 初始位置：迷雾森林
    
    // 检查并解锁符合初始等级的技能
    checkAndUnlockSkills();
}

Player::~Player() {

    if (divineSword != nullptr) {
        delete divineSword;
        divineSword = nullptr;
    }
    for (auto skill : skills) {
        delete skill;
    }
    skills.clear();
}

// 装备套装部件
void Player::equipSetPart(Equipment* part) {
    if (!part) return;
    
    // 使用DivineSet类来管理套装
    divineSet.addPart(part);
    
    // 装备加成生效
    setATK(getATK() + part->getAtkBonus());
    setDEF(getDEF() + part->getDefBonus());
    
    // 检查是否集齐套装，如果是则尝试解锁终极技能
    if (hasAllSetParts()) {
        checkAndUnlockSkills();
    }
}

// 获取神剑
DivineWeapon* Player::getDivineSword() const { return divineSword; }

// 检查是否集齐套装（6个部件）
bool Player::hasAllSetParts() const {
    return divineSet.isComplete();
}

std::map<EquipmentPart, Equipment*> Player::getAllEquippedItems() const {
    std::map<EquipmentPart, Equipment*> allItems;

    // 获取DivineSet中的装备
    for (int i = static_cast<int>(EquipmentPart::HELMET); i <= static_cast<int>(EquipmentPart::BOOTS); ++i) {
        EquipmentPart part = static_cast<EquipmentPart>(i);
        Equipment* equipment = divineSet.getEquipment(part);
        if (equipment) {
            allItems[part] = equipment;
        }
    }

    if (divineSword != nullptr) {
        allItems[divineSword->getPart()] = divineSword;
    }

    return allItems;
}

// 重写升级方法，包含技能解锁逻辑
bool Player::levelUp() {
    bool leveledUp = Attribute::levelUp(); // 调用基类的升级方法
    
    if (leveledUp) {
        // 升级后检查并解锁新技能
        checkAndUnlockSkills();
        
        // 神剑成长（如果有的话）
        if (divineSword) {
            divineSword->grow(getLevel());
        }
        
        // 显示升级信息
        std::cout << "恭喜！等级提升到 " << getLevel() << " 级！" << std::endl;
        std::cout << "属性得到了提升，生命值已回复到满值。" << std::endl;
    }
    
    return leveledUp;
}

// 解锁技能
void Player::unlockSkill(SkillType type) {
    // 检查是否已经拥有该技能
    for (auto skill : skills) {
        if (skill->getType() == type) {
            return; // 已有该技能，不重复添加
        }
    }
    
    Skill* newSkill = nullptr;
    
    // 根据技能类型创建技能
    switch (type) {
    case SkillType::HOLY_RIFT_SLASH:
        newSkill = new Skill(type, "圣界裂隙斩", "物理伤害技能", 1, SkillTarget::ENEMY, DamageType::PHYSICAL, 20);
        std::cout << "解锁了新技能: " << newSkill->getName() << std::endl;
        break;
    case SkillType::GOLDEN_TREE_VOW:
        newSkill = new Skill(type, "黄金树之誓", "加血增益", 5, SkillTarget::SELF, DamageType::BUFF, 10);
        std::cout << "解锁了新技能: " << newSkill->getName() << std::endl;
        break;
    case SkillType::HOLY_PRISON_JUDGMENT:
        newSkill = new Skill(type, "圣狱裁决", "魔法伤害技能", 10, SkillTarget::ENEMY, DamageType::MAGICAL, 30);
        std::cout << "解锁了新技能: " << newSkill->getName() << std::endl;
        break;
    case SkillType::STAR_ARMOR:
        newSkill = new Skill(type, "星辰圣铠", "提升防御", 15, SkillTarget::SELF, DamageType::STAR_ARMOR, 15);
        std::cout << "解锁了新技能: " << newSkill->getName() << std::endl;
        break;
    case SkillType::HOLY_MARK_SPEED:
        newSkill = new Skill(type, "圣痕疾影步", "提升速度", 20, SkillTarget::SELF, DamageType::HOLY_MARK_SPEED, 20);
        std::cout << "解锁了新技能: " << newSkill->getName() << std::endl;
        break;
    case SkillType::ULTIMATE_SLAY:
        if (hasAllSetParts()) { // 仅在集齐神器时解锁
            newSkill = new Skill(type, "星闪流河圣龙飞升·神界湮灭斩·最终式", "终极技能，毁灭一切", 50, SkillTarget::ENEMY, DamageType::MAGICAL, 100);
            std::cout << "集齐六誓圣辉套装！解锁了终极技能: " << newSkill->getName() << std::endl;
        }
        break;
    default: 
        break;
    }
    
    if (newSkill) {
        skills.push_back(newSkill);
    }
}

// 检查并解锁符合等级要求的技能
void Player::checkAndUnlockSkills() {
    int currentLevel = getLevel();
    
    // 根据等级解锁技能
    if (currentLevel >= 1 && !getSkill(SkillType::HOLY_RIFT_SLASH)) {
        unlockSkill(SkillType::HOLY_RIFT_SLASH);
    }
    if (currentLevel >= 5 && !getSkill(SkillType::GOLDEN_TREE_VOW)) {
        unlockSkill(SkillType::GOLDEN_TREE_VOW);
    }
    if (currentLevel >= 10 && !getSkill(SkillType::HOLY_PRISON_JUDGMENT)) {
        unlockSkill(SkillType::HOLY_PRISON_JUDGMENT);
    }
    if (currentLevel >= 15 && !getSkill(SkillType::STAR_ARMOR)) {
        unlockSkill(SkillType::STAR_ARMOR);
    }
    if (currentLevel >= 20 && !getSkill(SkillType::HOLY_MARK_SPEED)) {
        unlockSkill(SkillType::HOLY_MARK_SPEED);
    }
    if (currentLevel >= 50 && hasAllSetParts() && !getSkill(SkillType::ULTIMATE_SLAY)) {
        unlockSkill(SkillType::ULTIMATE_SLAY);
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

void Player::addItemByName(const std::string& itemName, int quantity) {
    inventory[itemName] += quantity;
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

const std::map<std::string, int>& Player::getInventory() const {
    return inventory;
}

void Player::clearInventory() {
    inventory.clear();
}