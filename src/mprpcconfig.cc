#include "mprpcconfig.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
// 负责解析加载配置文件
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    std::ifstream file(config_file);    //定义流对象从文件路径中读取内容
    if (!file.is_open())
    {
        std::cerr << config_file << " does not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }
    /*
     FILE *pf = fopen(config_file, "r");        //原始办法
        while(!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);
    }
    */
    std::string line;
    while (std::getline(file, line))        //逐行读取文件内容
    {
        // 去掉字符串前面多余的空格
        Trim(line);

        // 判断#的注释
        if (line.empty() || line[0] == '#')     //如果这一行加的全是空格去掉后变为空
        {
            continue;
        }

        // 解析配置项
        size_t idx = line.find('=');
        if (idx == std::string::npos)
        {
            // 配置项不合法
            continue;
        }

        std::string key = line.substr(0, idx);
        Trim(key);
        std::string value = line.substr(idx + 1);
        Trim(value);

        m_configMap[key] = value;
    }

    file.close();
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if (it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}

// 去掉字符串前后的空格
void MprpcConfig::Trim(std::string &str)
{
    // int idx = src_buf.find_first_not_of(' ');
    // if (idx != -1)
    // {
    //     // 说明字符串前面有空格
    //     src_buf = src_buf.substr(idx, src_buf.size()-idx);
    // }
    // // 去掉字符串后面多余的空格
    // idx = src_buf.find_last_not_of(' ');
    // if (idx != -1)
    // {
    //     // 说明字符串后面有空格
    //     src_buf = src_buf.substr(0, idx+1);
    // }
    // 去掉前后的空格
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);       
        //find_if通过回调用来查找第一个不是空白处，之后删除从begin到不是第一个空白处之前
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    //同理，不过rbegin,rend表示从后往前找第一个非空白处，然后将他转化为正序的迭代器位置，基于.base，最后erase
}