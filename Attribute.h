#pragma once
#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H
#include <string>
#include "GameData.h"

class Attribute {
protected:
    std::string name;       // ��ɫ����
    int level;              // �ȼ�
    int hp;                 // ��ǰ����ֵ
    int maxHp;              // �������ֵ
    int atk;                // ������
    int def;                // ������
    int speed;              // �ٶ�
    int exp;                // ��ǰ����ֵ
    int expToNextLevel;     // �������辭��ֵ
    int gold;               // ���
    float critRate;         // �����ʣ�0-1֮�䣩

public:
    Attribute(std::string name, int level = 1);

    // ���Ի�ȡ
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

    // �����޸�
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
    // �ȼ������������趨���ȼ�+1������*110%��������*120%��
    bool levelUp();

    bool isAlive() const;
    void takeDamage(int damage);
    void heal(int amount);
};

#endif // ATTRIBUTE_H