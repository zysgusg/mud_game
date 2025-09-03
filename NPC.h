#pragma once
#ifndef NPC_H
#define NPC_H
#include <string>
#include <vector>
#include "TaskSystem.h"

// NPC���ͣ����ھ籾�еĽ�ɫ��
enum class NPCType {
    BLACKSMITH,   // ��������˼�
    PRIEST,       // ���루�����
    GUARDIAN,     // �����ߣ��şj�ܣ�
    MAYOR,        // ��������־쿣�
    GENERAL,      // ���죨��仫z��
    SCAVENGER     // ʰ���ߣ�����Ѹ��
};

class NPC {
private:
    std::string name;
    NPCType type;
    std::vector<std::string> dialogues;         // �Ի�����
    std::string taskID;                         // �ɷ��ŵ�����ID

public:
    NPC(std::string name, NPCType type, std::vector<std::string> dialogues, std::string taskID = "");

    // ������Ϣ
    std::string getName() const;
    NPCType getType() const;

    // ����
    void showDialogue() const;                  // ��ʾ�Ի�
    std::string getTaskID() const;              // ��ȡ�ɷ�������ID
};

#endif // NPC_H