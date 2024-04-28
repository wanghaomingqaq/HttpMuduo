#pragma once
#include <string>
#include <article.hpp>
#include <articlemodel.hpp>
#include <vector>
#include "public.hpp"
class Note
{
public:
    void insertNode(string note);
    vector<Article> queryAllNote();
    string processNote(string note);
private:
    ArticleModel _articleModel;
};
