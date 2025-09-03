#include "Map.h"
#include <iostream>

// ���캯��
Map::Map() {
    initRooms();
    currentRoomId = 1; // ��ʼλ�ã�����ɭ��
}

// ��ʼ�����з���
void Map::initRooms() {
    // ��ʼ����
    Room forest(1, "����ɭ��", "���ϵ�ɭ�֣��������������գ������ڸ���·��",
        "�������ƺ��л�⣬�����ǿ�����ŵĵط�");
    forest.addExit("����", 2, "������");
    rooms.insert({ 1, forest });

    Room blacksmith(2, "����������", "¯�����ܵ������̣�ǽ�Ϲ������һռ�",
        "������ͨ����϶�����С���������Ǻ���Ȩ���");
    blacksmith.addExit("����", 1, "����ɭ��");
    blacksmith.addExit("��", 3, "��϶����");
    blacksmith.addExit("��", 4, "����Ȩ���");
    blacksmith.addNPC("��˼��׷�������");
    blacksmith.addItem("�Ƽ�֮����ͼ");
    rooms.insert({ 2, blacksmith });

    Room rift(3, "��϶����", "��������΢��ĹŴ����棬����ɢ���ź��׾���",
        "�ռ�3�ݺ��׾������޸�װ��");
    rift.addExit("��", 2, "����������");
    rift.addExit("����", 4, "����Ȩ���");
    rift.addItem("���׾�����1/3��");
    rooms.insert({ 3, rift });

    Room obsidian(4, "����Ȩ���", "����ʯ����ĺ�ΰ���ã������о޴�����",
        "���ܶ���������򶫽��뱳��̳֮");
    obsidian.addExit("��", 2, "����������");
    obsidian.addExit("����", 3, "��϶����");
    obsidian.addExit("��", 5, "����̳֮");
    obsidian.addNPC("����������Ȩ������");
    rooms.insert({ 4, obsidian });

    // ��������
    Room betrayal(5, "����̳֮", "���к�ɫ���ĵ�Բ��ʯ̳�����봣���Ŷ���",
        "������������������֪��������������");
    betrayal.addExit("��", 4, "����Ȩ���");
    betrayal.addExit("����", 6, "����֮��");
    betrayal.addNPC("����򣨼��룩");
    betrayal.addItem("�����ؼ�");
    rooms.insert({ 5, betrayal });

    Room cliff(6, "����֮��", "�ٺ����£������Х���±�������Ĵ���",
        "���߶�����������ͨ������̨��·��");
    cliff.addExit("����", 5, "����̳֮");
    cliff.addExit("��", 7, "��ԫ����");
    cliff.addNPC("�����������Ž�����");
    rooms.insert({ 6, cliff });

    Room pillar(7, "��ԫ����", "���й��Ͼ��ĵľ޴����������������ɳ����",
        "�şj�������������ָ�����ҵ���ʶ֮��");
    pillar.addExit("��", 6, "����֮��");
    pillar.addExit("����", 8, "��ԫ����̨");
    pillar.addNPC("�şj�ܣ������ߣ�");
    pillar.addItem("��ʶ֮��");
    rooms.insert({ 7, pillar });

    Room platform(8, "��ԫ����̨", "�����ڷ�ɫ�����еĲ���̨������ٸ�ʾ��",
        "������Ļ����������������ʶ֮����Ƴ�");
    platform.addExit("����", 7, "��ԫ����");
    platform.addExit("��", 9, "����֮��");
    platform.addNPC("�������ڿ�Խ�����");
    rooms.insert({ 8, platform });

    // ��������
    Room mercy(9, "����֮��", "���������ĳ��У�����Ϊ�п�Ķ�����",
        "��־쿳���֪������֮���Ĳ��䴦");
    mercy.addExit("��", 8, "��ԫ����̨");
    mercy.addExit("����", 10, "ɽ����");
    mercy.addExit("��", 11, "���̶�����");
    mercy.addNPC("��־쿣�������");
    rooms.insert({ 9, mercy });

    Room foot(10, "����ɽ����", "������ʯ��ɽ�£������ζ�Ѩ",
        "��Ѩ���������֮��");
    foot.addExit("����", 9, "����֮��");
    foot.addItem("����֮��");
    rooms.insert({ 10, foot });

    Room arena(11, "���̶�����", "���ζ������������Ǵ��̵���˿��",
        "��³������������вп�ĽǶ�����");
    arena.addExit("��", 9, "����֮��");
    arena.addExit("��", 12, "Į�ĳ�");
    arena.addNPC("��³��������Ű������");
    rooms.insert({ 11, arena });

    // Į������
    Room apathy(12, "Į�ĳ�", "�Ұ�ɫ���ĳ��У��������ޱ��飬Ŀ��ն�",
        "���ߵľ�Ĭ�������������еĵر�");
    apathy.addExit("��", 11, "���̶�����");
    apathy.addExit("��", 13, "��Ĭ����");
    rooms.insert({ 12, apathy });

    Room spire(13, "��Ĭ����", "�޴�ʯ��������'��ֹ����'�ķ���",
        "��������������·����ͨ���Թ�������");
    spire.addExit("��", 12, "Į�ĳ�");
    spire.addExit("��", 14, "�����Թ�");
    spire.addExit("��", 15, "����");
    rooms.insert({ 13, spire });

    Room maze(14, "�����Թ�", "���·��ʯ���Թ���ǽ�ڻ���΢�ƶ�",
        "��仫z��������������г�������");
    maze.addExit("��", 13, "��Ĭ����");
    maze.addNPC("��仫z���������죩");
    maze.addItem("��������");
    rooms.insert({ 14, maze });

    Room top(15, "����", "����ƽ̨�������к�ɫ��ʯ����ճ��ֻҰ�ɫ",
        "�����������������������ǵ����");
    top.addExit("��", 13, "��Ĭ����");
    top.addExit("��", 16, "����֮��");
    top.addNPC("����������������");
    rooms.insert({ 15, top });

    // ��������
    Room voidCity(16, "����֮��", "��̮���ĳ��У��ֵ������ź��Ļҳ�",
        "���ߵľ�ͼ��ݻ���������һЩ֪ʶ");
    voidCity.addExit("��", 15, "����");
    voidCity.addExit("��", 17, "��ͼ��ݷ���");
    rooms.insert({ 16, voidCity });

    Room library(17, "��ͼ��ݷ���", "�ջٵ�ͼ��ݣ�������ҳ�Կɱ���",
        "����Ѹ�������о��Ŵ����ף���֪������սѥ��λ��");
    library.addExit("��", 16, "����֮��");
    library.addExit("��", 18, "�����");
    library.addNPC("����Ѹ��ʰ���ߣ�");
    library.addItem("����սѥ");
    rooms.insert({ 17, library });

    Room fortress(18, "�����", "��ɫʯ�����ɵı��ݣ�����������Ϣ",
        "��ն������ĺڰ���������������");
    fortress.addExit("��", 17, "��ͼ��ݷ���");
    fortress.addExit("��", 19, "����֮��");
    fortress.addNPC("��ն����������");
    rooms.insert({ 18, fortress });

    // ��������
    Room chaos(19, "����֮��", "���֮�أ�Ư����ʱ����Ƭ����������������",
        "���������ں��Ĵ���׼�����վ�ս��");
    chaos.addExit("��", 18, "�����");
    chaos.addNPC("������������BOSS��");
    rooms.insert({ 19, chaos });
}

