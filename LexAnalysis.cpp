#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include "LexAnalysis.h" 

int main(int argc, char* argv[])
{

    FILE* frd;
    FILE* fwt;
    frd = fopen(argv[1], "r");
    fwt = fopen(argv[2], "w");
    char lineBuffer[1024];
    
    std::vector<std::vector<Token>> tokens;
    std::unordered_map<std::string, int> tokenstemp;
    
    int ret;
    size_t num_rules = sizeof(rules) / sizeof(rules[0]);
    regex_t regex[num_rules];
    for(int i = 0; i < num_rules; i++){
        ret = regcomp(&regex[i], rules[i].regex, REG_EXTENDED);
        if(ret) {
            printf("regex error\n");
            abort();
        }
    }

    int line = 0;

    while (fgets(lineBuffer, sizeof(lineBuffer), frd)) {
        std::vector<Token> tempv;  //源文件每一行初始化一个Token向量
        tokens.push_back(tempv); 
        regmatch_t pmatch[1];
        int ttl = 100;
        char* offset = lineBuffer; //offset指向字符串头
        while(*offset != 0){
            for(int i = 0; i < num_rules; i++){  //与每个规则匹配
                if(regexec(&regex[i], offset, 1, pmatch, 0) == 0 && pmatch->rm_so == 0) {
                    Token temp;
                    strncpy(temp.data, offset, pmatch->rm_eo-pmatch->rm_so);
                    temp.data[pmatch->rm_eo-pmatch->rm_so] = 0;
                    if(rules[i].toke_type == Identifiers_t) {    //若类型是标识符，则在标识符表中查询，生成Token
                        auto it = tokenstemp.find(temp.data);
                        if(it != tokenstemp.end())
                            temp.type = tokenstemp[temp.data];
                        else {
                            tokenstemp[temp.data] = tempindex;
                            temp.type = tempindex;
                            tempindex++;
                        }
                    } else                                     
                        temp.type = rules[i].toke_type;
                    if(rules[i].toke_type != space_t)       //删除已匹配部分
                        tokens[line].push_back(temp);
                    offset += pmatch->rm_eo-pmatch->rm_so;
                    break;
                }
            }
            ttl--;
        }
        line++;
    }
    
    for(int i = 0;i < line;i++)
        for(int j = 0; j < tokens[i].size();j++)
            printf("%s   , %d\n", tokens[i][j].data, tokens[i][j].type);
    printf("#   , 0\n");
    return 0;
}
