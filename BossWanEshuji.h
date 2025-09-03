#pragma once
#ifndef BOSSWANESHUJI_H
#define BOSSWANESHUJI_H
#include "EvilGeneral.h"
#include <vector>

class BossWanEshuji : public EvilGeneral {
private:
    int phase;                  // ս���׶Σ�1-3��
    std::vector<EvilGeneral*> illusions;  // �����Ӱ�����󽫾���ͶӰ��

public:
    BossWanEshuji();
    ~BossWanEshuji();

    // ��׶�ս���߼����׶�����ʱ���Ա仯��
    void enterNextPhase();
    int getPhase() const;

    // ��Ӱ�ٻ���ÿ���׶��ٻ���ͬ������Ӱ��
    std::vector<EvilGeneral*> summonIllusions() const;
};

#endif // BOSSWANESHUJI_H