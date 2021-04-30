#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using CharacterMap = std::unordered_map<char, int>;

void AddPermutationsRecursive(CharacterMap & charactersCount, const std::string & prefix, std::vector<std::string> & permutations, int charactersLeft)
{
    if (charactersLeft == 0)
    {
        permutations.emplace_back(prefix);
        return;
    }

    for (auto & pair : charactersCount)
    {
        if (pair.second == 0)
            continue;

        pair.second--;
        AddPermutationsRecursive(charactersCount, prefix + pair.first, permutations, charactersLeft - 1);
        pair.second++;
    }
}


std::vector<std::string> CalculatePermutations(const std::string & input)
{
    std::vector<std::string> permutations;
    CharacterMap charactersCount;

    for (const auto & character : input)
    {
        if (charactersCount.find(character) == charactersCount.end())
            charactersCount[character] = 1;
        else
            charactersCount[character] += 1;
    }


    AddPermutationsRecursive(charactersCount, "", permutations, input.length());

    return permutations;
}

int main()
{
    std::string input("aaaaaaaaaaaaaaac");
    auto permutations = CalculatePermutations(input);

    for( const auto & str : permutations)
    {
        std::cout<<str<<"\n";
    }

    return 0;
}
