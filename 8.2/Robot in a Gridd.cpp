#include <iostream>
#include <vector>
#include <algorithm>

constexpr int ROWS = 5;
constexpr int COLS = 5;
constexpr int TRAP = 1;

constexpr int grid[ROWS][COLS] = {
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,0,1},
    {1,1,1,0,0},
    {0,0,0,0,0}
};

void printGrid()
{
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            std::cout<<std::to_string(grid[r][c]) <<" ";
        }
        std::cout<<std::endl;
    }
}

struct Cell
{
    Cell(int row, int col) :r(row), c(col) {}
    int r;
    int c;

    bool operator==(const Cell & other)
    {
        return r == other.r && c == other.c;
    }
};

bool findPath(std::vector<Cell> & path, Cell cell)
{
    if (cell == Cell(ROWS-1, COLS-1) ) {
        path.push_back(cell);
        return true;
    }

    if (cell.c >= COLS || cell.r >=ROWS || grid[cell.r][cell.c] == TRAP)
        return false;

    if (findPath(path, Cell(cell.r, cell.c + 1)) || findPath(path, Cell(cell.r+1, cell.c))) {
        path.push_back(cell);
        return true;
    }

    return false;
}

void printPath(const std::vector<Cell> & path)
{
    std::for_each(path.rbegin(), path.rend(), [](const auto & cell) {
        std::cout<<"(" <<cell.r << "," << cell.c << "), ";
    });
    std::cout<<std::endl;
}

int main()
{
    printGrid();

    std::vector<Cell> path;
    findPath(path, Cell(0,0));

    if (path.size() > 0)
        printPath(path);

    return 0;
}
