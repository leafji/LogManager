/*
 * =====================================================================================
 *
 *       Filename:  NodeManagerment.cpp
 *
 *    Description:  :w
 *
 *        Version:  1.0
 *        Created:  01/04/16 13:19:50
 *       Revision:  non
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef NODEMANAGERMENT
#define NODEMANAGERMENT
#endif

#include <iostream>
#include "NodeManagerment.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

void NodeManagerment::GroupNodeByYearMonth(CSVParseLine CSVPL)
{
   vector<CSVParseComma>::iterator iter;
   vector<CSVParseComma> CommaByYear;
   vector<CSVParseComma> NodeComma = CSVPL.getNodeComma();
   iter = NodeComma.begin();
   string YearMonth = (*iter).YearNode;
   for( ; iter != NodeComma.end() ; iter++)
   {

       if(NodeMapByYearMonth.count((*iter).YearNode) == 0)
       {
          CommaByYear.clear();
          CommaByYear.push_back((*iter));
          NodeMapByYearMonth.insert(make_pair((*iter).YearNode,CommaByYear));   
       }
       else
       {
           NodeMapByYearMonth[(*iter).YearNode].push_back((*iter));
       }
   }
}

map<string, vector<string>> NodeManagerment::GroupNodeByDay(vector<CSVParseComma> CSVPC)
{
    vector<CSVParseComma>::iterator iter;
    map<string,vector<string>> map_result;
    vector<string> CommaByDate;
    iter = CSVPC.begin();
    string day = (*iter).YearNode +"-"+ (*iter).DateNode;
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


