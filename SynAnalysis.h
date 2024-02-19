#include <string>
#include <vector>

struct elem
{
    char str[10];
    char mes[10];
    // char message[256];
    int deep;
    int type;
};

struct Node
{
    std::vector<Node*> child;
    elem ele;
};


char* tablecol[] = {"#","+","-","*","/","!","u","v","(",")",">","<","do","while","{","}",";"};
char* tablerow[] = {"E","D","O","Q","P","P1","X","X1","Y","A","M","B"};

char* E1[] = {"O","E",nullptr};
char* E2[] = {"D","E",nullptr};
char* E3[] = {"e",nullptr};
char* D1[] = {"do","{","E","}","while","(","Q",")",nullptr};
char* O1[] = {"v","=","P",";",nullptr};
char* Q1[] = {"P","B","P",nullptr};
char* P1[] = {"X","P1",nullptr};
char* PA1[] = {"e",nullptr};
char* PA2[] = {"A","X","P1",nullptr};
char* X1[] = {"Y","X1",nullptr};
char* XA1[] = {"e",nullptr};
char* XA2[] = {"M","Y","X1",nullptr};
char* Y1[] = {"u",nullptr};
char* Y2[] = {"v",nullptr};
char* Y3[] = {"(","P",")",nullptr};
char* Y4[] = {">",nullptr};
char* Y5[] = {"<",nullptr};
char* Y6[] = {"do",nullptr};
char* Y7[] = {"while",nullptr};
char* Y8[] = {"{",nullptr};
char* Y9[] = {"}",nullptr};
char* A1[] = {"+",nullptr};
char* A2[] = {"-",nullptr};
char* M1[] = {"*",nullptr};
char* M2[] = {"/",nullptr};
char* B1[] = {">",nullptr};
char* B2[] = {"<",nullptr};

char** test[13][18] = 
    {{E3,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,E1,nullptr,nullptr,nullptr,nullptr,E2,nullptr,nullptr,E3,nullptr},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,D1,nullptr,nullptr,nullptr,nullptr},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,O1,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,Q1,Q1,Q1,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,P1,P1,P1,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {PA1,PA2,PA2,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,PA1,PA1,PA1,nullptr,nullptr,nullptr,PA1,PA1},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,X1,X1,X1,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {XA1,XA1,XA1,XA2,XA2,nullptr,nullptr,nullptr,nullptr,XA1,XA1,XA1,nullptr,nullptr,nullptr,XA1,XA1},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,Y1,Y2,Y3,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {nullptr,A1,A2,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {nullptr,nullptr,nullptr,M1,M2,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
    {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,B1,B2,nullptr,nullptr,nullptr,nullptr,nullptr}}; 

