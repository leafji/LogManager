/*
 * =====================================================================================
 *
 *       Filename:  CSVParse.h
 *
 *    Description:  CSVParse文件父类可以将文件按照类型切分
 *
 *        Version:  1.0
 *        Created:  29/03/16 09:51:29
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  leafji 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _CSVPARSE_H_
#define _CSVPARSE_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

struct NodeInfo
{
    string Date;
    string Time;
    string Module;
    string Level;
    string Message;
};


class CSVParse
{
public:
    CSVParse(){
        separate = "\n";
        content =  "";
    }
    CSVParse(const string sep, const string cnt)
    {
        separate = sep;
        content = cnt;
    }
    ~CSVParse(){}
    void Load(const string& filepathname);
    bool IsValid(const string& filepathname);
    void ParseString(void);
    void PrintNode(void);
public:
    string separate; // 代表分隔符变量
    string content; // 被解析的string变量
    vector<string> Node;  //被切分后的节点容器
};

class CSVParseComma : public CSVParse
{
public:
    CSVParseComma(const string sep, const string cnt):CSVParse(sep,cnt){}
    void FillNodeForNodeInfo(void);
    void PrintAllNodeInfo(void);
    string getYearNode(void){return YearNode;}
    string getDateNode(void){return DateNode;}
    vector<NodeInfo> getInfoNode(void){return infoNode;}
private:
    vector<NodeInfo> infoNode;
    string YearNode;
    string DateNode;
};


class CSVParseLine:public CSVParse
{
public:
    void FillNodeForComma(void);
    void PrintAllLine(void);
    vector<CSVParseComma> getNodeComma(void){return NodeComma;}
private:
    vector<CSVParseComma> NodeComma;
    map<string,vector<string> > NodeMap;
};
#endif


