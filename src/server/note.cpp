#include "note.h"
#include <json.hpp>
using json = nlohmann::json;
void Note::insertNode(std::string note)
{
    std::string label;
    std::string content;
    int startLabel = note.find("#");
    if (startLabel == std::string::npos)
    {
        label = "common";
        content = note;
    }
    else
    {
        int end = note.find(" ");
        label = note.substr(startLabel+1, end);
        content = note.substr(end+1);
    }
    Article article;
    article.setLabel(label);
    article.setContent(content);
    article.setTime(getCurrentTimeString());
    _articleModel.insert(article);
}

vector<Article> Note::queryAllNote()
{
    return _articleModel.queryAll();
}

string Note::processNote(string note)
{
    json response;
    insertNode(note);
    vector<Article> ret = queryAllNote();
    vector<string> result;
    for (auto article: ret)
    {
        json js;
        js["label"] = article.getLabel();
        js["content"] = article.getContent();
        js["createTime"] = article.getTime();
        result.push_back(js.dump());
    }
    response["note"] = result;
    return response.dump();
}