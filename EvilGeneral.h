#pragma once
#ifndef EVILGENERAL_H
#define EVILGENERAL_H
#include "CommonEnemy.h"
#include "GameData.h"
#include "Item.h"
#include <vector>

class EvilGeneral : public CommonEnemy {
private:
    EvilType evilType;         // 恶念类型
    std::string territory;     // 领地（如黑曜权枢殿）
    std::vector<Item*> drops;  // 掉落物品

public:
    // 声明构造函数，参数列表与实现匹配
    EvilGeneral(std::string name, EvilType type, std::string territory, int level);
};



#endif // EVILGENERAL_H