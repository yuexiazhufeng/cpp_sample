#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

/**
 * @brief 解析配置文件，配置文件中使用 "=" 赋值的格式，提起到c++中的map，方便后面使用配置文件。
 *        配置文件中支持 "#" 为注释字符
 * 
 * @param configFile 
 */
#define CONFIG_FILE "./xxxconfig.conf"

class configObj {
public:
    void readConfigFile(std::string configFile);
    void echo_config(void);

private:
  std::map<std::string, std::string> configMap_;
};

void configObj::readConfigFile(std::string configFile) {

  // Create a file stream from the file name
  std::ifstream configFileStream(configFile);

  // Iterate through each parameter in the file and read the key value pairs
  std::string param;
  while (std::getline(configFileStream >> std::ws, param)) {
    std::string key;
    std::istringstream paramStream(param);
    if (std::getline(paramStream, key, '=')) {
      // Ignore lines starting with # character
      if (key[0] == '#') {
        continue;
      }
      key = std::regex_replace(key, std::regex(" +$"), "");
      if (key.length() > 0) {
        std::string value;
        if (std::getline(paramStream, value)) {
          value = std::regex_replace(value, std::regex("^ +| +$"), "");
          configMap_[key] = value;
        }
      }
    }
  }
}

void configObj::echo_config(void){
  std::map<std::string, std::string>::iterator iter = configMap_.begin();
  while (iter != configMap_.end())
  {
    std::cout << iter->first << ":" << iter->second << std::endl;
    iter++;
  }
}

int main (int argc, char *argv[]) {
    configObj config;
    config.readConfigFile(CONFIG_FILE);
    config.echo_config();
}
