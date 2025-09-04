#include "TaskSystem.h"
#include <iostream>
#include <functional>
#include "UIManager.h"
#include "Player.h"
// --------------------------------------------------------------------
// Task 类实现
// --------------------------------------------------------------------
Task::Task(std::string id, std::string name, std::string desc, int level,
    std::function<bool(Player*)> condition, std::vector<Item*> rewards,
    int exp, int gold)
    : id(id), name(name), description(desc), requiredLevel(level),
    completionCondition(condition), rewards(rewards), expReward(exp),
    goldReward(gold), status(TaskStatus::UNACCEPTED) {}

void Task::accept() {
    if (status == TaskStatus::UNACCEPTED) {
        status = TaskStatus::ACCEPTED;
    }
}

bool Task::checkCompletion(Player* player) {
    if (status == TaskStatus::ACCEPTED && completionCondition(player)) {
        status = TaskStatus::COMPLETED;
        return true;
    }
    return false;
}

// --- 修正：complete方法现在只负责发放奖励，不再处理UI显示 ---
void Task::complete(Player* player) {
    if (status != TaskStatus::COMPLETED) return;

    // 发放经验和金币奖励 (假设Player类有这些方法)
    // player->addExp(expReward);
    // player->addGold(goldReward);

    // 发放物品奖励 (假设Player有addItem方法)
    // for (Item* item : rewards) {
    //     player->addItem(item);
    // }

    status = TaskStatus::REWARDED; // 标记为奖励已发放
}

// Getter 函数
std::string Task::getID() const { return id; }
std::string Task::getName() const { return name; }
std::string Task::getDescription() const { return description; }
TaskStatus Task::getStatus() const { return status; }
int Task::getRequiredLevel() const { return requiredLevel; }
int Task::getExpReward() const { return expReward; }
int Task::getGoldReward() const { return goldReward; }
std::string Task::getId() const { return id; } // 新增的getId方法实现

// --------------------------------------------------------------------
// TaskSystem 类实现
// --------------------------------------------------------------------
TaskSystem::TaskSystem(UIManager& uiManager) : ui(uiManager) {}

TaskSystem::~TaskSystem() {
    for (auto task : allTasks) {
        delete task;
    }
    allTasks.clear();
}

void TaskSystem::initializeTasks() {
    // 任务1: 寻黑曜晶尘
    addTask(new Task(
        "1", "【寻黑曜晶尘】", "前往裂隙废墟，击败守卫的“蚀骨恶狼”，收集 3 份黑曜晶尘。", 1,
        [](Player* player) -> bool {
            // 示例逻辑: return player->getItemCount("黑曜晶尘") >= 3; 
            return false;
        },
        {}, 150, 75
    ));

    // 任务2: 解封三千忠魂
    addTask(new Task(
        "2", "【解封三千忠魂】", "用王血解封三千忠魂...", 5,
        [](Player* player) -> bool {
            // 示例逻辑: return player->getStoryFlag("TRIBE_SOULS_UNLEASHED");
            return false;
        },
        {}, 200, 0
    ));

    ui.displayMessage("任务系统已初始化。", UIManager::Color::GRAY);
}


void TaskSystem::addTask(Task* task) {
    if (task) {
        allTasks.push_back(task);
    }
}

Task* TaskSystem::findTask(std::string id) const {
    for (auto task : allTasks) {
        if (task->getID() == id) {
            return task;
        }
    }
    return nullptr;
}

void TaskSystem::acceptTask(Player* player, std::string taskId) {
    Task* task = findTask(taskId);
    if (!task) {
        ui.displayMessage("无效的任务ID。", UIManager::Color::RED);
        return;
    }
    if (task->getStatus() != TaskStatus::UNACCEPTED) {
        ui.displayMessage("你已经接取或完成了这个任务。", UIManager::Color::YELLOW);
        return;
    }
    if (player->getLevel() < task->getRequiredLevel()) {
        ui.displayMessage("你的等级不足，无法接取这个任务。", UIManager::Color::RED);
        return;
    }

    task->accept();
    // 将任务添加到玩家的任务进度中
    player->taskProgress[taskId] = *task;
    ui.displayMessage("接取了新任务: " + task->getName(), UIManager::Color::GREEN);
}

void TaskSystem::update(Player* player) {
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::ACCEPTED) {
            if (task->checkCompletion(player)) {
                ui.displayMessage("任务 [" + task->getName() + "] 已达到完成条件！", UIManager::Color::CYAN);
            }
        }
    }
}

void Task::setStatus(TaskStatus newStatus) {
    status = newStatus; // 正确赋值逻辑
}

