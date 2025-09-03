#pragma once
#ifndef TASKSYSTEM_H
#define TASKSYSTEM_H

#include <string>
#include <vector>
#include <functional> // Task��ʹ����std::function����Ҫ��ͷ�ļ�
#include "Player.h"
#include "Item.h"   // Task��ʹ����Item*����Ҫ��ͷ�ļ�

// ����״̬
enum class TaskStatus {
    UNACCEPTED, ACCEPTED, COMPLETED, REWARDED
};

// --- Task �������û�б仯 ---
class Task {
private:
    std::string id;
    std::string name;
    std::string description;
    TaskStatus status;
    int requiredLevel;
    std::function<bool(Player*)> completionCondition;
    std::vector<Item*> rewards;
    int expReward;
    int goldReward;

public:
    Task(std::string id, std::string name, std::string desc, int level,
        std::function<bool(Player*)> condition, std::vector<Item*> rewards,
        int exp, int gold);

    void accept();
    bool checkCompletion(Player* player);
    void complete(Player* player);

    std::string getID() const;
    std::string getName() const;
    std::string getDescription() const;
    TaskStatus getStatus() const;
    int getRequiredLevel() const;
    // ����Getter������TaskSystem��ȡ������Ϣ������ʾ
    int getExpReward() const;
    int getGoldReward() const;
};


// ��ǰ����UIManager�࣬������ͷ�ļ�����������UIManager.h
class UIManager;

// --- TaskSystem ������������� ---
class TaskSystem {
private:
    std::vector<Task*> allTasks;
    UIManager& ui; // ������UIManager�����ó�Ա

public:
    TaskSystem(UIManager& uiManager); // ���������캯������
    ~TaskSystem();

    void initializeTasks(); // ��������ʼ����������
    void addTask(Task* task);
    void acceptTask(Player* player, std::string taskId); // ��������ȡ������
    void update(Player* player); // ����������/���������Ⱥ���
    void submitTask(Player* player, std::string taskId); // �������ύ������

    std::vector<Task*> getAvailableTasks(Player* player) const;
    std::vector<Task*> getAcceptedTasks() const;
    std::vector<Task*> getCompletedTasks() const;

    Task* findTask(std::string id) const;
    void showTaskList(Player* player) const;
};
#endif // TASKSYSTEM_H