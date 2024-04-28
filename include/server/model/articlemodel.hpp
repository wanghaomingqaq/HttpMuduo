#ifndef ARTICLEMODEL_H
#define ARTICLEMODEL_H

#include "article.hpp"
#include <vector>

// User表的数据操作类
class ArticleModel {
public:
    // User表的增加方法
    bool insert(Article &article);

    // 根据用户号码查询用户信息
    Article query(int id);
    std::vector<Article> queryAll();
    Article queryByLabel(string label);

};

#endif