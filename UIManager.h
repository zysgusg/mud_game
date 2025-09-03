#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>

// 使用ANSI转义码实现跨平台颜色显示。
class UIManager {
public:
    enum class Color {
        BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, GRAY,
        RESET // 重置颜色
    };

    // 显示带颜色的消息 
    void displayMessage(const std::string& message, Color color) const;

    // 显示玩家属性面板 
    void displayPlayerStatus(const class Player& player) const;

    // 显示场景描述 
    void displayScene(const std::string& description) const;

    // 暂停，等待用户输入
    void pause() const;
    void displayPlayerEquipment(const Player& player) const;
private:
    // 设置控制台文本颜色
    void setColor(Color color) const;
};

#endif // UIMANAGER_H