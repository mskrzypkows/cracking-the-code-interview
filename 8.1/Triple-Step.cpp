#include <iostream>

/*
 * Przetestowałem na do 30 i zgadza się z rozwiązaniem książkowym, a moje jest liniowe, ich chyba coś ok. n².
 * Ale jaja zrobiłem lepsze rozwiązanie niż w książce :D
 */

int Count(int n)
{
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;
    if (n == 3) return 4;

    int oneStep = 4;
    int twoSteps = 2;
    int threeSteps = 1;

    for (int i=4; i <=n;++i)
    {
        int counter = oneStep + twoSteps + threeSteps;

        threeSteps = twoSteps;
        twoSteps = oneStep;
        oneStep = counter;
    }

    return oneStep;
}


int main()
{
    std::cout<<"My solution: \n";
    for (int i=0; i < 30; ++i)
        std::cout<<Count(i)<<std::endl;

    return 0;
}
