#ifndef PUBLIC_H
#define PUBLIC_H
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

std::vector<std::string> stringToArray(std::string str);
std::string getCurrentTimeString();
enum EnMsgType
{
    LOGIN_MSG=1, //登录 
    LOGIN_MSG_ACK, //登录相应
    REG_MSG, //注册
    REG_MSG_ACK, //注册响应消息
    GET_GPT, // 请求GPT
    ADD_NOTE, //添加笔记

};
#endif