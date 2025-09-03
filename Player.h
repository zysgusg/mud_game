#ifndef PLAYER_H
#define PLAYER_H
#include "Attribute.h"
#include "Equipment.h"
#include "DivineWeapon.h"
#include "Skills.h"
#include <vector>
#include <map>

class Player : public Attribute {
private:
    DivineWeapon* divineSword;                  // ��ʥ�ö��񽣣�Ψһ������
    std::map<EquipmentPart, Equipment*> setParts; // ����ʥ�Ծ�����װ����
    std::vector<Skill*> skills;                 // �ѽ�������
public:
    Player(std::string name = "��������");
    ~Player();
    int extraActionTurns;
    // ������װ������
    void equipSetPart(Equipment* part);         // װ����װ����
    DivineWeapon* getDivineSword() const;
    bool hasAllSetParts() const;                // ����Ƿ�����װ
    std::map<EquipmentPart, Equipment*> getAllEquippedItems() const;

    // ���ܹ���
    void unlockSkill(SkillType type);           // ��������
    std::vector<Skill*> getSkills() const;
    Skill* getSkill(SkillType type) const;

    // �������
    std::map<std::string, bool> taskProgress;   // ������ȣ�����ID->�Ƿ���ɣ�
    void updateTaskProgress(std::string taskID, bool completed);
    bool isTaskCompleted(std::string taskID) const;

    // �浵��װ�������״̬ת��Ϊ�ɴ洢��ʽ��
    std::string serialize() const;
    void deserialize(const std::string& data);  // �Ӵ浵�ָ�״̬
    //��Ʒ����
    std::map<std::string, int> inventory;
    void addItem(const Item& item, int quantity = 1);
    bool useItem(const std::string& itemName);

};

#endif // PLAYER_H