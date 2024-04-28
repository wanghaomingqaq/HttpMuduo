#include "articlemodel.hpp"
#include "db.h"
#include <iostream>
#include <ctime>
using namespace std;
bool ArticleModel::insert(Article &article)
{
    char sql[1024] = {0};
    sprintf(sql,"insert into Article(label,content,createTime) values('%s','%s','%s')",
        article.getLabel().c_str(),article.getContent().c_str(),article.getTime().c_str());
    
    MySQL mysql;
    if(mysql.connect()) {
        if(mysql.update(sql)) {
            //获取插入成功的用户数据生成的主键id
            article.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}

Article ArticleModel::query(int id) 
{
    char sql[1024] = {0};
    sprintf(sql,"select * from Article where id = %d",id);
    
    MySQL mysql;
    if(mysql.connect()) {
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr) {
            /*获取行数据*/
           MYSQL_ROW row = mysql_fetch_row(res);
           if (row != nullptr)
           {
                Article article;
                article.setId(atoi(row[0]));
                article.setLabel(row[1]);
                article.setContent(row[2]);
                article.setTime(row[3]);
                /*释放资源*/
                mysql_free_result(res);
                return article;
           }
        }
    }
    return Article();
}

std::vector<Article> ArticleModel::queryAll()
{
    std::vector<Article> articles;
    MySQL mysql;
    char sql[1024] = "select * from Article";
    if(mysql.connect()) {
        MYSQL_RES *res = mysql.query(sql);
        if(res != nullptr) {
            /*获取行数据*/
           MYSQL_ROW row;
           while ((row = mysql_fetch_row(res)) != nullptr)
           {
                Article article;
                article.setId(atoi(row[0]));
                article.setLabel(row[1]);
                article.setContent(row[2]);
                article.setTime(row[3]);
                articles.push_back(article);
           }
            /*释放资源*/
            mysql_free_result(res);
        }
    }
    return articles;
}