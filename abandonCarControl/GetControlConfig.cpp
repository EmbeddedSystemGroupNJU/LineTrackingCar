//
// Created by leich on 2018/10/19.
//

#include "GetControlConfig.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> spilt(const std::string &str, const std::string &delim) {
    std::vector<std::string> spiltCollection;
    if (str.size() == 0)
        return spiltCollection;
    int start = 0;
    int idx = str.find(delim, start);
    while (idx != std::string::npos)
    {
        spiltCollection.push_back(str.substr(start, idx - start));
        start = idx + delim.size();
        idx = str.find(delim, start);
    }
    spiltCollection.push_back(str.substr(start));
    return spiltCollection;
}

void getConfigMap(std::unordered_map<std::string, std::string> &configMap, std::string filePath) {
    std::string content;
    std::vector<std::string> stringPair;
    const int KEY_INDEX = 0;
    const int VALUE_INDEX = 1;
    const int FIRST_CHAR_INDEX = 0;
    const char COMMENT_LINE = '*';
    const std::string SEPARATOR = "=";

    //配置文件要和exe文件在一起
    std::ifstream ifs(filePath);
    if(ifs.is_open()) {
        while (getline(ifs, content)) {
            ifs >> content;

            if (content[FIRST_CHAR_INDEX] == COMMENT_LINE) {
                continue;
            }

            stringPair = spilt(content, SEPARATOR);
            configMap[stringPair[KEY_INDEX]] = stringPair[VALUE_INDEX];
        }
        ifs.close();
    }
}

double parseDouble(const std::string &str)
{
	std::istringstream iss(str);
	double num = 0;
	iss >> num;
	return num;
}

void getControlConfig(ControlConfigs& controlConfigs) {
    std::unordered_map<std::string, std::string> *configMap = new std::unordered_map<std::string, std::string>();
	getConfigMap(*configMap, "ControlConfiguration.txt");

    controlConfigs.controlMethod = configMap->at("CONTROL_METHOD");
    controlConfigs.kp = parseDouble(configMap->at("KP"));
    controlConfigs.ki = parseDouble(configMap->at("KI"));
    controlConfigs.kd = parseDouble(configMap->at("KD"));
    controlConfigs.leftStdSpeed = parseDouble(configMap->at("LEFT_STANDARD_SPEED"));
    controlConfigs.rightStdSpeed = parseDouble(configMap->at("RIGHT_STANDARD_SPEED"));

	delete configMap;
}
