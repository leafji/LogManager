/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  29/03/16 13:27:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
//#include "CSVParse.h"
#include "NodeManagerment.h"
using namespace std;

int main(int argc, char* argv[])
{
    CSVParseLine csv;
    csv.Load("log.csv");
    csv.ParseString();
    csv.FillNodeForComma();
    NodeManagerment nmgnt;
    nmgnt.GroupNodeByYearMonth(csv);
    nmgnt.ShowNodeMapByYearMonthDay();
    return 0;

}

