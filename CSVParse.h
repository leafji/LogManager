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
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CSVPARSE_H_
#define CSVPARSE_H_
#endif

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
        cout<<"CSVParse init enter"<<endl;
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
    void ParseString(void);
    void PrintNode(void);
public:
    string separate;
    string content;
    vector<string> Node;
};

class CSVParseComma : public CSVParse
{
public:
    CSVParseComma(const string sep, const string cnt):CSVParse(sep,cnt){}
    void FillNodeForNodeInfo(void);
    void PrintAllNodeInfo(void);
public:
    vector<NodeInfo> infoNode;
    string YearNode;
    string DateNode;
};


class CSVParseLine:public CSVParse
{
public:
    void FillNodeForComma(void);
    void PrintAllLine(void);
    void GroupNodeLine(void);
    void ShowNodeMap(void);
    vector<CSVParseComma> getNodeComma(void){return NodeComma;}
private:
    vector<CSVParseComma> NodeComma;
    map<string,vector<string> > NodeMap;
};


