#include <bits/stdc++.h>

using namespace std;
class sudoku_cracker
{
private:
    vector<vector<char>> board;

    bool isvalid(vector<vector<char>> &board, int row, int col, char c)
    {
        for (int k = 0; k < 9; k++)
        {
            if (board[row][k] == c)
                return false; // this checks the whole row!
            if (board[k][col] == c)
                return false; // this checks the while col!
            // this is important, checking the sub matrix! it has a formula
            if (board[3 * (row / 3) + (k / 3)][3 * (col / 3) + (k % 3)] == c)
                return false;
        }
        return true;
    }
    bool solve(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    for (char c = '1'; c <= '9'; c++)
                    {
                        if (isvalid(board, i, j, c))
                        {
                            board[i][j] = c; // here we inserted the character at the place of '.'
                            if (solve(board) == true)
                            {
                                return true;
                            }
                            else
                            {
                                board[i][j] = '.';
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

public:
    sudoku_cracker(const vector<vector<char>> &initialBoard)
    {
        board = initialBoard;
    }

    bool solveSudoku(vector<vector<char>> &board)
    {
        return solve(board);
    }

    void printBoard()
    {
        for (auto &row : board)
        {
            for (auto &cell : row)
                cout << cell << " ";
            cout << endl;
        }
    }
};

void genRandomSudoku(vector<vector<char>> &board)
{
    // Step 1: Create an empty board
    board = vector<vector<char>>(9, vector<char>(9, '.'));

    // Step 2: Fill diagonal 3x3 boxes to reduce complexity
    //here we are using lamda function-> [capture_list](parameter_list) -> return_type{...... }; -> l
    auto fillBox = [&](int row, int col)
    {
        vector<char> nums = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        random_shuffle(nums.begin(), nums.end());
        int idx = 0;
        for (int i = row; i < row + 3; ++i)
        {
            for (int j = col; j < col + 3; ++j)
            {
                board[i][j] = nums[idx++];
            }
        }
    };

    fillBox(0, 0);//0'st subgrid(3X3)
    fillBox(3, 3);//4'th subgrid(3X3)
    fillBox(6, 6);//8'th subgrid(3X3)

    // Step 3: Solve the board completely using sudoku_cracker logic
    sudoku_cracker filler(board);//here this filler is and object of the sudoku_cracker class
    filler.solveSudoku(board); // Now board is fully solved

    // Step 4: Remove random 40-50 cells to create the puzzle
    int cells_to_remove = 50;//as removing 50+ element form the total of 81 elements from solved matrix of (9X9) makes it harder! 
    while (cells_to_remove > 0)
    {
        int i = rand() % 9;
        int j = rand() % 9;
        if (board[i][j] != '.')
        {
            board[i][j] = '.';
            cells_to_remove--;
        }
    }
}

int main()
{
    srand(time(0)); // Seed the random number generator FIRST, if we want that rand() generates random values then we need to seed it first.

    vector<vector<char>> board;
    genRandomSudoku(board); // board is now filled with a Sudoku puzzle

    sudoku_cracker prime_solver(board); // object created with the puzzle, it is the object of class sudoku_cracker, and with object we called the parameterized constructor in the class!  

    cout << "Sudoku Puzzle:\n";
    prime_solver.printBoard();

    cout << "\nSolving...\n\n";

    if (prime_solver.solveSudoku(board)) // Solve the puzzle
    {
        // print the solved sudoku!
        cout << "Solved Sudoku:\n";
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Sudoku is unsolvable.\n";
    }

    return 0;
}