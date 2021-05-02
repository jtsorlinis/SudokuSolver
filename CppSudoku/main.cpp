#include <iostream>
#include <string>

using Board = int[9][9];
int steps = 0;

Board board = {
    {0, 0, 0, 7, 0, 0, 0, 0, 0},  //
    {1, 0, 0, 0, 0, 0, 0, 0, 0},  //
    {0, 0, 0, 4, 3, 0, 2, 0, 0},  //
    {0, 0, 0, 0, 0, 0, 0, 0, 6},  //
    {0, 0, 0, 5, 0, 9, 0, 0, 0},  //
    {0, 0, 0, 0, 0, 0, 4, 1, 8},  //
    {0, 0, 0, 0, 8, 1, 0, 0, 0},  //
    {0, 0, 2, 0, 0, 0, 0, 5, 0},  //
    {0, 4, 0, 0, 0, 0, 3, 0, 0},  //
};

void PrintBoard(Board& board) {
  std::cout << "\n";
  for (int row = 0; row < 9; row++) {
    if (row % 3 == 0 && row != 0) {
      std::cout << "---------------------\n";
    }
    for (int col = 0; col < 9; col++) {
      if (col % 3 == 0 && col != 0) {
        std::cout << "| ";
      }
      std::cout << (board[row][col] == 0 ? " "
                                         : std::to_string(board[row][col]))
                << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

bool find_empty(Board& board, int& r, int& c) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == 0) {
        r = row;
        c = col;
        return true;
      }
    }
  }
  return false;
}

bool valid(Board& board, int row, int col, int num) {
  // check column
  for (int y = 0; y < 9; y++) {
    if (board[y][col] == num) {
      return false;
    }
  }

  // check row
  for (int x = 0; x < 9; x++) {
    if (board[row][x] == num) {
      return false;
    }
  }

  // check box
  int box_y = row / 3 * 3;
  int box_x = col / 3 * 3;
  for (int y = box_y; y < box_y + 3; y++) {
    for (int x = box_x; x < box_x + 3; x++) {
      if (board[y][x] == num) {
        return false;
      }
    }
  }

  return true;
}

bool solve(Board& board) {
  steps++;
  if (steps % 100000 == 0) {
    PrintBoard(board);
    std::cout << "Combinations tried: " << steps << "\n";
  }
  int row, col;
  bool first_empty = find_empty(board, row, col);

  if (!first_empty) {
    return true;
  }

  for (int i = 1; i <= 9; i++) {
    if (valid(board, row, col, i)) {
      board[row][col] = i;

      if (solve(board)) {
        return true;
      }

      board[row][col] = 0;
    }
  }
  return false;
}

int main(int, char**) {
  solve(board);
  PrintBoard(board);
  std::cout << "Solved in " << steps << " steps\n";
}
