#include "TaskSystem.h"
#include <iostream>
#include <functional>
#include "UIManager.h"

// --------------------------------------------------------------------
// Task ��ʵ��
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

// --- ������complete��������ֻ���𷢷Ž��������ٴ���UI��ʾ ---
void Task::complete(Player* player) {
    if (status != TaskStatus::COMPLETED) return;

    // ���ž���ͽ�ҽ��� (����Player������Щ����)
    // player->addExp(expReward);
    // player->addGold(goldReward);

    // ������Ʒ���� (����Player��addItem����)
    // for (Item* item : rewards) {
    //     player->addItem(item);
    // }

    status = TaskStatus::REWARDED; // ���Ϊ�����ѷ���
}

// Getter ����
std::string Task::getID() const { return id; }
std::string Task::getName() const { return name; }
std::string Task::getDescription() const { return description; }
TaskStatus Task::getStatus() const { return status; }
int Task::getRequiredLevel() const { return requiredLevel; }
int Task::getExpReward() const { return expReward; }
int Task::getGoldReward() const { return goldReward; }

// --------------------------------------------------------------------
// TaskSystem ��ʵ��
// --------------------------------------------------------------------
TaskSystem::TaskSystem(UIManager& uiManager) : ui(uiManager) {}

TaskSystem::~TaskSystem() {
    for (auto task : allTasks) {
        delete task;
    }
    allTasks.clear();
}

void TaskSystem::initializeTasks() {
    // ����1: Ѱ���׾���
    addTask(new Task(
        "1", "��Ѱ���׾�����", "ǰ����϶���棬���������ġ�ʴ�Ƕ��ǡ����ռ� 3 �ݺ��׾�����", 1,
        [](Player* player) -> bool {
            // ʾ���߼�: return player->getItemCount("���׾���") >= 3; 
            return false;
        },
        {}, 150, 75
    ));

    // ����2: �����ǧ�һ�
    addTask(new Task(
        "2", "�������ǧ�һ꡿", "����Ѫ�����ǧ�һ�...", 5,
        [](Player* player) -> bool {
            // ʾ���߼�: return player->getStoryFlag("TRIBE_SOULS_UNLEASHED");
            return false;
        },
        {}, 200, 0
    ));

    ui.displayMessage("����ϵͳ�ѳ�ʼ����", UIManager::Color::GRAY);
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
        ui.displayMessage("��Ч������ID��", UIManager::Color::RED);
        return;
    }
    if (task->getStatus() != TaskStatus::UNACCEPTED) {
        ui.displayMessage("���Ѿ���ȡ��������������", UIManager::Color::YELLOW);
        return;
    }
    if (player->getLevel() < task->getRequiredLevel()) {
        ui.displayMessage("��ĵȼ����㣬�޷���ȡ�������", UIManager::Color::RED);
        return;
    }

    task->accept();
    ui.displayMessage("��ȡ��������: " + task->getName(), UIManager::Color::GREEN);
}

void TaskSystem::update(Player* player) {
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::ACCEPTED) {
            if (task->checkCompletion(player)) {
                ui.displayMessage("���� [" + task->getName() + "] �Ѵﵽ���������", UIManager::Color::CYAN);
            }
        }
    }
}

// --- ������submitTask ���ڸ�����UI��ʾ ---
void TaskSystem::submitTask(Player* player, std::string taskId) {
    Task* task = findTask(taskId);
    if (!task) {
        ui.displayMessage("��Ч������ID��", UIManager::Color::RED);
        return;
    }
    if (task->getStatus() == TaskStatus::COMPLETED) {
        // �Ȼ�ȡ������Ϣ
        std::string taskName = task->getName();
        int exp = task->getExpReward();
        int gold = task->getGoldReward();

        // �������񷢷Ž���
        task->complete(player);

        // �����TaskSystem����ʾUI��Ϣ
        ui.displayMessage("���� [" + taskName + "] ��ɣ�", UIManager::Color::GREEN);
        if (exp > 0) ui.displayMessage("��þ���: " + std::to_string(exp), UIManager::Color::YELLOW);
        if (gold > 0) ui.displayMessage("��ý��: " + std::to_string(gold), UIManager::Color::YELLOW);

    }
    else if (task->getStatus() == TaskStatus::REWARDED) {
        ui.displayMessage("���Ѿ���ȡ���������Ľ����ˡ�", UIManager::Color::YELLOW);
    }
    else {
        ui.displayMessage("������δ�ﵽ���������", UIManager::Color::YELLOW);
    }
}

void TaskSystem::showTaskList(Player* player) const {
    ui.displayMessage("--- �����б� ---", UIManager::Color::WHITE);

    bool hasAvailable = false;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::UNACCEPTED && player->getLevel() >= task->getRequiredLevel()) {
            if (!hasAvailable) {
                ui.displayMessage("�ɽ�ȡ����", UIManager::Color::CYAN);
                hasAvailable = true;
            }
            std::cout << "[" << task->getID() << "] " << task->getName() << " (�ȼ�Ҫ��: " << task->getRequiredLevel() << ")" << std::endl;
        }
    }
    if (!hasAvailable) {
        ui.displayMessage("û�пɽ�ȡ������", UIManager::Color::GRAY);
    }

    std::cout << std::endl;

    bool hasAccepted = false;
    for (auto task : allTasks) {
        if (task->getStatus() == TaskStatus::ACCEPTED) {
            if (!hasAccepted) {
                ui.displayMessage("����������", UIManager::Color::YELLOW);
                hasAccepted = true;
            }
            std::cout << "[" << task->getID() << "] " << task->getName() << std::endl;
            std::cout << "  - " << task->getDescription() << std::endl;
        }
    }
    if (!hasAccepted) {
        ui.displayMessage("û�����ڽ��е�����", UIManager::Color::GRAY);
    }
    ui.displayMessage("--------------------", UIManager::Color::WHITE);
}

// --- getAvailableTasks, getAcceptedTasks, getCompletedTasks ��ʵ�� (��ѡ��������������) ---
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