/*
 * =====================================================================================
 *
 *       Filename:  NodeManagerment.h
 *
 *    Description:  CSV Node文件的管理类
 *
 *        Version:  1.0
 *        Created:  30/03/16 08:58:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class NodeManagerment
{
public:
    NodeManagerment(){}
    ~NodeManagerment(){}
    void ParseNodeToMap(const CSVParseLine CSVPl);
public:
    map<string,vector<string>> NodeMap;
};
