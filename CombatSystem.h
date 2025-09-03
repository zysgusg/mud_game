#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H
#include <map>
#include <memory>
#include"BossWanEshuji.h"
#include"Player.h"
#include "UIManager.h"

enum class CombatResult {
    Victory,          // 胜利
    Defeat_Restart,   // 战败 - 选择重试
    Defeat_Load,      // 战败 - 选择读档
    Defeat_Exit,      // 战败 - 选择退出
    Escaped           // 成功逃跑
};

class CombatSystem {
public:
    CombatSystem(UIManager& uiManager);
    CombatResult startCombat(Player& player, CommonEnemy& enemy, const std::map<int, std::unique_ptr<Item>>& itemDb);
    
private:
    UIManager& ui;
    
    void playerTurn(Player& player, CommonEnemy& enemy, const std::map<int, std::unique_ptr<Item>>& itemDb);
    void enemyTurn(CommonEnemy& enemy, Player& player);

    bool attemptEscape(const Player& player, const CommonEnemy& enemy);
    int calculateDamage(const Attribute& attacker, const Attribute& defender, int power = 0);
};

#endif // COMBATSYSTEM_H