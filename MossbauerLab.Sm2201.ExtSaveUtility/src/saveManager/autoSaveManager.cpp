#include "autoSaveManager.h"
#include <winbase.h>
#include <iostream>
#include <fstream>
#include <sstream>

#define CHECK_INTERVAL 1000

DWORD WINAPI TimerThreadFunc (LPVOID lpParam) 
{ 
    MossbauerLab::Sm2201::SaveManager::AutoSaveManager* manager = (MossbauerLab::Sm2201::SaveManager::AutoSaveManager*)lpParam;
    if (manager == NULL)
    {
        std::cerr << "===== >>> Thread function argument is NULL! <<< =====" << std::endl;
        return -1;
    }

    long channellElapsedTime = 0;
    long channel2ElapsedTime = 0;
    long elapsedTime = 0;

    while(manager->isRunning())
    {
        MossbauerLab::Sm2201::Config::SchedulerConfig* config = manager->getConfig();
        if(manager->getState())
        {
            if (config->getState())
            {
                if (config->isChannelOneUsing())
                {
                    if (channellElapsedTime >= config->getChannelOnePeriod() * 1000)
                    {
                        // todo: umv: impl save for channel 1
                        std::cout << "===== >>> Save spectrum from channel 1. <<< =====" << std::endl;
                        channellElapsedTime = 0;
                    }
                    else
                    {
                        Sleep(CHECK_INTERVAL);
                        channellElapsedTime += CHECK_INTERVAL;
                        elapsedTime += CHECK_INTERVAL;
                    }
                }
                
                if (config->isChannelTwoUsing())
                {
                    if (channel2ElapsedTime >= config->getChannelTwoPeriod() * 1000)
                    {
                        // todo: umv: impl save for channel 1
                        std::cout << "===== >>> Save spectrum from channel 2. <<< =====" << std::endl;
                        channel2ElapsedTime = 0;
                    }
                    else
                    {
                        Sleep(CHECK_INTERVAL);
                        channel2ElapsedTime += CHECK_INTERVAL;
                        elapsedTime += CHECK_INTERVAL;
                    }
                }
            }
            else
            {
                channellElapsedTime = 0;
                channel2ElapsedTime = 0;
                elapsedTime += CHECK_INTERVAL;
                Sleep(CHECK_INTERVAL);
            }
        }
        else
        {
            channellElapsedTime = 0;
            channel2ElapsedTime = 0;
            Sleep(CHECK_INTERVAL);
            elapsedTime += CHECK_INTERVAL;
        }
        
        if (elapsedTime > 0 && elapsedTime % (20 * CHECK_INTERVAL) == 0)
        {
            std::cout << "===== >>> Autosave manager config was reloaded. <<< =====" << std::endl;
            manager->reloadConfig();
            elapsedTime = 0;
        }
    }

    return 0; 
}


MossbauerLab::Sm2201::SaveManager::AutoSaveManager::AutoSaveManager(const std::string& configFile)
    :_configFile(configFile), _threadRunning(true), _state(false)
{
    _config = new MossbauerLab::Sm2201::Config::SchedulerConfig(_configFile);
    DWORD threadId;
    _timerThread = CreateThread(NULL, 0, TimerThreadFunc, this, 0, &threadId);
    
}

MossbauerLab::Sm2201::SaveManager::AutoSaveManager::~AutoSaveManager()
{
    _threadRunning = false;
    if (_timerThread != NULL)
        CloseHandle(_timerThread);
    delete _config;
}

void MossbauerLab::Sm2201::SaveManager::AutoSaveManager::start()
{
    // start timer
    _state = true;
}

void MossbauerLab::Sm2201::SaveManager::AutoSaveManager::stop()
{
    // stop timer
    _state = false;
}

void MossbauerLab::Sm2201::SaveManager::AutoSaveManager::reloadConfig()
{
    _config->reload();
}

