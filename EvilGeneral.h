#pragma once
#ifndef EVILGENERAL_H
#define EVILGENERAL_H
#include "CommonEnemy.h"
#include "GameData.h"
#include "Item.h"
#include <vector>

class EvilGeneral : public CommonEnemy {
private:
    EvilType evilType;         // ��������
    std::string territory;     // ��أ������Ȩ��
    std::vector<Item*> drops;  // ������Ʒ

public:
    // �������캯���������б���ʵ��ƥ��
    EvilGeneral(std::string name, EvilType type, std::string territory, int level);
};



#endif // EVILGENERAL_H