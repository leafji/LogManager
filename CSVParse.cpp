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
 *         Author:  leafji
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "CSVParse.h"
#include <fstream>
/*
 * IsValid:判断filepathname是否为csv文件。
 */
bool CSVParse::IsValid(const string& filepathname)
{
    return 1;
}
/* 
 * Load 读取filepathname的csv 文件，将流转入content中
 * 
 */

void CSVParse::Load(const string& filepathname)
{
    ifstream csv_file;
    int length;
    char* buffer;
    if(IsValid(filepathname))
    {
        csv_file.open(filepathname,ios::in);
        if(!csv_file )
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
        if(!content.length())
        {
            cout<<"csv file is empty!!" <<endl;
            exit(-1);
        }
        delete buffer;
        csv_file.close();   
    }
    else
    {
        cout<<"Not a regular CSV file, exit!!"<<endl;
        exit(-1);
    }
    
}

/* 
 * ParseString: 根据separate 将content进行切分
 * 保存到 vector<string> Node 中
 */
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
/* 
 *  FillNodeForComma: 根据切分后的Node，每一个Node对应一行信息
 *  将每个Node,建立一个CSVParseComma对象，并调用ParseString，进一步切分
 * */
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
/* 
 *
 *
 * */
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
/* *
 * 将每行的信息根据separate（“，”）切分，切分后以infoNode存储
 *
 * */
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
/* *
 *  打印出NodeInfo这个vector中的每个信息，
 *  以date time module...等分类显示
 *
 * */
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
