#include "public.hpp"
std::vector<std::string> stringToArray(std::string str)
{
    std::vector<std::string> result;
    int start = 0;
    int curr = str.find(',');
    while (curr != std::string::npos)
    {
        result.push_back(str.substr(start,curr-start));
        start = curr + 1;
        curr = str.find(',',start);
    }
    result.push_back(str.substr(start));
    return result;
}
std::string getCurrentTimeString()
{
    auto now = std::chrono::system_clock::now();
    auto now_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}