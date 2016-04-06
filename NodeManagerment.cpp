/*
 * =====================================================================================
 *
 *       Filename:  NodeManagerment.cpp
 *
 *    Description:  节点管理类[用于节点按日期和年月分类，并显示]
 *
 *        Version:  1.0
 *        Created:  01/04/16 13:19:50
 *       Revision:  non
 *       Compiler:  gcc
 *
 *         Author:  leafji 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _NODEMANAGERMENT_H_
#define _NODEMANAGERMENT_H_
#include <iostream>
#include "NodeManagerment.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

/* *
 * 根据csvpl对象，按照年月划分，保存到map中
 * map中为年月相同的logmessage的集合
 * */
void NodeManagerment::GroupNodeByYearMonth(CSVParseLine CSVPL)
{
   vector<CSVParseComma>::iterator iter;
   vector<CSVParseComma> CommaByYear;
   vector<CSVParseComma> NodeComma = CSVPL.getNodeComma();
   iter = NodeComma.begin();
   string YearMonth = (*iter).getYearNode();
   for( ; iter != NodeComma.end() ; iter++)
   {

       if(NodeMapByYearMonth.count((*iter).getYearNode()) == 0)
       {
          CommaByYear.clear();
          CommaByYear.push_back((*iter));
          NodeMapByYearMonth.insert(make_pair((*iter).getYearNode(),CommaByYear));   
       }
       else
       {
           NodeMapByYearMonth[(*iter).getYearNode()].push_back((*iter));
       }
   }
}
/*
 *  按照日期分类,将分类结果返回到map_result中去
 * */
map<string, vector<string>> NodeManagerment::GroupNodeByDay(vector<CSVParseComma> CSVPC)
{
    vector<CSVParseComma>::iterator iter;
    map<string,vector<string>> map_result;
    vector<string> CommaByDate;
    iter = CSVPC.begin();
    string day = (*iter).getYearNode() +"-"+ (*iter).getDateNode();
    for(; iter != CSVPC.end(); iter++)
    {
        if(map_result.count(day) == 0)
        {
            CommaByDate.clear();
            CommaByDate.push_back((*iter).content);
            map_result.insert(make_pair(day,CommaByDate));
        }
        else
        {
            map_result[day].push_back((*iter).content);
        }
    }
    return map_result;
}
/* *
 *   显示接口，最终已年月，日期进行分类显示。
 * */

void NodeManagerment::ShowNodeMapByYearMonthDay(void)
{
    map<string,vector<CSVParseComma>>::iterator iter;
    map<string,vector<string>> map_day;
    map<string,vector<string>>::iterator day_iter;
    vector<string>::iterator msg;
    cout << "NodeManagerment By Year list as below :"<< endl;
    for(iter = NodeMapByYearMonth.begin(); iter != NodeMapByYearMonth.end(); iter++ )
    {
        cout<< iter->first<<":"<<endl;
        map_day = this->GroupNodeByDay((iter->second));
        for(day_iter = map_day.begin() ; day_iter != map_day.end() ; day_iter++)
        {
            cout<<"  "<< day_iter->first<< ":" << endl;
            for(msg = (day_iter->second).begin();msg != (day_iter->second).end(); msg++)
                cout<<"    "<<*msg<<endl;
        }
    }
}
#endif


