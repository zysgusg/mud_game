#include "Player.h"
#include <sstream>

Player::Player(std::string name) : Attribute(name) {
    // ��ʼ���񽣣������Դ���
    divineSword = new DivineWeapon();
    this->extraActionTurns = 0;
}

Player::~Player() {
    delete divineSword;
    for (auto& pair : setParts) {
        delete pair.second;
    }
    for (auto skill : skills) {
        delete skill;
    }
}

// װ����װ����
void Player::equipSetPart(Equipment* part) {
    if (!part) return;
    EquipmentPart p = part->getPart();
    // �����иò�λװ������ɾ����װ��
    if (setParts.count(p)) {
        delete setParts[p];
    }
    setParts[p] = part;

    // װ���ӳ���Ч
    setATK(getATK() + part->getAtkBonus());
    setDEF(getDEF() + part->getDefBonus());
}

// ��ȡ��
DivineWeapon* Player::getDivineSword() const { return divineSword; }

// ����Ƿ�����װ��6��������
bool Player::hasAllSetParts() const {
    return setParts.size() == 6;
}

std::map<EquipmentPart, Equipment*> Player::getAllEquippedItems() const {
    std::map<EquipmentPart, Equipment*> allItems = setParts; // ����������װ����

    if (divineSword != nullptr) {
        allItems[divineSword->getPart()] = divineSword;
    }

    return allItems;
}
// ��������
void Player::unlockSkill(SkillType type) {
    // ���ݼ������ʹ������ܣ�ʾ����ʥ����϶ն��1��������
    switch (type) {
    case SkillType::HOLY_RIFT_SLASH:
        skills.push_back(new Skill(type, "ʥ����϶ն", "�����˺�����", 1,
            SkillTarget::ENEMY, DamageType::PHYSICAL, 20));
        break;
    case SkillType::GOLDEN_TREE_VOW:
        skills.push_back(new Skill(type, "�ƽ���֮��", "��Ѫ�ӹ�����", 5,
            SkillTarget::SELF, DamageType::BUFF, 10));
        break;
        // �����������ƣ����ȼ�����
    default: break;
    }
}

// ��ȡ�����б�
std::vector<Skill*> Player::getSkills() const { return skills; }

// ��ȡָ������
Skill* Player::getSkill(SkillType type) const {
    for (auto skill : skills) {
        if (skill->getType() == type) return skill;
    }
    return nullptr;
}

// �����������
void Player::updateTaskProgress(std::string taskID, bool completed) {
    taskProgress[taskID] = completed;
}

// ��������Ƿ����
bool Player::isTaskCompleted(std::string taskID) const {
    auto it = taskProgress.find(taskID);
    return (it != taskProgress.end()) && it->second;
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