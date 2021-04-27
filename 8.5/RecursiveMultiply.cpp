#include <iostream>

int minProductRecursive(int smaller, int bigger)
{
    if (smaller == 0)
        return 0;
    if (smaller == 1)
        return bigger;

    auto half = smaller >> 1;
    auto halfResult = minProductRecursive(half, bigger);
    if (smaller % 2 == 0)
        return halfResult + halfResult;
    else
        return halfResult + halfResult + bigger;
}

int minProduct(int first, int second)
{
    return minProductRecursive(std::min(first,second), std::max(first, second));
}


int main()
{

    std::cout<<minProduct(35, 23)<<std::endl;

    return 0;
}
