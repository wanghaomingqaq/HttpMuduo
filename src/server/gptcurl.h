#pragma once
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "json.hpp"
#include <muduo/base/Logging.h>

using namespace std;
using json = nlohmann::json;

string generate_response(string content);
size_t req_reply(void *ptr, size_t size, size_t nmemb, void *stream);