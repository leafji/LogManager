/*
 * =====================================================================================
 *
 *       Filename:  CSVParse.cpp
 *
 *    Description:  CSV文件的解析类  
 *
 *        Version:  1.0
 *        Created:  29/03/16 13:26:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "CSVParse.h"
#include <fstream>
/* 
 * Load 读取filepathname的csv 文件，将流转入content中
 * */

void CSVParse::Load(const string& filepathname)
{
    ifstream csv_file;
    int length;
    char* buffer;
    csv_file.open(filepathname,ios::in);
    if(!csv_file)
    {
        cout<< "Open CSV file failed!!" << endl;
        exit(-1);
    }
    csv_file.seekg(0,std::ios::end);
    length = csv_file.tellg();
    csv_file.seekg(0,std::ios::beg);
    buffer = new char[length];
    csv_file.read(buffer,length);
    content = string(buffer);
    delete buffer;
    csv_file.close();
}

void CSVParse::ParseString(void)
{
    int sep_pos;
    int start_find_pos = 0;
    int end_pos = content.length() - 1;

    sep_pos = content.find(separate,start_find_pos);
    do
    {
        string temp_str(content,start_find_pos, sep_pos - start_find_pos);
        Node.push_back(temp_str);
        start_find_pos = sep_pos + 1;
        sep_pos = content.find(separate,start_find_pos);
    }while(sep_pos != end_pos && sep_pos != -1);
    string temp_str(content,start_find_pos,end_pos - start_find_pos);
    Node.push_back(temp_str);
}

void CSVParse::PrintNode(void)
{
    cout<<"PrintNode function enter!!"<<endl;
    vector<string>::const_iterator iter;
    int number = 1;
    for(iter = Node.cbegin(); iter != Node.cend(); iter++,number++)
        cout<<"Node["<<number<<"]"<<*iter<<endl;
}

void CSVParseLine::FillNodeForComma(void)
{
    vector<string>::const_iterator iter;
    for(iter = Node.cbegin(); iter != Node.cend(); iter++)
    {
        CSVParseComma *CommaNode = new CSVParseComma(",",*iter);
        CommaNode->ParseString();
        CommaNode->FillNodeForNodeInfo();
        NodeComma.push_back(*CommaNode);
    }
}

void CSVParseLine::GroupNodeLine(void)
{
   vector<CSVParseComma>::iterator iter;
   vector<string> LogMessage;
   iter = NodeComma.begin();
   string YearMonth = (*iter).YearNode;
   for( ; iter != NodeComma.end() ; iter++)
   {
      
       if(NodeMap.count((*iter).YearNode) == 0)
       {
          LogMessage.clear();
          LogMessage.push_back((*iter).content);
          NodeMap.insert(make_pair((*iter).YearNode,LogMessage));   
       }
       else
       {
           NodeMap[(*iter).YearNode].push_back((*iter).content);
       }
   }
//   NodeMap.insert(make_pair(YearMonth ,LogMessage));
}

void CSVParseLine::ShowNodeMap(void)
{
    map<string,vector<string>>::iterator iter;
    vector<string>::iterator v_iter;
    for(iter = NodeMap.begin(); iter != NodeMap.end(); iter++ )
    {
        cout<< iter->first<<":"<<endl;
        for(v_iter =(iter->second).begin(); v_iter != (iter->second).end(); v_iter++)
            cout <<"  "<< *v_iter << endl;
    }

}

void CSVParseLine::PrintAllLine(void)
{
   vector<CSVParseComma>::iterator iter;
   int number = 0;
   for(iter = NodeComma.begin(); iter != NodeComma.end() ; iter++, number++)
   {
       cout << "Line" << number << ":" << endl;
       (*iter).PrintAllNodeInfo(); 
   }
}

void CSVParseComma::FillNodeForNodeInfo(void)
{
    vector<string>::const_iterator iter;
    iter = Node.cbegin();
    int blank_pos;
    struct NodeInfo ninfo;
    if(iter != Node.cend())
    {
        string temp_str(*iter);
        blank_pos = temp_str.find(" ",0);
        string str_date(temp_str,0, blank_pos);
        string str_time(temp_str,blank_pos+1,temp_str.length());
        ninfo.Date = str_date;
        YearNode = str_date.substr(0,7);
        DateNode = str_date.substr(8,9);
        ninfo.Time = str_time;
        iter++;
    }
    if(iter != Node.cend())
        ninfo.Module = *iter++;
    if(iter != Node.cend())
        ninfo.Level = *iter++;
    if(iter != Node.cend())
        ninfo.Message = *iter++;
    if(iter == Node.cend())
        infoNode.push_back(ninfo);
}

void CSVParseComma::PrintAllNodeInfo(void)
{
    vector<NodeInfo>::const_iterator iter;
    for(iter = infoNode.cbegin(); iter != infoNode.cend() ; iter++)
    {
        cout << "Node Info is:" << endl;
        cout << "Date:" << (*iter).Date << endl;
        cout << "Time:" << (*iter).Time << endl;
        cout << "Module:" << (*iter).Module << endl;
        cout << "Level:" << (*iter).Level << endl;
        cout << "Message:" << (*iter).Message << endl;
    }

}
