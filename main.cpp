/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  主进程函数
 *
 *        Version:  1.0
 *        Created:  29/03/16 13:27:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  leafji 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include "CSVParse.h"
#include "NodeManagerment.h"
using namespace std;

enum SHOW_TYPE
{
    SHOW_BY_DATE,
    SHOW_BY_YEAR_MONTH,
    SHOW_BY_YEAR
};

static struct option long_options[] = {
    {"filename",required_argument,NULL,'f'},
    {"showbydate",no_argument,NULL, 'd'},
    {"help",no_argument,NULL,'h'},
};

void usage(void)
{
    cout << "This Program is used for csv logshow!!" << endl;
    cout << "--filename/-f   [the csv log file pathname here]" << endl;
    cout << "--showbydate/-d [show log group by date]" << endl;
    cout << "--help/-h       [show help message ]" << endl;

}

int main(int argc, char* argv[])
{
    int opt;
    int option_index;
    const char *optstr = "dhf:";
    string filename;
    int show_format;
    CSVParseLine csv;
    NodeManagerment nmgnt;
    while((opt = getopt_long(argc,argv,optstr,long_options,&option_index)) != -1)
    {
        switch(opt)
        {
            case 'f':
                printf("filename is %s\n",optarg);
                filename = optarg;            
                break;
            case 'd':
                printf("show by date!!\n");
                show_format = SHOW_BY_DATE;
                break;
            case 'h':
                usage();
                break;
            default:
                printf("Not support options arguments:%s !!!\n",optarg);
                exit(-1);
        }

    }
    csv.Load(filename);
    csv.ParseString();
    csv.FillNodeForComma();
    nmgnt.GroupNodeByYearMonth(csv);
    if(show_format == SHOW_BY_DATE)
        nmgnt.ShowNodeMapByYearMonthDay();
    return 0;
}

