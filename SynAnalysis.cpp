#include <iostream>
#include <cstring>
#include <vector>
// #include <string>
#include <stack>
#include "SynAnalysis.h"
#include "LexAnalysis.h"

int gettablerow(char* a);
int gettablecol(char* a);
int getsize(char** a);
void show(Node* head, char* pre);
Node* getleftchild(Node* head);
void switchshow(Node* temp);
void popexpress();

std::stack<char*> express;
int lable = 1;
int index1 = 0;
int line = 1;
// int deep = 0;

int main(int argc,char *argv[])
{
    std::stack<char*> fenxiStack;
    std::stack<elem> yuyanStack;
    
    
    std::stack<elem> tempa;
    FILE* frd;
    frd = fopen("hello.txt", "r");
    char lineBuffer[100];
    while (fgets(lineBuffer, sizeof(lineBuffer), frd)) {
        elem temp;
        int result = sscanf(lineBuffer, "%s   , %d", temp.str, &temp.type);
        tempa.push(temp);
    }

    while (!tempa.empty()) {
        yuyanStack.push(tempa.top());
        printf("%s\n",tempa.top().str);
        printf("%d\n",tempa.top().type);
        tempa.pop();
    }
    
    fenxiStack.push("#");
    fenxiStack.push("E");
    std::stack<Node*> Stack;
    Node* head = new Node;
    strcpy(head->ele.str, "#");
    head->ele.type = 0;
    Node* temp = new Node;
    head->child.push_back(temp);
    strcpy(temp->ele.str, "E");
    head->ele.type = 0;
    Stack.push(head);
    Stack.push(temp);

    char* tempFenxi = "e";
    elem tempYuyan;
    strcpy(tempYuyan.str, "e");
    tempYuyan.type = 0;
    while (strcmp(tempFenxi,"#"))
    {
        tempFenxi = fenxiStack.top();
        Node* now = Stack.top();
        printf("stack top %s\n",now->ele.str);
        tempYuyan = yuyanStack.top();
        if (strcmp(tempFenxi,tempYuyan.str) == 0 || (tempFenxi == "v" && tempYuyan.type >= 63) \
            || (tempFenxi == "u" && tempYuyan.type == 4))
        {          //比较两栈栈顶元素，若同为终结符且相等，则出栈；对应语法树栈也出栈
            fenxiStack.pop();
            yuyanStack.pop();
            Stack.pop();
            printf("pop %s\n", tempFenxi);
        } else if(strcmp(tempFenxi,"e") == 0) {
            fenxiStack.pop();   //如果文法推导出空字符，则分析栈直接出栈；对应语法树栈也出栈
            Stack.pop();
        } else {                //如果分析栈中为非终结符，则根据分析表将产生式右部入栈
            Stack.pop();
            fenxiStack.pop();
            printf("pop %s\n", tempFenxi);
            int row = gettablerow(tempFenxi);
            int col;
            if(tempYuyan.type >= 63)
                col = gettablecol("v");
            else if(tempYuyan.type == 4)
                col = gettablecol("u");
            else
                col = gettablecol(tempYuyan.str);
            if(row == -1) {     //错误处理
                printf("NO\n");
                return 0;
            }
            if(temp == NULL) {
                printf("NO\n");
                return 0;
            }
            if(test[row][col] == nullptr) {
                printf("NO\n");
                return 0;
            }
            char** temp = test[row][col];
            int i = getsize(temp)-1;
            for (i; i >= 0; i--)      //将产生式右边依次入栈；语法树栈同时入栈，并建立对应树结构
            {
                Node* new1 = new Node;
                fenxiStack.push(temp[i]);
                if(temp[i] == "v" || temp[i] == "u")
                    new1->ele = tempYuyan;
                else {
                    strcpy(new1->ele.str, temp[i]);
                    new1->ele.type = 0;
                }
                now->child.push_back(new1);
                Stack.push(new1);
                printf("push %s\n", temp[i]);
            }
        }
    }
    printf("YES");
    printf("\n");
    char pre[256];
    show(head, pre);
    Node* aaa = getleftchild(head);
    // for(int i = 0; i < aaa->child.size();i++)
    //     printf("%s\n",aaa->child[i]->str);
    // switchshow(aaa);
    
    do 
    {
        switchshow(aaa);
        aaa = getleftchild(head);
        /* code */
    } while (aaa->ele.str[0] != '#');
    
    return 0;
}

