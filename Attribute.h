#pragma once
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <string>
#include "GameData.h"

class Attribute {
protected:
    std::string name;       // 角色名称
    int level;              // 等级
    int hp;                 // 当前生命值
    int maxHp;              // 最大生命值
    int atk;                // 攻击力
    int def;                // 防御力
    int speed;              // 速度
    int exp;                // 当前经验值
    int expToNextLevel;     // 升级所需经验值
    int gold;               // 金币
    float critRate;         // 暴击率（0-1之间）

public:
    Attribute(std::string name, int level = 1);

    // 属性获取
    std::string getName() const;
    int getLevel() const;
    int getHP() const;
    int getMaxHP() const;
    int getATK() const;
    int getDEF() const;
    int getSpeed() const;
    int getExp() const;
    int getExpToNextLevel() const;
    int getGold() const;
    float getCritRate() const;

    // 属性修改
    void setMaxHP(int value);
    void setHP(int value);
    void setATK(int value);
    void setDEF(int value);
    void setSpeed(int value);
    void addExp(int value);
    void addGold(int value);
    void setCritRate(float rate);
    void setExp(int value);
    void setGold(int value);
    void setExpToNextLevel(int value);
    void setLevel(int value);
    // 等级提升（基于设定：等级+1，属性*110%，经验条*120%）
    bool levelUp();

    bool isAlive() const;
    void takeDamage(int damage);
    void heal(int amount);
};

#endif // ATTRIBUTE_H