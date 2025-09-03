#include "CommonEnemy.h"

CommonEnemy::CommonEnemy(EnemyType type, int level) : Attribute("", level) {
    // ����С�����ͳ�ʼ������
    switch (type) {
    case EnemyType::CORRUPT_WOLF:
        name = "ʴ�Ƕ���";
        maxHp = 50 + level * 10;
        atk = 8 + level * 2;
        def = 3 + level;
        speed = 7 + level;
        expReward = 50 + level * 10;
        goldReward = 10 + level * 5;
        break;
    case EnemyType::GOBLIN:
        name = "�粼��";
        maxHp = 30 + level * 8;
        atk = 6 + level;
        def = 2 + level;
        speed = 5 + level;
        expReward = 30 + level * 5;
        goldReward = 5 + level * 2;
        break;
        // ����С���������Ƴ�ʼ��
    default:
        name = "δ֪����";
        maxHp = 40;
        atk = 5;
        def = 2;
        speed = 5;
        expReward = 40;
        goldReward = 8;
        break;
    }
    hp = maxHp; // ��ʼ����ֵΪ���ֵ
}

EnemyType CommonEnemy::getType() const { return type; }
int CommonEnemy::getExpReward() const { return expReward; }
int CommonEnemy::getGoldReward() const { return goldReward; }