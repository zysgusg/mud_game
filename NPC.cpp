#include "NPC.h"
#include <iostream>

NPC::NPC(std::string name, NPCType type, std::vector<std::string> dialogues, std::string taskID)
    : name(name), type(type), dialogues(dialogues), taskID(taskID) {}

std::string NPC::getName() const { return name; }
NPCType NPC::getType() const { return type; }

// ��ʾ�Ի�
void NPC::showDialogue() const {
    for (const auto& line : dialogues) {
        std::cout << name << ": " << line << std::endl;
    }
}

// ��ȡ�ɷ�������ID
std::string NPC::getTaskID() const { return taskID; }