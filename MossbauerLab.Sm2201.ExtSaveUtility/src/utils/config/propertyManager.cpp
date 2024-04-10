#include "propertyManager.h"
#include "strBaseUtils.h"
#include <fstream>
#include <iostream>

const static std::string emptyProperty = "";

MossbauerLab::Utils::Config::PropertyManager::PropertyManager(const std::string &fileName)
    :_fileName(fileName)
{
    reload();
}

/* MossbauerLab::Utils::Config::PropertyManager::PropertyManager(const std::string &fileName2)
    :_fileName(fileName2)
{
    save();
} */

bool MossbauerLab::Utils::Config::PropertyManager::containsKey(const std::string &key) const
{
    return _properties.find(key) != _properties.end();
}

const std::string& MossbauerLab::Utils::Config::PropertyManager::get(const std::string &key) const
{
    if (!containsKey(key))
        return emptyProperty;
    std::map<std::string, std::string>::const_iterator it = _properties.find(key);
    return it->second;
}

void MossbauerLab::Utils::Config::PropertyManager::reload()
{
    _properties.erase(_properties.begin(), _properties.end());
    std::ifstream propertyFileReader;
    propertyFileReader.open(_fileName.c_str(), std::ifstream::in);
    std::string line;
    while(propertyFileReader.good())
    {
        std::getline(propertyFileReader, line);
        int index = line.find("=");
        if (index > 0)
        {
            std::string key = line.substr(0, index);
            key = MossbauerLab::Utils::Strings::StrBaseUtils::trim(key.c_str(), key.length());
            if (key.empty() || key.at(0) == '#')
                continue;
            std::string value = line.length() - index >= 1 ? line.substr(index + 1, line.length() - (index + 1)) : "";
            if (value.length() >= 1)
                value = MossbauerLab::Utils::Strings::StrBaseUtils::trim(value.c_str(), value.length());
            _properties.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    propertyFileReader.close();
}

void MossbauerLab::Utils::Config::PropertyManager::save(bool Channel1, bool Channel2, long Channel1Period, long Channel2Period)
{
std::fstream fout("autosave.txt", std::ios::out | std::ios::trunc); // File name?
 
    if (!fout.is_open()) 
    {
          using namespace std; 
          ofstream outfile("autosave.txt");
    }
    
        fout << "useChannel1 "<< Channel1 << std::endl;   
        fout << "useChannel2 "<< Channel2 << std::endl;
        fout << "Chanel1Period "<< Channel1Period << std::endl;
        fout << "Chanel1Period "<< Channel2Period << std::endl;
        fout.close(); // программа больше не использует файл, поэтому его нужно закрыть
    
}