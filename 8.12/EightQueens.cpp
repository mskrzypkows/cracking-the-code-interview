#include <iostream>
#include <stdexcept>

/*
 * My solution to 8.12 Eight Queens task
 * It's much faster than book's solution, but implementation is a bit harder and timeconsuming.
 */

class Board
{
    static constexpr int BOARD_SIZE = 8;
    int captureGrid[BOARD_SIZE][BOARD_SIZE] = {};
    int queensGrid[BOARD_SIZE][BOARD_SIZE] = {};
    int nodesCounter = 0;

    void markBackSlashDiagonal(int row, int col, int value)
    {
        int rowBegin = row > col ? row - col : 0;
        int colBegin = col > row ? col - row : 0;

        while (rowBegin < BOARD_SIZE && colBegin < BOARD_SIZE) {
                captureGrid[rowBegin++][colBegin++] += value;
        }
        captureGrid[row][col] -= value;
    }

    void markSlashDiagonal(int row, int col, int value)
    {
        {
            int rowBegin = row;
            int colBegin = col;
            while (rowBegin < BOARD_SIZE && col > 0)
                captureGrid[rowBegin++][colBegin--] += value;
        }
        {
            int rowBegin = row;
            int colBegin = col;
            while (rowBegin >= 0 && col < BOARD_SIZE)
                captureGrid[rowBegin--][colBegin++] += value;
        }

        captureGrid[row][col] -= value;
    }

    void markCross(int row, int col, int value)
    {
        for (int c = 0; c<BOARD_SIZE; ++c)
        {
            captureGrid[row][c] += value;
        }

        for (int r = 0; r < BOARD_SIZE; ++r)
        {
            captureGrid[r][col] += value;
        }
        captureGrid[row][col] -= 2  * value;
    }

    void findQueenPossition(int col)
    {
        if ( col == BOARD_SIZE )
        {
            print();
            return;
        }

        ++nodesCounter;

        for (int row = 0; row < BOARD_SIZE; ++row)
        {
            if (captureGrid[row][col] == 0) {
                markAllQueensCapturedFiels(row, col, true);
                findQueenPossition(col+1);
                markAllQueensCapturedFiels(row, col, false);
            }
        }
    }

    void markQueen(int row, int col, bool addQueen)
    {
        queensGrid[row][col] = addQueen ? 1 : 0;
    }

    void print() const
    {
        std::cout<< std::endl;
        for(int row = 0; row<BOARD_SIZE; ++row)
        {
            for (int col=0; col<BOARD_SIZE; ++col)
            {
                std::cout<< "|" << (queensGrid[row][col] > 0 ? '+' : '.');
            }
            std::cout<<"|" << std::endl;
        }
    }

public:


    void printIterationsNumber() const
    {
        std::cout<<"\nVisisted only " << nodesCounter << " nodes! :-)\n\n";
    }

    void markAllQueensCapturedFiels(int row, int col, bool positive)
    {
        int value = positive ? 1 : -1;
        markCross(row, col, value);
        markBackSlashDiagonal(row, col, value);
        markSlashDiagonal(row, col, value);
        markQueen(row, col, positive);
    }

    void findQueensPossitions()
    {
        findQueenPossition(0);
    }

    void testMarkingCapturedFields()
    {
        markAllQueensCapturedFiels(2,5, true);
        markAllQueensCapturedFiels(2,5, false);
        for(int row = 0; row<BOARD_SIZE; ++row)
        {
            for (int col=0; col<BOARD_SIZE; ++col)
            {
                if (captureGrid[row][col] != 0)
                    throw std::logic_error(
                        "Wrong value for unsetting attacked field in position: " +
                        std::to_string(row) + ", " + std::to_string(col)
                    );
            }
        }
    }

};

int main()
{
    Board board;
    board.testMarkingCapturedFields();

    board.findQueensPossitions();
    board.printIterationsNumber();

    return 0;
}
