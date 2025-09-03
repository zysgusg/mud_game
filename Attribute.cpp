#include "Attribute.h"
#include <cstdlib>
#include <ctime>

Attribute::Attribute(std::string name, int level)
    : name(name), level(level), hp(100), maxHp(100), atk(10), def(5), speed(5),
    exp(0), expToNextLevel(100), gold(0), critRate(0.05f) {
    // 初始化随机数种子（用于暴击判定）
    srand(time(0));
}

// 属性获取
std::string Attribute::getName() const { return name; }
int Attribute::getLevel() const { return level; }
int Attribute::getHP() const { return hp; }
int Attribute::getMaxHP() const { return maxHp; }
int Attribute::getATK() const { return atk; }
int Attribute::getDEF() const { return def; }
int Attribute::getSpeed() const { return speed; }
int Attribute::getExp() const { return exp; }
int Attribute::getExpToNextLevel() const { return expToNextLevel; }
int Attribute::getGold() const { return gold; }
float Attribute::getCritRate() const { return critRate; }

// 属性修改

void Attribute::setMaxHP(int value) {
    // 可以添加一些合理性检查，确保生命值为非负值
    if (value >= 0) {
        maxHp = value;
    }
    else {
        // 可以根据需要处理无效值，这里简单设为0
        maxHp = 0;
    }
}
void Attribute::setHP(int value) { hp = std::max(0, std::min(value, maxHp)); }
void Attribute::setATK(int value) { atk = std::max(1, value); }
void Attribute::setDEF(int value) { def = std::max(0, value); }
void Attribute::setSpeed(int value) { speed = std::max(1, value); }
void Attribute::addExp(int value) { exp += value; }
void Attribute::addGold(int value) { gold = std::max(0, gold + value); }
void Attribute::setCritRate(float rate) { critRate = std::max(0.0f, std::min(1.0f, rate)); }
void Attribute::setGold(int value) { gold = value; }
void Attribute::setExp(int value) { exp = value; }
void Attribute::setLevel(int value) { level = value; }
void Attribute::setExpToNextLevel(int value) { expToNextLevel = value; }
// 等级提升
bool Attribute::levelUp() {
    if (exp < expToNextLevel) return false;

    // 扣除当前等级所需经验
    exp -= expToNextLevel;
    level++;

    // 属性提升（*110%）
    maxHp = static_cast<int>(maxHp * LEVEL_UP_ATTR_MULTIPLIER);
    hp = maxHp; // 升级回满HP
    atk = static_cast<int>(atk * LEVEL_UP_ATTR_MULTIPLIER);
    def = static_cast<int>(def * LEVEL_UP_ATTR_MULTIPLIER);
    speed = static_cast<int>(speed * LEVEL_UP_ATTR_MULTIPLIER);

    // 经验条长度提升（*120%）
    expToNextLevel = static_cast<int>(expToNextLevel * LEVEL_UP_EXP_MULTIPLIER);
    return true;
}


bool Attribute::isAlive() const { return hp > 0; }

void Attribute::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void Attribute::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}