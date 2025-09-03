#pragma once
#ifndef COMMONENEMY_H
#define COMMONENEMY_H
#include "Attribute.h"

// С�����ͣ����ھ籾�еĶ��ޣ�
enum class EnemyType {
    CORRUPT_WOLF,   // ʴ�Ƕ��ǣ���϶����������
    GOBLIN,         // �粼��
    SLIME,          // ʷ��ķ
    MINOTAUR,       // ţͷ��
    ZOMBIE,         // ��ʬ
    SKELETON        // ����
};

class CommonEnemy : public Attribute {
private:
    EnemyType type;
    int expReward;   // ���ܺ��齱��
    int goldReward;  // ���ܺ��ҽ���

public:
    CommonEnemy(EnemyType type, int level);

    EnemyType getType() const;
    int getExpReward() const;
    int getGoldReward() const;
};

#endif // COMMONENEMY_H