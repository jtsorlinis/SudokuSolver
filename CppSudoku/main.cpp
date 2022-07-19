#include <iostream>
#include <string>

using Board = uint[9][9];
size_t steps = 0;

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
  for (size_t row = 0; row < 9; row++) {
    if (row % 3 == 0 && row != 0) {
      std::cout << "------+-------+------\n";
    }
    for (size_t col = 0; col < 9; col++) {
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

bool find_empty(Board& board, size_t& r, size_t& c) {
  for (size_t row = 0; row < 9; row++) {
    for (size_t col = 0; col < 9; col++) {
      if (board[row][col] == 0) {
        r = row;
        c = col;
        return true;
      }
    }
  }
  return false;
}

bool valid(Board& board, size_t row, size_t col, uint num) {
  // check column
  for (size_t y = 0; y < 9; y++) {
    if (board[y][col] == num) {
      return false;
    }
  }

  // check row
  for (size_t x = 0; x < 9; x++) {
    if (board[row][x] == num) {
      return false;
    }
  }

  // check box
  size_t box_y = row / 3 * 3;
  size_t box_x = col / 3 * 3;
  for (size_t y = box_y; y < box_y + 3; y++) {
    for (size_t x = box_x; x < box_x + 3; x++) {
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
  size_t row, col;
  bool first_empty = find_empty(board, row, col);

  if (!first_empty) {
    return true;
  }

  for (size_t i = 1; i <= 9; i++) {
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

int main() {
  solve(board);
  PrintBoard(board);
  std::cout << "Solved in " << steps << " steps\n";
}
