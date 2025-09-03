#include <windows.h>
#include "Game.h"
//使用c++17
int main() {
    // 设置控制台输出编码为UTF-8，以正确显示中文
    SetConsoleOutputCP(65001); 

    // 创建游戏对象
    Game game;
    
    // 启动游戏
    game.run();

    return 0;
}