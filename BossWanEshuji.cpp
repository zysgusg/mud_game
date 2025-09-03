#include "BossWanEshuji.h"

BossWanEshuji::BossWanEshuji()
    : EvilGeneral("������", EvilType::POWER_HUNGRY, "����֮��", 30), phase(1) {
    // ��ʼ�����ԣ�Զ����ͨ������
    setMaxHP(3000);
    setHP(maxHp);
    setATK(200);
    setDEF(100);
    setSpeed(30);
    setCritRate(0.2f);

    // ��ʼ����Ӱ�����󽫾���
    illusions.push_back(new EvilGeneral("��������Ӱ", EvilType::POWER_HUNGRY, "", 10));
    illusions.push_back(new EvilGeneral("��������Ӱ", EvilType::BETRAYAL, "", 10));
    // ����������Ӱ...
}

BossWanEshuji::~BossWanEshuji() {
    for (auto illu : illusions) {
        delete illu;
    }
}

// ������һ�׶Σ�����ֵ����33%����׶�2������10%����׶�3��
void BossWanEshuji::enterNextPhase() {
    if (phase >= 3) return;
    phase++;
    // �׶��������Լӳ�
    setATK(getATK() * 1.2);
    setSpeed(getSpeed() * 1.1);
}

int BossWanEshuji::getPhase() const { return phase; }

// �ٻ���Ӱ���׶�1�ٻ�2�����׶�2�ٻ�4�����׶�3�ٻ�6����
std::vector<EvilGeneral*> BossWanEshuji::summonIllusions() const {
    std::vector<EvilGeneral*> result;
    int count = phase * 2; // �׶�1=2�����׶�2=4�����׶�3=6��
    for (int i = 0; i < count && i < illusions.size(); i++) {
        result.push_back(illusions[i]);
    }
    return result;
}