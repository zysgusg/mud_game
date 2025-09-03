#pragma once
#ifndef BOSSWANESHUJI_H
#define BOSSWANESHUJI_H
#include "EvilGeneral.h"
#include <vector>

class BossWanEshuji : public EvilGeneral {
private:
    int phase;                  // 战斗阶段（1-3）
    std::vector<EvilGeneral*> illusions;  // 恶念幻影（六大将军的投影）

public:
    BossWanEshuji();
    ~BossWanEshuji();

    // 多阶段战斗逻辑（阶段提升时属性变化）
    void enterNextPhase();
    int getPhase() const;

    // 幻影召唤（每个阶段召唤不同将军幻影）
    std::vector<EvilGeneral*> summonIllusions() const;
};

#endif // BOSSWANESHUJI_H