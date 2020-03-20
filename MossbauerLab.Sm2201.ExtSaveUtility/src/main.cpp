#include <iostream>
#include <string.h>
#include "autoSaveManager.h"
#include "applicationTextUserInterface.h"

const std::string APP_STARTED_MSG = "started";
const std::string APP_STOPPED_MSG = "stopped";
const std::string UNKNOWN_CMD_MSG = "unknown";

/*****************************************************************
 * �������� ������
 * 1. ��������� ���������� ��� ����������
 * 2. ��������� ������������ ./autosaveConfig.txt
 * 3. ���� ���� �� �� ������ ������ True, ��
 * 3.1 ���������� ����, �������������� ��������� MC.exe
 * 3.2 �������� �� ���� ����� �����
 * 3.3 ���������� ������� ����������: ������������������ ��� �.1
 *     �/��� �.2
 *     ���� ������:
 *     W - ���������� �������
 *     Right Arrow - ������������ � ������ 1 �� ����� 2
 *     Left Arrow - ������������ � ������ 2 �� ����� 1
 * 3.4 �������� ����������� .spc � �������� ����������
 * 3.5 ������� ����� �� ���������� ��2201
 *****************************************************************/
int main(int argc, char* argv[])
{
    MossbauerLab::Sm2201::SaveManager::ApplicationTextUserInterface::init();
    std::string condigFilePath = ".\\autosaveConfig.txt";
    std::string userInput;
    MossbauerLab::Sm2201::SaveManager::AutoSaveManager manager(condigFilePath);
    while(1)
    {
        std::cin >> userInput;
        if (strcmp(userInput.c_str(), "exit") == 0)
        {
            break;
        }
        if (strcmp(userInput.c_str(), "start") == 0)
        {  
            manager.start();
            MossbauerLab::Sm2201::SaveManager::ApplicationTextUserInterface::drawMsgStatus(APP_STARTED_MSG);
        }
        else if (strcmp(userInput.c_str(), "stop") == 0)
        {
            manager.stop();
            MossbauerLab::Sm2201::SaveManager::ApplicationTextUserInterface::drawMsgStatus(APP_STOPPED_MSG);
        }
        else 
        {
            if (userInput.size() > 1)
                MossbauerLab::Sm2201::SaveManager::ApplicationTextUserInterface::drawMsgStatus(UNKNOWN_CMD_MSG);
        }
        MossbauerLab::Sm2201::SaveManager::ApplicationTextUserInterface::clearCmd();
        userInput.erase(userInput.begin(), userInput.end());
    }
    return 0;
}



