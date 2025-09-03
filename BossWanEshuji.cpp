#include "BossWanEshuji.h"

BossWanEshuji::BossWanEshuji()
    : EvilGeneral("万恶枢机", EvilType::POWER_HUNGRY, "混沌之心", 30), phase(1) {
    // 初始化属性（远超普通将军）
    setMaxHP(3000);
    setHP(maxHp);
    setATK(200);
    setDEF(100);
    setSpeed(30);
    setCritRate(0.2f);

    // 初始化幻影（六大将军）
    illusions.push_back(new EvilGeneral("厄休拉幻影", EvilType::POWER_HUNGRY, "", 10));
    illusions.push_back(new EvilGeneral("卡莱恩幻影", EvilType::BETRAYAL, "", 10));
    // 其他将军幻影...
}

BossWanEshuji::~BossWanEshuji() {
    for (auto illu : illusions) {
        delete illu;
    }
}

// 进入下一阶段（生命值低于33%进入阶段2，低于10%进入阶段3）
void BossWanEshuji::enterNextPhase() {
    if (phase >= 3) return;
    phase++;
    // 阶段提升属性加成
    setATK(getATK() * 1.2);
    setSpeed(getSpeed() * 1.1);
}

int BossWanEshuji::getPhase() const { return phase; }

// 召唤幻影（阶段1召唤2个，阶段2召唤4个，阶段3召唤6个）
std::vector<EvilGeneral*> BossWanEshuji::summonIllusions() const {
    std::vector<EvilGeneral*> result;
    int count = phase * 2; // 阶段1=2个，阶段2=4个，阶段3=6个
    for (int i = 0; i < count && i < illusions.size(); i++) {
        result.push_back(illusions[i]);
    }
    return result;
}