// --- 修正：submitTask 现在负责处理UI显示 ---
void TaskSystem::submitTask(Player* player, std::string taskId) {
    Task* task = findTask(taskId);
    if (!task) {
        ui.displayMessage("无效的任务ID。", UIManager::Color::RED);
        return;
    }
    if (task->getStatus() == TaskStatus::COMPLETED) {
        // 先获取奖励信息
        std::string taskName = task->getName();
        int exp = task->getExpReward();
        int gold = task->getGoldReward();

        // 再让任务发放奖励
        task->complete(player);

        // 最后由TaskSystem来显示UI信息
        ui.displayMessage("任务 [" + taskName + "] 完成！", UIManager::Color::GREEN);
        if (exp > 0) ui.displayMessage("获得经验: " + std::to_string(exp), UIManager::Color::YELLOW);
        if (gold > 0) ui.displayMessage("获得金币: " + std::to_string(gold), UIManager::Color::YELLOW);

    }
    else if (task->getStatus() == TaskStatus::REWARDED) {
        ui.displayMessage("你已经领取过这个任务的奖励了。", UIManager::Color::YELLOW);
    }
    else {
        ui.displayMessage("该任务还未达到完成条件。", UIManager::Color::YELLOW);
    }
}

void TaskSystem::showTaskList(Player* player) const {
    ui.displayMessage("--- 任务列表 ---", UIManager::Color::WHITE);

    bool hasAvailable = false;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::UNACCEPTED && player->getLevel() >= task->getRequiredLevel()) {
            if (!hasAvailable) {
                ui.displayMessage("可接取任务：", UIManager::Color::CYAN);
                hasAvailable = true;
            }
            std::cout << "[" << task->getID() << "] " << task->getName() << " (等级要求: " << task->getRequiredLevel() << ")" << std::endl;
        }
    }
    if (!hasAvailable) {
        ui.displayMessage("没有可接取的任务。", UIManager::Color::GRAY);
    }

    std::cout << std::endl;

    bool hasAccepted = false;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::ACCEPTED) {
            if (!hasAccepted) {
                ui.displayMessage("进行中任务：", UIManager::Color::YELLOW);
                hasAccepted = true;
            }
            std::cout << "[" << task->getID() << "] " << task->getName() << std::endl;
            std::cout << "  - " << task->getDescription() << std::endl;
        }
    }
    if (!hasAccepted) {
        ui.displayMessage("没有正在进行的任务。", UIManager::Color::GRAY);
    }
    ui.displayMessage("--------------------", UIManager::Color::WHITE);
}

// --- getAvailableTasks, getAcceptedTasks, getCompletedTasks 的实现 (可选，但保持完整性) ---
std::vector<Task*> TaskSystem::getAvailableTasks(Player* player) const {
    std::vector<Task*> result;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::UNACCEPTED &&
            player->getLevel() >= task->getRequiredLevel()) {
            result.push_back(task);
        }
    }
    return result;
}

std::vector<Task*> TaskSystem::getAcceptedTasks() const {
    std::vector<Task*> result;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::ACCEPTED) {
            result.push_back(task);
        }
    }
    return result;
}

std::vector<Task*> TaskSystem::getCompletedTasks() const {
    std::vector<Task*> result;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::COMPLETED) {
            result.push_back(task);
        }
    }
    return result;
}

void TaskSystem::updateTaskProgress(Player* player, const std::string& taskId) {
    // 查找任务是否存在
    Task* task = findTask(taskId);
    if (task && player) {
        // 例如：将任务状态更新为“已完成”
        player->updateTaskProgress(taskId, TaskStatus::COMPLETED);
        ui.displayMessage("任务进度更新：" + task->getName(), UIManager::Color::GREEN);
    }
}

void TaskSystem::showPlayerTasks(const Player& player) const {
    // 获取玩家的任务进度（假设Player的taskProgress是std::map<std::string, Task>）
    const auto& playerTasks = player.taskProgress;

    if (playerTasks.empty()) {
        ui.displayMessage("你当前没有接取任何任务。", UIManager::Color::YELLOW);
        ui.displayMessage("输入 'task list' 查看可接取的任务。", UIManager::Color::GRAY);
        return;
    }

    ui.displayMessage("===== 你的任务列表 =====", UIManager::Color::CYAN);
    for (const auto& pair : playerTasks) {
        const Task& task = pair.second;
        std::string statusStr;

        // 根据任务状态转换为文字描述
        switch (task.getStatus()) {
        case TaskStatus::UNACCEPTED: statusStr = "未接取"; break;
        case TaskStatus::ACCEPTED: statusStr = "进行中"; break;
        case TaskStatus::COMPLETED: statusStr = "已完成"; break;
        case TaskStatus::REWARDED: statusStr = "已领奖"; break;
        }

        // 显示任务信息（名称、状态、描述等）
        ui.displayMessage(
            "[" + statusStr + "] " + task.getName() + " (ID: " + task.getId() + ")",
            UIManager::Color::WHITE
        );
        ui.displayMessage(
            "   描述: " + task.getDescription(),
            UIManager::Color::GRAY
        );
        
        // 如果是已完成状态，提示可以提交
        if (task.getStatus() == TaskStatus::COMPLETED) {
            ui.displayMessage("   → 输入 'task submit " + task.getId() + "' 提交任务", UIManager::Color::GREEN);
        }
    }
    ui.displayMessage("=======================", UIManager::Color::CYAN);
}