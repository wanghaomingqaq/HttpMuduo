#include "gptcurl.h"
size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream) { 
    string *str = (string*)stream;
    (*str).append((char*)ptr, size*nmemb);
    return size * nmemb;
}

string generate_response(string content) {
	string promt = "请帮我把一下句子分割成不同的要做的todo事项，以,分割每一个todo项,你的回答不需要任何其他内容，只有todo事项和,组成:";
	content = promt + content;
    cout<<content<<endl;
    string url_post0 = "https://dashscope.aliyuncs.com/api/v1/services/aigc/text-generation/generation";
    string resPost0;

    // curl初始化 
    CURL *curl = curl_easy_init();
    // curl返回值 
    CURLcode res;
    if (curl) { 
        // 设置请求头
        struct curl_slist* header_list = NULL;
        header_list = curl_slist_append(header_list, "Authorization: Bearer sk-a55e5b52b4d94f7c99dc6cadca239ef5");
        header_list = curl_slist_append(header_list, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

        // 不接收响应头数据
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        // 设置请求为post请求
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        // 设置请求的URL地址
        curl_easy_setopt(curl, CURLOPT_URL, url_post0.c_str());

        // 设置post请求的参数
        std::string json_data = R"({
            "model": "qwen-turbo",
            "input":{
                "messages":[
                    {
                        "role": "system",
                        "content": "You are a helpful assistant."
                    },
                    {
                        "role": "user",
                        "content": ")" + content + R"("
                    }
                ]
            },
            "parameters": {
                "result_format": "message"
            }
        })";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, json_data.length());

        // 设置ssl验证

        // 关闭调试信息
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

        // 设置数据接收和写入函数
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&resPost0);

        // 设置超时时间
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

        // 开启post请求
        res = curl_easy_perform(curl);
        
        // 释放curl 
        curl_easy_cleanup(curl);
        
        if (res != CURLE_OK) {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
            return "";
        }
    }
	string ret;
    if (!resPost0.empty()) {
        LOG_INFO<<"gpt inner";
        cout<<resPost0<<endl;
        json rep = json::parse(resPost0);
        ret = rep["output"]["choices"][0]["message"]["content"].get<string>();
        cout<<ret<<endl;
    }
    return ret;
}