#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
using namespace std;

// User表的ORM类
class Article
{
public:
    Article(int id = -1, string label = "common", string content = "", string createTime = "2024-04-27 15:30:00")
    {
        this->id = id;
        this->label = label;
        this->content = content;
        this->createTime = createTime;
    }

    void setId(int id) { this->id = id; }
    void setLabel(string label) { this->label = label; }
    void setContent(string content) { this->content = content; }
    void setTime(string createTime) { this->createTime = createTime; }

    int getId() { return this->id; }
    string getLabel() { return this->label; }
    string getContent() { return this->content; }
    string getTime() { return this->createTime; }

protected:
    int id;
    string label;
    string content;
    string createTime;
};

#endif