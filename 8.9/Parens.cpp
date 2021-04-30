#include <iostream>
#include <vector>
#include <string>




void SearchForParensCombinations(int openedParens, int closedParens, int n, std::string combination, std::vector<std::string> & results)
{
    if (closedParens == n)
    {
        results.emplace_back(combination);
        return;
    }

    if (openedParens < n)
    {
        SearchForParensCombinations(openedParens + 1, closedParens, n, combination + '(' , results);
    }

    if (openedParens > closedParens )
    {
        SearchForParensCombinations(openedParens, closedParens + 1, n, combination + ')', results);
    }
}

void printCombinations( const std::vector<std::string> & parens)
{
    for( const auto & s: parens)
    {
        std::cout<<s<<std::endl;
    }
}

int main()
{
    std::vector<std::string> parens;
    SearchForParensCombinations(0,0,4,"",parens);
    printCombinations(parens);

    return 0;
}
