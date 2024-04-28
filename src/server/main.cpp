#include "httpserver.h"
#include <iostream>
#include <json.hpp>
#include "chatservice.hpp"
#include "public.hpp"
using json = nlohmann::json;
using namespace std;

void onRequest(const HttpRequest& req, HttpResponse *resp)
{
    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addHeader("Access-Control-Allow-Credentials", "true");
    resp->addHeader("Access-Control-Expose-Headers", "FooBar");
    LOG_INFO<<"回调";
    if(req.method() != HttpRequest::POST)
    {
        resp->setCloseConnection(true);
        resp->setStatusCode(HttpResponse::CODE_400);
        resp->setStatusMessage("Bad Request");
        return ;
    }
    json js = json::parse(req.body());
    //达到的目的：： 完全解耦网络和业务模块
    //通过 msg_id 绑定不同回调操作，获取handler
    MsgHandler msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    //回调消息绑定好的事件处理器，来执行相应的业务处理
    Timestamp tmpTime;
    msgHandler(resp,js,tmpTime);
    resp->setStatusCode(HttpResponse::CODE_200);
    resp->setStatusMessage("OK");
}

int main() {
    EventLoop loop;
    InetAddress addr("0.0.0.0",7777);
    HttpServer server(&loop,addr);
    server.setHttpCallback(onRequest);
    server.start();
    loop.loop();
    return 0;
}