// ��ɢʽȫ�ֵ�ͼ
void Map::drawGlobalMap() const {
    std::cout << "\n\033[35m======================================= ���ش�½ȫ�ֵ�ͼ =======================================\033[0m" << std::endl;

    // ���㣺����֮϶(19)
    std::cout << "                                         �������������� " << std::endl;
    std::cout << "                                         ��     �� " << std::endl;
    std::cout << "                                         �������������� " << std::endl;
    std::cout << "                                     " << (currentRoomId == 19 ? "\033[31m��\033[0m " : "�� ") << "����֮϶(19) " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;

    // �ϲ㣺��������(18) - ��ͼͼ���(17)
    std::cout << "                 ������������������������������                        ������������������������������ " << std::endl;
    std::cout << "                /               \\                      /               \\ " << std::endl;
    std::cout << "               /                 \\                    /                 \\ " << std::endl;
    std::cout << "              /                   \\                  /                   \\ " << std::endl;
    std::cout << "              \\                   /                  \\                   / " << std::endl;
    std::cout << "               \\                 /                    \\                 / " << std::endl;
    std::cout << "                \\               /                      \\               / " << std::endl;
    std::cout << "                 ������������������������������                        ������������������������������ " << std::endl;
    std::cout << "               " << (currentRoomId == 18 ? "\033[31m��\033[0m " : "�� ") << "��������(18)                        " << (currentRoomId == 17 ? "\033[31m��\033[0m " : "�� ") << "��ͼͼ���(17) " << std::endl;
    std::cout << "                         ��                                 �� " << std::endl;
    std::cout << "                         ���������������������������������������������������������������������� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                         ������������������������������ " << std::endl;
    std::cout << "                                        /               \\ " << std::endl;
    std::cout << "                                       /                 \\ " << std::endl;
    std::cout << "                                      /                   \\ " << std::endl;
    std::cout << "                                      \\                   / " << std::endl;
    std::cout << "                                       \\                 / " << std::endl;
    std::cout << "                                        \\               / " << std::endl;
    std::cout << "                                         ������������������������������ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 16 ? "\033[31m��\033[0m " : "�� ") << "���֮��(16) " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;

    // �в����ϣ�����(15) - ĮȻ����(13) - �Թ�(14) - ��Į��(12)
    std::cout << "                                         O " << std::endl;
    std::cout << "                                        /|\\ " << std::endl;
    std::cout << "                                       / | \\ " << std::endl;
    std::cout << "                                      /  |  \\ " << std::endl;
    std::cout << "                                     �����������ة��������� " << std::endl;
    std::cout << "                                     ��         �� " << std::endl;
    std::cout << "                                     �����������Щ��������� " << std::endl;
    std::cout << "                                       " << (currentRoomId == 15 ? "\033[31m��\033[0m " : "�� ") << "����(15) " << std::endl;
    std::cout << "                                         �� " << std::endl;
    std::cout << "                                         �� " << std::endl;
    std::cout << "                 O                           O " << std::endl;
    std::cout << "                /|\\                         /|\\ " << std::endl;
    std::cout << "               / | \\                       / | \\ " << std::endl;
    std::cout << "              /  |  \\                     /  |  \\ " << std::endl;
    std::cout << "             �����������ة���������                 �����������ة��������� " << std::endl;
    std::cout << "             ��         ��                 ��         �� " << std::endl;
    std::cout << "             �����������Щ���������                 �����������Щ��������� " << std::endl;
    std::cout << "             " << (currentRoomId == 13 ? "\033[31m��\033[0m " : "�� ") << "ĮȻ����(13)                 " << (currentRoomId == 14 ? "\033[31m��\033[0m " : "�� ") << "�Թ�(14) " << std::endl;
    std::cout << "                 ��                             �� " << std::endl;
    std::cout << "                 �������������������������������������������������������������� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                         ������������������������������ " << std::endl;
    std::cout << "                                        /               \\ " << std::endl;
    std::cout << "                                       /                 \\ " << std::endl;
    std::cout << "                                      /                   \\ " << std::endl;
    std::cout << "                                      \\                   / " << std::endl;
    std::cout << "                                       \\                 / " << std::endl;
    std::cout << "                                        \\               / " << std::endl;
    std::cout << "                                         ������������������������������ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 12 ? "\033[31m��\033[0m " : "�� ") << "��Į��(12) " << std::endl;

    // �в����£�������(11) - ����֮��(9) - ɽ��(10)
    std::cout << "\n\n";
    std::cout << "                                         �������������� " << std::endl;
    std::cout << "                                        /       \\ " << std::endl;
    std::cout << "                                       /         \\ " << std::endl;
    std::cout << "                                      /           \\ " << std::endl;
    std::cout << "                                     /             \\ " << std::endl;
    std::cout << "                                    /               \\ " << std::endl;
    std::cout << "                                   /                 \\ " << std::endl;
    std::cout << "                                  ������������������������������������������ " << std::endl;
    std::cout << "                                     " << (currentRoomId == 11 ? "\033[31m��\033[0m " : "�� ") << "������(11) " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                         �������������� " << std::endl;
    std::cout << "                                        /       \\ " << std::endl;
    std::cout << "                                       /         \\ " << std::endl;
    std::cout << "                                      /           \\ " << std::endl;
    std::cout << "                                     /             \\ " << std::endl;
    std::cout << "                                      \\           / " << std::endl;
    std::cout << "                                       \\         / " << std::endl;
    std::cout << "                                        \\       / " << std::endl;
    std::cout << "                                         �������������� " << std::endl;
    std::cout << "                                     " << (currentRoomId == 9 ? "\033[31m��\033[0m " : "�� ") << "����֮��(9) " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                          �� " << std::endl;
    std::cout << "                                           �������������� " << std::endl;
    std::cout << "                                          /       \\ " << std::endl;
    std::cout << "                                         /         \\ " << std::endl;
    std::cout << "                                        /           \\ " << std::endl;
    std::cout << "                                       /             \\ " << std::endl;
    std::cout << "                                      /               \\ " << std::endl;
    std::cout << "                                     ������������������������������������ " << std::endl;
    std::cout << "                                       " << (currentRoomId == 10 ? "\033[31m��\033[0m " : "�� ") << "ɽ��(10) " << std::endl;

    // ���²㣺˫��ƽ̨(8) - ˫��ʯ��(7) - ����֮��(6)
    std::cout << "\n\n";
    std::cout << "                                      ������������������������������ " << std::endl;
    std::cout << "                                     /               \\ " << std::endl;
    std::cout << "                                    /                 \\ " << std::endl;
    std::cout << "                                   /                   \\ " << std::endl;
    std::cout << "                                  /                     \\ " << std::endl;
    std::cout << "                                   \\                   / " << std::endl;
    std::cout << "                                    \\                 / " << std::endl;
    std::cout << "                                     \\               / " << std::endl;
    std::cout << "                                      ������������������������������ " << std::endl;
    std::cout << "                                       " << (currentRoomId == 8 ? "\033[31m��\033[0m " : "�� ") << "˫��ƽ̨(8) " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                             ������������������������������ " << std::endl;
    std::cout << "                            /               \\ " << std::endl;
    std::cout << "                           /                 \\ " << std::endl;
    std::cout << "                          /                   \\ " << std::endl;
    std::cout << "                         /                     \\ " << std::endl;
    std::cout << "                          \\                   / " << std::endl;
    std::cout << "                           \\                 / " << std::endl;
    std::cout << "                            \\               / " << std::endl;
    std::cout << "                             ������������������������������ " << std::endl;
    std::cout << "                               " << (currentRoomId == 7 ? "\033[31m��\033[0m " : "�� ") << "˫��ʯ��(7) " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                    ������������������������������ " << std::endl;
    std::cout << "                   /               \\ " << std::endl;
    std::cout << "                  /                 \\ " << std::endl;
    std::cout << "                 /                   \\ " << std::endl;
    std::cout << "                /                     \\ " << std::endl;
    std::cout << "                 \\                   / " << std::endl;
    std::cout << "                  \\                 / " << std::endl;
    std::cout << "                   \\               / " << std::endl;
    std::cout << "                    ������������������������������ " << std::endl;
    std::cout << "                     " << (currentRoomId == 6 ? "\033[31m��\033[0m " : "�� ") << "����֮��(6) " << std::endl;

    // �ײ㣺����̳֮(5) - ����ʯʥ��(4) - ��϶(3) - ������(2) - ����ɭ��(1)
    std::cout << "                                              �� " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "    ������������������������������                        ���������������������������������� " << std::endl;
    std::cout << "   /               \\                       |               | " << std::endl;
    std::cout << "  /                 \\                      |               | " << std::endl;
    std::cout << " /                   \\                     |               | " << std::endl;
    std::cout << "|                     |                    |               | " << std::endl;
    std::cout << " \\                   /                     |               | " << std::endl;
    std::cout << "  \\                 /                      |               | " << std::endl;
    std::cout << "   \\               /                       ���������������������������������� " << std::endl;
    std::cout << "    ������������������������������                                   /|\\ " << std::endl;
    std::cout << "    " << (currentRoomId == 5 ? "\033[31m��\033[0m " : "�� ") << "����̳֮(5)                          " << (currentRoomId == 4 ? "\033[31m��\033[0m " : "�� ") << "����ʯʥ��(4)        " << std::endl;
    std::cout << "                                                       /   \\ " << std::endl;
    std::cout << "         ����������������������������������             ���������������������������������� " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         |               |             |               | " << std::endl;
    std::cout << "         ����������������������������������             ���������������������������������� " << std::endl;
    std::cout << "             " << (currentRoomId == 3 ? "\033[31m��\033[0m " : "�� ") << "��϶(3)                       " << (currentRoomId == 2 ? "\033[31m��\033[0m " : "�� ") << "������(2) " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                                              �� " << std::endl;
    std::cout << "                                     ���������������������������������� " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     |               | " << std::endl;
    std::cout << "                                     ���������������������������������� " << std::endl;
    std::cout << "                                      " << (currentRoomId == 1 ? "\033[31m��\033[0m " : "�� ") << "����ɭ��(1) " << std::endl;

    // ��ͼͼ��
    std::cout << "\n\033[35m========================================= ��ͼͼ�� =========================================\033[0m" << std::endl;
    std::cout << "  \033[31m��\033[0m - ��ǰλ��   �� - �ɵ��﷿��   �� - ��ֱ·��   �� - ˮƽ·��   �� - ����ָʾ " << std::endl;
    std::cout << "  ��״˵����" << std::endl;
    std::cout << "  ������ ����=��ʼ����   O/|\\ ����=�в�����   /\\ б�ǿ�=�ϲ�����" << std::endl;
    std::cout << "  �������Ӧ��1=�� 2=���� 3=�� 4=���� 5=�� 6=���� 7=�� 8=���� 9=�� 0=�� " << std::endl;
    std::cout << "\033[35m============================================================================================\033[0m" << std::endl;
}

// ���ƶ�λ��ͼ��������ͬ�淶��
void Map::drawLocationMap() const {
    std::cout << "\n\033[35m======================================= ʵʱ��λ��ͼ =======================================\033[0m" << std::endl;

    std::cout << "                                  ��������ͼ " << std::endl;
    std::cout << "                               ������ʾ��ǰλ�� " << std::endl;
    std::cout << "  ---------------------------------------------------------------------------------------- " << std::endl;

    if (currentRoomId >= 1 && currentRoomId <= 4) { // ��ʼ����
        std::cout << "                            ���������������������������������� " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            |               | " << std::endl;
        std::cout << "                            ���������������������������������� " << std::endl;
        std::cout << "                           " << (currentRoomId == 4 ? "\033[31m��\033[0m " : "�� ") << "����ʯʥ��(4) " << std::endl;
        std::cout << "                           /|              |\\ " << std::endl;
        std::cout << "                          / |              | \\ " << std::endl;
        std::cout << "                         /  |              |  \\ " << std::endl;
        std::cout << "         ��������������������������������+  |              |  +�������������������������������� " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         |               |  |              |  |               | " << std::endl;
        std::cout << "         ����������������������������������  |              |  ���������������������������������� " << std::endl;
        std::cout << "             " << (currentRoomId == 3 ? "\033[31m��\033[0m " : "�� ") << "��϶(3)                       " << (currentRoomId == 2 ? "\033[31m��\033[0m " : "�� ") << "������(2) " << std::endl;
        std::cout << "                                              �� " << std::endl;
        std::cout << "                                              �� " << std::endl;
        std::cout << "                                     ���������������������������������� " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     |               | " << std::endl;
        std::cout << "                                     ���������������������������������� " << std::endl;
        std::cout << "                                      " << (currentRoomId == 1 ? "\033[31m��\033[0m " : "�� ") << "����ɭ��(1) " << std::endl;
    }
    // ��������λ��ͼ����ͬ�淶ʵ��

    std::cout << "  ---------------------------------------------------------------------------------------- " << std::endl;
    std::cout << "  ��ǰλ�ã�" << rooms.at(currentRoomId).getRoomName() << "(ID:" << currentRoomId << ")" << std::endl;
    std::cout << "  ���ƶ�����";
    const auto& exits = rooms.at(currentRoomId).getExits();
    for (const auto& exit : exits) {
        std::cout << exit.first << "(" << Room::dirToNumber(exit.first) << ") ";
    }
    std::cout << std::endl;
    std::cout << "  ������ʾ��" << rooms.at(currentRoomId).getHint() << std::endl;
    std::cout << "\033[35m============================================================================================\033[0m" << std::endl;
}


// ��ʾȫ�ֵ�ͼ
void Map::showGlobalMap() {
    drawGlobalMap();
}

// ��ʾ��λ��ͼ
void Map::showLocationMap() {
    drawLocationMap();
}

// �ƶ����䣨֧�ַ������ֻ����֣�
bool Map::switchRoom(const std::string& input) {
    std::string dir;

    if (input.length() == 1 && isdigit(input[0])) {
        dir = Room::numberToDir(input);
        if (dir.empty()) {
            std::cout << "\033[33m[��ʾ] ��Ч���֣���ʹ��1-0��Ӧ����\033[0m" << std::endl;
            return false;
        }
    }
    else {
        dir = input;
    }

    auto currIt = rooms.find(currentRoomId);
    if (currIt == rooms.end()) {
        std::cerr << "\033[31m[����] ��ǰ���䲻����\033[0m" << std::endl;
        return false;
    }

    const auto& exits = currIt->second.getExits();
    auto exitIt = exits.find(dir);
    if (exitIt == exits.end()) {
        std::cout << "\033[33m[��ʾ] �޷���" << dir << "�����ƶ���û��ͨ·\033[0m" << std::endl;
        return false;
    }

    currentRoomId = exitIt->second.first;
    std::cout << "\n\033[32m[�ƶ��ɹ�] ͨ��" << dir << "���򵽴" << rooms.at(currentRoomId).getRoomName() << "(ID:" << currentRoomId << ")\033[0m" << std::endl;
    rooms.at(currentRoomId).showRoomInfo();
    return true;
}

// ��ʾ��ʼ������Ϣ
void Map::showInitialRoom() const {
    rooms.at(1).showRoomInfo();
}

// ������ת����
void Map::jumpToRoom(int roomId) {
    if (rooms.find(roomId) != rooms.end()) {
        currentRoomId = roomId;
        std::cout << "\033[32m[��ת�ɹ�] �ѵ��" << rooms.at(roomId).getRoomName() << "(ID:" << roomId << ")\033[0m" << std::endl;
        rooms.at(roomId).showRoomInfo();
    }
    else {
        std::cerr << "\033[31m[����] " << roomId << "�ŷ��䲻����\033[0m" << std::endl;
    }
}