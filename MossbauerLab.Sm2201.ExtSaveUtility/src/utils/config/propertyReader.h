#ifndef SM2201_SPECTRUM_SAVER_SRC_UTILS_CONFIG_PROPERTY_READER_H
#define SM2201_SPECTRUM_SAVER_SRC_UTILS_CONFIG_PROPERTY_READER_H

#pragma warning(disable:4786)

#include <string>
#include <map>

namespace MossbauerLab
{
    namespace Utils
    {
        namespace Config
        {
            class PropertyReader
            {
            public:
                PropertyReader(const std::string& fileName);
                bool containsKey(const std::string& key) const;
                const std::string& get(const std::string& key) const;
                void reload();
            private:
                std::string _fileName;
                std::map<std::string, std::string> _properties;
            };
        }
    }
}
#endif