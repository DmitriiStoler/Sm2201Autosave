// Sm2201SpectrumSaver.cpp : Defines the entry point for the application.
//
#include <iostream>
//#include <iomanip.h>
#include <string.h>
#include "autoSaveManager.h"
//#include "windowsInfo.h"

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
    std::cout << " ===== >>> Spectrum saver is running <<< =====" << std::endl;
    std::string condigFilePath = ".\\autosaveConfig.txt";
    std::cout << " ===== >>> Type: start or stop or exit <<< =====" << std::endl;
    std::string userInput;
    MossbauerLab::Sm2201::SaveManager::AutoSaveManager manager(condigFilePath);
    while(1)
    {
        std::cin >> userInput;
        //std::cin.getline(userInput, 256);
        if (strcmp(userInput.c_str(), "exit") == 0)
        {
            break;
        }
        if (strcmp(userInput.c_str(), "start") == 0)
        {
            std::cout << " ===== >>> Autosave manager has been started. <<< =====" << std::endl;
            manager.start();
        }
        else if (strcmp(userInput.c_str(), "stop") == 0)
        {
            manager.stop();
            std::cout << " ===== >>> Autosave manager has been stopped. <<< =====" << std::endl;
        }
        else 
        {
            std::cout << " ===== >>> Unknown command <<< =====" << std::endl;
        }
        std::cout << " ===== >>> Type: start or stop or exit <<< =====" << std::endl;
    }
    std::cout << " ===== >>> Spectrum saver is stopping <<< =====" << std::endl;
    return 0;
}



