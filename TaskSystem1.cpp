#include "TaskSystem.h"
#include <iostream>
#include "UIManager.h"

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


//奖励  待补充
void Task::complete(Player* player) {
    if (status != TaskStatus::COMPLETED) return;
    // 处理奖励发放（如增加经验、金币、物品等）
    player->addExp(expReward);
    player->addGold(goldReward);
    status = TaskStatus::REWARDED;
}

std::string Task::getID() const { return id; }
std::string Task::getName() const { return name; }
std::string Task::getDescription() const { return description; }
TaskStatus Task::getStatus() const { return status; }
int Task::getRequiredLevel() const { return requiredLevel; }

TaskSystem::~TaskSystem() {
    for (auto task : allTasks) delete task;
}

void TaskSystem::addTask(Task* task) {
    if (task) allTasks.push_back(task);
}

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

Task* TaskSystem::findTask(std::string id) const {
    for (auto task : allTasks) {
        if (task->getID() == id) return task;
    }
    return nullptr;
}

void TaskSystem::showTaskList(Player* player) const {
    auto available = getAvailableTasks(player);
    if (!available.empty()) {
        UIManager::printColored(UIManager::Color::CYAN, "可接取任务：");
        for (auto task : available) {
            std::cout << "[" << task->getID() << "] " << task->getName() << "（等级要求：" << task->getRequiredLevel() << "）" << std::endl;
        }
    }

    auto accepted = getAcceptedTasks();
    if (!accepted.empty()) {
        UIManager::printColored(UIManager::Color::YELLOW, "进行中任务：");
        for (auto task : accepted) {
            std::cout << "[" << task->getID() << "] " << task->getName() << std::endl;
            std::cout << "  " << task->getDescription() << std::endl;
        }
    }
}