int gettablerow(char* a) 
{
    int i = sizeof(tablerow) / 8 - 1;
    printf("gettablerow %d %s\n", i, a);
    for (i; i >= 0; i--)
    {
        if (strcmp(a,tablerow[i]) == 0)
            return i;
    }
    return -1;
}

int gettablecol(char* a) 
{
    int i = sizeof(tablecol) / 8 - 1;
    printf("gettablecol %d %s\n", i, a);
    for (i; i >= 0; i--)
    {
        if (strcmp(a,tablecol[i]) == 0)
            return i;
    }
    return -1;
}

int getsize(char** a)
{
    int i = 0;
    char** b = a;
    while (*b != nullptr) {
        i++;
        b++;
    }
    return i;    
}

void show(Node* head, char* pre)
{
    char str1[256] = "  |";
    char str2[256] = "   ";
    char temp[256];
    strcpy(temp, pre);
    for(int i = 0; i < head->child.size(); i++) {
        if(i == head->child.size()-1) {
            printf("%s%s--%s\n", temp, str1, head->child[i]->ele.str);
            strcat(pre, str2);
        } else {
            printf("%s%s--%s\n", temp, str1, head->child[i]->ele.str);
            strcat(pre, str1);
        }
        show(head->child[i], pre);
        strcpy(pre, temp);
    }
}

Node* getleftchild(Node* head) 
{
    int sum = 0;
    // Node* temp = *(head->child.end()-1);
    for(int i = 0; i < head->child.size(); i++) {
        if(head->child[i]->child.size() == 0)
            sum++;
    }
    if(sum == head->child.size())
        return head;
    // if(temp->child.size() == 0)
    //     return head;
    else {
        for(int i = head->child.size()-1; i >= 0; i--) {
            if(head->child[i]->child.size() != 0)
                return getleftchild(head->child[i]);
        }
    }
}

