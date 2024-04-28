#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <unordered_map>
#include <muduo/net/TcpConnection.h>
#include <functional>
#include <json.hpp>
#include "usermodel.hpp"
#include "httpresponse.h"
using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;
/*处理消息的事件回调方法类形*/
using MsgHandler = std::function<void(HttpResponse* resp,json &js, Timestamp)>;
//聊天服务器业务类 单例
class ChatService
{
public:
    /*获取单例的接口*/
    static ChatService* instance();
    void login(HttpResponse* resp,json &js, Timestamp time);
    void reg(HttpResponse* resp,json &js, Timestamp time);
    void gpt(HttpResponse* resp,json &js, Timestamp time);
    void addnote(HttpResponse* resp,json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);  
private:
    ChatService();
    unordered_map<int,MsgHandler> _msgHandlerMap; //消息id对应的处理操作

    //数据操作类对象
    UserModel _userModel;
};
#endif