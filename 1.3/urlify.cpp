#include <iostream>
#include <string>



std::pair<int, int> getNumberOfSpacesInTheString(std::string & input)
{
    int counter = 0;
    int lastNotSpaceChar = 0;

    bool foundFirstNotSpaceChar = false;
    size_t firstNotSpaceChar = 0;
    for (auto i = input.size() - 1; i>0; --i)
    {
        if( input[i] != ' ')
        {
            if (!foundFirstNotSpaceChar) {
                foundFirstNotSpaceChar = true;
                firstNotSpaceChar = i;
            }
        } else if (foundFirstNotSpaceChar) {
            ++counter;
        }
    }

    return std::make_pair(counter, firstNotSpaceChar);
}

std::string URLify(std::string input) {
    auto [numberOfSpaces, firstNotSpaceChar] = getNumberOfSpacesInTheString(input);
    input.resize(firstNotSpaceChar + 1 + numberOfSpaces * 2);

    size_t newIndex = input.size() - 1;
    for (size_t i = firstNotSpaceChar; i>0; --i)
    {
        if (input[i] == ' ') {
            input[newIndex-2] = '%';
            input[newIndex-1] = '2';
            input[newIndex] = '0';
            newIndex -= 3;

            //if no mor space left return
        } else {
            input[newIndex--] = input[i];
        }
    }

    return input;
}

//  0123456789
// "some strrr"
//      %20str"
// i = 4
// newIndex = 6
//
// i = 3
// newIndex = 3;

int main()
{
    std::string s("some string with spaces    ");
    std::cout<<"Valid spaces in the string: " << getNumberOfSpacesInTheString(s).first <<std::endl;
    std::cout<<URLify(s)<<std::endl;

    return 0;
}
