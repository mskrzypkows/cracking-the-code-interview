#include <iostream>
#include <cassert>
#include <vector>


class Tower
{
    std::vector<int> tower;
public:
    void push(int disk)
    {
        tower.push_back(disk);
    }

    void moveDiskTo(Tower & destination)
    {
        assert(tower.size() > 0);
        destination.push(tower.back());
        tower.pop_back();
    }

    int disks() {
        return tower.size();
    }

    void print() const
    {
        for( auto it = tower.crbegin(); it != tower.crend(); ++it)
        {
            std::cout<< *it <<std::endl;
        }
    }
};

void printTowers(std::vector<Tower> & towers)
{
    int counter = 0;
    for (const auto & t : towers)
    {
        std::cout<< "Tower " << counter++ << ":\n";
        t.print();
    }
}

void moveDisks(Tower & source, Tower & destination, Tower & buffer, int numberOfDisksToMove)
{
    if (source.disks() == 0 || numberOfDisksToMove == 0)
        return;
    moveDisks(source, buffer, destination, numberOfDisksToMove - 1);
    source.moveDiskTo(destination);
    moveDisks(buffer, destination, source, numberOfDisksToMove - 1);
}

int main()
{
    std::vector<Tower> towers(3);
    towers[0].push(8);
    towers[0].push(7);
    towers[0].push(6);
    towers[0].push(5);
    towers[0].push(4);
    towers[0].push(3);
    towers[0].push(2);
    towers[0].push(1);

    printTowers(towers);

    moveDisks(towers[0], towers[2], towers[1], towers[0].disks());

    printTowers(towers);

    return 0;
}
