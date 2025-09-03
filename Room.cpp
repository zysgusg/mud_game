#include "Room.h"
#include <iostream>

// ��ʼ����̬��Ա������ֻ��cpp�г�ʼ��һ�Σ�
const std::map<std::string, std::string> Room::DIR_TO_NUM = {
    {"��", "1"},   {"����", "2"}, {"��", "3"},  {"����", "4"},
    {"��", "5"},   {"����", "6"}, {"��", "7"},  {"����", "8"},
    {"��", "9"},   {"��", "0"}
};

const std::map<std::string, std::string> Room::NUM_TO_DIR = {
    {"1", "��"},   {"2", "����"}, {"3", "��"},  {"4", "����"},
    {"5", "��"},   {"6", "����"}, {"7", "��"},  {"8", "����"},
    {"9", "��"},   {"0", "��"}
};

// ���캯��ʵ��
Room::Room(int id, const std::string& name, const std::string& desc, const std::string& h)
    : roomId(id), roomName(name), description(desc), hint(h) {}

// ��ӳ���
void Room::addExit(const std::string& dir, int targetRoomId, const std::string& targetRoomName) {
    exits[dir] = { targetRoomId, targetRoomName };
}

// ���NPC
void Room::addNPC(const std::string& npcName) {
    npcs.push_back(npcName);
}

// �����Ʒ
void Room::addItem(const std::string& itemName) {
    items.push_back(itemName);
}

// ��ʾ������Ϣ
void Room::showRoomInfo() const {
    std::cout << "\033[34m[������Ϣ]\033[0m" << std::endl;
    std::cout << "����: " << roomName << " (ID: " << roomId << ")" << std::endl;
    std::cout << "����: " << description << std::endl;
    std::cout << "��ʾ: " << hint << std::endl;

    std::cout << "NPC: ";
    for (size_t i = 0; i < npcs.size(); ++i) {
        std::cout << npcs[i];
        if (i != npcs.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "��Ʒ: ";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << items[i];
        if (i != items.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "����: ";
    for (auto it = exits.begin(); it != exits.end(); ++it) {
        std::cout << it->first << "(" << dirToNumber(it->first) << ")->" << it->second.second;
        if (std::next(it) != exits.end()) std::cout << ", ";
    }
    std::cout << std::endl;
}
