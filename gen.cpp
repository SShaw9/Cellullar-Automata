#include <iostream>
#include <string>
#include <vector>

#define K 256
std::vector<std::string> ruleLT[K][K];
std::vector<std::string> rules;

std::vector<std::string>GenElemRules(int k)
{
    std::string str;
    for (int len=1; len<=k; len++)
    {
        str = str + "0";
        ruleLT[len][0].push_back(str);
    }
    rules.push_back(str);

    for(int len=1; len<=k; len++)
    {
        for(int n=1; n<=len; n++)
        {
            for(std::string str : ruleLT[len-1][n])
                ruleLT[len][n].push_back("0"+str);
            for(std::string str : ruleLT[len-1][n-1])
                ruleLT[len][n].push_back("1"+str);
        }
    }

    for (int n = 1; n <= k; n++)
    {
        for (std::string str : ruleLT[k][n])
        {
            rules.push_back(str);
        }
    }

    return rules;
}