void switchshow(Node* temp) 
{     //根据属性文法自底向上完成中间代码生成
    if(strcmp(temp->ele.str, "D") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "do") == 0) {
        temp->ele.deep = (*(temp->child.end()-7))->ele.deep + (*(temp->child.end()-3))->ele.deep;
        printf("if ( %s ) goto lable %d\n", (*(temp->child.end()-7))->ele.mes, line - temp->ele.deep);
    }
    if(strcmp(temp->ele.str, "E") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "O") == 0) {
        temp->ele.deep = (*(temp->child.end()-1))->ele.deep + (*(temp->child.end()-2))->ele.deep;
    }
    if(strcmp(temp->ele.str, "E") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "D") == 0) {
        temp->ele.deep = (*(temp->child.end()-1))->ele.deep + (*(temp->child.end()-2))->ele.deep;
    }
    else if(strcmp(temp->ele.str, "Y") == 0 && (*(temp->child.end()-1))->ele.type >= 63) {
        strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.str);
    }
    else if(strcmp(temp->ele.str, "Y") == 0 && (*(temp->child.end()-1))->ele.type == 4) {
        strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.str);
    }
    else if(strcmp(temp->ele.str, "Y") == 0 && strcmp((*(temp->child.end()-1))->ele.str,"(")) {
        strcpy(temp->ele.mes, (*(temp->child.end()-2))->ele.mes);
    }
    else if(strcmp(temp->ele.str, "X1") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "e") == 0) {
        strcpy(temp->ele.mes, "e");
    }
    else if(strcmp(temp->ele.str, "X1") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "M") == 0) {
        if(strcmp((*(temp->child.end()-3))->ele.mes, "e") != 0) {
            printf("%d: T%d = %s%s", line, index1, (*(temp->child.end()-2))->ele.mes, (*(temp->child.end()-3))->ele.mes);
            index1 ++;
            line ++;
            temp->ele.deep = (*(temp->child.end()-1))->ele.deep + 1;
            sprintf(temp->ele.mes, "%sT%d", (*(temp->child.end()-1))->ele.mes, index1);
        }   
        else 
        {
            sprintf(temp->ele.mes, "%s%s", (*(temp->child.end()-1))->ele.mes,(*(temp->child.end()-2))->ele.mes);
            temp->ele.deep = (*(temp->child.end()-2))->ele.deep;
        }
    }
    else if(strcmp(temp->ele.str, "X") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "Y") == 0) {
        if(strcmp((*(temp->child.end()-2))->ele.mes, "e") == 0)
            strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.mes);
        if((*(temp->child.end()-2))->ele.mes[0] == '*' || (*(temp->child.end()-2))->ele.mes[0] == '/')
        {
            printf("%d: T%d = %s%s\n", line, index1, (*(temp->child.end()-1))->ele.mes, (*(temp->child.end()-2))->ele.mes);
            sprintf(temp->ele.mes, "T%d", index1);
            temp->ele.deep = (*(temp->child.end()-1))->ele.deep + 1;
            index1 ++;
            line ++;
        }
        else {
            strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.mes);
            temp->ele.deep = (*(temp->child.end()-1))->ele.deep;
        }
    }
    else if(strcmp(temp->ele.str, "P1") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "e") == 0) {
        strcpy(temp->ele.mes, "e");
    }
    else if(strcmp(temp->ele.str, "P") == 0 && strcmp((*(temp->child.end()-1))->ele.str, "X") == 0) {
        if(strcmp((*(temp->child.end()-2))->ele.mes, "e") == 0)
            strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.mes);
        if((*(temp->child.end()-2))->ele.mes[0] == '+' || (*(temp->child.end()-2))->ele.mes[0] == '-')
        {
            printf("%d: T%d = %s%s\n", line, index1, (*(temp->child.end()-1))->ele.mes, (*(temp->child.end()-2))->ele.mes);
            sprintf(temp->ele.mes, "T%d", index1);
            temp->ele.deep = (*(temp->child.end()-1))->ele.deep + 1;
            index1 ++;
            line ++;
        }
        else {
            strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.mes);
            temp->ele.deep = (*(temp->child.end()-1))->ele.deep;
        }
    }
    else if(strcmp(temp->ele.str, "O") == 0 && (*(temp->child.end()-1))->ele.type >= 63) {
        printf("%d: ", line);
        line ++;
        temp->ele.deep = (*(temp->child.end()-3))->ele.deep + 1;
        printf((*(temp->child.end()-1))->ele.str);
        printf(" = ");
        printf((*(temp->child.end()-3))->ele.mes);
        printf("\n");
    }
    else if(strcmp(temp->ele.str, "P1") == 0 && strcmp(temp->ele.str, "A")) {
        if(strcmp((*(temp->child.end()-3))->ele.mes, "e") != 0) {
            printf("%d: T%d = %s%s", line, index1, (*(temp->child.end()-2))->ele.mes, (*(temp->child.end()-3))->ele.mes);
            index1 ++;
            line ++;
            temp->ele.deep = (*(temp->child.end()-3))->ele.deep + 1;
            sprintf(temp->ele.mes, "%sT%d", (*(temp->child.end()-1))->ele.mes, index1);
        }   
        else 
        {
            sprintf(temp->ele.mes, "%s%s", (*(temp->child.end()-1))->ele.mes,(*(temp->child.end()-2))->ele.mes);
            temp->ele.deep = (*(temp->child.end()-2))->ele.deep;
        }
    }
    else if(strcmp(temp->ele.str, "A") == 0) {
        strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.str);
    }
    else if(strcmp(temp->ele.str, "M") == 0) {
        strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.str);
    }
    else if(strcmp(temp->ele.str, "B") == 0) {
        strcpy(temp->ele.mes, (*(temp->child.end()-1))->ele.str);
    }
    else if(strcmp(temp->ele.str, "Q") == 0) {
        printf("%d: T%d = %s %s %s\n",line, index1, (*(temp->child.end()-1))->ele.mes, (*(temp->child.end()-2))->ele.mes, (*(temp->child.end()-3))->ele.mes);
        sprintf(temp->ele.mes, "T%d", index1);
        temp->ele.deep = (*(temp->child.end()-1))->ele.deep + 1 + (*(temp->child.end()-2))->ele.deep;
        index1 ++; 
        line ++;
    }
    int num = temp->child.size();
    for(int i = 0; i < num; i++)
        temp->child.pop_back();
}

void popexpress()
{
    while (express.size()>=3)
    {
        char* a = express.top();
        express.pop();
        char* b = express.top();
        express.pop();
        char* c = express.top();
        express.pop();
        printf("T%d = %s %s %s\n", index1, c, b, a);
        char* temp = new char[10];
        sprintf(temp,"T%d",index1);
        index1++;
        express.push(temp);
    }
}