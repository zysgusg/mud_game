#include "EvilGeneral.h"
#include <cstdlib>

EvilGeneral::EvilGeneral(std::string name, EvilType type, std::string territory, int level)
    :Attribute(name, level), evilType(type), territory(territory) {
    // ͨ������setter�������ԣ�ԭֱ�ӷ���˽�г�Ա����
    maxHp = 200 + level * 20; // ���Ӻ�����������ֵ
    setHP(maxHp);
    setHP(getMaxHP());
    setATK(50 + level * 5);
    setDEF(20 + level * 3);
    setSpeed(10 + level * 2);
    setCritRate(0.1f + level * 0.01f);
}
    // ��ӵ�����Ʒ��ʾ������Ȩ����������׾�����


// ս��AI�����ѡ�񹥻�����