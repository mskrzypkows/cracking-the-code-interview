#include <iostream>
#include <string>
#include <vector>
#include <algorithm>





void AddPermutationsRecursive(const std::string & prefix, const std::string & suffix, std::vector<std::string> & permutations)
{
    if (suffix.length() == 1)
    {
        permutations.emplace_back(prefix + suffix);
        return;
    }

    for (const auto & character: suffix)
    {
        std::string copyOfSuffix(suffix);
        copyOfSuffix.erase(copyOfSuffix.find(character), 1);// std::find(copyOfSuffix.cbegin(), copyOfSuffix.cend(), character));
        AddPermutationsRecursive(prefix + character, copyOfSuffix, permutations);
    }
}


void AddPermutations(const std::string & input, std::vector<std::string> & permutations)
{
    AddPermutationsRecursive(std::string(), input, permutations);
}

int main()
{
    std::vector<std::string> permutations;

    std::string input("abc");//defghijk");
    AddPermutations(input, permutations);

    for( const auto & str : permutations)
    {
        std::cout<<str<<"\n";
    }

    return 0;
}
