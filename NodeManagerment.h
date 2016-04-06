/*
 * =====================================================================================
 *
 *       Filename:  NodeManagerment.h
 *
 *    Description:  节点管理类[用于节点按日期和年月分类，并显示]
 *
 *        Version:  1.0
 *        Created:  30/03/16 08:58:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  leafji 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "CSVParse.h"
using namespace std;
class NodeManagerment
{
public: NodeManagerment(){}
    ~NodeManagerment(){}
    void GroupNodeByYearMonth(CSVParseLine NodeComma);
    map<string,vector<string>> GroupNodeByDay(vector<CSVParseComma> CSVPC);
    void ShowNodeMapByYearMonthDay(void);
public:
    map<string,vector<CSVParseComma>> NodeMapByYearMonth;
};
